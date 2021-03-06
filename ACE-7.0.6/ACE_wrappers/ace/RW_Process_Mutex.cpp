#include "ace/RW_Process_Mutex.h"
#include "ace/Log_Category.h"
#include "ace/ACE.h"

#if !defined (__ACE_INLINE__)
#include "ace/RW_Process_Mutex.inl"
#endif /* __ACE_INLINE__ */

#include "ace/Malloc_T.h"

#if defined (ACE_WIN32)
#include "ace/OS_NS_fcntl.h"
#endif /* ACE_WIN32 */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_ALLOC_HOOK_DEFINE(ACE_RW_Process_Mutex)

const ACE_TCHAR *
ACE_RW_Process_Mutex::unique_name ()
{
  ACE::unique_name (this, this->name_, ACE_UNIQUE_NAME_LEN);
  return this->name_;
}

ACE_RW_Process_Mutex::ACE_RW_Process_Mutex (const ACE_TCHAR *name,
                                            int flags,
                                            mode_t mode )
  : lock_ (name ? name : unique_name (), flags, mode)
{
// ACE_TRACE ("ACE_RW_Process_Mutex::ACE_RW_Process_Mutex");
}

ACE_RW_Process_Mutex::~ACE_RW_Process_Mutex ()
{
// ACE_TRACE ("ACE_RW_Process_Mutex::~ACE_RW_Process_Mutex");
}

void
ACE_RW_Process_Mutex::dump () const
{
#if defined (ACE_HAS_DUMP)
// ACE_TRACE ("ACE_RW_Process_Mutex::dump");
  ACELIB_DEBUG ((LM_DEBUG, ACE_BEGIN_DUMP, this));
  this->lock_.dump ();
  ACELIB_DEBUG ((LM_DEBUG, ACE_END_DUMP));
#endif /* ACE_HAS_DUMP */
}

ACE_END_VERSIONED_NAMESPACE_DECL
