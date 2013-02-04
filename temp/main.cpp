/*  This file is part of ViSig.
    ViSig is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2013 Martin Billinger
*/

#include "anyfactory.h"

#include <iostream>
#include <typeinfo>

#include <map>
#include <vector>
#include <string>
#include <boost/any.hpp>

template<typename T>
inline bool is_type( const boost::any& operand )
{
    return operand.type() == typeid(T);
}

// ======================================================


struct verboser
{
    verboser( ) { std::cout << "Constructor" << std::endl; }
    verboser( const verboser &) { std::cout << "Copy-Constructor" << std::endl; }
    ~verboser( ) { std::cout << "Destructor" << std::endl; }
};

// ======================================================


// ======================================================

bool check_type( const std::string &type_id, boost::any &op )
{
    return op.type().name() == type_id;
}

// ======================================================

class source
{
public:
    virtual std::string type_id() = 0;
    virtual void get( boost::any &buffer ) = 0;
};

class sink
{
public:
    virtual std::string type_id() = 0;
    virtual void set( boost::any &buffer ) = 0;
};

class node
{
public:
    node( )
    {
        buffer_ = boost::any();  // initialize empty
    }

    void connect( source *src )
    {
        std::cout << "Connecting source..." << std::endl;
        // source determines data type
        buffer_ = AnyFactory::create_object( src->type_id() );
        src_ = src;
    }

    void connect( sink *snk )
    {
        std::cout << "Connecting sink..." << std::endl;
        // no sink without source
        if( !check_type( snk->type_id(), buffer_ ) )
            std::cout << "Invalid sink type!" << std::endl;
        snk_ = snk;
    }

    void process( )
    {
        src_->get( buffer_ );
        snk_->set( buffer_ );
    }

private:
    boost::any buffer_;
    source *src_;
    sink *snk_;
};

// ======================================================

class my_source : public source
{
public:
    std::string type_id( )
    {
        return typeid(std::vector<int>).name();
    }

    void get( boost::any &buffer )
    {
        std::cout << "Entering my_source::get()" << std::endl;
        // We are responsible to cast to the correct type here
        std::vector<int> *vibuffer = boost::any_cast< std::vector<int> >( &buffer );
        if( !vibuffer )
        {
            std::cout << "Incompatible buffer type." << std::endl;
            return;
        }
        vibuffer->push_back( 1 );
        vibuffer->push_back( 2 );
        vibuffer->push_back( 3 );
    }
};

class my_sink : public sink
{
public:
    std::string type_id( )
    {
        return typeid(std::vector<int>).name();
    }

    void set( boost::any &buffer )
    {
        std::cout << "Entering my_sink::set()" << std::endl;
        // We are responsible to cast to the correct type here
        std::vector<int> *vibuffer = boost::any_cast< std::vector<int> >( &buffer );
        if( !vibuffer )
        {
            std::cout << "Incompatible buffer type." << std::endl;
            return;
        }
        for( size_t i=0; i<vibuffer->size(); i++ )
            std::cout << (*vibuffer)[i] << std::endl;
    }
};

struct A
{
    virtual void operator()( ) { std::cout << "A" << std::endl; }
};

struct B : public A
{
    void operator()( ) { std::cout << "B" << std::endl; }
};

int main()
{
    my_source msrc;
    my_sink msnk;
    node nd;

    nd.connect( &msrc );

    nd.connect( &msnk );

    nd.process( );

    /*std::vector<boost::any> l;

    l.push_back( int(1) );
    l.push_back( double(1) );
    l.push_back( boost::any() );
    l.push_back( std::string("DEF") );
    l.push_back( verboser() );

    for( size_t i=0; i<l.size(); i++ )
    {
        std::cout << i;
        std::cout << ": epmty=" << l[i].empty();
        std::cout << " int=" << is_type<int>(l[i]);
        std::cout << " double=" << is_type<double>(l[i]);
        std::cout << " str=" << is_type<std::string>(l[i]);
        std::cout << " *vb=" << is_type<verboser>(l[i]);
        try {
            std::cout << " -- " << boost::any_cast<std::string>( l[i] );
        }
        catch( ... ) { std::cout << "."; }
        try {
            boost::any_cast<verboser>( &l[i] );
            std::cout << " -- ";
        }
        catch( ... ) { std::cout << "."; }
        std::cout << std::endl;
    }*/

    return 0;
}

