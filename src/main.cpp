#include <iostream>

template<class I>
class InPort
{
public:
    typedef I type;

    void process( )
    {
        static_cast<I*>(this)->process( );
    }
};

template<typename I>
class StaticNode
{
public:
    void update( I in )
    {
        in.process( );
    }
};

// ======================================

using namespace std;

// ======================================

class MyInPort : public InPort<MyInPort>
{
public:
    void process( )
    {
        cout << "Hello!" << endl;
    }
};

// ======================================

int main()
{
    MyInPort mip;
    mip.process();

    InPort<MyInPort> ip = mip;
    ip.process();

    StaticNode<MyInPort> n;
    n.update( mip );

    return 0;
}

