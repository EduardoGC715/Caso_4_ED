# pragma once
# include "Node.h"
# include "Stack.h"
# include "Queue.h"

# define NOT_FOUND -1

template<typename T>
class List: public Stack<T>, public Queue<T> {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

        Node<T>* getNode(int pIndex) {
            if ( pIndex < size ) {
                Node<T>* current = head;
                while (pIndex > 0) {    // Link hops until pIndex runs out
                    current = current->next;
                    pIndex--;
                }
                return current;
            }
            return NULL;
        }

    public:
        List() {
            size = 0;
            head = NULL;
            tail = NULL;
        }

        int getSize() const {
            return size;
        }

        bool isEmpty() const {
            return size == 0;
        }

        void clear() {
            while (! isEmpty()) {
                remove(0);
            }
        }

        const T* getFirst() const {
            return head->data;
        }

        const T* getLast() const {
            return tail->data;
        }

        T* getFirst() {
            return head->data;
        }

        T* getLast() {
            return tail->data;
        }

        void add(T* pData) {
            Node<T>* newTail = new Node<T>(pData);
            if (! isEmpty()) {  // Tail Insert for !empty list
                newTail->prev = tail;
                tail->next = newTail;
                tail = newTail;
            } else {            // Tail Insert for empty list
                head = tail = newTail;
            }
            size++;
        }

        void insert(T* pData, int pIndex) {
            if (pIndex < size && head != NULL){
                Node<T>* newNode = new Node(pData);    
                if (pIndex > 0) {   // Inserts at [1, N-1]
                    Node<T>* prior = getNode(pIndex - 1);
                    Node<T>* after = prior->next;
                    prior->next = after->prev = newNode;
                    newNode->prev = prior;
                    newNode->next = after;
                } else {            // Head Insert if (0 || Negative OutOfBounds)
                    newNode->next = head;
                    head->prev = newNode;
                    head = newNode;
                }
                size++;
            } else {    // Tail Insert if (Empty || Positive OutOfBounds)
                add(pData);
            }
        }

        T* get(int pIndex) {
            Node<T>* search = getNode(pIndex);
            if (search != NULL) {
                return search->data;
            } else {
                return NULL;
            }
        }

        int find(const T& pData) {
            int index = 0;
            Node<T>* current = head;
            while (current != NULL) {
                if (current->data == pData) {
                    return index;
                }
                current = current->next;
                index++;
            }
            return NOT_FOUND;
        }

        T* remove(int pIndex)
        {
            T* result = NULL;
            if (pIndex < size && head != NULL) {
                Node<T>* search = NULL;
                if (pIndex > 0) {   // Removes at [1, N-1]
                    search = getNode(pIndex);
                    (search->prev)->next = search->next;    // Unlink prior node
                    if (search != tail) {
                        (search->next)->prev = search->prev; // Unlink next node
                    }
                } else {            // Removes Head if (0 || Negative OutOfBounds)
                    search = head;
                    head = search->next;
                    if (head != NULL) {
                        head->prev = NULL;   // Unlink newHead's *prev
                    }
                }
                result = search->data;
                delete search;
                size--;
            }
            return result;
        }

        // Stack inheritance
        T* top() {
            return getFirst();
        }

        void push(T* pData) {
            insert(pData, 0);
        }

        T* pop() {
            return remove(0);
        }

        // Queue inheritance
        T* getFront() {
            return getFirst();
        }

        void enqueue(T* pData) {
            add(pData);
        }

        T* dequeue() {
            return remove(0);
        }
};