
// -*- C++ -*-
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl Framework_Component_DLL
// ------------------------------
#ifndef FRAMEWORK_COMPONENT_DLL_EXPORT_H
#define FRAMEWORK_COMPONENT_DLL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (FRAMEWORK_COMPONENT_DLL_HAS_DLL)
#  define FRAMEWORK_COMPONENT_DLL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ! TEST_HAS_DLL */

#if !defined (FRAMEWORK_COMPONENT_DLL_HAS_DLL)
#  define FRAMEWORK_COMPONENT_DLL_HAS_DLL 1
#endif /* ! FRAMEWORK_COMPONENT_DLL_HAS_DLL */

#if defined (FRAMEWORK_COMPONENT_DLL_HAS_DLL) && (FRAMEWORK_COMPONENT_DLL_HAS_DLL == 1)
#  if defined (FRAMEWORK_COMPONENT_DLL_BUILD_DLL)
#    define Framework_Component_DLL_Export ACE_Proper_Export_Flag
#    define FRAMEWORK_COMPONENT_DLL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define FRAMEWORK_COMPONENT_DLL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* FRAMEWORK_COMPONENT_DLL_BUILD_DLL */
#    define Framework_Component_DLL_Export ACE_Proper_Import_Flag
#    define FRAMEWORK_COMPONENT_DLL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define FRAMEWORK_COMPONENT_DLL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* FRAMEWORK_COMPONENT_DLL_BUILD_DLL */
#else /* FRAMEWORK_COMPONENT_DLL_HAS_DLL == 1 */
#  define Framework_Component_DLL_Export
#  define FRAMEWORK_COMPONENT_DLL_SINGLETON_DECLARATION(T)
#  define FRAMEWORK_COMPONENT_DLL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* FRAMEWORK_COMPONENT_DLL_HAS_DLL == 1 */

// Set FRAMEWORK_COMPONENT_DLL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (FRAMEWORK_COMPONENT_DLL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define FRAMEWORK_COMPONENT_DLL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define FRAMEWORK_COMPONENT_DLL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !FRAMEWORK_COMPONENT_DLL_NTRACE */

#if (FRAMEWORK_COMPONENT_DLL_NTRACE == 1)
#  define FRAMEWORK_COMPONENT_DLL_TRACE(X)
#else /* (FRAMEWORK_COMPONENT_DLL_NTRACE == 1) */
#  define FRAMEWORK_COMPONENT_DLL_TRACE(X) ACE_TRACE_IMPL(X)
#endif /* (FRAMEWORK_COMPONENT_DLL_NTRACE == 1) */

#endif /* FRAMEWORK_COMPONENT_DLL_EXPORT_H */

// End of auto generated file.
