project(
  'xdwayland',
  'c',
  default_options: [
    'optimization=3',
  ],
)

if get_option('logs')
  add_project_arguments('-DLOGS', language: 'c')
endif

includes = []
includes += include_directories('include')
includes += include_directories('private')

sources = [
  './src/xdwayland-client.c',
  './src/xdwayland-collections.c',
  './src/xdwayland-core.c',
  './src/xdwayland-error.c',
  './src/xdwayland-utils.c',
]

if get_option('scanner')
  install_data(
    './src/xdwayland-scanner.py',
    install_dir: get_option('bindir'),
    rename: ['xdwayland-scanner'],
  )
endif

project_target = shared_library(
  meson.project_name(),
  sources,
  install: true,
  include_directories: includes,
)

public_headers = files(
  './include/xdwayland-client.h',
  './include/xdwayland-collections.h',
  './include/xdwayland-core.h',
  './include/xdwayland-types.h',
)
install_headers(public_headers)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  project_target,
  name: meson.project_name(),
  filebase: meson.project_name(),
)
