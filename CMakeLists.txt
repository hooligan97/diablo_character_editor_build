cmake_minimum_required(VERSION 3.21)
project(d1_edit)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3p")

set(DEVILUTIONX_STATIC_ZLIB ON)
set(DEVILUTIONX_STATIC_BZIP2 ON)

add_subdirectory(3p/zlib)
add_subdirectory(3p/bzip2)
add_subdirectory(3p/PKWare)
add_subdirectory(3p/libmpq)

add_library(d1edit
    src/hero_json.cpp
    src/codec.cpp
    src/sha.cpp
    src/encrypt.cpp
    src/pfile.cpp
    src/mpq/mpq_common.cpp
    src/mpq/mpq_reader.cpp
    src/mpq/mpq_writer.cpp
)

target_include_directories(d1edit
    PUBLIC
        src
        3p/PKWare
)

target_compile_features(d1edit PUBLIC cxx_std_20)

target_link_libraries(d1edit
    PUBLIC
        PKWare
        libmpq
        ZLIB::ZLIB
        BZip2::BZip2
)

add_executable(editor src/editor.cpp)
target_link_libraries(editor PRIVATE d1edit)

if(EMSCRIPTEN)
    add_executable(d1_wasm src/editor.cpp)
    target_link_libraries(d1_wasm PRIVATE d1edit)
    set_target_properties(d1_wasm PROPERTIES OUTPUT_NAME "d1_edit")
    target_link_options(d1_wasm PRIVATE "-sEXPORTED_RUNTIME_METHODS=['callMain']")
endif()
