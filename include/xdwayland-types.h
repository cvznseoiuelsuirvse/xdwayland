#ifndef XDWAYLAND_TYPES_H
#define XDWAYLAND_TYPES_H

#include <stdint.h>
#include <stdio.h>

#ifdef __GNUC__
#define XDWL_MUST_CHECK __attribute__((warn_unused_result))
#else
#define XDWL_MUST_CHECK
#endif

typedef unsigned int xdwl_id;

struct xdwl_map_pair {
  size_t key;
  void *value;
  struct xdwl_map_pair *next;
  struct xdwl_map_pair *prev;
};

typedef struct xdwl_map {
  struct xdwl_map_pair **pairs;
  size_t size;
} xdwl_map;

typedef union xdwl_arg {
  xdwl_id object_id;
  int32_t i;
  uint32_t u;
  float f;
  char *s;
  int fd;
} xdwl_arg;

typedef struct xdwl_proxy {
  int sockfd;
  xdwl_map *object_registry;
  struct xdwl_bitmap *client_id_pool;
  struct xdwl_bitmap *server_id_pool;
  xdwl_map *event_listeners;
  uint32_t seq;
} xdwl_proxy;

typedef struct xdwl_object {
  xdwl_id id;
  char *name;
  const struct xdwl_interface *interface;
  uint32_t seq;
} xdwl_object;

typedef struct xdwl_bitmap {
  uint8_t *bytes;
  size_t size;
} xdwl_bitmap;

typedef struct xdwl_list {
  void *data;
  struct xdwl_list *prev;
  struct xdwl_list *next;
} xdwl_list;

struct xdwl_method {
  char *name;
  size_t arg_count;
  char *signature;
};

struct xdwl_interface {
  char *name;
  const struct xdwl_method *requests;
  const struct xdwl_method *events;
};

enum xdwl_errors {
  XDWLERR_STD = 1,
  XDWLERR_ENV,
  XDWLERR_IDTAKEN,
  XDWLERR_NULLARG,
  XDWLERR_NULLOBJ,
  XDWLERR_NULLREQ,
  XDWLERR_NULLEVENT,
  XDWLERR_NULLIFACE,
  XDWLERR_NULLLISTNR,
  XDWLERR_SOCKCONN,
  XDWLERR_SOCKSEND,
  XDWLERR_SOCKRECV,
  XDWLERR_NOFREEBIT,
  XDWLERR_OUTOFRANGE,
  XDWLERR_NOPROTOXML,
};

typedef void(xdwl_event_handler)(void *, xdwl_arg *);

#endif
