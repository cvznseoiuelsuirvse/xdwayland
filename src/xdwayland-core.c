#include "xdwayland-client.h"
#include "xdwayland-core.h"


struct xdwl_display_event_handlers;int xdwl_display_add_listener(xdwl_proxy *proxy, struct xdwl_display_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_display", event_handlers, sizeof(void *) * 2, user_data);
};


int xdwl_display_sync(xdwl_proxy *proxy, xdwl_id _callback) {
    return xdwl_send_request(proxy, 1, "wl_display", 0, 1, _callback);
};
int xdwl_display_get_registry(xdwl_proxy *proxy, xdwl_id _registry) {
    return xdwl_send_request(proxy, 1, "wl_display", 1, 1, _registry);
};

static const struct xdwl_method xdwl_display_requests[] = {
    {"sync", 1, "u"},
    {"get_registry", 1, "u"},
};
static const struct xdwl_method xdwl_display_events[] = {
    {"error", 3, "uus"},
    {"delete_id", 1, "u"},
};
const struct xdwl_interface xdwl_display_interface = {
    .name = "wl_display",
    .requests = xdwl_display_requests,
    .events = xdwl_display_events,
};
struct xdwl_registry_event_handlers;int xdwl_registry_add_listener(xdwl_proxy *proxy, struct xdwl_registry_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_registry", event_handlers, sizeof(void *) * 2, user_data);
};


int xdwl_registry_bind(xdwl_proxy *proxy, xdwl_id wl_registry_id, uint32_t _name, const char *_interface, uint32_t _version, xdwl_id _new_id) {
    return xdwl_send_request(proxy, wl_registry_id, "wl_registry", 0, 4, _name, _interface, _version, _new_id);
};

static const struct xdwl_method xdwl_registry_requests[] = {
    {"bind", 4, "usuu"},
};
static const struct xdwl_method xdwl_registry_events[] = {
    {"global", 3, "usu"},
    {"global_remove", 1, "u"},
};
const struct xdwl_interface xdwl_registry_interface = {
    .name = "wl_registry",
    .requests = xdwl_registry_requests,
    .events = xdwl_registry_events,
};
struct xdwl_callback_event_handlers;int xdwl_callback_add_listener(xdwl_proxy *proxy, struct xdwl_callback_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_callback", event_handlers, sizeof(void *) * 1, user_data);
};

static const struct xdwl_method xdwl_callback_events[] = {
    {"done", 1, "u"},
};
const struct xdwl_interface xdwl_callback_interface = {
    .name = "wl_callback",
    .events = xdwl_callback_events,
};
int xdwl_compositor_create_surface(xdwl_proxy *proxy, xdwl_id wl_compositor_id, xdwl_id _id) {
    return xdwl_send_request(proxy, wl_compositor_id, "wl_compositor", 0, 1, _id);
};
int xdwl_compositor_create_region(xdwl_proxy *proxy, xdwl_id wl_compositor_id, xdwl_id _id) {
    return xdwl_send_request(proxy, wl_compositor_id, "wl_compositor", 1, 1, _id);
};

static const struct xdwl_method xdwl_compositor_requests[] = {
    {"create_surface", 1, "u"},
    {"create_region", 1, "u"},
};
const struct xdwl_interface xdwl_compositor_interface = {
    .name = "wl_compositor",
    .requests = xdwl_compositor_requests,
};
int xdwl_shm_pool_create_buffer(xdwl_proxy *proxy, xdwl_id wl_shm_pool_id, xdwl_id _id, int32_t _offset, int32_t _width, int32_t _height, int32_t _stride, xdwl_id _format) {
    return xdwl_send_request(proxy, wl_shm_pool_id, "wl_shm_pool", 0, 6, _id, _offset, _width, _height, _stride, _format);
};
int xdwl_shm_pool_destroy(xdwl_proxy *proxy, xdwl_id wl_shm_pool_id) {
    return xdwl_send_request(proxy, wl_shm_pool_id, "wl_shm_pool", 1, 0);
};
int xdwl_shm_pool_resize(xdwl_proxy *proxy, xdwl_id wl_shm_pool_id, int32_t _size) {
    return xdwl_send_request(proxy, wl_shm_pool_id, "wl_shm_pool", 2, 1, _size);
};

