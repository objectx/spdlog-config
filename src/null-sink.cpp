/* -*- mode: c++; coding: utf-8 -*- */
/*
 * null-sink.cpp:
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#include "internal.hpp"
#include <spdlog/sinks/null_sink.h>

using namespace std;
using namespace spdlog_config::detail;

namespace spdlog_config { namespace detail {

    spdlog::sink_ptr create_null_sink (std::shared_ptr<cpptoml::table> /* toml */) {
        return std::make_shared<spdlog::sinks::null_sink_mt> ();
    }
}}
