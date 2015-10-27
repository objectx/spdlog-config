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
    spdlog::level::level_enum parse_log_level (const std::string & s) {
        struct level_desc_t {
            std::string          name_;
            spdlog::level::level_enum level_;

            level_desc_t (const char * name, int lvl)
                    : name_ { name }, level_ { static_cast<spdlog::level::level_enum> (lvl) } {
                /* NO-OP */
            }
        };
        const static std::array<level_desc_t, 10>
                levels { level_desc_t { "trace", 0 }
                         , level_desc_t { "debug", 1 }
                         , level_desc_t { "info", 2 }
                         , level_desc_t { "notice", 3 }
                         , level_desc_t { "warn", 4 }
                         , level_desc_t { "err", 5 }
                         , level_desc_t { "critical", 6 }
                         , level_desc_t { "alert", 7 }
                         , level_desc_t { "emerg", 8 }
                         , level_desc_t { "off", 9 }};

        const level_desc_t * found = nullptr;

        for (size_t i = 0; i < levels.size (); ++i) {
            auto const & lv = levels[i].name_;
            if (strncasecmp (lv.c_str (), s.c_str (), std::min (s.size (), lv.size ())) == 0) {
                if (lv.size () == s.size ()) {
                    // Found exact match
                    return levels[i].level_;
                }
                if (found != nullptr) {
                    throw std::runtime_error {
                            std::string { "Log level \"" }.append (s).append ("\" is ambiguous.") };
                }
                found = &levels[i];
            }
        }
        if (found == nullptr) {
            throw std::runtime_error { std::string { "Unknown log level \"" }.append (s).append ("\" found.") };
        }
        return found->level_;
    }
}}