# include <iostream>
# include <thread>

using namespace std;

int input() {
    int result;
    cout << "Input: ";
    cin >> result;
    return result;
}

struct timedInput {
    bool isRunning = true;

    void operator() () {
        thread* inputThread = nullptr;
        while (isRunning) {
            if (inputThread == nullptr) {
                inputThread = new thread(input);
                inputThread->detach();
            } else {
                this_thread::yield();
            }
        }
        cout << "\nMain Thread finished";
    }

    void stop() {
        isRunning = false;
    }
};
