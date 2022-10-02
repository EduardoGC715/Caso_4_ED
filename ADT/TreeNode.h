# pragma once
# include "List.h"

template<typename T>
class TreeNode {
    public:
        T* data;
        TreeNode* parent;
        List<TreeNode>* children;

        TreeNode(T* pData)
        : data(pData), parent(NULL) {
            children = new List<TreeNode>;
        }
};