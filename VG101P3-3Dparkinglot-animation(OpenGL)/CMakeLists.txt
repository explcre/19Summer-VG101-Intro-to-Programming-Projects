cmake_minimum_required(VERSION 2.7)


project(p3)



set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -Wno-unused-result -Wno-deprecated-declarations")



find_package(OpenGL REQUIRED)


include_directories(${OPENGL_INCLUDE_DIR})



find_package(GLUT REQUIRED)


include_directories(${GLUT_INCLUDE_DIR})





add_executable(wall main.cpp head.h p3.h ElementFigure.h ComplexFigure.h Control.h  Analysis.h)



target_link_libraries(wall ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

