
cmake_minimum_required (VERSION 3.3)

project (SPDLOG_CONFIG
        LANGUAGES CXX C
        VERSION 1.0.0.0)

list (INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

function (setvar_default var_)
    if (NOT DEFINED ${var_})
        set (${var_} ${ARGN} PARENT_SCOPE)
    endif ()
endfunction ()

setvar_default (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
setvar_default (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
setvar_default (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories (${CMAKE_CURRENT_BINARY_DIR})

set (SOURCE_FILES src/spdlog-config.cpp
                  src/null-sink.cpp
                  src/stdout-sink.cpp
                  src/file-sink.cpp
                  src/sinks.cpp
                  src/loglevel.cpp)
set (HEADER_FILES include/spdlog-config.hpp src/internal.hpp)

enable_testing ()

add_library (spdlog-config ${SOURCE_FILES} ${HEADER_FILES})
    target_compile_features (spdlog-config PUBLIC cxx_auto_type)
    target_include_directories (spdlog-config
            PUBLIC ${PROJECT_SOURCE_DIR}/include
            PRIVATE ${PROJECT_SOURCE_DIR}/ext/spdlog/include
                    ${PROJECT_SOURCE_DIR}/ext/cpptoml/include)

add_subdirectory (test)
