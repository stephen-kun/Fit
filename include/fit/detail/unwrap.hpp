/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    unwrap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef FIT_GUARD_UNWRAP_H
#define FIT_GUARD_UNWRAP_H

#include <type_traits>
#include <functional>

namespace fit { namespace detail {

template <class T>
struct unwrap_reference
{
    typedef T type;
};
template <class T>
struct unwrap_reference<std::reference_wrapper<T>>
{
    typedef T& type;
};

}} // namespace fit

#endif
