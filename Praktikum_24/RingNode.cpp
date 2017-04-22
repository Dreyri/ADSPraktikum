#include "RingNode.h"

RingNode::RingNode(const std::string& description, const std::string& data, RingNode* next)
    : mOldAge(0), mDescription(description), mSymbolicData(data), mNext(next)
{

}

RingNode::~RingNode()
{
    //only responsible for yourself, don't change other nodes
}

int RingNode::getAge() const
{
    return mOldAge;
}

void RingNode::setAge(int age)
{
    mOldAge = age;
}

const std::string& RingNode::getDescription() const
{
    return mDescription;
}

void RingNode::setDescription(const std::string& desc)
{
    mDescription = desc;
}

const Tree* RingNode::getData() const
{
    return mTreeData;
}

void RingNode::setData(Tree* tree)
{
    delete mTreeData;
    mTreeData = tree;
}

RingNode* RingNode::getNext()
{
    return mNext;
}

void RingNode::setNext(RingNode* next)
{
    mNext = next;
}
