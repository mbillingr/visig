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

#ifndef DLL_H
#define DLL_H

#include <string>

struct DLL_impl;

class DLL
{
public:
    DLL( const std::string &filename );
    ~DLL( );
private:
    DLL( const DLL & ); // disable copy constructor
    DLL_impl *impl;
};

#endif // DLL_H
