# pragma once
# include <iostream>
# include <chrono>
# include "../../ADT/List.h"

using namespace std;

class IntConsumer {
    public:
        bool isRunning = false;

        void start() {
            isRunning = true;
        }

        void stop() {
            isRunning = false;
        }

        void operator() (Queue<int>* pQueue) {
            printf("Dequeue Thread Start!\n");
            while (isRunning) {
                while (pQueue->isEmpty()) {
                    this_thread::sleep_for(chrono::seconds(1));
                }
                
                int* item = pQueue->dequeue_safe();
                printf("- Dequeued: %d\n", *item);

                this_thread::sleep_for(chrono::seconds(2));
            }
            printf("Finished Dequeue\n");
        }

};