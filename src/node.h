#ifndef NODE_H
#define NODE_H

#include "ring_buffer.h"

#include <vector>

// Draft of the Node class

template<typename T, unsigned N>
class Node
{
public:
private:
    T buffer[N];
};

#endif // NODE_H
