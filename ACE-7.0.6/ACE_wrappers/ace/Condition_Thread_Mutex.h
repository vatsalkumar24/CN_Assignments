// -*- C++ -*-

//==========================================================================
/**
 *  @file    Condition_Thread_Mutex.h
 *
 *  @author Douglas C. Schmidt <d.schmidt@vanderbilt.edu>
 */
//==========================================================================

#ifndef ACE_CONDITION_THREAD_MUTEX_H
#define ACE_CONDITION_THREAD_MUTEX_H
#include /**/ "ace/pre.h"

#include /**/ "ace/ACE_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined (ACE_HAS_THREADS)
#  include "ace/Null_Condition.h"
#else /* ACE_HAS_THREADS */
// ACE platform supports some form of threading.

#include "ace/Thread_Mutex.h"
#include "ace/Condition_Attributes.h"
#include "ace/Condition_T.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class ACE_Time_Value;

/**
 * @brief ACE_Condition template specialization written using
 * ACE_Mutexes. This allows threads to block until shared data
 * changes state.
 * A condition variable enables threads to atomically block and
 * test the condition under the protection of a mutual exclu-
 * sion lock (mutex) until the condition is satisfied.  That is,
 * the mutex must have been held by the thread before calling
 * wait or signal on the condition.  If the condition is false,
 * a thread blocks on a condition variable and atomically
 * releases the mutex that is waiting for the condition to
 * change.  If another thread changes the condition, it may wake
 * up waiting threads by signaling the associated condition
 * variable.  The waiting threads, upon awakening, reacquire the
 * mutex and re-evaluate the condition.
 */
template <>
class ACE_Export ACE_Condition<ACE_Thread_Mutex>
{
public:
  /// Initialize the condition variable.
  ACE_Condition (ACE_Thread_Mutex &m,
                 const ACE_TCHAR *name = 0,
                 void *arg = 0);

  /// Initialize the condition variable.
  ACE_Condition (ACE_Thread_Mutex &m,
                 const ACE_Condition_Attributes &attributes,
                 const ACE_TCHAR *name = 0,
                 void *arg = 0);

  /// Implicitly destroy the condition variable.
  ~ACE_Condition ();

  /**
   * Explicitly destroy the condition variable.  Note that only one
   * thread should call this method since it doesn't protect against
   * race conditions.
   */
  int remove ();

  /**
   * Block on condition, or until absolute time-of-day has passed.  If
   * abstime == 0 use "blocking" wait semantics.  Else, if @a abstime
   * != 0 and the call times out before the condition is signaled
   * wait() returns -1 and sets errno to ETIME.
   */
  int wait (const ACE_Time_Value *abstime);

  /// Block on condition.
  int wait ();

  /**
   * Block on condition or until absolute time-of-day has passed.  If
   * abstime == 0 use "blocking" wait() semantics on the @a mutex
   * passed as a parameter (this is useful if you need to store the
   * <Condition> in shared memory).  Else, if @a abstime != 0 and the
   * call times out before the condition is signaled <wait> returns -1
   * and sets errno to ETIME.
   */
  int wait (ACE_Thread_Mutex &mutex, const ACE_Time_Value *abstime = 0);

  /// Signal one waiting thread.
  int signal ();

  /// Signal *all* waiting threads.
  int broadcast ();

  /// Returns a reference to the underlying mutex;
  ACE_Thread_Mutex &mutex ();

  /// Dump the state of an object.
  void dump () const;

  /// Declare the dynamic allocation hooks.
  ACE_ALLOC_HOOK_DECLARE;

protected:
  /// Condition variable.
  ACE_cond_t cond_;

  /// Reference to mutex lock.
  ACE_Thread_Mutex &mutex_;

  /// Keeps track of whether remove() has been called yet to avoid
  /// multiple remove() calls, e.g., explicitly and implicitly in the
  /// destructor.  This flag isn't protected by a lock, so make sure
  /// that you don't have multiple threads simultaneously calling
  /// remove() on the same object, which is a bad idea anyway...
  bool removed_;

private:
  void operator= (const ACE_Condition<ACE_Thread_Mutex> &) = delete;
  ACE_Condition (const ACE_Condition<ACE_Thread_Mutex> &) = delete;
};

typedef ACE_Condition<ACE_Thread_Mutex> ACE_Condition_Thread_Mutex;

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (__ACE_INLINE__)
#include "ace/Condition_Thread_Mutex.inl"
#endif /* __ACE_INLINE__ */

#endif /* !ACE_HAS_THREADS */

#include /**/ "ace/post.h"
#endif /* ACE_CONDITION_THREAD_MUTEX_H */
