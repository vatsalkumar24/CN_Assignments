// -*- C++ -*-
// Returns a count of the number of currently valid entries (counting
// both resumed and suspended entries).

#if defined (ACE_MT_SAFE) && (ACE_MT_SAFE != 0)
#include "ace/Guard_T.h"
#include "ace/Thread_Mutex.h"
#endif /* ACE_MT_SAFE */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE size_t
ACE_Service_Repository::current_size () const
{
  ACE_TRACE ("ACE_Service_Repository::current_size");
  ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex,
                            ace_mon,
                            (ACE_Recursive_Thread_Mutex &) this->lock_, 0));
  return this->service_array_.size ();
}

ACE_INLINE ACE_SYNCH_RECURSIVE_MUTEX&
ACE_Service_Repository::lock () const
{
  return this->lock_;
}

ACE_INLINE int
ACE_Service_Repository_Iterator::done () const
{
  ACE_TRACE ("ACE_Service_Repository_Iterator::done");

  return this->next_ >= this->svc_rep_.current_size ();
}

ACE_INLINE
ACE_Service_Repository_Iterator::~ACE_Service_Repository_Iterator ()
{
}

ACE_END_VERSIONED_NAMESPACE_DECL
