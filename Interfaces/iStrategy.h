# pragma once
# include <string>
# include <iostream>
# include <unordered_map>
# include "State.h"
# include "PlayerScore.h"
# include "RandOption.h"
# include "../ADT/List.h"
# include "../Map/Map.h"

using namespace std;

typedef Tree_Node<Chamber> ChamberNode;
typedef Stack<RandOption> PathOption;
typedef unordered_map<int, ChamberNode*> ChamberHash;

class iStrategy {
    protected:
        PlayerScore* score;
        State state;
        bool isStocked;

        List<Room>* currentRoom;
        List<RandOption>* roomOptions;

        ChamberNode* tunnelEntrance;
        ChamberNode* currentChamber;
        List<RandOption>* tunnelOptions;

        ChamberHash* clearedChambers;

        virtual int getRoomQuota() = 0; // Para regular puertas exploradas
        virtual bool isDepthLimit() = 0; // Para regular profundidad explorada
        virtual bool decide_mining() = 0; // Para regular probabilidad de minado

    public:
        string name;
        const int* maxLoad;
        int* load;

        virtual iStrategy* clone() = 0;
        virtual void mineChamber() = 0;
        

        void init(int* pLoad, const int* pMaxLoad, Map* pMap, PlayerScore* pScore) {
            state = SEARCH;
            score = pScore;
            load = pLoad;
            maxLoad = pMaxLoad;

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
            int option = roomOptions->top()->getOption();
            Room* nextRoom = currentRoom->top()->get_direction(option);
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
                        // state = RETRIEVE; ++(*load);
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

        

        void retrieveMineral() { // Action for State = RETRIEVE
            if (currentChamber != nullptr) {
                retreat_chamber();
            } else {
                printf("Retrieved minerals from tunnel #%d\n", tunnelEntrance->get_data()->get_ID());
                state = SCORE;
            }
        }

        
        void score_minerals() {
            score->add(*load);
            printf("Scored %d points\n", *load);
            /* if (explore_again()) {
                strategy->enter_tunnel();
                strategy->state = UNDERGROUND;
                // printf("Enters again to mine more minerals")
            } else {
                strategy->discard_tunnel();
                strategy->state = SEARCH;
                // printf("Moves on to search other tunnels")
            } */
            *load = 0;
        }
       
};
