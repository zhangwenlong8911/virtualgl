/* Copyright 2005 Caleb Epstein
 * Copyright 2006 John Maddock
 * Copyright 2010 Rene Rivera
 * Distributed under the Boost Software License, Version 1.0. (See accompany-
 * ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Copyright (c) 1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/*
 * Copyright notice reproduced from <boost/detail/limits.hpp>, from
 * which this code was originally taken.
 *
 * Modified by Caleb Epstein to use <endian.h> with GNU libc and to
 * defined the BOOST_ENDIAN macro.
 */

#ifndef BOOST_DETAIL_ENDIAN_HPP
#define BOOST_DETAIL_ENDIAN_HPP

/*
 * Special cases come first:
 */
#if defined (__GLIBC__)
/* GNU libc offers the helpful header <endian.h> which defines
 * __BYTE_ORDER
 */
# include <endian.h>
# if (__BYTE_ORDER == __LITTLE_ENDIAN)
#  define BOOST_LITTLE_ENDIAN
# elif (__BYTE_ORDER == __BIG_ENDIAN)
#  define BOOST_BIG_ENDIAN
# elif (__BYTE_ORDER == __PDP_ENDIAN)
#  define BOOST_PDP_ENDIAN
# else
#  error Unknown machine endianness detected.
# endif
# define BOOST_BYTE_ORDER __BYTE_ORDER

#elif defined(__NetBSD__) || defined(__FreeBSD__) || \
    defined(__OpenBSD__) || defined(__DragonFly__)
/*
 * BSD has endian.h, see https://svn.boost.org/trac/boost/ticket/6013
 */
#  if defined(__OpenBSD__)
#  include <machine/endian.h>
#  else
#  include <sys/endian.h>
#  endif
# if (_BYTE_ORDER == _LITTLE_ENDIAN)
#  define BOOST_LITTLE_ENDIAN
# elif (_BYTE_ORDER == _BIG_ENDIAN)
#  define BOOST_BIG_ENDIAN
# elif (_BYTE_ORDER == _PDP_ENDIAN)
#  define BOOST_PDP_ENDIAN
# else
#  error Unknown machine endianness detected.
# endif
# define BOOST_BYTE_ORDER _BYTE_ORDER

#elif defined( __ANDROID__ )
/* Adroid specific code, see: https://svn.boost.org/trac/boost/ticket/7528
 * Here we can use machine/_types.h, see:
 * http://stackoverflow.com/questions/6212951/endianness-of-android-ndk
 */
# include "machine/_types.h"
# ifdef __ARMEB__
#  define BOOST_BIG_ENDIAN
#  define BOOST_BYTE_ORDER 4321
# else
#  define BOOST_LITTLE_ENDIAN
#  define BOOST_BYTE_ORDER 1234
# endif /* __ARMEB */

#elif defined( _XBOX )
/*
 * XBox is always big endian??
 */
# define BOOST_BIG_ENDIAN
# define BOOST_BYTE_ORDER 4321

#elif defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN) || \
    defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__) || \
    defined(__BIGENDIAN__) && !defined(__LITTLEENDIAN__) || \
    defined(_STLP_BIG_ENDIAN) && !defined(_STLP_LITTLE_ENDIAN)
# define BOOST_BIG_ENDIAN
# define BOOST_BYTE_ORDER 4321
#elif defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN) || \
    defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) || \
    defined(__LITTLEENDIAN__) && !defined(__BIGENDIAN__) || \
    defined(_STLP_LITTLE_ENDIAN) && !defined(_STLP_BIG_ENDIAN)
# define BOOST_LITTLE_ENDIAN
# define BOOST_BYTE_ORDER 1234
#elif defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hpux) || defined(__hppa) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__) || defined(__ARMEB__)
# define BOOST_BIG_ENDIAN
# define BOOST_BYTE_ORDER 4321
#elif defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(__amd64) \
   || defined(__amd64__) || defined(_M_AMD64) \
   || defined(__x86_64) || defined(__x86_64__) \
   || defined(_M_X64) || defined(__bfin__) \
   || defined(__ARMEL__) || defined(__aarch64__) \
   || defined(__riscv) || defined(__loongarch__) \
   || (defined(_WIN32) && defined(__ARM__) && defined(_MSC_VER)) /* ARM Windows CE don't define anything reasonably unique, but there are no big-endian Windows versions */

# define BOOST_LITTLE_ENDIAN
# define BOOST_BYTE_ORDER 1234
#else
# error The file boost/detail/endian.hpp needs to be set up for your CPU type.
#endif


#endif