static const struct xdwl_method xdwl_shm_pool_requests[] = {
    {"create_buffer", 6, "uiiiiu"},
    {"destroy", 0, NULL},
    {"resize", 1, "i"},
};
const struct xdwl_interface xdwl_shm_pool_interface = {
    .name = "wl_shm_pool",
    .requests = xdwl_shm_pool_requests,
};
struct xdwl_shm_event_handlers;int xdwl_shm_add_listener(xdwl_proxy *proxy, struct xdwl_shm_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_shm", event_handlers, sizeof(void *) * 1, user_data);
};


int xdwl_shm_create_pool(xdwl_proxy *proxy, xdwl_id wl_shm_id, xdwl_id _id, int _fd, int32_t _size) {
    return xdwl_send_request(proxy, wl_shm_id, "wl_shm", 0, 3, _id, _fd, _size);
};
int xdwl_shm_release(xdwl_proxy *proxy, xdwl_id wl_shm_id) {
    return xdwl_send_request(proxy, wl_shm_id, "wl_shm", 1, 0);
};

static const struct xdwl_method xdwl_shm_requests[] = {
    {"create_pool", 3, "uhi"},
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_shm_events[] = {
    {"format", 1, "u"},
};
const struct xdwl_interface xdwl_shm_interface = {
    .name = "wl_shm",
    .requests = xdwl_shm_requests,
    .events = xdwl_shm_events,
};
struct xdwl_buffer_event_handlers;int xdwl_buffer_add_listener(xdwl_proxy *proxy, struct xdwl_buffer_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_buffer", event_handlers, sizeof(void *) * 1, user_data);
};


int xdwl_buffer_destroy(xdwl_proxy *proxy, xdwl_id wl_buffer_id) {
    return xdwl_send_request(proxy, wl_buffer_id, "wl_buffer", 0, 0);
};

static const struct xdwl_method xdwl_buffer_requests[] = {
    {"destroy", 0, NULL},
};
static const struct xdwl_method xdwl_buffer_events[] = {
    {"release", 0, NULL},
};
const struct xdwl_interface xdwl_buffer_interface = {
    .name = "wl_buffer",
    .requests = xdwl_buffer_requests,
    .events = xdwl_buffer_events,
};
struct xdwl_data_offer_event_handlers;int xdwl_data_offer_add_listener(xdwl_proxy *proxy, struct xdwl_data_offer_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_data_offer", event_handlers, sizeof(void *) * 3, user_data);
};


int xdwl_data_offer_accept(xdwl_proxy *proxy, xdwl_id wl_data_offer_id, xdwl_id _serial, const char *_mime_type) {
    return xdwl_send_request(proxy, wl_data_offer_id, "wl_data_offer", 0, 2, _serial, _mime_type);
};
int xdwl_data_offer_receive(xdwl_proxy *proxy, xdwl_id wl_data_offer_id, const char *_mime_type, int _fd) {
    return xdwl_send_request(proxy, wl_data_offer_id, "wl_data_offer", 1, 2, _mime_type, _fd);
};
int xdwl_data_offer_destroy(xdwl_proxy *proxy, xdwl_id wl_data_offer_id) {
    return xdwl_send_request(proxy, wl_data_offer_id, "wl_data_offer", 2, 0);
};
int xdwl_data_offer_finish(xdwl_proxy *proxy, xdwl_id wl_data_offer_id) {
    return xdwl_send_request(proxy, wl_data_offer_id, "wl_data_offer", 3, 0);
};
int xdwl_data_offer_set_actions(xdwl_proxy *proxy, xdwl_id wl_data_offer_id, xdwl_id _dnd_actions, xdwl_id _preferred_action) {
    return xdwl_send_request(proxy, wl_data_offer_id, "wl_data_offer", 4, 2, _dnd_actions, _preferred_action);
};

static const struct xdwl_method xdwl_data_offer_requests[] = {
    {"accept", 2, "us"},
    {"receive", 2, "sh"},
    {"destroy", 0, NULL},
    {"finish", 0, NULL},
    {"set_actions", 2, "uu"},
};
static const struct xdwl_method xdwl_data_offer_events[] = {
    {"offer", 1, "s"},
    {"source_actions", 1, "u"},
    {"action", 1, "u"},
};
const struct xdwl_interface xdwl_data_offer_interface = {
    .name = "wl_data_offer",
    .requests = xdwl_data_offer_requests,
    .events = xdwl_data_offer_events,
};
struct xdwl_data_source_event_handlers;int xdwl_data_source_add_listener(xdwl_proxy *proxy, struct xdwl_data_source_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_data_source", event_handlers, sizeof(void *) * 6, user_data);
};


int xdwl_data_source_offer(xdwl_proxy *proxy, xdwl_id wl_data_source_id, const char *_mime_type) {
    return xdwl_send_request(proxy, wl_data_source_id, "wl_data_source", 0, 1, _mime_type);
};
int xdwl_data_source_destroy(xdwl_proxy *proxy, xdwl_id wl_data_source_id) {
    return xdwl_send_request(proxy, wl_data_source_id, "wl_data_source", 1, 0);
};
int xdwl_data_source_set_actions(xdwl_proxy *proxy, xdwl_id wl_data_source_id, xdwl_id _dnd_actions) {
    return xdwl_send_request(proxy, wl_data_source_id, "wl_data_source", 2, 1, _dnd_actions);
};

static const struct xdwl_method xdwl_data_source_requests[] = {
    {"offer", 1, "s"},
    {"destroy", 0, NULL},
    {"set_actions", 1, "u"},
};
static const struct xdwl_method xdwl_data_source_events[] = {
    {"target", 1, "s"},
    {"send", 2, "sh"},
    {"cancelled", 0, NULL},
    {"dnd_drop_performed", 0, NULL},
    {"dnd_finished", 0, NULL},
    {"action", 1, "u"},
};
const struct xdwl_interface xdwl_data_source_interface = {
    .name = "wl_data_source",
    .requests = xdwl_data_source_requests,
    .events = xdwl_data_source_events,
};
struct xdwl_data_device_event_handlers;int xdwl_data_device_add_listener(xdwl_proxy *proxy, struct xdwl_data_device_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_data_device", event_handlers, sizeof(void *) * 6, user_data);
};


int xdwl_data_device_start_drag(xdwl_proxy *proxy, xdwl_id wl_data_device_id, xdwl_id _source, xdwl_id _origin, xdwl_id _icon, xdwl_id _serial) {
    return xdwl_send_request(proxy, wl_data_device_id, "wl_data_device", 0, 4, _source, _origin, _icon, _serial);
};
int xdwl_data_device_set_selection(xdwl_proxy *proxy, xdwl_id wl_data_device_id, xdwl_id _source, xdwl_id _serial) {
    return xdwl_send_request(proxy, wl_data_device_id, "wl_data_device", 1, 2, _source, _serial);
};
int xdwl_data_device_release(xdwl_proxy *proxy, xdwl_id wl_data_device_id) {
    return xdwl_send_request(proxy, wl_data_device_id, "wl_data_device", 2, 0);
};

static const struct xdwl_method xdwl_data_device_requests[] = {
    {"start_drag", 4, "uuuu"},
    {"set_selection", 2, "uu"},
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_data_device_events[] = {
    {"data_offer", 1, "u"},
    {"enter", 5, "uuffu"},
    {"leave", 0, NULL},
    {"motion", 3, "uff"},
    {"drop", 0, NULL},
    {"selection", 1, "u"},
};
const struct xdwl_interface xdwl_data_device_interface = {
    .name = "wl_data_device",
    .requests = xdwl_data_device_requests,
    .events = xdwl_data_device_events,
};
int xdwl_data_device_manager_create_data_source(xdwl_proxy *proxy, xdwl_id wl_data_device_manager_id, xdwl_id _id) {
    return xdwl_send_request(proxy, wl_data_device_manager_id, "wl_data_device_manager", 0, 1, _id);
};
int xdwl_data_device_manager_get_data_device(xdwl_proxy *proxy, xdwl_id wl_data_device_manager_id, xdwl_id _id, xdwl_id _seat) {
    return xdwl_send_request(proxy, wl_data_device_manager_id, "wl_data_device_manager", 1, 2, _id, _seat);
};

static const struct xdwl_method xdwl_data_device_manager_requests[] = {
    {"create_data_source", 1, "u"},
    {"get_data_device", 2, "uu"},
};
const struct xdwl_interface xdwl_data_device_manager_interface = {
    .name = "wl_data_device_manager",
    .requests = xdwl_data_device_manager_requests,
};
int xdwl_shell_get_shell_surface(xdwl_proxy *proxy, xdwl_id wl_shell_id, xdwl_id _id, xdwl_id _surface) {
    return xdwl_send_request(proxy, wl_shell_id, "wl_shell", 0, 2, _id, _surface);
};

static const struct xdwl_method xdwl_shell_requests[] = {
    {"get_shell_surface", 2, "uu"},
};
const struct xdwl_interface xdwl_shell_interface = {
    .name = "wl_shell",
    .requests = xdwl_shell_requests,
};
struct xdwl_shell_surface_event_handlers;int xdwl_shell_surface_add_listener(xdwl_proxy *proxy, struct xdwl_shell_surface_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_shell_surface", event_handlers, sizeof(void *) * 3, user_data);
};


int xdwl_shell_surface_pong(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _serial) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 0, 1, _serial);
};
int xdwl_shell_surface_move(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _seat, xdwl_id _serial) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 1, 2, _seat, _serial);
};
int xdwl_shell_surface_resize(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _seat, xdwl_id _serial, xdwl_id _edges) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 2, 3, _seat, _serial, _edges);
};
int xdwl_shell_surface_set_toplevel(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 3, 0);
};
int xdwl_shell_surface_set_transient(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _parent, int32_t _x, int32_t _y, xdwl_id _flags) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 4, 4, _parent, _x, _y, _flags);
};
int xdwl_shell_surface_set_fullscreen(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _method, xdwl_id _framerate, xdwl_id _output) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 5, 3, _method, _framerate, _output);
};
int xdwl_shell_surface_set_popup(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _seat, xdwl_id _serial, xdwl_id _parent, int32_t _x, int32_t _y, xdwl_id _flags) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 6, 6, _seat, _serial, _parent, _x, _y, _flags);
};
int xdwl_shell_surface_set_maximized(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, xdwl_id _output) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 7, 1, _output);
};
int xdwl_shell_surface_set_title(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, const char *_title) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 8, 1, _title);
};
int xdwl_shell_surface_set_class(xdwl_proxy *proxy, xdwl_id wl_shell_surface_id, const char *_class_) {
    return xdwl_send_request(proxy, wl_shell_surface_id, "wl_shell_surface", 9, 1, _class_);
};

