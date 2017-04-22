#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <string>

class TreeNode
{
    friend class Tree;
private:
    int mNodePosId;
    int mNodeId;
    std::string mName;
    int mAge;
    double mIncome;
    int mPLZ;

    TreeNode* mLeft;
    TreeNode* mRight;

private:
    TreeNode(int id, const std::string& name, int age, double income, int plz);

    const std::string& getName() const;
    int getAge() const;
    double getIncome() const;
    int getPLZ() const;
    int getNodePosId() const;
    int getNodeId() const;

    void setName(const std::string& name);
    void setAge(int age);
    void setIncome(double income);
    void setPLZ(int plz);

    void updatePosId();
    void printData() const;
};

#endif
