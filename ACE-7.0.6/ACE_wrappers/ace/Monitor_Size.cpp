#include "ace/Monitor_Size.h"

#if defined (ACE_HAS_MONITOR_FRAMEWORK) && (ACE_HAS_MONITOR_FRAMEWORK == 1)

#include "ace/Guard_T.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace ACE
{
  namespace Monitor_Control
  {
    Size_Monitor::Size_Monitor ()
      : Monitor_Base ("", Monitor_Control_Types::MC_NUMBER)
    {
    }

    Size_Monitor::Size_Monitor (const char* name)
      : Monitor_Base (name, Monitor_Control_Types::MC_NUMBER)
    {
    }

    void
    Size_Monitor::update ()
    {
      // No platform-specific or periodic code is needed, receive() can be
      // called directly whenever the size changes.
    }

    void
    Size_Monitor::clear ()
    {
      this->Monitor_Base::clear ();
    }
  }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_MONITOR_FRAMEWORK==1 */

