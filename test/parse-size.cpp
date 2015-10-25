/* -*- mode: c++; coding: utf-8 -*- */
/*
 * parse-file.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include <catch.hpp>

#include <spdlog-config.hpp>
#include <internal.hpp>

using namespace std ;
using namespace spdlog_config::detail ;

SCENARIO ("Test size parser", "[parse-size]") {
    GIVEN ("Empty string") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_size (""), std::runtime_error) ;
    }}}

    GIVEN ("\"-1234\"") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_size (""), std::runtime_error);
    }}}

    GIVEN ("\"1234\"") {
    WHEN ("Try to parse") {
        auto sz = parse_size ("1234") ;
    THEN ("Should be 1234") {
        REQUIRE (sz == 1234) ;
    }}}

    GIVEN ("\"1234k\"") {
    WHEN ("Try to parse") {
        auto sz = parse_size ("1234k");
    THEN ("Should be 1234 * 1024") {
        REQUIRE (sz == 1234 * 1024);
    }}}

    GIVEN ("\"1234?\"") {
    WHEN ("Try to parse") {
    THEN ("Throws std::runtime_error") {
        REQUIRE_THROWS_AS (parse_size ("1234?"), std::runtime_error) ;
    }}}
}
