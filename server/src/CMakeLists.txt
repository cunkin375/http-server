file(GLOB_RECURSE SOURCE_FILES  ./*.cpp)
file(GLOB_RECURSE HEADER_FILES  ./*.hpp)

add_executable(http-server ${SOURCE_FILES} ${HEADER_FILES})

target_compile_options(http-server PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:-fexperimental-library>
    $<$<CONFIG:Release>:-O3>
    -Wall
)

target_include_directories(http-server PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
