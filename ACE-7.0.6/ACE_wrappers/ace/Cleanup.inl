// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_Cleanup::ACE_Cleanup ()
{
}

ACE_INLINE void*
ACE_Cleanup_Info_Node::object()
{
  return this->object_;
}

ACE_INLINE ACE_CLEANUP_FUNC
ACE_Cleanup_Info_Node::cleanup_hook ()
{
  return this->cleanup_hook_;
}

ACE_INLINE void *
ACE_Cleanup_Info_Node::param ()
{
  return this->param_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
