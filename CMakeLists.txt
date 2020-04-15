cmake_minimum_required (VERSION 2.6)
project (opengl_framework)

find_package(OpenGL REQUIRED)

set(GLFW_INCLUDE_PATH PATH "" CACHE PATH "external/glfw-3.1.2/include/" )
set(GLFW_LIBRARY "glfw" )

set(GLEW_INCLUDE_PATH "" CACHE PATH "external/glew-1.13.0/include" )
set(GLEW_LIBRARY "GLEW_1130" )

set(GLM_INCLUDE_PATH "" CACHE PATH "external/glm-0.9.7.1/" )

set(MY_HEADER_FILES
	src/color.hpp
	src/coordinates.hpp
	src/element.hpp
	src/ogl_world.hpp
	src/ogl_wrapper.hpp
	src/shader.hpp
	src/triangle.hpp
)

set(MY_SOURCE_FILES
	src/element.cpp
	src/ogl_world.cpp
	src/ogl_wrapper.cpp
	src/shader.cpp
	src/triangle.cpp
	src/main.cpp
)


include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
    src/
)

add_subdirectory(
    external/
)
set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(opengl_framework
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)
target_link_libraries(opengl_framework
	${ALL_LIBS}
)