static const struct xdwl_method xdwl_shell_surface_requests[] = {
    {"pong", 1, "u"},
    {"move", 2, "uu"},
    {"resize", 3, "uuu"},
    {"set_toplevel", 0, NULL},
    {"set_transient", 4, "uiiu"},
    {"set_fullscreen", 3, "uuu"},
    {"set_popup", 6, "uuuiiu"},
    {"set_maximized", 1, "u"},
    {"set_title", 1, "s"},
    {"set_class", 1, "s"},
};
static const struct xdwl_method xdwl_shell_surface_events[] = {
    {"ping", 1, "u"},
    {"configure", 3, "uii"},
    {"popup_done", 0, NULL},
};
const struct xdwl_interface xdwl_shell_surface_interface = {
    .name = "wl_shell_surface",
    .requests = xdwl_shell_surface_requests,
    .events = xdwl_shell_surface_events,
};
struct xdwl_surface_event_handlers;int xdwl_surface_add_listener(xdwl_proxy *proxy, struct xdwl_surface_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_surface", event_handlers, sizeof(void *) * 4, user_data);
};


int xdwl_surface_destroy(xdwl_proxy *proxy, xdwl_id wl_surface_id) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 0, 0);
};
int xdwl_surface_attach(xdwl_proxy *proxy, xdwl_id wl_surface_id, xdwl_id _buffer, int32_t _x, int32_t _y) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 1, 3, _buffer, _x, _y);
};
int xdwl_surface_damage(xdwl_proxy *proxy, xdwl_id wl_surface_id, int32_t _x, int32_t _y, int32_t _width, int32_t _height) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 2, 4, _x, _y, _width, _height);
};
int xdwl_surface_frame(xdwl_proxy *proxy, xdwl_id wl_surface_id, xdwl_id _callback) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 3, 1, _callback);
};
int xdwl_surface_set_opaque_region(xdwl_proxy *proxy, xdwl_id wl_surface_id, xdwl_id _region) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 4, 1, _region);
};
int xdwl_surface_set_input_region(xdwl_proxy *proxy, xdwl_id wl_surface_id, xdwl_id _region) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 5, 1, _region);
};
int xdwl_surface_commit(xdwl_proxy *proxy, xdwl_id wl_surface_id) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 6, 0);
};
int xdwl_surface_set_buffer_transform(xdwl_proxy *proxy, xdwl_id wl_surface_id, int32_t _transform) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 7, 1, _transform);
};
int xdwl_surface_set_buffer_scale(xdwl_proxy *proxy, xdwl_id wl_surface_id, int32_t _scale) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 8, 1, _scale);
};
int xdwl_surface_damage_buffer(xdwl_proxy *proxy, xdwl_id wl_surface_id, int32_t _x, int32_t _y, int32_t _width, int32_t _height) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 9, 4, _x, _y, _width, _height);
};
int xdwl_surface_offset(xdwl_proxy *proxy, xdwl_id wl_surface_id, int32_t _x, int32_t _y) {
    return xdwl_send_request(proxy, wl_surface_id, "wl_surface", 10, 2, _x, _y);
};

