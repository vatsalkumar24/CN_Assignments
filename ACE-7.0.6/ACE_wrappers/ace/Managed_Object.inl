// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template <class TYPE>
ACE_INLINE
ACE_Cleanup_Adapter<TYPE>::ACE_Cleanup_Adapter ()
  // Note: don't explicitly initialize "object_", because TYPE may not
  // have a default constructor.  Let the compiler figure it out . . .
{
}

template <class TYPE>
ACE_INLINE
TYPE &
ACE_Cleanup_Adapter<TYPE>::object ()
{
  return this->object_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
