cmake_minimum_required(VERSION 3.19.2)

project(Cube)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(GLUT REQUIRED)
find_package(glm CONFIG REQUIRED)
#find_package(SFML REQUIRED COMPONENTS audio graphics window system)

add_executable(prog)
target_sources(prog
    PRIVATE
        src/main.cpp
)

if(MSVC)
    set_property(TARGET prog PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_link_libraries(prog 
    PRIVATE
        GLUT::GLUT 
        glm::glm
        #sfml-window 
        #sfml-graphics 
        #sfml-system 
        #sfml-main
)


target_include_directories(prog PRIVATE include)
