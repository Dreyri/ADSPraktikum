#include "Ringpuffer.h"

Ringpuffer::Ringpuffer()
{

}

Ringpuffer::~Ringpuffer()
{

}

void Ringpuffer::addNode(const std::string& description, const std::string& data)
{
    //increase age of all nodes by 1

    RingNode* curNode = mAnchor;

    do
    {
        curNode->setAge(curNode->getAge() + 1);
        curNode = curNode->getNext();
    }
    while(curNode != mAnchor);

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
            print(ostream, curNode); //OldAge: x, Descr: y, Data: z
            ostream << "---------------------------" << std::endl;

            //increment to next node
            curNode = curNode->getNext();
        }
        while(curNode != mAnchor); //do until back at start
    }

}
