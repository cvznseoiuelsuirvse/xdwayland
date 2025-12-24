#include "xdwayland-private.h"

#include <stdlib.h>
#include <string.h>

#define byte_index(n) ((n) / 8)
#define bit_index(n) ((n) % 8)

static size_t hash_string(const char *string) {
  size_t hash = 5381;
  int c;

  while ((c = *string++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

xdwl_map *xdwl_map_new(size_t size) {
  xdwl_map *m = malloc(sizeof(xdwl_map));
  if (m == NULL) {
    perror("malloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_map_new: failed to malloc()");
    return NULL;
  }

  m->size = size;
  m->pairs = calloc(size, sizeof(void *));
  if (m->pairs == NULL) {
    perror("calloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_map_new: failed to calloc()");
    free(m);
    return NULL;
  }

  return m;
}

void xdwl_map_destroy(xdwl_map *m) {
  if (m) {
    for (size_t i = 0; i < m->size; i++) {
      struct xdwl_map_pair *pair = m->pairs[i];
      while (pair) {
        struct xdwl_map_pair *next = pair->next;
        free(pair->value);
        free(pair);
        pair = next;
      }
    }
  }

  free(m->pairs);
  free(m);
}

void *xdwl_map_set(xdwl_map *m, size_t key, void *value, size_t value_size) {
  size_t n = key % m->size;

  struct xdwl_map_pair *new_pair = malloc(sizeof(struct xdwl_map_pair));
  struct xdwl_map_pair *current_pair = m->pairs[n];

  new_pair->prev = NULL;
  new_pair->next = current_pair;
  new_pair->key = key;

  new_pair->value = malloc(value_size);
  if (!new_pair) {
    perror("malloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_map_set: failed to malloc() new value");
    return NULL;
  }
  memcpy(new_pair->value, value, value_size);
  if (current_pair) {
    current_pair->prev = new_pair;
  }

  m->pairs[n] = new_pair;

  return new_pair->value;
};

void *xdwl_map_set_str(xdwl_map *m, const char *key_str, void *value,
                       size_t value_size) {
  size_t key = hash_string(key_str);
  return xdwl_map_set(m, key, value, value_size);
};

void xdwl_map_remove(xdwl_map *m, size_t key) {
  size_t n = key % m->size;
  struct xdwl_map_pair *pair = m->pairs[n];

  for (; pair && pair->key != key; pair = pair->next)
    ;

  if (pair) {
    if (!pair->prev && !pair->next) { // first and only
      m->pairs[n] = NULL;

    } else if (!pair->prev) { // first
      pair->next->prev = NULL;
      m->pairs[n] = pair->next;

    } else if (!pair->next) { // last
      pair->prev->next = NULL;

    } else { // middle
      pair->prev->next = pair->next;
      pair->next->prev = pair->prev;
    }

    free(pair->value);
    free(pair);
  }
}

void xdwl_map_remove_str(xdwl_map *m, const char *key_str) {
  size_t key = hash_string(key_str);
  return xdwl_map_remove(m, key);
}

void *xdwl_map_get(xdwl_map *m, size_t key) {
  size_t n = key % m->size;
  struct xdwl_map_pair *pair = m->pairs[n];

  for (; pair && pair->key != key; pair = pair->next)
    ;

  if (pair)
    return pair->value;

  return NULL;
};

void *xdwl_map_get_str(xdwl_map *m, const char *key_str) {
  size_t key = hash_string(key_str);
  return xdwl_map_get(m, key);
}

xdwl_list *xdwl_list_new() {
  xdwl_list *l = malloc(sizeof(xdwl_list));
  if (l == NULL) {
    perror("malloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_list_new: failed to malloc()");
    return NULL;
  }

  l->data = NULL;
  l->next = NULL;
  l->prev = NULL;

  return l;
}

void xdwl_list_destroy(xdwl_list *l) {
  while (l) {
    xdwl_list *next = l->next;
    free(l->data);
    free(l);
    l = next;
  }
}

void *xdwl_list_push(xdwl_list *l, void *data, size_t data_size) {
  for (; l->next; l = l->next)
    ;

  l->next = xdwl_list_new();
  l->next->prev = l;

  l->data = malloc(data_size);
  if (!l->data) {
    perror("malloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_list_push: failed to malloc() data");
    return NULL;
  }
  memcpy(l->data, data, data_size);

  return l->data;
}

void xdwl_list_remove(xdwl_list **head, size_t n) {
  size_t i;
  xdwl_list *l = *head;

  for (i = 0; l; l = l->next, i++) {
    if (n == i) {
      if (l->prev) {
        l->prev->next = l->next;
      } else {
        *head = l->next;
      }

      l->next->prev = l->prev;
      free(l->data);
      free(l);
      break;
    }
  }
}

void *xdwl_list_get(xdwl_list *l, size_t n) {
  size_t i;
  for (i = 0; l->next; l = l->next, i++) {
    if (n == i) {
      return l->data;
    }
  }

  xdwl_error_set(XDWLERR_OUTOFRANGE, "xdwl_list_get: %ld is out of range", n);
  return NULL;
}

size_t xdwl_list_len(xdwl_list *l) {
  size_t i;
  if (!l)
    return 0;

  for (i = 0; l->next; l = l->next, i++)
    ;
  return i;
}

xdwl_bitmap *xdwl_bitmap_new(size_t size) {
  xdwl_bitmap *bm = malloc(sizeof(xdwl_bitmap));
  if (bm == NULL) {
    perror("malloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_bitmap_new: failed to malloc()");
    return NULL;
  }

  bm->bytes = calloc(1, size / 8);
  if (!bm->bytes) {
    perror("calloc");
    xdwl_error_set(XDWLERR_STD, "xdwl_bitmap_new: failed to calloc()");
    return NULL;
  }
  bm->size = size;

  return bm;
}

void xdwl_bitmap_destroy(xdwl_bitmap *bm) {
  if (!bm)
    return;

  free(bm->bytes);
  free(bm);
}

int xdwl_bitmap_set(xdwl_bitmap *bm, uint32_t n) {
  if (n > bm->size) {
    xdwl_error_set(XDWLERR_OUTOFRANGE, "xdwl_bitmap_set: %ld is out of range",
                   n);
    return -1;
  }

  bm->bytes[byte_index(n)] |= (1 << bit_index(n));
  return 0;
}

int xdwl_bitmap_get(xdwl_bitmap *bm, uint32_t n) {
  if (n > bm->size) {
    xdwl_error_set(XDWLERR_OUTOFRANGE, "xdwl_bitmap_get: %ld is out of range",
                   n);
    return -1;
  }

  return (bm->bytes[byte_index(n)] & (1 << bit_index(n))) != 0;
}

uint32_t xdwl_bitmap_get_free(xdwl_bitmap *bm) {
  for (size_t byte_i = 0; byte_i < bm->size / 8; byte_i++) {
    uint8_t byte = bm->bytes[byte_i];
    if ((byte & 0xff) != 0xff) {
      for (size_t bit_i = 0; bit_i < 8; bit_i++) {
        if (!(byte & (1 << bit_i))) {
          return byte_i * 8 + bit_i;
        }
      }
    }
  }

  xdwl_error_set(XDWLERR_NOFREEBIT, "xdwl_bitmap_get_free: no free bits found");
  return 0;
}

int xdwl_bitmap_unset(xdwl_bitmap *bm, uint32_t n) {
  if (n > bm->size) {
    xdwl_error_set(XDWLERR_OUTOFRANGE, "xdwl_bitmap_unset: %ld is out of range",
                   n);
    return -1;
  }

  bm->bytes[byte_index(n)] &= ~(1 << bit_index(n));
  return 0;
}
