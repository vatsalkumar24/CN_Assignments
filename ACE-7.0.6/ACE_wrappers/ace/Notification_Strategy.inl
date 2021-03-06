// -*- C++ -*-
//
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE ACE_Event_Handler *
ACE_Notification_Strategy::event_handler ()
{
  return eh_;
}

ACE_INLINE void
ACE_Notification_Strategy::event_handler (ACE_Event_Handler *eh)
{
  this->eh_ = eh;
}

ACE_INLINE ACE_Reactor_Mask
ACE_Notification_Strategy::mask () const
{
  return mask_;
}

ACE_INLINE void
ACE_Notification_Strategy::mask (ACE_Reactor_Mask m)
{
  this->mask_ = m;
}

ACE_END_VERSIONED_NAMESPACE_DECL
