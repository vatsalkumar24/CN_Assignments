// -*- C++ -*-

//=============================================================================
/**
 *  @file   Hashable.h
 *
 *  @author Doug Schmidt
 */
//=============================================================================

#ifndef ACE_HASHABLE_H
#define ACE_HASHABLE_H

#include /**/ "ace/pre.h"

#include /**/ "ace/ACE_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class ACE_Hashable
 *
 * @brief ACE_Hashable
 */
class ACE_Export ACE_Hashable
{
public:
  /// Destructor.
  virtual ~ACE_Hashable () = default;

  /// Computes and returns hash value.  This "caches" the hash value to
  /// improve performance.
  virtual unsigned long hash () const;

protected:
  /// Protected constructor.
  ACE_Hashable () = default;

  /// This is the method that actually performs the non-cached hash
  /// computation.
  virtual unsigned long hash_i () const = 0;

protected:
  /// Pre-computed hash-value.
  mutable unsigned long hash_value_ {};
};

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"

#endif /*ACE_HASHABLE_H*/
