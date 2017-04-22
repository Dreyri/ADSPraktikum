#ifndef _RING_NODE_H_
#define _RING_NODE_H_

#include <string>
#include "tree.h"

class RingNode
{
    friend class Ringpuffer;
private:
    int mOldAge;
    std::string mDescription;
    Tree mTreeData;
    RingNode* mNext;

private:
    RingNode(const std::string& description, const Tree& data, RingNode* next = nullptr);
    ~RingNode();

    int getAge() const;
    void setAge(int age);

    const std::string& getDescription() const;
    void setDescription(const std::string& desc);

    const Tree& getData() const;
    void setData(const Tree& tree);

    RingNode* getNext();
    void setNext(RingNode* next);
};

#endif
