#include <iostream>

#include <string>
#include <vector>

#include "multi_type.h"

#include <boost/mpl/vector.hpp>

// ======================================

template<typename T>
struct vector_member_wrapper
{
    vector_member_wrapper( ) : member() { }
    std::vector<T> member;
};

// ======================================

int main()
{
    multi_type< boost::mpl::vector<int,std::string,bool> > x;
    std::cout << x.get<int>( ) << std::endl;
    std::cout << x.get<std::string>( ) << std::endl;
    std::cout << x.get<bool>( ) << std::endl;
    return 0;
}

