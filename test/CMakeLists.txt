
cmake_minimum_required (VERSION 3.3)

set (SOURCE_FILES main.cpp log-level.cpp parse-size.cpp parse-time.cpp sinks.cpp)

function (make_test name_)
    add_executable (${name_} ${SOURCE_FILES})
    target_include_directories (${name_}
                                PRIVATE ${PROJECT_SOURCE_DIR}/src
                                        ${PROJECT_SOURCE_DIR}/ext/Catch/include
                                        ${PROJECT_SOURCE_DIR}/ext/spdlog/include
                                        ${PROJECT_SOURCE_DIR}/ext/cpptoml/include)
    target_link_libraries (${name_} PRIVATE spdlog-config)
endfunction ()

make_test (test-spdlog-config)

add_test (NAME test-spdlog-config COMMAND test-spdlog-config -r compact)
