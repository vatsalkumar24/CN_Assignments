// -*- C++ -*-

//=============================================================================
/**
 * @file Monitor_Size.h
 *
 * @author Jeff Parsons <j.parsons@vanderbilt.edu>
 */
//=============================================================================

#ifndef SIZE_MONITOR_H
#define SIZE_MONITOR_H

#include /**/ "ace/pre.h"

#include /**/ "ace/ACE_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Monitor_Base.h"

#if defined (ACE_HAS_MONITOR_FRAMEWORK) && (ACE_HAS_MONITOR_FRAMEWORK == 1)

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace ACE
{
  namespace Monitor_Control
  {
    /**
     * @class Size_Monitor
     *
     * @brief Base class from which ACE monitors of size are
     *        derived.
     *
     */
    class ACE_Export Size_Monitor : public Monitor_Base
    {
    public:
      Size_Monitor ();
      Size_Monitor (const char* name);
      ~Size_Monitor () override = default;

      /// Implemented by the most-derived class. Does the actual
      /// work of fetching the monitored value.
      void update () override;

      /// Reset function.
      void clear () override;
    };
  }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_MONITOR_FRAMEWORK==1 */

#include /**/ "ace/post.h"

#endif // SIZE_MONITOR_H
