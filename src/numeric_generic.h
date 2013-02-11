#ifndef NUMERIC_GENERIC_H
#define NUMERIC_GENERIC_H

#include <boost/mpl/vector.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>

namespace numeric_generic
{

    namespace mpl = boost::mpl;

    typedef mpl::vector<int,double> types;

    namespace aux
    {
        template<typename T>
        class add_to
        {
        public:
            virtual void add( T ) = 0;
        };
    }

    class base : public mpl::inherit_linearly<
            types,
            mpl::inherit< mpl::_1, aux::add_to<mpl::_2> >
          >::type
    {
    public:
        //using add_to<int>::add;
    };

    void test( )
    {
        base *b;
        //b->add<int>( 1.0 );
    }
}

#endif // NUMERIC_GENERIC_H
