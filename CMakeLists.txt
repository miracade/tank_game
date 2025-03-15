cmake_minimum_required(VERSION 3.10)
project(TankGame)

set(CMAKE_BUILD_TYPE Debug)
set(NSPIRE 0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
	./src/io.cpp
	./src/main.cpp 
	./src/sample_scene.cpp
	./src/util.cpp
	)

set(SDL3_DIR "./lib/x86_64-w64-mingw32/lib/cmake/SDL3")
find_package(SDL3 REQUIRED)

add_executable(main ${SOURCE_FILES})
target_include_directories(main PRIVATE ${SDL3_INCLUDE_DIRS})

target_link_libraries(main PRIVATE SDL3::SDL3)