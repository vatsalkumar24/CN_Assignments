// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template<class MUTEX> ACE_INLINE int
ACE_Condition<MUTEX>::remove ()
{
  // ACE_TRACE ("ACE_Condition<MUTEX>::remove");

  // cond_destroy() is called in a loop if the condition variable is
  // BUSY.  This avoids a condition where a condition is signaled and
  // because of some timing problem, the thread that is to be signaled
  // has called the cond_wait routine after the signal call.  Since
  // the condition signal is not queued in any way, deadlock occurs.

  int result = 0;

  while ((result = ACE_OS::cond_destroy (&this->cond_)) == -1
          && errno == EBUSY)
    {
      ACE_OS::cond_broadcast (&this->cond_);
      ACE_OS::thr_yield ();
    }

  return result;
}

template<class MUTEX> ACE_INLINE MUTEX &
ACE_Condition<MUTEX>::mutex ()
{
  // ACE_TRACE ("ACE_Condition<MUTEX>::mutex");
  return this->mutex_;
}

template <class MUTEX> ACE_INLINE int
ACE_Condition<MUTEX>::signal ()
{
// ACE_TRACE ("ACE_Condition<MUTEX>::signal");
  return ACE_OS::cond_signal (&this->cond_);
}

template <class MUTEX> ACE_INLINE int
ACE_Condition<MUTEX>::broadcast ()
{
// ACE_TRACE ("ACE_Condition<MUTEX>::broadcast");
  return ACE_OS::cond_broadcast (&this->cond_);
}

ACE_END_VERSIONED_NAMESPACE_DECL
