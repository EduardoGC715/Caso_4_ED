# pragma once
# include <iostream>
# include <ctime>
# include "../../ADT/List.h"

using namespace std;

class IntProducer {
    public:
        bool isRunning = false;

        void start() {
            isRunning = true;
        }

        void stop() {
            isRunning = false;
        }

        void operator() (Queue<int>* pQueue) {
            srand(time(NULL));
            printf("Enqueue Thread Start!\n");

            while (isRunning) {
                int* item = new int(rand()%10);
                pQueue->enqueue_safe(item);
                printf("+ Enqueued: %d\n", *item);

                this_thread::sleep_for(chrono::seconds(1));
            }
            printf("Finished Enqueue\n");
        }
};