/* -*- mode: c++; coding: utf-8 -*- */
/*
 * parse-time.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include <catch.hpp>
#include <spdlog-config.hpp>
#include <internal.hpp>

using namespace std;
using namespace spdlog_config::detail;

SCENARIO ("Test time parser", "[parse-time]") {
    GIVEN ("Empty string") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_time (""), std::runtime_error) ;
    }}}

    GIVEN ("00:9") {
    WHEN ("Try to parse") {
        int hour ;
        int minutes ;
        std::tie (hour, minutes) = parse_time ("00:9") ;
    THEN ("Hour should be 12 and Minutes should be 34") {
        REQUIRE (hour == 0) ;
        REQUIRE (minutes == 9) ;
    }}}

    GIVEN ("12:34") {
    WHEN ("Try to parse") {
        int hour ;
        int minutes ;
        std::tie (hour, minutes) = parse_time ("12:34") ;
    THEN ("Hour should be 12 and Minutes should be 34") {
        REQUIRE (hour == 12) ;
        REQUIRE (minutes == 34) ;
    }}}

    GIVEN ("23:59") {
    WHEN ("Try to parse") {
        int hour;
        int minutes;
        std::tie (hour, minutes) = parse_time ("23:59");
    THEN ("Hour should be 12 and Minutes should be 34") {
        REQUIRE (hour == 23);
        REQUIRE (minutes == 59);
    }}}

    GIVEN ("25:61") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_time ("25:61"), std::runtime_error);
    }}}
}
