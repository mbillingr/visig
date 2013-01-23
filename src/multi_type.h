#ifndef MULTI_TYPE_H
#define MULTI_TYPE_H

#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>

// default wrapper for class multi_type.
// multi_type inherits direct_member_wrapper repeatedly for each type.
template<typename T>
struct direct_member_wrapper
{
    direct_member_wrapper( ) : member() { }
    T member;
};

// class multi_type
// inherits member_wrapper<T> for every type T specified in type_sequence.
// Example:
// multi_type<int,string,foo> example;
// example.get<string>() = "hello";
template< class type_sequence,                                              // boost::mpl sequence that contains unique types
          template<typename>class member_wrapper = direct_member_wrapper>   // default to direct member wrapper
class multi_type
        : private boost::mpl::inherit_linearly                                  // privately inherit inherit_linearly construct
        <
          type_sequence                                                         // for every type:
        , boost::mpl::inherit<boost::mpl::_1, member_wrapper<boost::mpl::_2> >  // successively inherit the wrapped type
        >::type
{
public:

    template<typename T>
    T &get( ) { return member_wrapper<T>::member; }
};

#endif // MULTI_TYPE_H
