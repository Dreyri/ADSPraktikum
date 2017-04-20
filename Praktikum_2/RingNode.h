#ifndef _RING_NODE_H_
#define _RING_NODE_H_

#include <string>

class RingNode
{
    friend class Ringpuffer;
private:
    int mOldAge;
    std::string mDescription;
    std::string mSymbolicData;
    RingNode* mNext;

private:
    RingNode(const std::string& description, const std::string& data, RingNode* next = nullptr);
    ~RingNode();

    const int& getAge() const;
    void setAge(const int& age);

    const std::string& getDescription() const;
    void setDescription(const std::string& desc);

    const std::string& getData() const;
    void setData(const std::string& data);

    RingNode* getNext();
    void setNext(RingNode* next);
};

#endif
