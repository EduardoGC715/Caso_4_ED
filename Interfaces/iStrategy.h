# pragma once
# include <string>
# include <iostream>
# include "State.h"
# include "RandOption.h"
# include "../ADT/List.h"
# include "../Map/Map.h"

using namespace std;

typedef List< Tree_Node<Chamber> > TunnelPath;
typedef Stack<RandOption> PathOption;

class iStrategy {
    protected:
        State state;

        List<Room>* currentRoom;
        List<RandOption>* roomOptions;

        TunnelPath* currentChamber;
        List<RandOption>* tunnelOptions;

        virtual int getRoomQuota() = 0;

    public:
        string name;

        virtual iStrategy* clone() = 0;
        virtual void mineChamber() = 0;
        virtual void retrieveMineral() = 0;

        void init(Map* pMap) {
            state = SEARCH;
            currentRoom = new List<Room>;
            roomOptions = new List<RandOption>;
            currentChamber = new TunnelPath;
            tunnelOptions = new List<RandOption>;

            currentRoom->push(pMap->get_main_room());
            roomOptions->push(new RandOption(4));
        }

        State getState() {
            return state;
        }

        void searchTunnel() {
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
            switch (currentOptions->getOption()) {
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
                printf("Is deciding where to go\n");
            } else {
                currentRoom->push(nextRoom);
                roomOptions->push(new RandOption(4));
                int roomID = nextRoom->get_ID();
                if (decide_mining(nextRoom)) {
                    printf("Entered room #%d and found a tunnel\n", roomID);
                    // state = UNDERGROUND;
                    // Cambiar nombre de Tunnel::get_tunnel a get_entrance
                    currentChamber->push(nextRoom->get_tunnel()->get_tunnel());
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

        bool decide_mining(Room* pRoom) {
            if (currentRoom->getSize() >= getRoomQuota()) {
                return (pRoom->get_tunnel() != nullptr);
            }
            return false;
        }
        
        virtual void searchChamber() = 0;
};