static const struct xdwl_method xdwl_surface_requests[] = {
    {"destroy", 0, NULL},
    {"attach", 3, "uii"},
    {"damage", 4, "iiii"},
    {"frame", 1, "u"},
    {"set_opaque_region", 1, "u"},
    {"set_input_region", 1, "u"},
    {"commit", 0, NULL},
    {"set_buffer_transform", 1, "i"},
    {"set_buffer_scale", 1, "i"},
    {"damage_buffer", 4, "iiii"},
    {"offset", 2, "ii"},
};
static const struct xdwl_method xdwl_surface_events[] = {
    {"enter", 1, "u"},
    {"leave", 1, "u"},
    {"preferred_buffer_scale", 1, "i"},
    {"preferred_buffer_transform", 1, "u"},
};
const struct xdwl_interface xdwl_surface_interface = {
    .name = "wl_surface",
    .requests = xdwl_surface_requests,
    .events = xdwl_surface_events,
};
struct xdwl_seat_event_handlers;int xdwl_seat_add_listener(xdwl_proxy *proxy, struct xdwl_seat_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_seat", event_handlers, sizeof(void *) * 2, user_data);
};


int xdwl_seat_get_pointer(xdwl_proxy *proxy, xdwl_id wl_seat_id, xdwl_id _id) {
    return xdwl_send_request(proxy, wl_seat_id, "wl_seat", 0, 1, _id);
};
int xdwl_seat_get_keyboard(xdwl_proxy *proxy, xdwl_id wl_seat_id, xdwl_id _id) {
    return xdwl_send_request(proxy, wl_seat_id, "wl_seat", 1, 1, _id);
};
int xdwl_seat_get_touch(xdwl_proxy *proxy, xdwl_id wl_seat_id, xdwl_id _id) {
    return xdwl_send_request(proxy, wl_seat_id, "wl_seat", 2, 1, _id);
};
int xdwl_seat_release(xdwl_proxy *proxy, xdwl_id wl_seat_id) {
    return xdwl_send_request(proxy, wl_seat_id, "wl_seat", 3, 0);
};

