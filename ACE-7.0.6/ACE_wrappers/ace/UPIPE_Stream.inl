// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE ACE_HANDLE
ACE_UPIPE_Stream::get_handle () const
{
  ACE_TRACE ("ACE_UPIPE_Stream::get_handle");
  return this->ACE_SPIPE::get_handle ();
}

ACE_END_VERSIONED_NAMESPACE_DECL
