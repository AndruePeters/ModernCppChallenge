add_executable(c1_p1 c1_p1.cpp)
target_link_libraries(c1_p1 PUBLIC project_options project_warnings CONAN_PKG::fmt CONAN_PKG::docopt.cpp math_lib )

add_executable(c1_p2 c1_p2.cpp)
target_link_libraries(c1_p2 PUBLIC project_options project_warnings CONAN_PKG::fmt CONAN_PKG::docopt.cpp math_lib )