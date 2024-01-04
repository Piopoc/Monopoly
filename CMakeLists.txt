# @author Filippo Corradi, matricola: 2066680

cmake_minimum_required(VERSION 3.10)
project(exe)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
endif()

	# target_include_directories(${PROJECT_NAME} PRIVATE ../include)
include_directories(../include)

add_executable(${PROJECT_NAME} 
    ../src/main.cpp
    ../src/Table.cpp
    ../src/Player.cpp
    ../src/Cell.cpp
)
