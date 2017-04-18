#include "RingNode.h"

const int& RingNode::getAge() const
{
    return mOldAge;
}

void RingNode::setAge(const int& age)
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

const std::string& RingNode::getData() const
{
    return mSymbolicData;
}

void RingNode::setData(const std::string& data)
{
    mSymbolicData = data;
}
