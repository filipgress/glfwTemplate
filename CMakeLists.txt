cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # YCM

set(HEADER_FILES
	src/core/pch.h
	src/core/base.h
	src/core/log.h
	src/core/config.h.in

	src/window/window.h
	src/window/event.h
	src/window/app_event.h
	src/window/key_event.h
	src/window/mouse_event.h
)

set(SOURCE_FILES
	${HEADER_FILES}

	src/core/main.cc
	src/core/log.cc

	src/window/window.cc
)

project(glfw_template VERSION 1.0.0)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
configure_file(src/core/config.h.in config.h)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/core/pch.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR} src)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw GLEW::GLEW)
