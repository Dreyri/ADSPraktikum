#include "Ringpuffer.h"

Ringpuffer::Ringpuffer()
    : mAnchor(nullptr)
{

}

Ringpuffer::~Ringpuffer()
{

}

void Ringpuffer::addNode(const std::string& description, const std::string& data)
{
    RingNode* newNode = new RingNode(description, data);

    //if not nullptr then increase all nodes
    if(mAnchor != nullptr)
    {
        //increase age of all nodes by 1

        RingNode* curNode = mAnchor;

        do
        {
            curNode->setAge(curNode->getAge() + 1);
            curNode = curNode->getNext();
        }
        while(curNode != mAnchor);
        //now that all have aged see how old the one after the anchor is
        RingNode* oldest = mAnchor->getNext();
        if(oldest->getAge() > MAX_AGE)
        {
            //you're too old, get out
            RingNode* oldestNext = oldest->getNext();
            delete oldest;

            //insert our newnode and set it as the new anchor
            newNode->setNext(oldestNext);
            mAnchor->setNext(newNode);
            mAnchor = newNode;
        }
        else //not too old so simply add a node and move anchor
        {
            RingNode* nextNode = mAnchor->getNext();
            mAnchor->setNext(newNode);
            newNode->setNext(nextNode);
            mAnchor = newNode;
        }
    }
    else //if nullptr then we don't have any nodes yet, let's add one
    {
        //point at yourself I guess
        newNode->setNext(newNode);
        mAnchor = newNode;
    }
}

RingNode* Ringpuffer::search(const std::string& descr) const
{
    RingNode* curNode = this->mAnchor;

    do
    {
        if(curNode->getDescription().compare(descr) == 0)
            return curNode;
        curNode = curNode->getNext();
    }
    while(curNode != mAnchor);

    return nullptr;
}


void Ringpuffer::print(std::ostream& ostream, RingNode* node) const
{
    if(node != nullptr)
        ostream << "OldAge: " << node->getAge() << ", Descr: " << node->getDescription() << ", Data: " << node->getData() << std::endl;

    else
    {
        RingNode* curNode = mAnchor;

        do
        {
            if(curNode != nullptr)
            {
                print(ostream, curNode); //OldAge: x, Descr: y, Data: z
                ostream << "---------------------------" << std::endl;

                //increment to next node
                curNode = curNode->getNext();
            }
        }
        while(curNode != mAnchor); //do until back at start
    }

}
