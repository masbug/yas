
// Copyright (c) 2010-2018 niXman (i dot nixman dog gmail dot com). All
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

#ifndef __yas__detail__config__config_hpp
#define __yas__detail__config__config_hpp

/***************************************************************************/

#if defined(_MSC_VER)
#  if _MSC_VER < 1900
#   error "Visual Studio 2015 or greater is required"
#  endif
#else
# if __cplusplus < 201103L
#  error "C++11 or greater is required"
# endif
#endif

/***************************************************************************/

#if __cplusplus >= 201703L
#define __YAS_CONSTEXPR_IF(...) if constexpr ( static_cast<bool>(__VA_ARGS__) )
#else
#define __YAS_CONSTEXPR_IF(...) if (__VA_ARGS__)
#endif

/***************************************************************************/

#ifndef __YAS_OBJECT_MAX_MEMBERS
#   define __YAS_OBJECT_MAX_MEMBERS 20
#endif // __YAS_OBJECT_MAX_MEMBERS

/***************************************************************************/

#include <yas/detail/config/endian.hpp>

#if defined(__clang__)
#  define __YAS_COMPILER_CONFIG <yas/detail/config/compiler/clang.hpp>
#elif defined(__GNUC__)
#  define __YAS_COMPILER_CONFIG <yas/detail/config/compiler/gcc.hpp>
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#  define __YAS_COMPILER_CONFIG <yas/detail/config/compiler/intel.hpp>
#elif defined(_MSC_VER)
#  define __YAS_COMPILER_CONFIG <yas/detail/config/compiler/msvc.hpp>
#else
#  error "Unknown compiler"
#endif

#include __YAS_COMPILER_CONFIG

/***************************************************************************/

#endif // __yas__detail__config__config_hpp
