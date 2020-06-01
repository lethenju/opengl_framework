
set(TESTS_INCLUDE_FILE
	../include/opengl_framework.hpp
)

	#[[ Compiling Pong ]]

set(PONG_SOURCE_FILES
	pong.cpp
)

add_executable(pong_exe
	${TESTS_INCLUDE_FILE}
	${PONG_SOURCE_FILES}
)

target_link_libraries(pong_exe
	opengl_framework
)	

set(PLATFORMER_SOURCE_FILES
	platformer.cpp
)

add_executable(platformer_exe
	${TESTS_INCLUDE_FILE}
	${PLATFORMER_SOURCE_FILES}
)

target_link_libraries(platformer_exe
	opengl_framework
)	

set(TEST_COLLISION_SOURCE_FILES
	tests_collision.cpp
)

add_executable(test_collision_exe
	${TESTS_INCLUDE_FILE}
	${TEST_COLLISION_SOURCE_FILES}
)

target_link_libraries(test_collision_exe
	opengl_framework
)	

set(TEST_INPUT_COLLISION_SOURCE_FILES
	tests_input_collision.cpp
)

add_executable(test_input_collision_exe
	${TESTS_INCLUDE_FILE}
	${TEST_INPUT_COLLISION_SOURCE_FILES}
)

target_link_libraries(test_input_collision_exe
	opengl_framework
)	



set(TEST_GEOM_SOURCE_FILES
	tests_geom.cpp
)

add_executable(test_geom_exe
	${TESTS_INCLUDE_FILE}
	${TEST_GEOM_SOURCE_FILES}
)

target_link_libraries(test_geom_exe
	opengl_framework
)	

set(TEST_RESIZE_SOURCE_FILES
	tests_resize.cpp
)

add_executable(test_resize_exe
	${TESTS_INCLUDE_FILE}
	${TEST_RESIZE_SOURCE_FILES}
)

target_link_libraries(test_resize_exe
	opengl_framework
)	


set(TEST_SEVENSEG_SOURCE_FILES
	tests_sevenseg.cpp
)

add_executable(test_sevenseg_exe
	${TESTS_INCLUDE_FILE}
	${TEST_SEVENSEG_SOURCE_FILES}
)

target_link_libraries(test_sevenseg_exe
	opengl_framework
)	

set(TEST_MOUSE_SOURCE_FILES
	tests_mouse.cpp
)

add_executable(test_mouse_exe
	${TESTS_INCLUDE_FILE}
	${TEST_MOUSE_SOURCE_FILES}
)

target_link_libraries(test_mouse_exe
	opengl_framework
)	