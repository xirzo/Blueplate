project('project-creator', 'cpp',
        default_options: 'default_library=static')


cc = meson.get_compiler('cpp')

ftxui_dep = dependency('ftxui')
m_dep = cc.find_library('m', required: false)

executable('creator', 
           sources: ['./bin/main.cpp'],
           dependencies: [ftxui_dep, m_dep])
