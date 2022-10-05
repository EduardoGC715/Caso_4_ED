# pragma once
# include <iostream>
# include <chrono>
# include "../ADT/List.h"

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
            cout << "Dequeue Thread Start!" << endl;
            while (isRunning) {
                while (pQueue->isEmpty()) {
                    this_thread::sleep_for(chrono::seconds(1));
                }
                
                int* item = pQueue->dequeue();
                cout << "- Dequeued: " << *item << endl;

                this_thread::sleep_for(chrono::seconds(2));
            }
            cout << "Finished Dequeue" << endl;
        }

};