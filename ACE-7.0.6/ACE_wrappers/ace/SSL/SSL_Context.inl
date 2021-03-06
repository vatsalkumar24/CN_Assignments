// -*- C++ -*-
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_SSL_Data_File::ACE_SSL_Data_File ()
  : type_ (-1)
{
}

ACE_INLINE
ACE_SSL_Data_File::ACE_SSL_Data_File (const char *file_name,
                                      int type)
  : file_name_ (file_name),
    type_ (type)
{
}

ACE_INLINE const char *
ACE_SSL_Data_File::file_name () const
{
  return this->file_name_.c_str ();
}

ACE_INLINE int
ACE_SSL_Data_File::type () const
{
  return this->type_;
}

// ****************************************************************

ACE_INLINE void
ACE_SSL_Context::check_context ()
{
  if (this->context_ == 0)
    {
      this->set_mode ();
    }

  if (this->context_ != 0)
    {
      ::SSL_CTX_set_verify (this->context_, this->default_verify_mode (),
                            this->default_verify_callback ());
    }
}

ACE_INLINE SSL_CTX *
ACE_SSL_Context::context ()
{
  this->check_context ();
  return this->context_;
}

ACE_INLINE int
ACE_SSL_Context::private_key_type () const
{
  return this->private_key_.type ();
}

ACE_INLINE const char*
ACE_SSL_Context::private_key_file_name () const
{
  return this->private_key_.file_name ();
}

ACE_INLINE int
ACE_SSL_Context::certificate_type () const
{
  return this->certificate_.type ();
}

ACE_INLINE const char*
ACE_SSL_Context::certificate_file_name () const
{
  return this->certificate_.file_name ();
}

ACE_INLINE int
ACE_SSL_Context::dh_params_file_type () const
{
  return this->dh_params_.type ();
}

ACE_INLINE const char*
ACE_SSL_Context::dh_params_file_name () const
{
  return this->dh_params_.file_name ();
}

ACE_INLINE void
ACE_SSL_Context::default_verify_mode (int mode)
{
  this->default_verify_mode_ = mode;
}

ACE_INLINE int
ACE_SSL_Context::default_verify_mode () const
{
  return this->default_verify_mode_;
}

ACE_INLINE void
ACE_SSL_Context::default_verify_callback (extern_C_CallBackVerify_t  callback)
{
  this->default_verify_callback_ = callback;
}

ACE_INLINE extern_C_CallBackVerify_t  ACE_SSL_Context::default_verify_callback() const
{
  return this->default_verify_callback_;
}

ACE_INLINE int
ACE_SSL_Context::get_mode () const
{
  return this->mode_;
}

ACE_INLINE int
ACE_SSL_Context::have_trusted_ca () const
{
  return this->have_ca_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
