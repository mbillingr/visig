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

#ifndef ANYFACTORY_H
#define ANYFACTORY_H

#include "DLL.h"

#include <boost/any.hpp>

#include <list>
#include <map>
#include <stdexcept>

#define AF_REGISTER_CLASS( T, pretty_name ) \
    AnyFactoryProxy<T> proxy_instance_ ## T ## ___( pretty_name );

class AnyFactory
{
public:
    typedef std::string keytype_t;
    typedef boost::any create_t();

    ~AnyFactory()
    {
        std::list<DLL*>::iterator it = dll_list.begin();
        for( ; it!=dll_list.end(); it++ )
        {
            delete *it;
        }
    }

    static void add_module( const std::string &filename )
    {
        get_instance().dll_list.push_back( new DLL( filename.c_str() ) );
    }

    static boost::any create_object( const keytype_t &class_id )
    {
        factorymap_t &f = get_instance().factory;
        typename factorymap_t::iterator it = f.find(class_id);
        if( it == f.end() )
            throw std::runtime_error( "Unknown class ID." );

        return get_instance().factory[class_id]();
    }

    static std::list<keytype_t> get_IDs( )
    {
        std::list<keytype_t> ids;
        factorymap_t &f = get_instance().factory;
        typename factorymap_t::iterator it = f.begin();
        for( ; it!=f.end(); it++ )
        {
            ids.push_back( it->first );
        }
        return ids;
    }

    static std::string get_name( keytype_t id )
    {
        return get_instance().names[id];
    }

protected:
    template<typename T> friend class AnyFactoryProxy;

    static void registrate( const keytype_t &class_id, create_t* creator_func, const std::string &pretty_name )
    {
        factorymap_t &f = get_instance().factory;
        typename factorymap_t::iterator it = f.find(class_id);
        if( it != f.end() )
            throw std::runtime_error( "Class ID already defined." );

        f[class_id] = creator_func;
        get_instance().names[class_id] = pretty_name;
    }

private:
    typedef typename std::map<keytype_t, create_t*> factorymap_t;

    std::list<DLL*> dll_list;
    factorymap_t factory;
    std::map<keytype_t, std::string> names;

    static AnyFactory& get_instance( )
    {
        static AnyFactory instance;
        return instance;
    }
};

template<typename T>
class AnyFactoryProxy
{
public:
    AnyFactoryProxy( const std::string &pretty_name )
    {
        AnyFactory::registrate( typeid(T).name(), create_instance, pretty_name );
    }

private:
    static boost::any create_instance( )
    {
        return T( );
    }
};

#endif // ANYFACTORY_H
