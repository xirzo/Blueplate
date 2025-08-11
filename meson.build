project('project-creator', 'cpp', default_options: 'default_library=static')

incdir = include_directories('src')
cc = meson.get_compiler('cpp')

ftxui_dep = dependency('ftxui')
m_dep = cc.find_library('m', required: false)

srcs = files(
  'bin/main.cpp',
  'src/app.cpp',
  'src/project_creator.cpp',
  'src/ui.cpp',
)

executable(
  'creator',
  sources: srcs,
  include_directories: incdir,
  dependencies: [ftxui_dep, m_dep],
)
