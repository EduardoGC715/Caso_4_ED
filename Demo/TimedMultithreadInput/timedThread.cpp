# include "timedInput.h"

int main() {
    timedInput obj;
    thread* mainThread = nullptr;
    mainThread = new thread(ref(obj));
    this_thread::sleep_for(chrono::seconds(3));
    obj.stop();
    mainThread->join();
    return 0;
}