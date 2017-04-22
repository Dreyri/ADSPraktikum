#include "treenode.h"

TreeNode::TreeNode(int id, const std::string& name, int age, double income, int plz)
    : mNodeId(id), mName(name), mAge(age), mIncome(income), mPLZ(plz), mLeft(nullptr), mRight(nullptr)
{
    updatePosId();
}


const std::string& TreeNode::getName() const
{
    return mName;
}
int TreeNode::getAge() const
{
    return mAge;
}
double TreeNode::getIncome() const
{
    return mIncome;
}
int TreeNode::getPLZ() const
{
    return mPLZ;
}

int TreeNode::getNodePosId() const
{
    return mNodePosId;
}

int TreeNode::getNodeId() const
{
    return mNodeId;
}

void TreeNode::setName(const std::string& name)
{
    mName = name;
}

void TreeNode::setAge(int age)
{
    mAge = age;
    updatePosId();
}

void TreeNode::setIncome(double income)
{
    mIncome = income;
    updatePosId();
}

void TreeNode::setPLZ(int plz)
{
    mPLZ = plz;
    updatePosId();
}

void TreeNode::updatePosId()
{
    mNodePosId = mAge + mPLZ + static_cast<int>(mIncome);
}

void TreeNode::printData() const
{

}
