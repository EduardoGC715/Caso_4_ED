# pragma once
# include <string>
# include <iostream>
# include <unordered_map>
# include "State.h"
# include "RandOption.h"
# include "../ADT/List.h"
# include "../Map/Map.h"

using namespace std;

typedef Tree_Node<Chamber> ChamberNode;
typedef Stack<RandOption> PathOption;
typedef unordered_map<int, ChamberNode*> ChamberHash;

class iStrategy {
    protected:
        State state;

        List<Room>* currentRoom;
        List<RandOption>* roomOptions;

        ChamberNode* tunnelEntrance;
        ChamberNode* currentChamber;
        List<RandOption>* tunnelOptions;

        ChamberHash* clearedChambers;

        virtual int getRoomQuota() = 0;
        virtual bool isDepthLimit() = 0; // Para regular profundidad explorada

        int getDepthQuota() {
            ChamberNode* tunnel = currentRoom->top()->get_tunnel()->get_entrance();
            int tunnelHeight = tunnel->get_height();
            int halfHeight = (tunnelHeight/2);
            return random(0,1);
        }

    public:
        string name;

        virtual iStrategy* clone() = 0;
        virtual void mineChamber() = 0;
        

        void init(Map* pMap) {
            state = SEARCH;
            currentRoom = new List<Room>;
            roomOptions = new List<RandOption>;
            currentChamber = nullptr;
            tunnelOptions = new List<RandOption>;
            clearedChambers = new ChamberHash;

            currentRoom->push(pMap->get_main_room());
            roomOptions->push(new RandOption(4));
        }

        State getState() {
            return state;
        }

        void searchTunnel() { // Action for State = SEARCH
            if (currentRoom->isEmpty()) {
                printf("Has finished the maze\n");
            } else if (! roomOptions->top()->isCleared()) {
                proceed_room();
            } else {
                retreat_door();
            }
        }

        void proceed_room() {
            Room* nextRoom = nullptr;
            RandOption* currentOptions = roomOptions->top();
            switch (currentOptions->getOption()) { // Selecciona puerta
                case 0:
                    nextRoom = currentRoom->top()->get_north();
                    break;
                case 1:
                    nextRoom = currentRoom->top()->get_south();
                    break;
                case 2:
                    nextRoom = currentRoom->top()->get_east();
                    break;
                case 3:
                    nextRoom = currentRoom->top()->get_west();
                    break;
            }
            if (nextRoom == nullptr) {
                printf("Took a break\n");
            } else if (currentRoom->find(nextRoom) != NOT_FOUND) {
                printf("Considers returning\n");
            } else {
                currentRoom->push(nextRoom);
                roomOptions->push(new RandOption(4));
                int roomID = nextRoom->get_ID();
                if (decide_tunnel(nextRoom)) {
                    printf("Entered room #%d and found a tunnel\n", roomID);
                    state = UNDERGROUND;
                    currentChamber = tunnelEntrance;
                    tunnelOptions->push(new RandOption(2));
                } else {
                    printf("Entered room #%d\n", roomID);
                }
            }
        }

        void retreat_door() {
            delete roomOptions->pop();
            currentRoom->pop();
            Room* nextRoom = currentRoom->top();
            if (nextRoom != nullptr) {
                printf("Returned to room #%d\n", nextRoom->get_ID());
            } else {
                printf("Cleared maze\n");
            }
        }

        bool decide_tunnel(Room* pRoom) {
            if (currentRoom->getSize() >= getRoomQuota())
            {// Si cumple cuota de profundidad explorada
                if (pRoom->get_tunnel() != nullptr)
                {// Si hay un tunel no descartado, lo visita
                    tunnelEntrance = pRoom->get_tunnel()->get_entrance();
                    int tunnelID = tunnelEntrance->get_data()->get_ID();
                    return !(clearedChambers->count(tunnelID));
                }
            }
            return false;
        }

        void searchChamber() { // Action for State = UNDERGROUND
            if (currentChamber == nullptr) {
                int tunnelID = tunnelEntrance->get_data()->get_ID();
                clearedChambers->emplace(tunnelID, tunnelEntrance);
                printf("Cleared tunel #%d\n", (tunnelID/100));
                state = SEARCH;
            } else if (! tunnelOptions->top()->isCleared() && !isDepthLimit()) {
                proceed_chamber();
            } else {
                retreat_chamber();
            }
        }

        void proceed_chamber() {
            int chamberID;
            ChamberNode* nextChamber = nullptr;
            RandOption* currentOptions = tunnelOptions->top();
            switch (currentOptions->getOption()) { // Selecciona camara
                case 0:
                    nextChamber = currentChamber->get_left();
                    break;
                case 1:
                    nextChamber = currentChamber->get_right();
                    break;
            }

            if (nextChamber != nullptr) {
                chamberID = nextChamber->get_data()->get_ID();
                bool isCleared = clearedChambers->count(chamberID);
                bool isTransitable = nextChamber->get_data()->is_transitable();
                if (! isCleared && isTransitable) {
                    currentChamber = nextChamber;
                    tunnelOptions->push(new RandOption(2));
                    // sleep(distance/speed)
                    if (decide_mining()) {
                        // state = MINING;
                        printf("Entered chamber #%d and started mining\n", chamberID);
                    } else {
                        printf("Entered chamber #%d\n", chamberID);
                    }
                } else { // Ignora camaras colapsadas o completadas
                    printf("Ignored chamber #%d\n", chamberID);
                }
            } else { // Descarta opcion nula
                printf("Took a break underground\n");
            }
        }

        void retreat_chamber() {
            delete tunnelOptions->pop();
            currentChamber = currentChamber->get_parent();
            if (currentChamber != nullptr) {
                // sleep(distance/speed)
                if (currentChamber->get_data()->is_transitable()) {
                    int chamberID = currentChamber->get_data()->get_ID();
                    printf("Returned to chamber #%d\n", chamberID);
                } else {
                    printf("Got trapped behind a collapsed chamber");
                    state = UNAVAILABLE;
                }
            } else {
                printf("Returned to tunnel entrance\n");
            }
        }

        bool decide_mining() {
            // TODO: Desarrollar polimorfismo segun estrategias concretas
            // Ej. Greedy aumenta frecuencia de minado segun profundidad (i.e node.height closer to 1)
            // Ej. Spiteful aumenta frecuencia segun profundidad baja (node height closer to entrance.height)
            // Ej. Cautious tiene una frecuencia consistente (i.e probabilidad con random(a,b))
            // Ej. Bold/Spelunker similar a greedy para enfatizar "mayor interes por exploracion que minar"
            return getDepthQuota();
        }

        void retrieveMineral() { // Action for State = RETRIEVE
            if (currentChamber != nullptr) {
                retreat_chamber();
            } else {
                printf("Exited tunnel #%d\n", tunnelEntrance->get_data()->get_ID());
            }
            // Random: 
            // Minero se cansa, descarta tunel y busca otro, de lo contrario continua a UNDERGROUND
        }
};
