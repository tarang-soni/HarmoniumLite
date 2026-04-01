cmake_minimum_required(VERSION 3.16)
project(MusicGame)

set(CMAKE_CXX_STANDARD 17)

# Force SFML to build statically
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(SFML)

set(NLOHMANN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../dir/include")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(MusicGame ${SOURCES})

# Tell your code that SFML is static
target_compile_definitions(MusicGame PRIVATE SFML_STATIC)

target_include_directories(MusicGame PRIVATE ${NLOHMANN_INCLUDE_DIR})

target_link_libraries(MusicGame PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
        sfml-network
)

# Bake the MinGW standard C++ libraries directly into the .exe
target_link_options(MusicGame PRIVATE -static -static-libgcc -static-libstdc++)
file(COPY "${CMAKE_SOURCE_DIR}/resources" DESTINATION "${CMAKE_BINARY_DIR}")