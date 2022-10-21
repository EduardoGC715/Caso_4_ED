# pragma once
# include <iostream>
# include "PathOptions.h"
# include "../ADT/List.h"
# include "../Map/Map.h"

typedef Tree_Node<Chamber> Path;
class iExpedition {
    public:
        void searchTunnel(List<Room>* pRoomStack, Stack<RandOption>* pOptions, Stack<Path>* pCurrentPath) {
            if (pRoomStack->isEmpty()) {
                printf("Has finished the maze\n");
            }
            Room* nextRoom = nullptr;
            Room* currentRoom = pRoomStack->top();
            RandOption* currentOptions = pOptions->top();
            if (! currentOptions->isCleared()) {
                switch (currentOptions->getOption()) {
                    case 0:
                        nextRoom = currentRoom->get_north();
                        break;
                    case 1:
                        nextRoom = currentRoom->get_south();
                        break;
                    case 2:
                        nextRoom = currentRoom->get_east();
                        break;
                    case 3:
                        nextRoom = currentRoom->get_west();
                        break;
                }
                if (nextRoom == nullptr) {
                    printf("Took a break\n");
                } else if (pRoomStack->find(nextRoom) != NOT_FOUND) {
                    printf("Is deciding where to go\n");
                } else {
                    pRoomStack->push(nextRoom);
                    pOptions->push(new RandOption(4));
                    printf("Entered room #%d\n", nextRoom->get_ID());
                }
            } else {
                delete pOptions->pop();
                pRoomStack->pop();
                nextRoom = pRoomStack->top();
                printf("Returned to room #%d\n", nextRoom->get_ID());
            }
            
        }

        
        virtual void searchChamber(List<Path>* pCurrent, List<RandOption>* pOptions) = 0;
};