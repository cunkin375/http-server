file(GLOB_RECURSE HEADER_FILES  ./*.hpp)

add_executable(http-producer producer.cpp)
add_executable(http-consumer consumer.cpp)

set(BINARIES http-producer http-consumer)

foreach(target IN LISTS BINARIES)
    target_compile_options(${target} PRIVATE
        $<$<CXX_COMPILER_ID:Clang>:-fexperimental-library>
        $<$<CONFIG:Release>:-O3>
        -Wall
    )
    target_include_directories(${target} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
    )
endforeach()

