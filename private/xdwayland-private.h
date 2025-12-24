#ifndef XDWL_PRIVATE_H
#define XDWL_PRIVATE_H

#include "xdwayland-types.h"
#include <stdint.h>
#include <stdio.h>

struct xdwl_raw_message {
  xdwl_id object_id;
  xdwl_id method_id;
  size_t body_length;
  char *body;
  int fd;
};

struct xdwl_listener {
  void *event_handlers;
  void *user_data;
};

void xdwl_log(const char *level, const char *message, ...);
void xdwl_show_args(xdwl_arg *args, char *signature);

void xdwl_error_set(enum xdwl_errors errcode, const char *errmsg, ...);
enum xdwl_errors xdwl_error_get_code();

void xdwl_buf_write_u32(void *buffer, size_t *buf_size, uint32_t n);
void xdwl_buf_write_u16(void *buffer, size_t *buf_size, uint16_t n);
void xdwl_write_args(char *buffer, size_t *offset, xdwl_arg *args,
                     size_t arg_count, char *signature);

uint32_t xdwl_buf_read_u32(void *buffer, size_t *buf_size);
uint16_t xdwl_buf_read_u16(void *buffer, size_t *buf_size);
int xdwl_read_args(struct xdwl_raw_message *message, xdwl_arg *args,
                   const char *signature);
uint16_t xdwl_calculate_body_size(xdwl_arg *args, size_t arg_count,
                                  char *signature);

#endif
