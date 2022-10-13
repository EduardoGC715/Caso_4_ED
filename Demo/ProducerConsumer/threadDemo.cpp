# include <thread>
# include "../../ADT/List.h"
# include "ProducerThread.h"
# include "ConsumerThread.h"

# define QUANTITY 8
# define DEMO_TIME 10

using namespace std;

int main() {
    Queue<int>* numQueue = new List<int>;
    IntProducer producerObj;
    IntConsumer consumerObj;

    // Thread Object prep work
    producerObj.start();
    consumerObj.start();
    
    // Thread Start
    thread producerThread(ref(producerObj), numQueue);
    thread consumerThread(ref(consumerObj), numQueue);

    // Timed demo sleep
    this_thread::sleep_for(chrono::seconds(DEMO_TIME));
    producerObj.stop();
    consumerObj.stop();
    printf("\nFinish Test!\n");

    // Waiting for threads to finish
    producerThread.join();
    consumerThread.join();
}

/* Referencias consultadas
    https://www.geeksforgeeks.org/multithreading-in-cpp/
    https://cplusplus.com/reference/thread/this_thread/
    https://cplusplus.com/reference/thread/thread/
    https://thispointer.com//c11-multithreading-part-3-carefully-pass-arguments-to-threads/

    Esta ultima es particularme importante, pues no utilizar std::ref() en el objeto
    al construir el Thread implica que cambios fuera de dicho Thread no son registrados.
    En este caso, los thread objects se diseñaron para detenerse cuando isRunning == false.
    Si ocuparamos detener nuestro thread o ponerlo en pausa, los cambios no se registrarian
    en el objeto incluso utilizando punteros. Por ejemplo, las 26 y 27 funcionaban pero los
    threads no se detenian antes de agregar ref(thread_obj) a los parametros.
*/