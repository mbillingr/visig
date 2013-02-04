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

#include <vector>

AnyFactoryProxy<char> proxy_i8( "int8" );
AnyFactoryProxy<unsigned char> proxy_ui8( "uint8" );
AnyFactoryProxy<short> proxy_i16( "int16" );
AnyFactoryProxy<unsigned short> proxy_ui16( "uint16" );
AnyFactoryProxy<int> proxy_i32( "int32" );
AnyFactoryProxy<unsigned int> proxy_ui32( "uint32" );
AnyFactoryProxy<long> proxy_i64( "int64" );
AnyFactoryProxy<unsigned long> proxy_ui64( "uint64" );
AnyFactoryProxy<float> proxy_f32( "float32" );
AnyFactoryProxy<double> proxy_f64( "float64" );

AnyFactoryProxy< std::vector<double> > proxy_vf64( "vfloat64" );
AnyFactoryProxy< std::vector<int> > proxy_vi32( "vint32" );
