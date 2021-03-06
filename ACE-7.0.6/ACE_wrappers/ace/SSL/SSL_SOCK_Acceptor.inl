// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_SSL_SOCK_Acceptor::ACE_SSL_SOCK_Acceptor ()
  : acceptor_ ()
{
  ACE_TRACE ("ACE_SSL_SOCK_Acceptor::ACE_SSL_SOCK_Acceptor");
}

ACE_INLINE
ACE_SSL_SOCK_Acceptor::ACE_SSL_SOCK_Acceptor (const ACE_Addr &local_sap,
                                              int reuse_addr,
                                              int protocol_family,
                                              int backlog,
                                              int protocol,
                                              int ipv6_only)
  : acceptor_ (local_sap,
               reuse_addr,
               protocol_family,
               backlog,
               protocol,
               ipv6_only)
{
  ACE_TRACE ("ACE_SSL_SOCK_Acceptor::ACE_SSL_SOCK_Acceptor");

  this->set_handle (this->acceptor_.get_handle ());
}

ACE_INLINE
ACE_SSL_SOCK_Acceptor::ACE_SSL_SOCK_Acceptor (const ACE_Addr &local_sap,
                                              ACE_Protocol_Info *protocolinfo,
                                              ACE_SOCK_GROUP g,
                                              u_long flags,
                                              int reuse_addr,
                                              int protocol_family,
                                              int backlog,
                                              int protocol,
                                              int ipv6_only)
  : acceptor_ (local_sap,
               protocolinfo,
               g,
               flags,
               reuse_addr,
               protocol_family,
               backlog,
               protocol,
               ipv6_only)
{
  ACE_TRACE ("ACE_SSL_SOCK_Acceptor::ACE_SSL_SOCK_Acceptor");

  this->set_handle (this->acceptor_.get_handle ());
}

ACE_INLINE int
ACE_SSL_SOCK_Acceptor::open (const ACE_Addr &local_sap,
                             int reuse_addr,
                             int protocol_family,
                             int backlog,
                             int protocol,
                             int ipv6_only)
{
  ACE_TRACE ("ACE_SSL_SOCK_Acceptor::open");
  if (this->acceptor_.open (local_sap,
                            reuse_addr,
                            protocol_family,
                            backlog,
                            protocol,
                            ipv6_only) != 0)
    return -1;
  else
    this->set_handle (this->acceptor_.get_handle ());

  return 0;
}

ACE_INLINE int
ACE_SSL_SOCK_Acceptor::close ()
{
  ACE_TRACE ("ACE_SSL_SOCK_Acceptor::close ()");

  int const result = this->acceptor_.close ();
  this->set_handle (ACE_INVALID_HANDLE);

  return result;
}

ACE_END_VERSIONED_NAMESPACE_DECL
