// ============================================================================
/**
 * @file INET_Addr_Test_IPV6.cpp
 *
 * @brief  Additional tests on the ACE_INET_Addr class above and beyond
 * those found in INET_Addr_Test. These primarily focus on additional
 * functionality and bug fixes to ACE_INET_Addr.
 *
 * @author John Aughey <jha@aughey.com>
 *         Brian Buesker <bbuesker@qualcomm.com>
 */
// ============================================================================

#include "test_config.h"
#include "ace/OS_NS_string.h"
#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_arpa_inet.h"

#if defined (ACE_HAS_IPV6)

#define LINK_LOCAL_ADDR ACE_TEXT ("fe80::")
#define SITE_LOCAL_ADDR ACE_TEXT ("fec0::")
#define THE_INTERFACE ("eth0")

// Make sure that ACE_Addr::addr_type_ is the same
// as the family of the inet_addr_.
static int check_type_consistency (const ACE_INET_Addr &addr)
{
  int family = -1;

  if (addr.get_type () == AF_INET)
    {
      struct sockaddr_in *sa4 = (struct sockaddr_in *)addr.get_addr();
      family = sa4->sin_family;
    }
  else if (addr.get_type () == AF_INET6)
    {
      struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)addr.get_addr();
      family = sa6->sin6_family;
    }

  if (addr.get_type () != family)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("Inconsistency between ACE_SOCK::addr_type_ (%d) ")
                  ACE_TEXT ("and the sockaddr family (%d)\n"),
                  addr.get_type (),
                  family));
      return 1;
    }
  return 0;
}

// A test to ensure ACE_INET_Addr can select the protocol family.
static bool check_both_families()
{
  bool good = true;
  ACE_INET_Addr a;
  if (-1 == a.set(ACE_TEXT (""), ACE_TEXT ("www.google.com"), ACE_TEXT ("tcp")))
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%p\n"),
                  ACE_TEXT ("both test 4, www.google.com")));
      good = false;
    }
  else
    {
      ACE_TCHAR str[1000];
      a.addr_to_string (str, 1000, 1);
      ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("got type %d, addr %s\n"), a.get_type(), str));
      // Should have selected IPv4.
      if (a.get_type() != AF_INET)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("Wrong address family, expecting IPv4\n")));
          good = false;
        }
    }

  ACE_INET_Addr b;
  if (-1 == b.set(ACE_TEXT(""), ACE_TEXT("www.google.com"), ACE_TEXT("tcp6")))
    {
      ACE_ERROR((LM_ERROR,
                 ACE_TEXT("%p\n"),
                 ACE_TEXT("both test 6, www.google.com")));
      good = false;
    }
  else
    {
      ACE_TCHAR str[1000];
      b.addr_to_string(str, 1000, 1);
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("got type %d, addr %s\n"), b.get_type(), str));
      // Should have selected IPv6.
      if (b.get_type() != AF_INET6)
        {
          ACE_ERROR((LM_ERROR,
                     ACE_TEXT("Wrong address family, expecting IPv6\n")));
          good = false;
        }
    }
  return good;
}
#endif /* ACE_HAS_IPV6 */


int run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("INET_Addr_Test_IPV6"));

  int status = 0;     // Innocent until proven guilty

#if defined (ACE_HAS_IPV6)
  if (ACE::ipv6_enabled ())
    {
      ACE_INET_Addr addr ("::");

      // this should switch it back to an IPv4 address
      addr.set (80);

      if (AF_INET != addr.get_type())
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("set failed: Address type %d != AF_INET\n"),
                      addr.get_type()));
          status = 1;
        }

      // this should get mapped to an IPv6 address
      addr.set (80, ACE_UINT32 (INADDR_ANY), 1, 1);

      if (AF_INET6 != addr.get_type())
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("set failed: Address type %d != AF_INET6\n"),
                      addr.get_type()));
          status = 1;
        }

      // Test for ACE_INET_Addr::set_addr().
      struct in_addr addrv4;

      ACE_OS::inet_pton (AF_INET, "127.0.0.1", &addrv4);

      struct sockaddr_in sa4;
      sa4.sin_family = AF_INET;
      sa4.sin_addr = addrv4;
      sa4.sin_port = ACE_HTONS (8080);

      addr.set (0, ACE_UINT32 (1), 1);

      // test to make sure this doesn't get mapped to an IPv6 address
      addr.set_addr (&sa4, sizeof(sa4), 0);

      if (addr.get_type() != AF_INET)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT
                      ("set_addr failed: Address type %d != AF_INET\n"),
                      addr.get_type()));
          status = 1;
        }

      // now test to make sure it does get mapped to an IPv6 address
      addr.set_addr (&sa4, sizeof(sa4), 1);

      if (addr.get_type() != AF_INET6)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT
                      ("set_addr failed: Address type %d != AF_INET6\n"),
                      addr.get_type()));
          status = 1;
        }

     // test to make sure that the type gets set correctly when set is
     // called with another ACE_INET_Addr
     addr.set (0, ACE_UINT32 (1), 1);

     ACE_INET_Addr addrIPv6 ((u_short) 0, ACE_IPV6_LOCALHOST);

     addr.set (addrIPv6);

     status |= check_type_consistency (addr);

#if defined (ACE_LINUX)
      // test a link local address to make sure the set_interface method works
      ACE_INET_Addr link_local_addr (80, LINK_LOCAL_ADDR);
      if (!link_local_addr.is_linklocal())
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("IPv6 is_linklocal failed\n")));
          status = 1;
        }

      if (0 != ACE_OS::strcmp (ACE_TEXT_CHAR_TO_TCHAR(link_local_addr.get_host_addr ()),
                               LINK_LOCAL_ADDR))
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("IPv6 get_host_addr failed: %s != %s\n"),
                      link_local_addr.get_host_addr (),
                      LINK_LOCAL_ADDR));
          status = 1;
        }

      if (-1 == link_local_addr.set_interface (THE_INTERFACE))
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("%p\n"),
                      ACE_TEXT ("IPv6 set_interface failed\n")));
          status = 1;
        }

      // test a site local address
      ACE_INET_Addr site_local_addr (80, SITE_LOCAL_ADDR);
      if (!site_local_addr.is_sitelocal())
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("IPv6 is_sitelocal failed\n")));
          status = 1;
        }

#endif /* ACE_LINUX */
    }

  if (!check_both_families())
    status = 1;

#endif /* ACE_HAS_IPV6 */

  ACE_END_TEST;

  return status;
}
