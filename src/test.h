#ifndef TEST_H
#define TEST_H

#include <boost/any.hpp>

class base
{
public:
    virtual void add(  boost::any x ) = 0;
    virtual void add( base* x ) = 0;

    inline boost::any& get_value( ) { return value; }

protected:
    boost::any value;
};

template<typename T>
class numeric : public base
{
public:
    numeric( ) { value = T(); }
    numeric( T x ) { value = x; }

    void add( boost::any x )
    {
        value = boost::any_cast<T>(value) + boost::any_cast<T>(x);
    }

    void add( const numeric<T> *x )
    {
        value = boost::any_cast<T>(value) + boost::any_cast<T>(x->value);
    }

    void add( base* x )
    {
        value = boost::any_cast<T>(value) + boost::any_cast<T>(x->get_value());
    }

};

void test( )
{
    numeric<int> a;
    numeric<int> b;
    numeric<int> c(1);
    numeric<double> d(2);

    base *p = &b;

    a.add( &c );

    p->add( &c );

}

#endif // TEST_H
