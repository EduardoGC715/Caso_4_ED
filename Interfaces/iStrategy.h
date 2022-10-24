# pragma once
# include <string>
# include <iostream>
# include <unordered_map>
# include "State.h"
# include "PlayerScore.h"
# include "RandOption.h"
# include "../utils/ThreadUtils.h"
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

        bool explore_again() { // Para regular probabilidad de repetir tunel
            return random(0,2); // Flat 66.67% chance of repeat
        }

        void travel_delay() {
            double distance = currentChamber->get_data()->get_distance();
            double seconds = distance / double(*speed);
            // printf("\nSpan %f\n", seconds); // Showcase print
            sleep(seconds);
        }

    public:
        string name;
        string message;
        const int* maxLoad;
        int* load;
        int* speed;

        virtual iStrategy* clone() = 0;
        virtual void mineChamber() = 0;
        

        void init(int* pSpeed, int* pLoad, const int* pMaxLoad, Map* pMap, PlayerScore* pScore) {
            state = SEARCH;
            score = pScore;
            speed = pSpeed;
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
                message = ("Has finished the maze");
                state = DONE;
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
                message = ("Took a break");
            } else if (currentRoom->find(nextRoom) != NOT_FOUND) {
                message = ("Considers returning");
            } else {
                currentRoom->push(nextRoom);
                roomOptions->push(new RandOption(4));
                int roomID = nextRoom->get_ID();
                if (decide_tunnel(nextRoom)) {
                    message = ("Entered room #" + to_string(roomID) + " and found a tunnel");
                    enter_tunnel();
                } else {
                    message = ("Entered room #" + to_string(roomID));
                }
            }
            sleep(1);
        }

        void retreat_door() {
            delete roomOptions->pop();
            currentRoom->pop();
            Room* nextRoom = currentRoom->top();
            if (nextRoom != nullptr) {
                message = ("Returned to room #" + to_string(nextRoom->get_ID()));
            } else {
                message = ("Cleared maze");
            }
            sleep(1);
        }

        void enter_tunnel() {
            state = UNDERGROUND;
            currentChamber = tunnelEntrance;
            tunnelOptions->push(new RandOption(2));
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

        void discard_tunnel() {
            add_to_score();
            int tunnelID = tunnelEntrance->get_data()->get_ID();
            clearedChambers->emplace(tunnelID, tunnelEntrance);
            message += ("Cleared tunel #" + to_string(tunnelID/100));
            state = SEARCH;
        }

        void discard_chamber() {
            int tunnelID = currentChamber->get_data()->get_ID();
            clearedChambers->emplace(tunnelID, currentChamber);
        }

        void searchChamber() { // Action for State = UNDERGROUND
            if (currentChamber == nullptr) {
                discard_tunnel();
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
            }// Nota: Posible mejor a TreeNode -> getChild(Direction);

            if (nextChamber != nullptr) {
                chamberID = nextChamber->get_data()->get_ID();
                bool isCleared = clearedChambers->count(chamberID);
                bool isTransitable = nextChamber->get_data()->is_transitable();
                if (! isCleared && isTransitable) {
                    currentChamber = nextChamber;
                    tunnelOptions->push(new RandOption(2));
                    travel_delay(); // TODO: Activar delay
                    if (decide_mining()) {
                        state = MINING;
                        message = ("Entered chamber #" + to_string(chamberID) + " and started mining");
                    } else {
                        message = ("Entered chamber #" + to_string(chamberID));
                    }
                } else { // Ignora camaras colapsadas o completadas
                    message = ("Ignored chamber #" + to_string(chamberID));
                }
            } else { // Descarta opcion nula
                message = ("Took a break underground");
            }
        }

        void retreat_chamber() {
            delete tunnelOptions->pop();
            travel_delay(); // TODO: Activar delay
            currentChamber = currentChamber->get_parent();
            if (currentChamber != nullptr) {
                if (currentChamber->get_data()->is_transitable()) {
                    int chamberID = currentChamber->get_data()->get_ID();
                    message = ("Returned to chamber #" + to_string(chamberID));
                } else {
                    message = ("Got trapped behind a collapsed chamber");
                    state = UNAVAILABLE;
                }
            } else {
                message = ("Returned to tunnel entrance");
                sleep(1);
            }
        }

        void retrieveMineral() { // Action for State = RETRIEVE
            if (currentChamber != nullptr) {
                retreat_chamber();
            } else {
                int chamberID = tunnelEntrance->get_data()->get_ID();
                message = ("Retrieved minerals from tunnel #" + to_string(chamberID/100));
                state = SCORE;
                sleep(1);
            }
        }

        void add_to_score() {
            message = ""; // Clear buffer
            if (*load > 0) { // Add score message if possible
                message += ("Scored " + to_string(*load) + " points! - ");
                score->add(*load);
                *load = 0;
            }
        }
        
        void score_minerals() {
            if (explore_again()) {
                enter_tunnel();
                add_to_score();
                message += ("Explores tunnel again");
            } else {
                discard_tunnel(); // add_to_score call inside
            }
            sleep(1);
        }
       
};