static const struct xdwl_method xdwl_seat_requests[] = {
    {"get_pointer", 1, "u"},
    {"get_keyboard", 1, "u"},
    {"get_touch", 1, "u"},
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_seat_events[] = {
    {"capabilities", 1, "u"},
    {"name", 1, "s"},
};
const struct xdwl_interface xdwl_seat_interface = {
    .name = "wl_seat",
    .requests = xdwl_seat_requests,
    .events = xdwl_seat_events,
};
struct xdwl_pointer_event_handlers;int xdwl_pointer_add_listener(xdwl_proxy *proxy, struct xdwl_pointer_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_pointer", event_handlers, sizeof(void *) * 11, user_data);
};


int xdwl_pointer_set_cursor(xdwl_proxy *proxy, xdwl_id wl_pointer_id, xdwl_id _serial, xdwl_id _surface, int32_t _hotspot_x, int32_t _hotspot_y) {
    return xdwl_send_request(proxy, wl_pointer_id, "wl_pointer", 0, 4, _serial, _surface, _hotspot_x, _hotspot_y);
};
int xdwl_pointer_release(xdwl_proxy *proxy, xdwl_id wl_pointer_id) {
    return xdwl_send_request(proxy, wl_pointer_id, "wl_pointer", 1, 0);
};

static const struct xdwl_method xdwl_pointer_requests[] = {
    {"set_cursor", 4, "uuii"},
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_pointer_events[] = {
    {"enter", 4, "uuff"},
    {"leave", 2, "uu"},
    {"motion", 3, "uff"},
    {"button", 4, "uuuu"},
    {"axis", 3, "uuf"},
    {"frame", 0, NULL},
    {"axis_source", 1, "u"},
    {"axis_stop", 2, "uu"},
    {"axis_discrete", 2, "ui"},
    {"axis_value120", 2, "ui"},
    {"axis_relative_direction", 2, "uu"},
};
const struct xdwl_interface xdwl_pointer_interface = {
    .name = "wl_pointer",
    .requests = xdwl_pointer_requests,
    .events = xdwl_pointer_events,
};
struct xdwl_keyboard_event_handlers;int xdwl_keyboard_add_listener(xdwl_proxy *proxy, struct xdwl_keyboard_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_keyboard", event_handlers, sizeof(void *) * 6, user_data);
};


int xdwl_keyboard_release(xdwl_proxy *proxy, xdwl_id wl_keyboard_id) {
    return xdwl_send_request(proxy, wl_keyboard_id, "wl_keyboard", 0, 0);
};

static const struct xdwl_method xdwl_keyboard_requests[] = {
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_keyboard_events[] = {
    {"keymap", 3, "uhu"},
    {"enter", 3, "uu"},
    {"leave", 2, "uu"},
    {"key", 4, "uuuu"},
    {"modifiers", 5, "uuuuu"},
    {"repeat_info", 2, "ii"},
};
const struct xdwl_interface xdwl_keyboard_interface = {
    .name = "wl_keyboard",
    .requests = xdwl_keyboard_requests,
    .events = xdwl_keyboard_events,
};
struct xdwl_touch_event_handlers;int xdwl_touch_add_listener(xdwl_proxy *proxy, struct xdwl_touch_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_touch", event_handlers, sizeof(void *) * 7, user_data);
};


int xdwl_touch_release(xdwl_proxy *proxy, xdwl_id wl_touch_id) {
    return xdwl_send_request(proxy, wl_touch_id, "wl_touch", 0, 0);
};

static const struct xdwl_method xdwl_touch_requests[] = {
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_touch_events[] = {
    {"down", 6, "uuuiff"},
    {"up", 3, "uui"},
    {"motion", 4, "uiff"},
    {"frame", 0, NULL},
    {"cancel", 0, NULL},
    {"shape", 3, "iff"},
    {"orientation", 2, "if"},
};
const struct xdwl_interface xdwl_touch_interface = {
    .name = "wl_touch",
    .requests = xdwl_touch_requests,
    .events = xdwl_touch_events,
};
struct xdwl_output_event_handlers;int xdwl_output_add_listener(xdwl_proxy *proxy, struct xdwl_output_event_handlers *event_handlers, void *user_data) {
      return xdwl_add_listener(proxy, "wl_output", event_handlers, sizeof(void *) * 6, user_data);
};


int xdwl_output_release(xdwl_proxy *proxy, xdwl_id wl_output_id) {
    return xdwl_send_request(proxy, wl_output_id, "wl_output", 0, 0);
};

static const struct xdwl_method xdwl_output_requests[] = {
    {"release", 0, NULL},
};
static const struct xdwl_method xdwl_output_events[] = {
    {"geometry", 8, "iiiiissi"},
    {"mode", 4, "uiii"},
    {"done", 0, NULL},
    {"scale", 1, "i"},
    {"name", 1, "s"},
    {"description", 1, "s"},
};
const struct xdwl_interface xdwl_output_interface = {
    .name = "wl_output",
    .requests = xdwl_output_requests,
    .events = xdwl_output_events,
};
int xdwl_region_destroy(xdwl_proxy *proxy, xdwl_id wl_region_id) {
    return xdwl_send_request(proxy, wl_region_id, "wl_region", 0, 0);
};
int xdwl_region_add(xdwl_proxy *proxy, xdwl_id wl_region_id, int32_t _x, int32_t _y, int32_t _width, int32_t _height) {
    return xdwl_send_request(proxy, wl_region_id, "wl_region", 1, 4, _x, _y, _width, _height);
};
int xdwl_region_subtract(xdwl_proxy *proxy, xdwl_id wl_region_id, int32_t _x, int32_t _y, int32_t _width, int32_t _height) {
    return xdwl_send_request(proxy, wl_region_id, "wl_region", 2, 4, _x, _y, _width, _height);
};

static const struct xdwl_method xdwl_region_requests[] = {
    {"destroy", 0, NULL},
    {"add", 4, "iiii"},
    {"subtract", 4, "iiii"},
};
const struct xdwl_interface xdwl_region_interface = {
    .name = "wl_region",
    .requests = xdwl_region_requests,
};
int xdwl_subcompositor_destroy(xdwl_proxy *proxy, xdwl_id wl_subcompositor_id) {
    return xdwl_send_request(proxy, wl_subcompositor_id, "wl_subcompositor", 0, 0);
};
int xdwl_subcompositor_get_subsurface(xdwl_proxy *proxy, xdwl_id wl_subcompositor_id, xdwl_id _id, xdwl_id _surface, xdwl_id _parent) {
    return xdwl_send_request(proxy, wl_subcompositor_id, "wl_subcompositor", 1, 3, _id, _surface, _parent);
};

static const struct xdwl_method xdwl_subcompositor_requests[] = {
    {"destroy", 0, NULL},
    {"get_subsurface", 3, "uuu"},
};
const struct xdwl_interface xdwl_subcompositor_interface = {
    .name = "wl_subcompositor",
    .requests = xdwl_subcompositor_requests,
};
int xdwl_subsurface_destroy(xdwl_proxy *proxy, xdwl_id wl_subsurface_id) {
    return xdwl_send_request(proxy, wl_subsurface_id, "wl_subsurface", 0, 0);
};
int xdwl_subsurface_set_position(xdwl_proxy *proxy, xdwl_id wl_subsurface_id, int32_t _x, int32_t _y) {
    return xdwl_send_request(proxy, wl_subsurface_id, "wl_subsurface", 1, 2, _x, _y);
};
int xdwl_subsurface_place_above(xdwl_proxy *proxy, xdwl_id wl_subsurface_id, xdwl_id _sibling) {
    return xdwl_send_request(proxy, wl_subsurface_id, "wl_subsurface", 2, 1, _sibling);
};
int xdwl_subsurface_place_below(xdwl_proxy *proxy, xdwl_id wl_subsurface_id, xdwl_id _sibling) {
    return xdwl_send_request(proxy, wl_subsurface_id, "wl_subsurface", 3, 1, _sibling);
};
int xdwl_subsurface_set_sync(xdwl_proxy *proxy, xdwl_id wl_subsurface_id) {
    return xdwl_send_request(proxy, wl_subsurface_id, "wl_subsurface", 4, 0);
};
int xdwl_subsurface_set_desync(xdwl_proxy *proxy, xdwl_id wl_subsurface_id) {
    return xdwl_send_request(proxy, wl_subsurface_id, "wl_subsurface", 5, 0);
};

static const struct xdwl_method xdwl_subsurface_requests[] = {
    {"destroy", 0, NULL},
    {"set_position", 2, "ii"},
    {"place_above", 1, "u"},
    {"place_below", 1, "u"},
    {"set_sync", 0, NULL},
    {"set_desync", 0, NULL},
};
const struct xdwl_interface xdwl_subsurface_interface = {
    .name = "wl_subsurface",
    .requests = xdwl_subsurface_requests,
};
int xdwl_fixes_destroy(xdwl_proxy *proxy, xdwl_id wl_fixes_id) {
    return xdwl_send_request(proxy, wl_fixes_id, "wl_fixes", 0, 0);
};
int xdwl_fixes_destroy_registry(xdwl_proxy *proxy, xdwl_id wl_fixes_id, xdwl_id _registry) {
    return xdwl_send_request(proxy, wl_fixes_id, "wl_fixes", 1, 1, _registry);
};

static const struct xdwl_method xdwl_fixes_requests[] = {
    {"destroy", 0, NULL},
    {"destroy_registry", 1, "u"},
};
const struct xdwl_interface xdwl_fixes_interface = {
    .name = "wl_fixes",
    .requests = xdwl_fixes_requests,
};


__attribute__((constructor)) static void add_interfaces() {
  xdwl_interface_register(&xdwl_display_interface);
  xdwl_interface_register(&xdwl_registry_interface);
  xdwl_interface_register(&xdwl_callback_interface);
  xdwl_interface_register(&xdwl_compositor_interface);
  xdwl_interface_register(&xdwl_shm_pool_interface);
  xdwl_interface_register(&xdwl_shm_interface);
  xdwl_interface_register(&xdwl_buffer_interface);
  xdwl_interface_register(&xdwl_data_offer_interface);
  xdwl_interface_register(&xdwl_data_source_interface);
  xdwl_interface_register(&xdwl_data_device_interface);
  xdwl_interface_register(&xdwl_data_device_manager_interface);
  xdwl_interface_register(&xdwl_shell_interface);
  xdwl_interface_register(&xdwl_shell_surface_interface);
  xdwl_interface_register(&xdwl_surface_interface);
  xdwl_interface_register(&xdwl_seat_interface);
  xdwl_interface_register(&xdwl_pointer_interface);
  xdwl_interface_register(&xdwl_keyboard_interface);
  xdwl_interface_register(&xdwl_touch_interface);
  xdwl_interface_register(&xdwl_output_interface);
  xdwl_interface_register(&xdwl_region_interface);
  xdwl_interface_register(&xdwl_subcompositor_interface);
  xdwl_interface_register(&xdwl_subsurface_interface);
  xdwl_interface_register(&xdwl_fixes_interface);
}