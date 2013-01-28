#ifndef PORTS_H
#define PORTS_H

template<typename T> class Node;

template<typename T>
class OutPort
{
public:
    // write output data into buffer
    void execute( T* buffer );
private:
    Node<T> *node;
};

template<typename T>
class InPort
{
public:
    // tell the input port that data is available
    void notify( );
private:
    Node<T> *node;
};

#endif // PORTS_H
