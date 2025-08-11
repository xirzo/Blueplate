project(
  'project-creator',
  'cpp',
  version: '0.0.1',
  default_options: [
    'default_library=static',
    'cpp_std=c++23',
    'warning_level=2',
  ],
)

cc = meson.get_compiler('cpp')

ftxui_dep = dependency('ftxui', required: true)
m_dep = cc.find_library('m', required: false)

srcs = files(
  'bin/main.cpp',
  'src/app.cpp',
  'src/project_creator.cpp',
  'src/ui.cpp',
)

executable(
  'creator',
  srcs,
  include_directories: [
    include_directories('src'),
  ],
  dependencies: [
    ftxui_dep,
    m_dep,
  ],
  install: true,
)
