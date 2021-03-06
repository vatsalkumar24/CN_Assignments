// -*- C++ -*-

//==========================================================================
/**
 *  @file    Null_Mutex.h
 *
 *  @author Douglas C. Schmidt <d.schmidt@vanderbilt.edu>
 */
//==========================================================================

#ifndef ACE_NULL_MUTEX_H
#define ACE_NULL_MUTEX_H
#include /**/ "ace/pre.h"

#include "ace/os_include/os_errno.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Global_Macros.h"
#include "ace/OS_Memory.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class ACE_Time_Value;

/**
 * @class ACE_Null_Mutex
 *
 * @brief Implement a do nothing ACE_Mutex, i.e., all the methods are
 * no ops.
 */
class ACE_Export ACE_Null_Mutex
{
public:
  ACE_Null_Mutex (const ACE_TCHAR * = 0)
    : lock_ (0) {}
  ~ACE_Null_Mutex () = default;
  /// Return 0.
  int remove () {return 0;}

  /// Return 0.
  int acquire () {return 0;}

  /// Return -1 with @c errno == @c ETIME.
  int acquire (ACE_Time_Value &) {errno = ETIME; return -1;}

  /// Return -1 with @c errno == @c ETIME.
  int acquire (ACE_Time_Value *) {errno = ETIME; return -1;}

  /// Return 0.
  int tryacquire () {return 0;}

  /// Return 0.
  int release () {return 0;}

  /// Return 0.
  int acquire_write () {return 0;}

  /// Return 0.
  int tryacquire_write () {return 0;}

  /// Return 0.
  int tryacquire_write_upgrade () {return 0;}

  /// Return 0.
  int acquire_read () {return 0;}

  /// Return 0.
  int tryacquire_read () {return 0;}

  /// Dump the state of an object.
  void dump () const {}

  /// Declare the dynamic allocation hooks.
  //ACE_ALLOC_HOOK_DECLARE;

  int lock_; // A dummy lock.

  ACE_ALLOC_HOOK_DECLARE;
};

// FUZZ: disable check_for_ACE_Guard

template <class ACE_LOCK>
class ACE_Guard;

/**
 * @brief Template specialization of ACE_Guard for the
 * ACE_Null_Mutex.
 *
 * This specialization is useful since it helps to speedup
 * performance of the "Null_Mutex" considerably.
 */
template<>
class ACE_Export ACE_Guard<ACE_Null_Mutex>
{
public:
  ACE_Guard (ACE_Null_Mutex &) {}
  ACE_Guard (ACE_Null_Mutex &, int) {}
  ACE_Guard (ACE_Null_Mutex &, int, int) {}
#if defined (ACE_WIN32)
  ~ACE_Guard () = default;
#endif /* ACE_WIN32 */

  int acquire () { return 0; }
  int tryacquire () { return 0; }
  int release () { return 0; }
  void disown () {}
  int locked () { return 1; }
  int remove () { return 0; }
  void dump () const {}

private:
  ACE_Guard (const ACE_Guard<ACE_Null_Mutex> &) = delete;
  void operator= (const ACE_Guard<ACE_Null_Mutex> &) = delete;
  ACE_Guard (ACE_Guard<ACE_Null_Mutex> &&) = delete;
  void operator= (ACE_Guard<ACE_Null_Mutex> &&) = delete;
};

template <class ACE_LOCK>
class ACE_Write_Guard;

/**
 * @brief Template specialization of ACE_Write_Guard for the
 * ACE_Null_Mutex.
 */
template<>
class ACE_Export ACE_Write_Guard<ACE_Null_Mutex>
  : public ACE_Guard<ACE_Null_Mutex>
{
public:
  ACE_Write_Guard (ACE_Null_Mutex &m)
    : ACE_Guard<ACE_Null_Mutex> (m) {}
  ACE_Write_Guard (ACE_Null_Mutex &m, int blocked)
    : ACE_Guard<ACE_Null_Mutex> (m, blocked) {}

  int acquire_write () { return 0; }
  int acquire () { return 0; }
  int tryacquire_write () { return 0; }
  int tryacquire () { return 0; }
  void dump () const {}
};

template <class ACE_LOCK>
class ACE_Read_Guard;

/**
 * @brief Template specialization of ACE_Read)Guard for the
 * ACE_Null_Mutex.
 */
template<>
class ACE_Export ACE_Read_Guard<ACE_Null_Mutex>
  : public ACE_Guard<ACE_Null_Mutex>
{
public:
  ACE_Read_Guard (ACE_Null_Mutex &m)
    : ACE_Guard<ACE_Null_Mutex> (m) {}
  ACE_Read_Guard (ACE_Null_Mutex &m, int blocked)
    : ACE_Guard<ACE_Null_Mutex> (m, blocked) {}

  int acquire_read () { return 0; }
  int acquire () { return 0; }
  int tryacquire_read () { return 0; }
  int tryacquire () { return 0; }
  void dump () const {}
};

// FUZZ: enable check_for_ACE_Guard

template <class T> class ACE_Malloc_Lock_Adapter_T;

/**
 * @brief Template specialization of ACE_Malloc_Lock_Adapter_T for the
 * ACE_Null_Mutex.
 */
template<>
class ACE_Export ACE_Malloc_Lock_Adapter_T<ACE_Null_Mutex>
{
public:
  ACE_Null_Mutex * operator () (const ACE_TCHAR *name)
  {
    ACE_Null_Mutex *p;
    ACE_NEW_RETURN (p, ACE_Null_Mutex (name), 0);
    return p;
  }
};

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* ACE_NULL_MUTEX_H */
