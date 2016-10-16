/* -*- mode: c++; coding: utf-8 -*- */
/*
 * loglevel.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include <cpptoml.h>
#include <regex>
#include "spdlog-config.hpp"
#include "internal.hpp"

#ifdef _MSC_VER
#define strncasecmp strnicmp
#endif

namespace spdlog_config { namespace detail {
    spdlog::level::level_enum parse_log_level (const std::string &s) {
        int32_t found = -1 ;

        for (int32_t i = 0; i <= spdlog::level::off ; ++i) {
            auto const *lv = spdlog::level::level_names [i] ;
            size_t sz = strlen (lv) ;
            if (strncasecmp (lv, s.c_str (), std::min (s.size (), sz)) == 0) {
                if (sz == s.size ()) {
                    // Found exact match
                    return static_cast<spdlog::level::level_enum> (i) ;
                }
                if (0 <= found) {
                    throw std::runtime_error { std::string { "Log level \"" }
                                               .append (s)
                                               .append ("\" is ambiguous.") };
                }
                found = i ;
            }
        }
        if (found < 0) {
            throw std::runtime_error { std::string { "Unknown log level \"" }.append (s).append ("\" found.") };
        }
        return static_cast<spdlog::level::level_enum> (found) ;
    }
}}
