# include <iostream>
# include <ctime>

# include "../ADT/List.h"
# include "../ADT/Tree.h"
# include "Door.h"

using namespace std;

void printNodes(TreeNode<Door>* pNode) {
    List<TreeNode<Door>>* list = pNode->children;
    Door* data = pNode->data;
    cout << data->getID() << "(" << data->hasTunnel() << "):[";
    for(int i = 0; i < list->getSize(); i++) {
        printNodes(list->get(i));
    }
    cout << "], ";
}

void printTree(Tree<Door>* pTree) {
    printNodes(pTree->getRoot());
}

Tree<Door>* generateMap() {
    srand(time(NULL));

    Queue<TreeNode<Door>>* nodeQueue = new List<TreeNode<Door>>;
    Tree<Door>* tree = new Tree<Door>;
    TreeNode<Door>* node;

    Door* newDoor = new Door(0, false);
    tree->add(newDoor, nullptr);

    int tChance, dChance, index, total;
    total = 12;
    dChance = rand() % 3 + 2;

    for (index=1; dChance > 0; dChance--) {
        tChance = rand() % 2;
        newDoor = new Door(index++, tChance);
        node = tree->add(newDoor, tree->getRoot());
        nodeQueue->enqueue(node);
    }

    while (true) {
        dChance = rand() % 2 + 2;
        node = nodeQueue->dequeue();
        for (; dChance > 0; --dChance) {
            tChance = rand() % 2;
            newDoor = new Door(index++, tChance);
            nodeQueue->enqueue(tree->add(newDoor, node));
            if (index > total) {
                return tree;
            }
        }
    }
}


int main() {
    Tree<Door>* map = generateMap();
    printTree(map);
    return 0;
}