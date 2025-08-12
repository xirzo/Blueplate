project(
  '${pc_project_name}',
  'cpp',
  version: '0.0.1',
  default_options: [
    'default_library=static',
    'cpp_std=c++20',
    'warning_level=2',
  ],
)

srcs = files(
  'bin/main.cpp',
  'src/${pc_project_name}.cpp',
)

executable(
  '${pc_project_name}',
  srcs,
  include_directories: [
    include_directories('src'),
  ],
  dependencies: [],
  install: true,
)
