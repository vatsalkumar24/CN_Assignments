#include "ace/DEV_IO.h"
#include "ace/Log_Category.h"
#if defined (ACE_HAS_ALLOC_HOOKS)
# include "ace/Malloc_Base.h"
#endif /* ACE_HAS_ALLOC_HOOKS */

#if !defined (__ACE_INLINE__)
#include "ace/DEV_IO.inl"
#endif /* __ACE_INLINE__ */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_ALLOC_HOOK_DEFINE(ACE_DEV_IO)

// Return the local endpoint address.

int
ACE_DEV_IO::get_local_addr (ACE_DEV_Addr &addr) const
{
  ACE_TRACE ("ACE_DEV_IO::get_local_addr");

  addr = this->addr_;
  return 0;
}

// Return the address of the remotely connected peer (if there is
// one).

int
ACE_DEV_IO::get_remote_addr (ACE_DEV_Addr &addr) const
{
  ACE_TRACE ("ACE_DEV_IO::get_remote_addr");
  addr = this->addr_;
  return 0;
}

void
ACE_DEV_IO::dump () const
{
#if defined (ACE_HAS_DUMP)
  ACE_TRACE ("ACE_DEV_IO::dump");

  ACELIB_DEBUG ((LM_DEBUG, ACE_BEGIN_DUMP, this));
  this->addr_.dump ();
  ACELIB_DEBUG ((LM_DEBUG, ACE_END_DUMP));
#endif /* ACE_HAS_DUMP */
}

// Simple-minded do nothing constructor.

ACE_DEV_IO::ACE_DEV_IO ()
{
  ACE_TRACE ("ACE_DEV_IO::ACE_DEV_IO");
}

// Send N char *ptrs and int lengths.  Note that the char *'s precede
// the ints (basically, an varargs version of writev).  The count N is
// the *total* number of trailing arguments, *not* a couple of the
// number of tuple pairs!

ssize_t
ACE_DEV_IO::send (size_t n, ...) const
{
  ACE_TRACE ("ACE_DEV_IO::send");
#ifdef ACE_LACKS_VA_FUNCTIONS
  ACE_UNUSED_ARG (n);
  ACE_NOTSUP_RETURN (-1);
#else
  va_list argp;
  int total_tuples = static_cast<int> (n / 2);
  iovec *iovp;
#if defined (ACE_HAS_ALLOCA)
  iovp = (iovec *) alloca (total_tuples * sizeof (iovec));
#else
# ifdef ACE_HAS_ALLOC_HOOKS
  ACE_ALLOCATOR_RETURN (iovp, (iovec *)
                        ACE_Allocator::instance ()->malloc (total_tuples *
                                                            sizeof (iovec)),
                        -1);
# else
  ACE_NEW_RETURN (iovp,
                  iovec[total_tuples],
                  -1);
# endif /* ACE_HAS_ALLOC_HOOKS */
#endif /* !defined (ACE_HAS_ALLOCA) */

  va_start (argp, n);

  for (int i = 0; i < total_tuples; i++)
    {
      iovp[i].iov_base = va_arg (argp, char *);
      iovp[i].iov_len  = va_arg (argp, int);
    }

  ssize_t result = ACE_OS::writev (this->get_handle (), iovp, total_tuples);
#if !defined (ACE_HAS_ALLOCA)
# ifdef ACE_HAS_ALLOC_HOOKS
  ACE_Allocator::instance ()->free (iovp);
# else
  delete [] iovp;
# endif /* ACE_HAS_ALLOC_HOOKS */
#endif /* !defined (ACE_HAS_ALLOCA) */
  va_end (argp);
  return result;
#endif // ACE_LACKS_VA_FUNCTIONS
}

// This is basically an interface to ACE_OS::readv, that doesn't use the
// struct iovec explicitly.  The ... can be passed as an arbitrary
// number of (char *ptr, int len) tuples.  However, the count N is the
// *total* number of trailing arguments, *not* a couple of the number
// of tuple pairs!

ssize_t
ACE_DEV_IO::recv (size_t n, ...) const
{
  ACE_TRACE ("ACE_DEV_IO::recv");
#ifdef ACE_LACKS_VA_FUNCTIONS
  ACE_UNUSED_ARG (n);
  ACE_NOTSUP_RETURN (-1);
#else
  va_list argp;
  int total_tuples = static_cast<int> (n / 2);
  iovec *iovp;
#if defined (ACE_HAS_ALLOCA)
  iovp = (iovec *) alloca (total_tuples * sizeof (iovec));
#else
# ifdef ACE_HAS_ALLOC_HOOKS
  ACE_ALLOCATOR_RETURN (iovp, (iovec *)
                        ACE_Allocator::instance ()->malloc (total_tuples *
                                                            sizeof (iovec)),
                        -1);
# else
  ACE_NEW_RETURN (iovp,
                  iovec[total_tuples],
                  -1);
# endif /* ACE_HAS_ALLOC_HOOKS */
#endif /* !defined (ACE_HAS_ALLOCA) */

  va_start (argp, n);

  for (int i = 0; i < total_tuples; i++)
    {
      iovp[i].iov_base = va_arg (argp, char *);
      iovp[i].iov_len  = va_arg (argp, int);
    }

  ssize_t result = ACE_OS::readv (this->get_handle (), iovp, total_tuples);
#if !defined (ACE_HAS_ALLOCA)
# ifdef ACE_HAS_ALLOC_HOOKS
  ACE_Allocator::instance ()->free (iovp);
# else
  delete [] iovp;
# endif /* ACE_HAS_ALLOC_HOOKS */
#endif /* !defined (ACE_HAS_ALLOCA) */
  va_end (argp);
  return result;
#endif // ACE_LACKS_VA_FUNCTIONS
}

ACE_END_VERSIONED_NAMESPACE_DECL
