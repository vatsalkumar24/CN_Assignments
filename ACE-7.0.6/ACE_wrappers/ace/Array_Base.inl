// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// Clean up the array (e.g., delete dynamically allocated memory).
template <class T> ACE_INLINE
ACE_Array_Base<T>::~ACE_Array_Base ()
{
  ACE_DES_ARRAY_FREE (this->array_,
                      this->max_size_,
                      this->allocator_->free,
                      T);
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::iterator
ACE_Array_Base<T>::begin ()
{
  return this->array_;
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::iterator
ACE_Array_Base<T>::end ()
{
  return this->array_ + this->cur_size_;
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::const_iterator
ACE_Array_Base<T>::begin () const
{
  return this->array_;
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::const_iterator
ACE_Array_Base<T>::end () const
{
  return this->array_ + this->cur_size_;
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::reverse_iterator
ACE_Array_Base<T>::rbegin ()
{
  return reverse_iterator (this->end ());
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::reverse_iterator
ACE_Array_Base<T>::rend ()
{
  return reverse_iterator (this->begin ());
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::const_reverse_iterator
ACE_Array_Base<T>::rbegin () const
{
  return const_reverse_iterator (this->end ());
}

template <class T>
ACE_INLINE typename ACE_Array_Base<T>::const_reverse_iterator
ACE_Array_Base<T>::rend () const
{
  return const_reverse_iterator (this->begin ());
}

template <class T> ACE_INLINE typename ACE_Array_Base<T>::size_type
ACE_Array_Base<T>::size () const
{
  return this->cur_size_;
}

template <class T> ACE_INLINE typename ACE_Array_Base<T>::size_type
ACE_Array_Base<T>::max_size () const
{
  return this->max_size_;
}

template <class T> ACE_INLINE bool
ACE_Array_Base<T>::in_range (typename ACE_Array_Base<T>::size_type index) const
{
  return index < this->cur_size_;
}

template <class T> ACE_INLINE T &
ACE_Array_Base<T>::operator[] (typename ACE_Array_Base<T>::size_type index)
{
  return this->array_[index];
}

template <class T> ACE_INLINE const T &
ACE_Array_Base<T>::operator[] (typename ACE_Array_Base<T>::size_type index) const
{
  return this->array_[index];
}

// ****************************************************************

template <class T> ACE_INLINE void
ACE_Array_Iterator<T>::dump () const
{
#if defined (ACE_HAS_DUMP)
  // ACE_TRACE ("ACE_Array_Iterator<T>::dump");
#endif /* ACE_HAS_DUMP */
}

template <class T> ACE_INLINE
ACE_Array_Iterator<T>::ACE_Array_Iterator (ACE_Array_Base<T> &a)
    : current_ (0),
      array_ (a)
{
  // ACE_TRACE ("ACE_Array_Iterator<T>::ACE_Array_Iterator");
}

template <class T> ACE_INLINE int
ACE_Array_Iterator<T>::advance ()
{
  // ACE_TRACE ("ACE_Array_Iterator<T>::advance");

  if (this->current_ < array_.size ())
    {
      ++this->current_;
      return 1;
    }
  else
    {
      // Already finished iterating.
      return 0;
    }
}

template <class T> ACE_INLINE int
ACE_Array_Iterator<T>::done () const
{
  ACE_TRACE ("ACE_Array_Iterator<T>::done");

  return this->current_ >= array_.size ();
}

ACE_END_VERSIONED_NAMESPACE_DECL
