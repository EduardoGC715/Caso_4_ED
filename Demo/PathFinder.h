# pragma once
# include <iostream>
# include "../ADT/List.h"
# include "../ADT/Tree.h"
# include "Door.h"

using namespace std;

template<typename T>
void printList(List<T>* pList) {
    cout << "[";
    for (int index = 0; index < pList->getSize();) {
        Door* data = pList->get(index++)->data;
        cout << data->getID();
        if (index != pList->getSize()) {
            cout << ", ";
        }
    }
    cout << "]";
}

template<typename T>
List<T>* findPending(List<T>* pPathList, List<T>* pClearedList) {
    List<T>* pendingList = new List<T>;
    for (int index = 0; index < pPathList->getSize(); ++index) {
        T* path = pPathList->get(index);
        if (pClearedList->find(path) == NOT_FOUND) {
            pendingList->add(path);
        }
    }
    return pendingList;
}

void pathFinding(Tree<Door>* pDoorMap) {
    List<TreeNode<Door>>* currentList = new List<TreeNode<Door>>;
    Stack<TreeNode<Door>>* currentPath = currentList;
    List<TreeNode<Door>>* clearedOptions = new List<TreeNode<Door>>;

    currentPath->push(pDoorMap->getRoot());

    while (clearedOptions->getSize() != pDoorMap->getSize()) {
        cout << "Current Path: "; printList(currentList); cout << endl;
        cout << "Cleared Paths: "; printList(clearedOptions); cout << endl;

        List<TreeNode<Door>>* pathList = currentPath->top()->children;
        cout << "\nOptions: "; printList(pathList); cout << endl;
        
        pathList = findPending(pathList, clearedOptions);
        bool isCleared = pathList->isEmpty();
        cout << "Is Cleared: " << isCleared << endl;

        if (isCleared) {
            TreeNode<Door>* discardedPath = currentPath->pop();
            clearedOptions->add( discardedPath );
            cout << "Cleared Door #" << discardedPath->data->getID() << endl;
        } else {
            int choice = rand() % pathList->getSize();
            TreeNode<Door>* pathChoice = pathList->get(choice);
            currentPath->push(pathChoice);
            cout << "Entered Door #" << pathChoice->data->getID() << endl;
        }
        cout << "------------------------------------------------" << endl;
    }

}

// [0, 3, 6, 10, 13, 15] current

// [0, 3, 4, 6, 7, 10, 11, 12, 13, 14, 15, 16, 17]

// Cuando currentPath no tiene mas opciones disponibles
// i.e children == empty list, entonces se agrega dicho
// nodo/posicion a cleared options y se devuelve (pop)
// a la posicion anterior de ser necesario. Para revisar
// que opciones tiene de una puerta a otra, debe hallar
// por lo menos un child node que no este en cleared