cmake_minimum_required(VERSION 3.8)
project(GlowMinimal)


# ===============================================
# Global settings

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# ==============================================================================
# Set bin dir
if(MSVC)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
elseif(CMAKE_BUILD_TYPE STREQUAL "")
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/Default)
else()
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR})


# ===============================================
# Dependencies

# Add GLFW lib (with disabled spam)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)
add_subdirectory(extern/glfw)

# math library
add_subdirectory(extern/typed-geometry)

# graphics library
add_subdirectory(extern/glow)

# graphics extras library
add_subdirectory(extern/glow-extras)


# ===============================================
# Configure executable

file(GLOB_RECURSE SOURCES
    "src/*.cc"
    "src/*.hh"
    "src/*.fsh"
    "src/*.vsh"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    glow
    glow-extras
)

target_include_directories(${PROJECT_NAME} PUBLIC "src")


# ===============================================
# Compile flags

if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC
        /MP
    )
else()
    target_compile_options(${PROJECT_NAME} PUBLIC
        -Wall
        -Wno-unused-variable
        -march=native
    )
endif()


# ===============================================
# Folder grouping

foreach(TARGET_NAME
    glfw
    glow
    typed-geometry
    glad
    glow-extras
)
    set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Extern")
endforeach()
