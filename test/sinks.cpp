/* -*- mode: c++; coding: utf-8 -*- */
/*
 * sinks.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include <catch.hpp>
#include <spdlog-config.hpp>
#include <internal.hpp>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/file_sinks.h>

using namespace std ;
using namespace spdlog_config::detail ;

SCENARIO ("Create null sink", "[sinks]") {
    GIVEN ("A toml definition for null sink") {
        auto toml = cpptoml::make_table () ;
        toml->insert ("type", std::string { "null" }) ;
    WHEN ("Create sink") {
        auto sink = create_sink (toml) ;
    THEN ("null sink should be created") {
        REQUIRE (dynamic_cast<spdlog::sinks::null_sink_mt *> (sink.get ()) != nullptr) ;
    }}}
}

SCENARIO ("Create stdout/stderr sink", "[sinks]") {
    GIVEN ("A toml definition for stdout sink") {
        auto toml = cpptoml::make_table () ;
        toml->insert ("type", std::string { "stdout" }) ;
    WHEN ("Create sink") {
        auto sink = create_sink (toml) ;
    THEN ("null sink should be created") {
        REQUIRE (dynamic_cast<spdlog::sinks::stdout_sink_mt *> (sink.get ()) != nullptr) ;
    }}}
    GIVEN ("A toml definition for stderr sink") {
        auto toml = cpptoml::make_table ();
        toml->insert ("type", std::string { "stderr" });
    WHEN ("Create sink") {
        auto sink = create_sink (toml);
    THEN ("null sink should be created") {
        REQUIRE (dynamic_cast<spdlog::sinks::stderr_sink_mt *> (sink.get ()) != nullptr);
    }}}
}

SCENARIO ("Create file sink", "[sinks]") {
    GIVEN ("A toml definition for file sink") {
        auto toml = cpptoml::make_table () ;
        toml->insert ("type", std::string { "file" }) ;
        toml->insert ("path", std::string { "log.log" }) ;
    WHEN ("Create file sink") {
        auto sink = create_sink (toml) ;
    THEN ("Should be a file sink") {
        REQUIRE (dynamic_cast<spdlog::sinks::simple_file_sink_mt *> (sink.get ()) != nullptr) ;
    }}}
}

SCENARIO ("Create rotating file sink", "[sinks]") {
    GIVEN ("A toml definition for file sink") {
        auto toml = cpptoml::make_table () ;
        toml->insert ("type", "rotating-file") ;
        toml->insert ("path", std::string { "rotate" }) ;
        toml->insert ("extension", std::string { "log" }) ;
        toml->insert ("keep", static_cast<int64_t> (3)) ;
        toml->insert ("max_size", std::string { "10k" }) ;
    WHEN ("Create file sink") {
        auto sink = create_sink (toml) ;
    THEN ("Should be a file sink") {
        REQUIRE (dynamic_cast<spdlog::sinks::rotating_file_sink_mt *> (sink.get ()) != nullptr) ;
    }}}
}

SCENARIO ("Create daily file sink", "[sinks]") {
    GIVEN ("A toml definition for file sink") {
        auto toml = cpptoml::make_table () ;
        toml->insert ("type", std::string { "daily-file" }) ;
        toml->insert ("path", std::string { "daily" }) ;
        toml->insert ("extension", std::string { "log" }) ;
        toml->insert ("refresh_on", std::string { "23:59" }) ;
    WHEN ("Create file sink") {
        auto sink = create_sink (toml) ;
    THEN ("Should be a file sink") {
        REQUIRE (dynamic_cast<spdlog::sinks::daily_file_sink_mt *> (sink.get ()) != nullptr) ;
    }}}
}
