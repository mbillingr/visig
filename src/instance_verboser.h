#ifndef INSTANCE_VERBOSER_H
#define INSTANCE_VERBOSER_H

#include <iostream>

class instance_verboser
{
public:
    instance_verboser( )
    { std::cout << "Constructor." << std::endl; }

    instance_verboser( const instance_verboser& other )
    { std::cout << "Copy Constructor." << std::endl; }

    ~instance_verboser( )
    { std::cout << "Destructor." << std::endl; }

};

#endif // INSTANCE_VERBOSER_H
