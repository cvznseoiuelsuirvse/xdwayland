#include "xdwayland-client.h"
#include <stdarg.h>

static enum xdwl_errors xdwl_errcode = 0;
static char xdwl_errmsg[1024];

void xdwl_error_set(enum xdwl_errors errcode, const char *errmsg, ...) {
  xdwl_errcode = errcode;
  va_list args;
  va_start(args, errmsg);
  vsnprintf(xdwl_errmsg, sizeof(xdwl_errmsg), errmsg, args);
  va_end(args);
}

void xdwl_error_print() {
  if (xdwl_errcode >= 0) {
    fprintf(stderr, "%s\n", xdwl_errmsg);
    xdwl_errcode = 0;
  }
}

enum xdwl_errors xdwl_error_get_code() { return xdwl_errcode; }
