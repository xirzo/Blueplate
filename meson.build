project(
  'blueplate',
  'cpp',
  version: '0.0.2',
  default_options: [
    'default_library=static',
    'cpp_std=c++23',
    'warning_level=2',
  ],
)

cmake = import('cmake')

ftxui_proj = cmake.subproject('ftxui')
ftxui_screen = ftxui_proj.dependency('screen')
ftxui_dom = ftxui_proj.dependency('dom')
ftxui_component = ftxui_proj.dependency('component')

cli11_dep = dependency('CLI11', fallback: ['cli11', 'cli11_dep'])
tomlcpp_dep = dependency('tomlplusplus', fallback: ['tomlplusplus', 'tomlplusplus_dep'])

srcs = files(
  'bin/main.cpp',
  'src/app.cpp',
  'src/configuration.cpp',
  'src/key_inserter.cpp',
  'src/project_creator.cpp',
  'src/ui.cpp',
)

executable(
  'blueplate',
  srcs,
  include_directories: [
    include_directories('src'),
  ],
  dependencies: [
    ftxui_screen,
    ftxui_dom,
    ftxui_component,
    cli11_dep,
    tomlcpp_dep,
  ],
  install: true,
)
