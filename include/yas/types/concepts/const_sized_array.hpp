
// Copyright (c) 2010-2021 niXman (github dot nixman at pm dot me). All
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

#ifndef __yas__types__concepts__const_sized_array_hpp
#define __yas__types__concepts__const_sized_array_hpp

namespace yas {
namespace detail {
namespace concepts {
namespace const_sized_array {

/***************************************************************************/

template<std::size_t N, std::size_t F, typename Archive, typename T>
Archive& save_chars(Archive &ar, const T *beg, const T *, __YAS_ENABLE_IF_IS_ANY_OF(T, char, signed char)) {
    ar.write("\"", 1);
    ar.write(beg, N-1);
    ar.write("\"", 1);

    return ar;
}

template<std::size_t N, std::size_t F, typename Archive, typename T>
Archive& save_chars(Archive &ar, const T *beg, const T *end, __YAS_DISABLE_IF_IS_ANY_OF(T, char, signed char)) {
    ar.write("[", 1);

    ar & (*beg);
    for ( ++beg; beg != end; ++beg ) {
        ar.write(",", 1);
        ar & (*beg);
    }

    ar.write("]", 1);

    return ar;
}

template<std::size_t N, std::size_t F, typename Archive, typename T>
Archive& save(Archive &ar, const T *beg, const T *end) {
    __YAS_CONSTEXPR_IF ( F & yas::json ) {
        return save_chars<N, F>(ar, beg, end);
    } else {
        ar.write_seq_size(N);
        __YAS_CONSTEXPR_IF ( can_be_processed_as_byte_array<F, T>::value ) {
            ar.write(beg, sizeof(T) * N);
        } else {
            for ( ; beg != end; ++beg ) {
                ar & (*beg);
            }
        }
    }

    return ar;
}

/***************************************************************************/

template<std::size_t N, std::size_t F, typename Archive, typename T>
Archive& load_chars(Archive &ar, T *beg, T *, __YAS_ENABLE_IF_IS_ANY_OF(T, char, signed char)) {
    __YAS_THROW_IF_WRONG_JSON_CHARS(ar, "\"");

    ar.read(beg, N-1);

    __YAS_THROW_IF_WRONG_JSON_CHARS(ar, "\"");

    return ar;
}

template<std::size_t N, std::size_t F, typename Archive, typename T>
Archive& load_chars(Archive &ar, T *beg, T *end, __YAS_DISABLE_IF_IS_ANY_OF(T, char, signed char)) {
    __YAS_CONSTEXPR_IF ( !(F & yas::compacted) ) {
        json_skipws(ar);
    }

    __YAS_THROW_IF_WRONG_JSON_CHARS(ar, "[");

    __YAS_CONSTEXPR_IF ( !(F & yas::compacted) ) {
        json_skipws(ar);
    }

    ar & (*beg);

    __YAS_CONSTEXPR_IF ( !(F & yas::compacted) ) {
        json_skipws(ar);
    }

    for ( ++beg; beg != end; ++beg ) {
        __YAS_CONSTEXPR_IF ( !(F & yas::compacted) ) {
            json_skipws(ar);
        }

        __YAS_THROW_IF_WRONG_JSON_CHARS(ar, ",");

        __YAS_CONSTEXPR_IF ( !(F & yas::compacted) ) {
            json_skipws(ar);
        }

        ar & (*beg);
    }

    __YAS_CONSTEXPR_IF ( !(F & yas::compacted) ) {
        json_skipws(ar);
    }

    __YAS_THROW_IF_WRONG_JSON_CHARS(ar, "]");

    return ar;
}

template<std::size_t N, std::size_t F, typename Archive, typename T>
Archive& load(Archive &ar, T *beg, T *end) {
    __YAS_CONSTEXPR_IF ( F & yas::json ) {
        return load_chars<N, F>(ar, beg, end);
    } else {
        const auto size = ar.read_seq_size();
        if ( size != N ) {
            __YAS_THROW_WRONG_ARRAY_SIZE();
        }
        __YAS_CONSTEXPR_IF ( can_be_processed_as_byte_array<F, T>::value ) {
            ar.read(beg, sizeof(T) * N);
        } else {
            for ( ; beg != end; ++beg ) {
                ar & (*beg);
            }
        }
    }

    return ar;
}

/***************************************************************************/

} // ns const_sized_array
} // ns concepts
} // ns detail
} // ns yas

#endif // __yas__types__concepts__const_sized_array_hpp
