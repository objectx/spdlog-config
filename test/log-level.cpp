#include <catch.hpp>

#include <string>
#include <spdlog-config.hpp>
#include <internal.hpp>

using namespace std;
using namespace spdlog_config::detail;

SCENARIO ("Parse log level string", "[log-level]") {
    GIVEN ("Empty log level string") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_log_level (""), std::runtime_error) ;
    }}}

    GIVEN ("Abbreviated level string \"t\" for trace level") {
    WHEN ("Try to parse") {
        auto level = parse_log_level ("t") ;
    THEN ("Should be parsed as \"trace\"") {
        REQUIRE (level == spdlog::level::trace) ;
    }}}

    GIVEN ("Level string \"information\" for info level") {
    WHEN ("Try to parse") {
        auto level = parse_log_level ("information") ;
    THEN ("Should be parsed as \"info\"") {
        REQUIRE (level == spdlog::level::info) ;
    }}}

    GIVEN ("Abbreviated level string \"e\"") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_log_level ("e"), std::runtime_error) ;
    }}}

    GIVEN ("Level strings") {
    WHEN ("Try to parse") {
    THEN ("Should be parsed correctly") {
        for (int i = 0 ; i <= 9 ; ++i) {
            auto lv = static_cast<spdlog::level::level_enum> (i) ;
            std::string long_names { spdlog::level::to_str (lv) } ;
            REQUIRE (parse_log_level (long_names) == lv) ;
        }
    }}}
}
