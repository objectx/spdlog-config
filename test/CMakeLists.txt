
cmake_minimum_required (VERSION 3.3)

set (SOURCE_FILES main.cpp log-level.cpp parse-size.cpp parse-time.cpp sinks.cpp)

add_executable (test-spdlog-config ${SOURCE_FILES})
    target_include_directories (test-spdlog-config
            PRIVATE ${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/ext/Catch/include
                    ${PROJECT_SOURCE_DIR}/ext/spdlog/include
                    ${PROJECT_SOURCE_DIR}/ext/cpptoml/include)
    target_link_libraries (test-spdlog-config PRIVATE spdlog-config)

add_test (NAME test-spdlog-config COMMAND test-spdlog-config -r compact)
