/* -*- mode: c++; coding: utf-8 -*- */
/*
 * internal.hpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#pragma once
#ifndef internal_h__D25B1522_ED75_4BBB_91E1_D8EB06F6D0FA
#define internal_h__D25B1522_ED75_4BBB_91E1_D8EB06F6D0FA

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <string>
#include <spdlog/spdlog.h>
#include <cpptoml.h>

namespace spdlog_config { namespace detail {

    extern spdlog::level::level_enum parse_log_level (const std::string & s);

    extern size_t parse_size (const std::string & s);

    std::tuple<int, int> parse_time (const std::string & s);

    spdlog::sink_ptr create_null_sink (std::shared_ptr<cpptoml::table> /* toml */) ;

    spdlog::sink_ptr create_stdout_sink (std::shared_ptr<cpptoml::table> /* toml */) ;

    spdlog::sink_ptr create_stderr_sink (std::shared_ptr<cpptoml::table> /* toml */) ;

    spdlog::sink_ptr create_file_sink (std::shared_ptr<cpptoml::table> toml) ;

    spdlog::sink_ptr create_rotating_file_sink (std::shared_ptr<cpptoml::table> toml) ;

    spdlog::sink_ptr create_daily_file_sink (std::shared_ptr<cpptoml::table> toml) ;

    spdlog::sink_ptr create_sink (std::shared_ptr<cpptoml::table> toml) ;
}}

#endif  /* internal_h__D25B1522_ED75_4BBB_91E1_D8EB06F6D0FA */
