/* -*- mode: c++; coding: utf-8 -*- */
/*
 * spdlog-config.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include "spdlog-config.hpp"
#include "internal.hpp"

#include <regex>
#include <set>

using namespace std ;
using namespace spdlog_config::detail ;

using toml_t = std::shared_ptr<cpptoml::table> ;

static std::tuple<std::string, std::vector<spdlog::sink_ptr>> read_sinks (toml_t toml) {
    auto name = toml->get_as<std::string> ("name") ;
    if (! name) {
        throw std::runtime_error { "No sink names" } ;
    }
    auto outputs = toml->get_table_array ("output") ;
    if (! outputs) {
        throw std::runtime_error { "No outputs" };
    }
    std::vector<spdlog::sink_ptr>   result ;
    for (auto o : *outputs) {
        result.emplace_back (create_sink (o)) ;
    }
    return std::make_tuple (*name, result) ;
}

void configure_logger (std::shared_ptr<cpptoml::table> toml) {
    // Default pattern
    auto default_pattern = toml->get_as<std::string> ("pattern").value_or ("%+") ;
    auto default_level = toml->get_as<std::string> ("level").value_or ("off") ;
    auto default_sink = toml->get_as<std::string> ("default_sink") ;

    auto get_level = [&default_level](auto lv) {
        if (! lv) {
            return parse_log_level (default_level) ;
        }
        else {
            return parse_log_level (*lv) ;
        }
    } ;
    auto get_sink_name = [&default_sink](auto name) {
        if (! name) {
            if (! default_sink) {
                throw std::runtime_error { "No sink names" };
            }
            return *default_sink ;
        }
        else {
            return *name ;
        }
    } ;
    auto get_pattern = [&default_pattern] (auto pat) {
        if (! pat) {
            return default_pattern ;
        }
        else {
            return *pat ;
        }
    } ;

    std::map<std::string, std::vector<spdlog::sink_ptr>>    sink_dict ;
    {
        auto sinks = toml->get_table_array ("sink") ;
        if (! sinks) {
            throw std::runtime_error { "No sinks" } ;
        }
        for (auto s : *sinks) {
            std::string name ;
            std::vector<spdlog::sink_ptr>   outputs ;
            std::tie (name, outputs) = read_sinks (s) ;
            sink_dict [name] = outputs ;
        }
    }
    {
        auto channels = toml->get_table_array ("channel") ;
        if (! channels) {
            throw std::runtime_error { "No channels" };
        }
        for (auto ch : *channels) {
            auto name = ch->get_as<std::string> ("name") ;
            if (! name) {
                throw std::runtime_error { "No channel names" };
            }
            auto lvl       = get_level (ch->get_as<std::string> ("level")) ;
            auto sink_name = get_sink_name (ch->get_as<std::string> ("sink")) ;
            auto pat = get_pattern (ch->get_as<std::string> ("pattern")) ;

            auto it = sink_dict.find (sink_name) ;
            if (it == sink_dict.cend ()) {
                throw std::runtime_error { std::string { "Bad sink name \"" }.append (sink_name).append ("\" found") };
            }
            auto logger = std::make_shared<spdlog::logger> (*name, begin (it->second), end (it->second)) ;
            logger->set_level (lvl) ;
            logger->set_pattern (pat) ;
            spdlog::register_logger (logger) ;
        }
    }
}

void configure_logger (std::istream &input) {
    auto toml = cpptoml::parser { input }.parse () ;
    configure_logger (toml) ;
}

bool configure_logger (const std::string & file, bool ignore_missing_file) {
    std::ifstream   input { file } ;
    if (input.bad ()) {
        if (ignore_missing_file) {
            return false ;
        }
        throw std::runtime_error { std::string { "Failed to read \"" }.append (file).append ("\".") };
    }
    configure_logger (input) ;
    return true ;
}

