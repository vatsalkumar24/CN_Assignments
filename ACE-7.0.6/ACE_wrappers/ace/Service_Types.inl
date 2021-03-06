// -*- C++ -*-
#include "ace/ACE.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE void *
ACE_Service_Type_Impl::object () const
{
  ACE_TRACE ("ACE_Service_Type_Impl::object");
  return this->obj_;
}

ACE_INLINE const ACE_TCHAR *
ACE_Service_Type_Impl::name () const
{
  ACE_TRACE ("ACE_Service_Type_Impl::name");
  return this->name_;
}

ACE_INLINE void
ACE_Service_Type_Impl::name (const ACE_TCHAR *n)
{
  ACE_TRACE ("ACE_Service_Type_Impl::name");

  ACE::strdelete (const_cast<ACE_TCHAR*> (this->name_));
  this->name_ = ACE::strnew (n);
}

ACE_INLINE int
ACE_Service_Type_Impl::service_type () const
{
  return service_type_;
}

ACE_INLINE void
ACE_Service_Type_Impl::service_type (int stype)
{
  service_type_ = stype;
}
ACE_END_VERSIONED_NAMESPACE_DECL
