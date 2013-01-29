#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <list>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <iostream>

// TODO: Don't use pointers... somehow... maybe iterators?

template<typename T, unsigned N>
class SharedBuffer
{

};

// Specialization for N=1
template<typename T>
class SharedBuffer<T,1>
{
public:
    SharedBuffer( ) : buffer(), claimed(false) { }

    T* claim_buffer( )
    {
        if( claimed )
            throw std::runtime_error( "Attempt to claim claimed buffer." );
        claimed = true;
        return &buffer;
    }

    void release_buffer( T* buf )
    {
        assert( buf == &buffer );
        claimed = false;
    }

private:
    T buffer;
    bool claimed;
};

// Specialization for N=0 => Dynamic Size
template<typename T>
class SharedBuffer<T,0>
{
public:
    SharedBuffer( size_t pre_alloc=1 ) : available_buffers(), reserved_buffers()
    {
        for( size_t i=0; i<pre_alloc; i++ )
            available_buffers.push_back( new T() );
    }

    ~SharedBuffer( )
    {
        assert( reserved_buffers.empty() );
        typename std::list<T*>::iterator it = available_buffers.begin( );
        while( it != available_buffers.end() )
        {
            delete *(it++);
        }
    }

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
#ifndef NDEBUG
        size_t s = reserved_buffers.size( );
#endif
        reserved_buffers.remove( buf );
#ifndef NDEBUG
        if( s <= reserved_buffers.size() )
            throw std::runtime_error( "Attempt to release element that does not belong to the buffer." );
#endif
        available_buffers.push_back( buf );
    }

private:
    std::list<T*> available_buffers;
    std::list<T*> reserved_buffers;
};

#include "instance_verboser.h"

void testSharedBuffer( )
{
    SharedBuffer<instance_verboser,0> sb;

    instance_verboser *a, *b, *c;

    a = sb.claim_buffer( );
    b = sb.claim_buffer( );
    c = sb.claim_buffer( );

    sb.release_buffer( a );
    sb.release_buffer( b );
    sb.release_buffer( c );

}

#endif // SHAREDBUFFER_H
