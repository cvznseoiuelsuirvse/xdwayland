#ifndef XDWAYLAND_COLLECTIONS_H
#define XDWAYLAND_COLLECTIONS_H

#include "xdwayland-types.h"
#include <stdio.h>

#define xdwl_list_for_each(pos, head, member)                                  \
  for (pos = (head); pos->next && ((member = pos->data), 1); pos = pos->next)

#define xdwl_map_for_each(m, p)                                                \
  for (size_t __i = 0; __i < (m)->size; __i++)                                 \
    for ((p) = (m)->pairs[__i]; (p) != NULL; (p) = (p)->next)

xdwl_map *xdwl_map_new(size_t size);
void xdwl_map_destroy(xdwl_map *m);
XDWL_MUST_CHECK void *xdwl_map_set(xdwl_map *m, size_t key, void *value,
                                   size_t value_size);
XDWL_MUST_CHECK void *xdwl_map_set_str(xdwl_map *m, const char *key_str,
                                       void *value, size_t value_size);
void xdwl_map_remove(xdwl_map *m, size_t key);
void xdwl_map_remove_str(xdwl_map *m, const char *key_str);
void *xdwl_map_get(xdwl_map *m, size_t key);
void *xdwl_map_get_str(xdwl_map *m, const char *key_str);

xdwl_list *xdwl_list_new();
void xdwl_list_destroy(xdwl_list *l);
XDWL_MUST_CHECK void *xdwl_list_push(xdwl_list *l, void *data,
                                     size_t data_size);
void xdwl_list_remove(xdwl_list **head, size_t n);
XDWL_MUST_CHECK void *xdwl_list_get(xdwl_list *l, size_t n);
size_t xdwl_list_len(xdwl_list *l);

xdwl_bitmap *xdwl_bitmap_new(uint32_t limit);
void xdwl_bitmap_destroy(xdwl_bitmap *bm);
XDWL_MUST_CHECK int xdwl_bitmap_set(xdwl_bitmap *bm, uint32_t n);
XDWL_MUST_CHECK uint8_t xdwl_bitmap_get(xdwl_bitmap *bm, uint32_t n);
XDWL_MUST_CHECK uint32_t xdwl_bitmap_get_free(xdwl_bitmap *bm);
XDWL_MUST_CHECK int xdwl_bitmap_unset(xdwl_bitmap *bm, uint32_t n);

#endif
