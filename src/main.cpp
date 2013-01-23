#include <iostream>

#include <string>
#include <vector>

#include "multi_type.h"

#include <boost/mpl/vector.hpp>

// ======================================

typedef boost::mpl::vector<int,std::string,bool,double> typelist;

template<typename T>
struct vector_member_wrapper
{
    vector_member_wrapper( ) : member() { }
    std::vector<T> member;
};

//template<typename T>
//typedef container_member_wrapper<std::vector,T> vector_member_wrapper;



typedef multi_type<typelist> Test;
typedef multi_type<typelist,vector_member_wrapper> TestV;

// ======================================

int main()
{
    Test x;
    std::cout << x.get<int>( ) << std::endl;
    std::cout << x.get<std::string>( ) << std::endl;
    std::cout << x.get<bool>( ) << std::endl;
    return 0;
}

