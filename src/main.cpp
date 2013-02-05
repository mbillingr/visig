
#include "BlockInterface.h"

#include "test.h"

#include "node.h"

#include "SharedBuffer.h"

#include "multi_type.h"
#include "thread_pool.h"

#include <boost/mpl/vector.hpp>

#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>

// ======================================

template<typename T>
struct vector_member_wrapper
{
    vector_member_wrapper( ) : member() { }
    std::vector<T> member;
};

struct print_action
{
    template<typename T>
    void operator()( T& t )
    {
        std::cout << typeid(T).name() << std::endl;
    }
};

struct execute_action
{
    template<typename T>
    void operator()( T& t )
    {
        t.execute();
    }
};

// ======================================

int main()
{
    /*multi_type< boost::mpl::vector<int,std::string,bool> > x;
    std::cout << x.get<int>( ) << std::endl;
    std::cout << x.get<std::string>( ) << std::endl;
    std::cout << x.get<bool>( ) << std::endl;

    x.for_all( print_action() );*/

    test( );

    testSharedBuffer( );

    return 0;
}

