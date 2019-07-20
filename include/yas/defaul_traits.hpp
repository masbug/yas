
// Copyright (c) 2010-2019 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __yas__defaul_traits_hpp
#define __yas__defaul_traits_hpp

#include <yas/detail/config/config.hpp>
#include <yas/detail/tools/cast.hpp>
#include <yas/detail/tools/rapidjson_dtoa.hpp>

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cmath>

namespace yas {

/***************************************************************************/

struct default_traits {
	template<typename T>
	static T atou(const char *str, std::size_t size);
	template<typename T>
	static T atoi(const char *str, std::size_t size);

	template<typename T>
	static std::size_t utoa(char *buf, const std::size_t bufsize, T v);
	template<typename T>
	static std::size_t itoa(char *buf, const std::size_t bufsize, T v);

	template<typename T>
	static T atof(const char *str, std::size_t size);
	template<typename T>
	static T atod(const char *str, std::size_t size);

	template<typename T>
	static std::size_t ftoa(char *buf, const std::size_t bufsize, T v);
	template<typename T>
	static std::size_t dtoa(char *buf, const std::size_t bufsize, T v);
}; // struct default_traits

/***************************************************************************/

template<typename T>
T default_traits::atou(const char *str_, std::size_t size) {
	const std::uint8_t *str = __YAS_RCAST(const std::uint8_t *, str_);
	std::uint64_t v= 0;
	switch ( size ) {
		case 20: v = __YAS_SCAST(T, v+(str[size-20]-'0')*10000000000000000000ull); // fallthrough
		case 19: v = __YAS_SCAST(T, v+(str[size-19]-'0')*1000000000000000000ull); // fallthrough
		case 18: v = __YAS_SCAST(T, v+(str[size-18]-'0')*100000000000000000ull); // fallthrough
		case 17: v = __YAS_SCAST(T, v+(str[size-17]-'0')*10000000000000000ull); // fallthrough
		case 16: v = __YAS_SCAST(T, v+(str[size-16]-'0')*1000000000000000ull); // fallthrough
		case 15: v = __YAS_SCAST(T, v+(str[size-15]-'0')*100000000000000ull); // fallthrough
		case 14: v = __YAS_SCAST(T, v+(str[size-14]-'0')*10000000000000ull); // fallthrough
		case 13: v = __YAS_SCAST(T, v+(str[size-13]-'0')*1000000000000ull); // fallthrough
		case 12: v = __YAS_SCAST(T, v+(str[size-12]-'0')*100000000000ull); // fallthrough
		case 11: v = __YAS_SCAST(T, v+(str[size-11]-'0')*10000000000ull); // fallthrough
		case 10: v = __YAS_SCAST(T, v+(str[size-10]-'0')*1000000000ull); // fallthrough
		case  9: v = __YAS_SCAST(T, v+(str[size- 9]-'0')*100000000ull); // fallthrough
		case  8: v = __YAS_SCAST(T, v+(str[size- 8]-'0')*10000000ull); // fallthrough
		case  7: v = __YAS_SCAST(T, v+(str[size- 7]-'0')*1000000ull); // fallthrough
		case  6: v = __YAS_SCAST(T, v+(str[size- 6]-'0')*100000ull); // fallthrough
		case  5: v = __YAS_SCAST(T, v+(str[size- 5]-'0')*10000ull); // fallthrough
		case  4: v = __YAS_SCAST(T, v+(str[size- 4]-'0')*1000ull); // fallthrough
		case  3: v = __YAS_SCAST(T, v+(str[size- 3]-'0')*100ull); // fallthrough
		case  2: v = __YAS_SCAST(T, v+(str[size- 2]-'0')*10ull); // fallthrough
		case  1: v = __YAS_SCAST(T, v+(str[size- 1]-'0')*1ull); // fallthrough
        default: break;
	}

	return __YAS_SCAST(T, v);
}

template<typename T>
T default_traits::atoi(const char *str, std::size_t size) {
	if ( *str == '-' ) {
		++str;

        return -default_traits::atou<T>(str, size-1);
	}

    return default_traits::atou<T>(str, size);
}

/***************************************************************************/

template<typename T>
std::size_t default_traits::utoa(char *buf, const std::size_t, T v) {
	std::uint64_t l = __YAS_SCAST(std::uint64_t, v), n = l;

	std::size_t len = 1;
	if ( l >= 10000000000000000ull ) { len += 16; l /= 10000000000000000ull; }
	if ( l >= 100000000ull ) { len += 8; l /= 100000000ull; }
	if ( l >= 10000ull ) { len += 4; l /= 10000ull; }
	if ( l >= 100ull ) { len += 2; l /= 100ull; }
	if ( l >= 10ull ) { len += 1; }

	*(buf+len) = 0;
	char *p = buf+len-1;
	switch ( len ) {
		case 20: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 19: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 18: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 17: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 16: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 15: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 14: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 13: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 12: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 11: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 10: *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 9 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 8 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 7 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 6 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 5 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 4 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 3 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 2 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
		case 1 : *p-- = __YAS_SCAST(char, '0'+(n % 10)); n /= 10; // fallthrough
        default: break;
	}

	return len;
}

template<typename T>
std::size_t default_traits::itoa(char *buf, const std::size_t, T v) {
	if ( v < 0 ) {
        *buf++ = '-';
        return 1 + default_traits::utoa(buf, 0/*unused*/, __YAS_SCAST(std::int64_t, std::abs(v)));
    }

    return default_traits::utoa(buf, 0/*unused*/, __YAS_SCAST(std::int64_t, v));
}

/***************************************************************************/

template<typename T>
T default_traits::atof(const char *str, std::size_t size) {
	return default_traits::atod<T>(str, size);
}
template<typename T>
T default_traits::atod(const char *str, std::size_t size) {
    static const double es[] = { // 1e-0...1e308: 309 * 8 bytes = 2472 bytes
         1e+0  ,1e+1  ,  1e+2,  1e+3,  1e+4,  1e+5,  1e+6,  1e+7,  1e+8,  1e+9
        ,1e+10 ,1e+11 , 1e+12, 1e+13, 1e+14, 1e+15, 1e+16, 1e+17, 1e+18, 1e+19
        ,1e+20 ,1e+21 , 1e+22, 1e+23, 1e+24, 1e+25, 1e+26, 1e+27, 1e+28, 1e+29
        ,1e+30 ,1e+31 , 1e+32, 1e+33, 1e+34, 1e+35, 1e+36, 1e+37, 1e+38, 1e+39
        ,1e+40 ,1e+41 , 1e+42, 1e+43, 1e+44, 1e+45, 1e+46, 1e+47, 1e+48, 1e+49
        ,1e+50 ,1e+51 , 1e+52, 1e+53, 1e+54, 1e+55, 1e+56, 1e+57, 1e+58, 1e+59
        ,1e+60 ,1e+61 , 1e+62, 1e+63, 1e+64, 1e+65, 1e+66, 1e+67, 1e+68, 1e+69
        ,1e+70 ,1e+71 , 1e+72, 1e+73, 1e+74, 1e+75, 1e+76, 1e+77, 1e+78, 1e+79
        ,1e+80 ,1e+81 , 1e+82, 1e+83, 1e+84, 1e+85, 1e+86, 1e+87, 1e+88, 1e+89
        ,1e+90 ,1e+91 , 1e+92, 1e+93, 1e+94, 1e+95, 1e+96, 1e+97, 1e+98, 1e+99
        ,1e+100,1e+101,1e+102,1e+103,1e+104,1e+105,1e+106,1e+107,1e+108,1e+109
        ,1e+110,1e+111,1e+112,1e+113,1e+114,1e+115,1e+116,1e+117,1e+118,1e+119
        ,1e+120,1e+121,1e+122,1e+123,1e+124,1e+125,1e+126,1e+127,1e+128,1e+129
        ,1e+130,1e+131,1e+132,1e+133,1e+134,1e+135,1e+136,1e+137,1e+138,1e+139
        ,1e+140,1e+141,1e+142,1e+143,1e+144,1e+145,1e+146,1e+147,1e+148,1e+149
        ,1e+150,1e+151,1e+152,1e+153,1e+154,1e+155,1e+156,1e+157,1e+158,1e+159
        ,1e+160,1e+161,1e+162,1e+163,1e+164,1e+165,1e+166,1e+167,1e+168,1e+169
        ,1e+170,1e+171,1e+172,1e+173,1e+174,1e+175,1e+176,1e+177,1e+178,1e+179
        ,1e+180,1e+181,1e+182,1e+183,1e+184,1e+185,1e+186,1e+187,1e+188,1e+189
        ,1e+190,1e+191,1e+192,1e+193,1e+194,1e+195,1e+196,1e+197,1e+198,1e+199
        ,1e+200,1e+201,1e+202,1e+203,1e+204,1e+205,1e+206,1e+207,1e+208,1e+209
        ,1e+210,1e+211,1e+212,1e+213,1e+214,1e+215,1e+216,1e+217,1e+218,1e+219
        ,1e+220,1e+221,1e+222,1e+223,1e+224,1e+225,1e+226,1e+227,1e+228,1e+229
        ,1e+230,1e+231,1e+232,1e+233,1e+234,1e+235,1e+236,1e+237,1e+238,1e+239
        ,1e+240,1e+241,1e+242,1e+243,1e+244,1e+245,1e+246,1e+247,1e+248,1e+249
        ,1e+250,1e+251,1e+252,1e+253,1e+254,1e+255,1e+256,1e+257,1e+258,1e+259
        ,1e+260,1e+261,1e+262,1e+263,1e+264,1e+265,1e+266,1e+267,1e+268,1e+269
        ,1e+270,1e+271,1e+272,1e+273,1e+274,1e+275,1e+276,1e+277,1e+278,1e+279
        ,1e+280,1e+281,1e+282,1e+283,1e+284,1e+285,1e+286,1e+287,1e+288,1e+289
        ,1e+290,1e+291,1e+292,1e+293,1e+294,1e+295,1e+296,1e+297,1e+298,1e+299
        ,1e+300,1e+301,1e+302,1e+303,1e+304,1e+305,1e+306,1e+307,1e+308
    };

	((void)size);
	T v = 0.0;
	bool neg = false;
	if ( *str == '-' ) {
		neg = true;
		++str;
	}
	for ( ; *str >= '0' && *str <= '9'; ++str) {
		v = __YAS_SCAST(T, (v*10.0) + (*str - '0'));
	}
	if ( *str == '.' ) {
		double f = 0.0;
		int n = 0;
		++str;
		for ( ; *str >= '0' && *str <= '9'; ++str, ++n) {
			f = (f*10.0) + (*str - '0');
		}
		v += __YAS_SCAST(T, f/es[n]);
	}

	v = neg ? -v : v;

	return v;
}

/***************************************************************************/

template<typename T>
std::size_t default_traits::ftoa(char *buf, const std::size_t bufsize, T v) {
	return default_traits::dtoa(buf, bufsize, v);
}

template<typename T>
std::size_t default_traits::dtoa(char *buf, const std::size_t size, T v) {
    (void)size;

    return detail::rapidjson_dtoa(v, buf) - buf;
}

/***************************************************************************/

} // ns yas

#endif // __yas__defaul_traits_hpp
