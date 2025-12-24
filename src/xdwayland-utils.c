#include "xdwayland-private.h"
#include "xdwayland-types.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define CAP 4096
#define PADDED4(n) ((n + 4) & ~3)

void print_buffer(char *buffer, size_t buffer_len) {
  for (size_t i = 0; i < buffer_len; i++) {
    uint8_t c = buffer[i];
    if (32 <= c && c <= 126) {
      printf("%c ", c);
    } else {
      printf("%02x ", c);
    }
  }
  printf("\n");
}

void xdwl_log(const char *level, const char *message, ...) {
  va_list args;
  time_t t;
  struct tm *tt;
  char timestamp_string[10];

  t = time(NULL);
  tt = localtime(&t);

  strftime(timestamp_string, sizeof(timestamp_string), "%H:%M:%S", tt);

  va_start(args, message);
  printf("[libxdwayland %s %s] ", timestamp_string, level);
  vprintf(message, args);

  va_end(args);
  fflush(stdout);
}

void xdwl_show_args(xdwl_arg *args, char *signature) {
  size_t argc = strlen(signature);
  printf("(");

  for (size_t i = 0; i < argc; i++) {
    char arg_type = signature[i];
    switch (arg_type) {
    case 'i':
      printf("%d", args[i].i);
      break;
    case 'u':
      printf("%u", args[i].u);
      break;
    case 'f':
      printf("%f", args[i].f);
      break;

    case 's':
      printf("\"%s\"", args[i].s);
      break;

    case 'h':
      printf("%d", args[i].fd);
      break;
    }
    if (i != argc - 1) {
      printf(", ");
    }
  }

  printf(")\n");
  fflush(stdout);
}

int xdwl_read_args(struct xdwl_raw_message *message, xdwl_arg *args,
                   const char *signature) {
  size_t arg_count = strlen(signature);
  size_t offset = 0;

  for (size_t i = 1; i <= arg_count; i++) {
    char arg_signature = signature[i - 1];
    switch (arg_signature) {
    case 'i':
      args[i].i = *(uint32_t *)(message->body + offset);
      offset += sizeof(uint32_t);
      break;

    case 'u':
      args[i].u = *(uint32_t *)(message->body + offset);
      offset += sizeof(uint32_t);
      break;

    case 'f':
      args[i].f = *(double *)(message->body + offset);
      offset += sizeof(double);
      break;

    case 's':
      offset += sizeof(uint32_t);

      args[i].s = (char *)(message->body + offset);
      offset += PADDED4(strlen(args[i].s));
      break;

    case 'h':
      args[i].fd = message->fd;
      break;
    }
  }

  return 0;
};

void xdwl_write_args(char *buffer, size_t *offset, xdwl_arg *args,
                     size_t arg_count, char *signature) {
  size_t string_length;

  for (size_t i = 0; i < arg_count; i++) {
    char arg_signature = signature[i];
    xdwl_arg arg = args[i];

    if (*offset >= CAP) {
      return;
    }

    switch (arg_signature) {
    case 'i':
      *(int32_t *)(buffer + *offset) = arg.i;
      *offset += sizeof(int32_t);
      break;

    case 'u':
      *(uint32_t *)(buffer + *offset) = arg.u;
      *offset += sizeof(uint32_t);
      break;

    case 'f':
      *(float *)(buffer + *offset) = arg.f;
      *offset += sizeof(float);
      break;

    case 's':
      // write normal string length
      string_length = strlen(arg.s);
      *(uint32_t *)(buffer + *offset) = string_length + 1;
      *offset += sizeof(uint32_t);

      // write padded string
      memset(buffer + *offset, 0, PADDED4(string_length));
      memcpy((char *)(buffer + *offset), arg.s, string_length);

      *offset += PADDED4(string_length);
      break;
    }
  }
}

void xdwl_buf_write_u32(void *buf, size_t *offset, uint32_t n) {
  *(uint32_t *)(buf + *offset) = n;
  *offset += sizeof(n);
}

void xdwl_buf_write_u16(void *buf, size_t *offset, uint16_t n) {
  *(uint16_t *)(buf + *offset) = n;
  *offset += sizeof(n);
}

uint32_t xdwl_buf_read_u32(void *buf, size_t *offset) {
  uint32_t value = *(uint32_t *)(buf + *offset);
  *offset += sizeof(value);

  return value;
}

uint16_t xdwl_buf_read_u16(void *buf, size_t *offset) {
  uint16_t value = *(uint16_t *)(buf + *offset);
  *offset += sizeof(value);

  return value;
}

uint16_t xdwl_calculate_body_size(xdwl_arg *args, size_t arg_count,
                                  char *signature) {
  uint16_t body_size = 0;

  for (size_t i = 0; i < arg_count; i++) {
    xdwl_arg arg = args[i];
    char arg_signature = signature[i];

    switch (arg_signature) {
    case 'i':
    case 'u':
    case 'f':
      body_size += sizeof(uint32_t);
      break;

    case 's':
      body_size += sizeof(uint32_t);
      body_size += PADDED4(strlen(arg.s) + 1);
      break;
    }
  };

  return body_size;
}
