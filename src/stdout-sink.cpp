/* -*- mode: c++; coding: utf-8 -*- */
/*
 * stdout-sink.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include "internal.hpp"
#include <spdlog/sinks/stdout_sinks.h>

namespace spdlog_config { namespace detail {
    spdlog::sink_ptr create_stdout_sink (std::shared_ptr<cpptoml::table> /* toml */) {
        return std::make_shared<spdlog::sinks::stdout_sink_mt> ();
    }

    spdlog::sink_ptr create_stderr_sink (std::shared_ptr<cpptoml::table> /* toml */) {
        return std::make_shared<spdlog::sinks::stderr_sink_mt> ();
    }
}}
