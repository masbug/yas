
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

#ifndef __yas__tests__base__include__auto_array_hpp
#define __yas__tests__base__include__auto_array_hpp

/***************************************************************************/

template<typename archive_traits>
bool auto_array_test(std::ostream &log, const char *archive_type, const char *test_name) {
    enum {
        array_size = 6
    };

    std::int8_t ca1[] = {"string"}, ca2[array_size + 1] = {0};
    std::uint8_t uca1[] = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x00}, uca2[array_size + 1] = {0};
    std::int16_t sa1[array_size] = {1, 2, 3, 4, 5, 6}, sa2[array_size] = {0};
    std::uint16_t usa1[array_size] = {1, 2, 3, 4, 5, 6}, usa2[array_size] = {0};
    std::int32_t ia1[array_size] = {1, 2, 3, 4, 5, 6}, ia2[array_size] = {0};
    std::uint32_t uia1[array_size] = {1, 2, 3, 4, 5, 6}, uia2[array_size] = {0};
    std::int64_t i64a1[array_size] = {1, 2, 3, 4, 5, 6}, i64a2[array_size] = {0};
    std::uint64_t ui64a1[array_size] = {1, 2, 3, 4, 5, 6}, ui64a2[array_size] = {0};
    double da1[array_size] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, da2[array_size] = {0};
    float fa1[array_size] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f}, fa2[array_size] = {0};
    std::string stra1[array_size] = {"1", "2", "3", "4", "5", "6"}, stra2[array_size];

    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("ca1", ca1));

        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("ca1", ca2));
        if ( std::memcmp(ca1, ca2, array_size * sizeof(ca1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("uca1", uca1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("uca1", uca2));
        if ( std::memcmp(uca1, uca2, array_size * sizeof(uca1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("sa1", sa1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("sa1", sa2));
        if ( std::memcmp(sa1, sa2, array_size * sizeof(sa1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("usa1", usa1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("usa1", usa2));
        if ( std::memcmp(usa1, usa2, array_size * sizeof(usa1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("ia1", ia1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("ia1", ia2));
        if ( std::memcmp(ia1, ia2, array_size * sizeof(ia1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("uia1", uia1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("uia1", uia2));
        if ( std::memcmp(uia1, uia2, array_size * sizeof(uia1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("i64a1", i64a1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("i64a1", i64a2));
        if ( std::memcmp(i64a1, i64a2, array_size * sizeof(i64a1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("ui64a1", ui64a1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("ui64a1", ui64a2));
        if ( std::memcmp(ui64a1, ui64a2, array_size * sizeof(ui64a1[0])) ) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("da1", da1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("da1", da2));
        if (yas::is_binary_archive<typename archive_traits::oarchive_type>::value) {
            if ( std::memcmp(da1, da2, array_size * sizeof(da1[0])) ) {
                YAS_TEST_REPORT(log, archive_type, test_name);
                return false;
            }
        } else {
            if (!std::equal(da1, da1 + array_size, da2)) {
                YAS_TEST_REPORT(log, archive_type, test_name);
                return false;
            }
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("fa1", fa1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("fa1", fa2));
        if (yas::is_binary_archive<typename archive_traits::oarchive_type>::value) {
            if ( std::memcmp(fa1, fa2, array_size * sizeof(fa1[0])) ) {
                YAS_TEST_REPORT(log, archive_type, test_name);
                return false;
            }
        } else {
            if (!std::equal(fa1, fa1 + array_size, fa2)) {
                YAS_TEST_REPORT(log, archive_type, test_name);
                return false;
            }
        }
    }
    {
        typename archive_traits::oarchive oa;
        archive_traits::ocreate(oa, archive_type);
        oa & YAS_OBJECT_NVP("obj", ("stra1", stra1));
        typename archive_traits::iarchive ia;
        archive_traits::icreate(ia, oa, archive_type);
        ia & YAS_OBJECT_NVP("obj", ("stra1", stra2));
        if (!std::equal(stra1, stra1 + array_size, stra2)) {
            YAS_TEST_REPORT(log, archive_type, test_name);
            return false;
        }
    }

    return true;
}

/***************************************************************************/

#endif // __yas__tests__base__include__auto_array_hpp
