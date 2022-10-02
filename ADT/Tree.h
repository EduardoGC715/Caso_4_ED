# include "TreeNode.h"

template<typename T>
class Tree {
    private:
        TreeNode<T>* root;
        int size;
    
    public:
        Tree() {
            size = 0;
            root = NULL;
        }

        int getSize() const {
            return size;
        }

        bool isEmpty() const {
            return !(size);
        }

        TreeNode<T>* getRoot() {
            return root;
        }

        TreeNode<T>* add(T* pData, TreeNode<T>* pNode) {
            TreeNode<T>* newNode = new TreeNode<T>(pData);
            if (this->isEmpty()) {
                root = newNode;
            } else if (pNode != NULL) {
                pNode->children->add(newNode);
                newNode->parent = pNode;
            } else {
                root->children->add(newNode);
                newNode->parent = pNode;
            }
            ++size;
            return newNode;
        }
};