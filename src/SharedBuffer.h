#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <list>
#include <cstring>

// TODO: Don't use pointers... somehow... maybe iterators?

template<typename T>
class SharedBuffer
{
public:
    SharedBuffer( unsigned int pre_alloc=1 ) : available_buffers(pre_alloc), reserved_buffers() { }

    T* claim_buffer( )
    {
        if( available_buffers.empty() )
        {
            reserved_buffers.push_back( new T() );
        }
        else
        {
            reserved_buffers.push_back( available_buffers.back() );
            available_buffers.pop_back( );
        }

        return reserved_buffers.back( );
    }

    void release_buffer( T* buf )
    {
        available_buffers.push_back( buf );
        reserved_buffers.remove( buf );
    }

private:

    std::list<T*> available_buffers;
    std::list<T*> reserved_buffers;

};

#include "instance_verboser.h"

void testSharedBuffer( )
{
    SharedBuffer<instance_verboser> sb;

    instance_verboser *a, *b, *c;

    a = sb.claim_buffer( );
    b = sb.claim_buffer( );
    c = sb.claim_buffer( );

}

#endif // SHAREDBUFFER_H
