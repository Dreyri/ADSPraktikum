#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include "treenode.h"

#include <iostream>
#include <vector>
#include <functional>

class Tree
{
private:
    TreeNode* mAnchor;
    int mNextId;

public:
    Tree();
    Tree(const Tree& t);
    ~Tree();

    const Tree& operator=(Tree t);

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
    void traverse(std::function<void(const TreeNode*)> func) const;
    /**
     * @brief pretraverse executes func before going to subnodes, good for copying trees
     * @param func
     */
    void pretraverse(std::function<void(const TreeNode*)> func) const;
    void printTree(std::ostream& stream = std::cout) const;
    static void printNode(TreeNode* node, std::ostream& stream = std::cout);

    friend void swap(Tree& t1, Tree& t2);
private:
    static TreeNode* insertNode(TreeNode* node, TreeNode* newNode);
};

#endif
