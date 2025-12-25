#ifndef XDWAYLAND_CLIENT_H
#define XDWAYLAND_CLIENT_H

#include "xdwayland-types.h"

int xdwl_send_request(xdwl_proxy *proxy, xdwl_id object_id, char *object_name,
                      xdwl_id method_id, size_t arg_count, ...);

int xdwl_add_listener(xdwl_proxy *proxy, const char *object_name,
                      void *event_handlers, size_t event_handlers_size,
                      void *user_data);

xdwl_proxy *xdwl_proxy_create();
void xdwl_proxy_destroy(xdwl_proxy *proxy);

XDWL_MUST_CHECK int xdwl_roundtrip(xdwl_proxy *proxy);
XDWL_MUST_CHECK int xdwl_dispatch(xdwl_proxy *proxy);

struct xdwl_object *xdwl_object_get_by_id(xdwl_proxy *proxy, xdwl_id object_id);
struct xdwl_object *xdwl_object_get_by_name(xdwl_proxy *proxy,
                                            const char *object_name);
XDWL_MUST_CHECK xdwl_id xdwl_object_register(xdwl_proxy *proxy,
                                             xdwl_id object_id,
                                             const char *object_name);
XDWL_MUST_CHECK int xdwl_object_unregister(xdwl_proxy *proxy,
                                           xdwl_id object_id);
XDWL_MUST_CHECK int xdwl_object_unregister_last(xdwl_proxy *proxy,
                                                const char *object_name);

void xdwl_interface_register(const struct xdwl_interface *interface);
void xdwl_error_print();

#endif
