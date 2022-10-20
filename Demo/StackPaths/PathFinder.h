# pragma once
# include <iostream>
# include "../../ADT/List.h"
# include "../../ADT/Tree.h"
# include "Door.h"

using namespace std;

template<typename T>
void printList(List<T>* pList) {
    cout << "[";
    for (int index = pList->getSize()-1; index >= 0; --index) {
        Door* data = pList->get(index)->data;
        cout << data->getID();
        if (index != 0) {
            cout << ", ";
        }
    }
    cout << "]";
}

void printIntList(List<int>* pList) {
    cout << "[";
    for (int index = pList->getSize()-1; index >= 0; --index) {
        int* data = pList->get(index);
        cout << *data;
        if (index != 0) {
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

void pathFindingV1(Tree<Door>* pDoorMap) {
    List<TreeNode<Door>>* currentList = new List<TreeNode<Door>>;
    Stack<TreeNode<Door>>* currentPath = currentList;
    List<TreeNode<Door>>* clearedOptions = new List<TreeNode<Door>>;

    currentPath->push(pDoorMap->getRoot()); // Push del root path

    while (clearedOptions->getSize() != pDoorMap->getSize()) {
        cout << "Current Path: "; printList(currentList); cout << endl;
        cout << "Cleared Paths: "; printList(clearedOptions); cout << endl;

        // Obtiene children list de stack's top
        List<TreeNode<Door>>* pathList = currentPath->top()->children;
        cout << "\nOptions: "; printList(pathList); cout << endl;

        // Descarta opciones ya revisadas
        pathList = findPending(pathList, clearedOptions);
        bool isCleared = pathList->isEmpty();
        cout << "Is Cleared: " << isCleared << endl;

        if (isCleared) 
        {// Si no hay opciones o ya se descartaron todas
            TreeNode<Door>* discardedPath = currentPath->pop(); // Pop para regresar al path previo
            clearedOptions->add( discardedPath );               // Dicho pop queda enlistado como revisado
            cout << "Cleared Door #" << discardedPath->data->getID() << endl;
        } else {
            int choice = rand() % pathList->getSize();
            TreeNode<Door>* pathChoice = pathList->get(choice); // Selecciona una opcion disponible
            currentPath->push(pathChoice);                      // Push para avanzar al path seleccionado
            cout << "Entered Door #" << pathChoice->data->getID() << endl;
        }
        cout << "------------------------------------------------" << endl;
    }
}

void pathFindingV2(Tree<Door>* pDoorMap) {
    typedef TreeNode<Door> Path;
    List<Path>* currentList = new List<Path>;
    List<int>* optionsList = new List<int>;
    Stack<Path>* currentPath = currentList;
    Stack<int>* pendingPaths = optionsList;

    List<Path>* pathList;
    int* optionsLeft;

    currentPath->push(pDoorMap->getRoot()); // Push del root path

    // Prepara root options
    pathList = currentPath->top()->children;
    optionsLeft = new int(pathList->getSize());
    pendingPaths->push( optionsLeft );

    while (! optionsList->isEmpty()) {
        cout << "Current Path: "; printList(currentList); cout << endl;
        cout << "Pending Paths: "; printIntList(optionsList); cout << endl;

        // Revisa opciones disponibles
        optionsLeft = pendingPaths->top();
        bool isCleared = (*optionsLeft < 1);
        cout << "Is Cleared: " << isCleared << endl;

        if (isCleared) {
            Path* discarded = currentPath->pop();
            pendingPaths->pop();
            cout << "Cleared Door #" << discarded->data->getID() << endl;
            // Actualiza pathList para siguiente iteracion
            if (! currentPath->isEmpty()) {
                pathList = currentPath->top()->children;
            }
        } else {
            Path* choice = pathList->get(--(*optionsLeft));
            currentPath->push(choice);
            pathList = choice->children;
            optionsLeft = new int(pathList->getSize());
            pendingPaths->push(optionsLeft);
            cout << "Entered Door #" << choice->data->getID() << endl;
        }
        cout << "------------------------------------------------" << endl;
    }
}

// KeyPar<Path, PathOptions>
// = [0:3, 1:2, 4:2, 5:0, 2:3, 6:0, 7:0, 8:0, 3:2, 9:0, 10:0]

// currentPath: [ 0
// pendingPaths: [
// pathList: [

// optionsLeft: -
// isCleared: -

/* Map:
0:[
    1:[      
        4:[
            11:[],

            12:[]
        ],

        5:[],
     ],      

    2:[
        6:[],

        7:[],

        8:[],
     ],

    3:[
        9:[],

        10:[],
     ],
], */