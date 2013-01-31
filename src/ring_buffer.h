#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstring>  // for size_t declaration

// TODO: Locking Mechanisms

template<typename T, unsigned N>
class ring_buffer
{
public:
    ring_buffer( )
    {
        pos_ = -1;
    }

    inline void write( T& item )
    {
        // TODO: lock here
        pos_ = (pos_ + 1) % N;
        buffer_[pos_] = item;
        // TODO: unlock here
    }

    T& begin_writing( )
    {
        // TODO: lock here
        pos_ = (pos_ + 1) % N;
        return buffer_[pos_];
    }

    void end_writing( )
    {
        // TODO: unlock here
    }

    inline T& get( )
    {
        // TODO: wait for lock here
        // TODO: lock here? Is there a read lock that only prevents writing?
        return buffer_[pos_];
        // TODO: unlock here?
    }

    inline T& get( int offset )
    {
        // TODO: wait for lock here
        // TODO: lock here? Is there a read lock that only prevents writing?
        return buffer_[(pos_+offset)%N];
        // TODO: unlock here?
    }

    // get two arrays and returns the number of items in array a. i.e. items 1..ret are in a, and ret+1..N are in b
    int get_arrays( T*a[], T*b[] )
    {
        // TODO: wait for lock here
        // TODO: how to handle locking in this case?
        *a = buffer_ + (pos_ + 1)%N;
        *b = buffer_;
        return N - pos_;
    }

private:
    T buffer_[N];
    int pos_;    // position of the newest item
};

// Specialization for N=1
template<typename T>
class ring_buffer<T,1>
{
public:
    inline void write( T& item ) { buf_ = item; }

    T& begin_writing( )
    {
        // TODO: lock here
        return buf_;
    }

    void end_writing( )
    {
        // TODO: unlock here
    }

    inline T& get( )
    {
        // TODO: wait for lock here
        // TODO: lock here? Is there a read lock that only prevents writing?
        return buf_;
        // TODO: unlock here?
    }

    int get_arrays( T*a[], T*b[] )
    {
        // TODO: wait for lock here
        // TODO: how to handle locking in this case?
        *a = &buf_;
        *b = &buf_;
        return 1;
    }

private:
    T buf_;
};

#endif // RING_BUFFER_H
