// -*- c++ -*-
#ifndef JAWS_HTTP_10_REQUEST_H
#define JAWS_HTTP_10_REQUEST_H

#include "HTTPU/http_request.h"


class JAWS_HTTP_10_Request : public HTTP_Request, public HTTP_HCodes
{
public:

  JAWS_HTTP_10_Request (void);
  ~JAWS_HTTP_10_Request (void);

  int type () const;
  const char * method () const;
  const char * uri () const;
  const char * version () const;

  const char * path () const;
  void path (const char *);
  void set_status (int);

private:

  char *path_;
};

#endif /* JAWS_HTTP_10_REQUEST_H */
