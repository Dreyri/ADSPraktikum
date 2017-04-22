#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include "treenode.h"

#include <iostream>
#include <vector>

class Tree
{
private:
    TreeNode* mAnchor;
    int mNextId;

public:
    Tree();
    ~Tree();

    void insertNode(const std::string& name, int age, double income, int plz);
    bool deleteNode(int nodePosId);
    /**
     * @brief search search tree for nodes named name and store result in nodes
     * @param name name to search for
     * @param nodes array to fill with found nodes
     * @return amount of nodes found
     */
    std::vector<TreeNode*> search(const std::string& name);

    /**
     * @brief traverse traverse the tree and execute func on each node
     * starting bottom left to right and up, which makes it safe for deletion
     */
    void traverse(std::function<void(TreeNode*)> func);

    void printTree(std::ostream& stream = std::cout) const;
    static void printNode(TreeNode* node, std::ostream& stream = std::cout);
private:
    static TreeNode* insertNode(TreeNode* node, TreeNode* newNode);
};

#endif
