# pragma once
# include <iostream>
# include <ctime>
# include "../ADT/List.h"

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
            cout << "Enqueue Thread Start!" << endl;

            while (isRunning) {
                int* item = new int(rand()%10);
                pQueue->enqueue(item);
                cout << "+ Enqueued: " << *item << endl;

                this_thread::sleep_for(chrono::seconds(1));
            }
            cout << "Finished Enqueue" << endl;
        }
};