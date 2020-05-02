cmake_minimum_required (VERSION 3.9)
project (opengl_framework VERSION 0.1.0 DESCRIPTION "A simple OpenGL game library")

#[[ Building Library ]]

include(GNUInstallDirs)

set(CMAKE_BUILD_TYPE Debug)


	#[[ Dependencies ]]

find_package(OpenGL REQUIRED)

set(GLFW_INCLUDE_PATH PATH "" CACHE PATH "external/glfw-3.1.2/include/" )
set(GLFW_LIBRARY "glfw" )

set(GLEW_INCLUDE_PATH "" CACHE PATH "external/glew-1.13.0/include" )
set(GLEW_LIBRARY "GLEW_1130" )


include_directories(
	GLFW_INCLUDE_PATH
	GLEW_INCLUDE_PATH
)

add_subdirectory(
    external/
)
set(ALL_LIBS
	${OPENGL_LIBRARY}
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
)


set(LIBRARY_HEADER_FILES
	src/color.hpp
	src/coordinates.hpp
	src/element.hpp
	src/ogl_world.hpp
	src/ogl_wrapper.hpp
	src/shader.hpp
	src/triangle.hpp
	src/geom.hpp
	src/physics.hpp
)

set(LIBRARY_SOURCE_FILES
	src/coordinates.cpp
	src/element.cpp
	src/ogl_world.cpp
	src/ogl_wrapper.cpp
	src/shader.cpp
	src/triangle.cpp
	src/geom.cpp
	src/physics.cpp
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)
	


add_library(opengl_framework STATIC
	${LIBRARY_HEADER_FILES}
	${LIBRARY_SOURCE_FILES})
target_link_libraries(opengl_framework
	${ALL_LIBS}
)	

set_target_properties(opengl_framework PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(opengl_framework PROPERTIES PUBLIC_HEADER include/opengl_framework.hpp)

target_include_directories(opengl_framework PRIVATE include)
target_include_directories(opengl_framework PRIVATE src)
#[[
install(TARGETS opengl_framework
    	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
]]


#[[ Building Tests ]]

	#[[ Compiling Main ]]

set(TESTS_SOURCE_FILES
	tests/main.cpp
)

set(TESTS_INCLUDE_FILE
	include/opengl_framework.hpp
)

add_executable(test_exe
	${TESTS_INCLUDE_FILE}
	${TESTS_SOURCE_FILES}
)

target_link_libraries(test_exe
	opengl_framework
)	
