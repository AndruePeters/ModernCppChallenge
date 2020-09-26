add_executable(c1_p1 c1_p1.cpp)
target_include_directories(c1_p1 PUBLIC )
target_link_libraries(c1_p1 PUBLIC CONAN_PKG::fmt CONAN_PKG::docopt.cpp )