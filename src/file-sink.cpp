/* -*- mode: c++; coding: utf-8 -*- */
/*
 * file-sink.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include "internal.hpp"
#include <regex>

namespace spdlog_config { namespace detail {

    spdlog::sink_ptr create_file_sink (std::shared_ptr<cpptoml::table> toml) {
        auto path = toml->get_as<std::string> ("path");
        if (!path) {
            throw std::runtime_error { "Missing log file path for rotating file sink" };
        }
        return std::make_shared<spdlog::sinks::simple_file_sink_mt> (*path);
    }

    spdlog::sink_ptr create_rotating_file_sink (std::shared_ptr<cpptoml::table> toml) {
        auto path = toml->get_as<std::string> ("path");
        if (!path) {
            throw std::runtime_error { "Missing log file path for rotating file sink" } ;
        }
        auto ext      = toml->get_as<std::string> ("extension").value_or ("log");
        auto max_size = toml->get_as<std::string> ("max_size").value_or ("1M");
        auto keep     = toml->get_as<int64_t> ("keep").value_or (3);
        return std::make_shared<spdlog::sinks::rotating_file_sink_mt> (*path, ext, parse_size (max_size), keep);
    }

    spdlog::sink_ptr create_daily_file_sink (std::shared_ptr<cpptoml::table> toml) {
        auto path = toml->get_as<std::string> ("path");
        if (!path) {
            throw std::runtime_error { "Missing log file path for daily file sink" } ;
        }
        auto ext     = toml->get_as<std::string> ("extension").value_or ("log");
        auto refresh = toml->get_as<std::string> ("refresh_on").value_or ("00:00");
        int  hour;
        int  minutes;
        std::tie (hour, minutes) = parse_time (refresh);
        return std::make_shared<spdlog::sinks::daily_file_sink_mt> (*path, ext, hour, minutes);
    }

    size_t parse_size (const std::string & s) {
        static const std::regex rx { "^\\s*(\\d+)\\s*(k|m|g)?$"
                                   , std::regex_constants::ECMAScript | std::regex_constants::icase };
        std::smatch             m;
        if (!std::regex_match (s, m, rx)) {
            throw std::runtime_error { std::string { "Bad size specifier \"" }.append (s).append ("\".") };
        }
        auto digits = m[1].str ();
        auto sz     = strtol (digits.c_str (), nullptr, 10);
        if (sz < 0) {
            throw std::range_error { "Negative size supplied" };
        }
        if (m[2].matched) {
            auto suffix = m[2].str ();
            switch (suffix[0]) {
            case 'k': case 'K': sz *= 1024; break;
            case 'm': case 'M': sz *= 1024 * 1024; break;
            case 'g': case 'G': sz *= 1024 * 1024 * 1024; break;
            default:
                throw std::runtime_error { std::string { "Unknown suffix \'" }.append (suffix).append ("\'.") };
            }
        }
        return static_cast<size_t> (sz);
    }

    std::tuple<int, int> parse_time (const std::string & s) {
        static const std::regex rx { "^\\s*(0?\\d|1[0-9]|2[0-3]):([0-5]?\\d)$" };
        std::smatch             m;

        if (!std::regex_match (s, m, rx)) {
            throw std::runtime_error { std::string { "Bad time specifier \"" }.append (s).append ("\".") };
        }
        auto hour    = m[1].str ();
        auto minutes = m[2].str ();
        auto H       = strtol (hour.c_str (), nullptr, 10);
        auto M       = strtol (minutes.c_str (), nullptr, 10);
        return std::make_tuple (H, M);
    }
}}
