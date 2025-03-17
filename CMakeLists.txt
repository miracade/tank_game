cmake_minimum_required(VERSION 3.11)
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
	./src/world_scene.cpp
	)

set(SDL3_DIR "./lib/x86_64-w64-mingw32/lib/cmake/SDL3")
find_package(SDL3 REQUIRED)

add_executable(main ${SOURCE_FILES})
target_include_directories(main PRIVATE ${SDL3_INCLUDE_DIRS})

target_link_libraries(main PRIVATE SDL3::SDL3)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

target_link_libraries(main PRIVATE fmt::fmt)