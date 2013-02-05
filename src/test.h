#ifndef TEST_H
#define TEST_H

#include <boost/any.hpp>
#include <boost/cast.hpp>

#include <iostream>

/// @todo Can use virtual operators (yay!)
/// @todo Any way to reduce boiler-plate code?
class base
{
public:
    virtual base* new_same( ) = 0;

    //virtual void operator+=( boost::any x ) { }

    virtual void add( boost::any x ) = 0;
    virtual void add( base* x ) = 0;
    virtual void add( int i ) = 0;
    virtual void add( unsigned int u ) = 0;
    virtual void add( double d ) = 0;

    virtual boost::any get_value( ) = 0;
};

template<typename T>
class numeric : public base
{
public:
    numeric( ) { value = T(); }
    numeric( T x ) { value = x; }

    operator T(){ return value; }

    base* new_same( )
    {
        return new numeric<T>;
    }

    void add( const numeric<T> *x )
    {
        value += x->value;
    }

    void add( boost::any x )
    {
        value += boost::any_cast<T>(x);
    }

    void add( base* x )
    {
        value += boost::any_cast<T>(x->get_value());
    }

    void add( int x )
    {
        value += boost::numeric_cast<T>(x);
    }

    void add( unsigned int x )
    {
        value += boost::numeric_cast<T>(x);
    }

    void add( double x )
    {
        value += boost::numeric_cast<T>(x);
    }

    boost::any get_value( ) { return value; }
private:
    T value;
};

template<typename T>
void generic_code( T* a )
{
    a->add( 2 );
    a->add( a );
}

void test( )
{
    numeric<int> a;
    numeric<int> b;
    numeric<int> c(3);
    numeric<double> d(2.5);

    base *p = &b;

    a.add( &c );

    p->add( &c );

    std::cout << d << std::endl;

    numeric<int> x;
    base *y = new numeric<double>;

    generic_code(&x);
    generic_code<base>(y);

    std::cout << x << ", " << boost::any_cast<double>(y->get_value()) << std::endl;

    delete y;

}

#endif // TEST_H
