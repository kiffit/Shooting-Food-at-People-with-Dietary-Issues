# CMAKE
cmake_minimum_required(VERSION 3.28)
project(Shooting_Food_at_People_with_Dietary_Issues LANGUAGES CXX)

# Dynamically obtain SFML
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add all CXX files
file(GLOB_RECURSE SRC_FILES Code/*.cpp)

# Create executable and link libraries
add_executable(main ${SRC_FILES})
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
