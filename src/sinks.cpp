/* -*- mode: c++; coding: utf-8 -*- */
/*
 * sinks.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include <spdlog-config.hpp>
#include "internal.hpp"

namespace spdlog_config { namespace detail {
    spdlog::sink_ptr create_sink (std::shared_ptr<cpptoml::table> toml) {
        using sink_gen_t = spdlog::sink_ptr (*) (std::shared_ptr<cpptoml::table> conf);
        static const std::map<std::string, sink_gen_t> sinks { { "null"         , create_null_sink }
                                                             , { "stdout"       , create_stdout_sink }
                                                             , { "stderr"       , create_stderr_sink }
                                                             , { "file"         , create_file_sink }
                                                             , { "rotating-file", create_rotating_file_sink }
                                                             , { "daily-file"   , create_daily_file_sink }};
        auto typ = toml->get_as<std::string> ("type") ;
        auto const &    type_name = typ.value_or ("null") ;
        // MEMO: We can write above lines like below, but VC++2015 returns "" :-(
        //auto const & type_name = toml->get_as<std::string> ("type").value_or ("null");
        auto it = sinks.find (type_name);
        if (it == sinks.cend ()) {
            throw std::runtime_error (
                    std::string { "Unknown sink type \"" }.append (type_name).append ("\" found."));
        }
        return it->second (toml);
    }
}}
