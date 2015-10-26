/*
 * spdlog-config.hpp: Configure spdlog instance from supplied TOML file
 *
 * Copyright (c) 2015 Masashi Fujita
 */
#pragma once
#ifndef spdlog_config_hpp__3E367102_1064_40E2_A799_6E6DC69F87A1
#define spdlog_config_hpp__3E367102_1064_40E2_A799_6E6DC69F87A1 1

#include <cstddef>
#include <cstdint>
#include <string>
#include <iosfwd>
#include <tuple>
#include <memory>

namespace cpptoml {
    class table ;
}

extern void configure_logger (std::shared_ptr<cpptoml::table> toml) ;
extern void configure_logger (std::istream &input) ;
extern bool configure_logger (const std::string &file, bool ignore_missing_file = false) ;

#endif /* spdlog_config_hpp__3E367102_1064_40E2_A799_6E6DC69F87A1 */
