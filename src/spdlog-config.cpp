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

void configure_logger (std::shared_ptr<cpptoml::table> toml) {
    auto channels = toml->get_table_array ("channels");
    if (!channels) {
        return;
    }

    std::set<std::string> channel_names;

    for (auto chan : *channels) {
        std::vector<spdlog::sink_ptr> sinks;

        for (auto sink : *chan->get_table_array ("sinks")) {
            sinks.push_back (create_sink (sink));
        }
        if (sinks.empty ()) {
            sinks.push_back (create_null_sink (nullptr));
        }
        auto const name = chan->get_as<std::string> ("name");
        if (!name) {
            throw std::runtime_error { "Missing channel names." };
        }
        if (channel_names.find (*name) != end (channel_names)) {
            throw std::runtime_error {
                    std::string { "Channel name \"" }.append (*name).append ("\" was appeard twice.") };
        }
        auto const level_name = chan->get_as<std::string> ("level");
        auto       level      = parse_log_level (level_name.value_or ("off"));

        auto logger = std::make_shared<spdlog::logger> (*name, begin (sinks), end (sinks));
        logger->set_level (level);

        auto const pattern = chan->get_as<std::string> ("pattern");
        if (pattern) {
            logger->set_pattern (*pattern);
        }

        spdlog::register_logger (logger);
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

