#include "ace/Trace.h"

// Turn off tracing for the duration of this file.
#if defined (ACE_NTRACE)
#undef ACE_NTRACE
#endif /* ACE_NTRACE */
#define ACE_NTRACE 1

#include "ace/Log_Category.h"
#include "ace/Object_Manager_Base.h"
#if defined (ACE_HAS_ALLOC_HOOKS)
# include "ace/Malloc_Base.h"
#endif /* ACE_HAS_ALLOC_HOOKS */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// = Static initialization.

// Keeps track of how far to indent per trace call.
int ACE_Trace::nesting_indent_ = ACE_Trace::DEFAULT_INDENT;

// Is tracing enabled?
bool ACE_Trace::enable_tracing_ = ACE_Trace::DEFAULT_TRACING;

ACE_ALLOC_HOOK_DEFINE(ACE_Trace)

void
ACE_Trace::dump () const
{
#if defined (ACE_HAS_DUMP)
#endif /* ACE_HAS_DUMP */
}

// Determine whether or not tracing is enabled

bool
ACE_Trace::is_tracing ()
{
  return ACE_Trace::enable_tracing_;
}

// Enable the tracing facility.

void
ACE_Trace::start_tracing ()
{
  ACE_Trace::enable_tracing_ = true;
}

// Disable the tracing facility.

void
ACE_Trace::stop_tracing ()
{
  ACE_Trace::enable_tracing_ = false;
}

// Change the nesting indentation level.

void
ACE_Trace::set_nesting_indent (int indent)
{
  ACE_Trace::nesting_indent_ = indent;
}

// Get the nesting indentation level.

int
ACE_Trace::get_nesting_indent ()
{
  return ACE_Trace::nesting_indent_;
}

// Perform the first part of the trace, which prints out the string N,
// the LINE, and the ACE_FILE as the function is entered.

ACE_Trace::ACE_Trace (const ACE_TCHAR *n,
                      int line,
                      const ACE_TCHAR *file)
{
#if defined (ACE_NLOGGING)
  ACE_UNUSED_ARG (line);
  ACE_UNUSED_ARG (file);
#endif /* ACE_NLOGGING */

  this->name_ = n;

  // If ACE has not yet been initialized, don't try to trace... there's
  // too much stuff not yet initialized.
  if (ACE_Trace::enable_tracing_ && !ACE_OS_Object_Manager::starting_up ())
    {
      ACE_Log_Msg *lm = ACE_LOG_MSG;
      if (lm->tracing_enabled ()
          && lm->trace_active () == 0)
        {
          lm->trace_active (1);
          ACELIB_DEBUG ((LM_TRACE,
                      ACE_TEXT ("%*s(%t) calling %s in file `%s' on line %d\n"),
                      ACE_Trace::nesting_indent_ * lm->inc (),
                      ACE_TEXT (""),
                      this->name_,
                      file,
                      line));
          lm->trace_active (0);
        }
    }
}

// Perform the second part of the trace, which prints out the NAME as
// the function is exited.

ACE_Trace::~ACE_Trace ()
{
  // If ACE has not yet been initialized, don't try to trace... there's
  // too much stuff not yet initialized.
  if (ACE_Trace::enable_tracing_ && !ACE_OS_Object_Manager::starting_up ())
    {
      ACE_Log_Msg *lm = ACE_LOG_MSG;
      if (lm->tracing_enabled ()
          && lm->trace_active () == 0)
        {
          lm->trace_active (1);
          ACELIB_DEBUG ((LM_TRACE,
                      ACE_TEXT ("%*s(%t) leaving %s\n"),
                      ACE_Trace::nesting_indent_ * lm->dec (),
                      ACE_TEXT (""),
                      this->name_));
          lm->trace_active (0);
        }
    }
}

ACE_END_VERSIONED_NAMESPACE_DECL
