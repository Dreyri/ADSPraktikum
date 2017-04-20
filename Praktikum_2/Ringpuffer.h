#ifndef _RINGPUFFER_H_
#define _RINGPUFFER_H_

#include "RingNode.h"
#include <iostream>

constexpr int MAX_RING_SIZE = 6;
constexpr int MAX_AGE = MAX_RING_SIZE-1;

class Ringpuffer
{
private:
    /**
     * @brief mAnchor our youngest element
     * anchor should always have age 0, the next pointer in anchor
     * should always refer to the oldest element in the list
     */
    RingNode* mAnchor;

public:
    Ringpuffer();
    ~Ringpuffer();

    void addNode(const std::string& description, const std::string& data);
    RingNode* search(const std::string& descr) const;

    void print(std::ostream& ostream = std::cout, RingNode* node = nullptr) const;


};

#endif
