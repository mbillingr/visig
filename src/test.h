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
    //virtual base* new_same( ) = 0;

    template<class derived>
    derived *ptr_cast( ) { return dynamic_cast<derived*>( this ); }

    virtual bool implements_algebra( ) = 0;

    //virtual void operator+=( boost::any x ) { }

    /*virtual void add( boost::any x ) = 0;
    virtual void add( base* x ) = 0;
    virtual void add( int i ) = 0;
    virtual void add( unsigned int u ) = 0;
    virtual void add( double d ) = 0;*/

    //virtual boost::any get_value( ) = 0;
};

class numericbase : public base
{
public:
    virtual void operator+=( const int i ) { std::cout << "adding 'int' not supported." << std::endl; }
    virtual void operator+=( const double d ) { std::cout << "adding 'double' not supported." << std::endl; }
    virtual void operator+=( const numericbase* b ) { std::cout << "adding 'numericbase*' not supported." << std::endl; }
};

class numericbase_wrapper
{
public:
    numericbase_wrapper( base *b ) { ptr = dynamic_cast<numericbase*>( b ); }

    void operator+=( const int i ) { (*ptr) += i; }
    void operator+=( const double d ) { (*ptr) += d; }
    void operator+=( const numericbase_wrapper &b ) { (*ptr) += b.ptr; }

private:
    numericbase *ptr;
};

template<typename T>
class numeric : public numericbase
{
public:
    numeric( ) { value = T(); }
    numeric( T x ) { value = x; }

    operator T(){ return value; }

    void operator+=( const T other ) { value += other; }
    //void operator+=( const numericbase* other ) { value += other->numeric_cast<T>(); }


    bool implements_algebra() { return true; }

    /*base* new_same( )
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

    boost::any get_value( ) { return value; }*/
private:
    T value;
};

class specialA: public base
{
public:
    bool implements_algebra() { return false; }

    void doA( ){ std::cout << "A" << std::endl; }
};

class specialB : public base
{
public:
    bool implements_algebra() { return false; }

    void doB( ){ std::cout << "B" << std::endl; }
};

template<typename T>
void generic_code( T* a )
{
    //a->add( 2 );
    //a->add( a );
}

class numericalgo
{
public:
    void execute( base* b )
    {
        numericbase_wrapper x( b );

        x += 2;
        x += x;
    }
};

class algoA
{
public:
    void execute( base* b )
    {
        specialA* a = dynamic_cast<specialA*>( b );
        a->doA();
    }
};

void test( )
{
    numeric<int> i(4);

    numericalgo algo;
    algo.execute( &i );

    std::cout << i << std::endl;

    /*numeric<int> a;
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
*/
}

#endif // TEST_H
