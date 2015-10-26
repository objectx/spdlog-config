#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <spdlog/spdlog.h>
#include <spdlog-config.hpp>

static const char * toml_text [] =
    { "# Logger configuration"
    , "pattern      = \"%+\""
    , "level        = \"info\""
    , "default_sink = \"default\""
    , ""
    , "[[sink]]"
    , "    name       = \"default\""
    , "    [[sink.output]]"
    , "        type       = \"null\""
    , "    [[sink.output]]"
    , "        type       = \"stdout\""
    , "    [[sink.output]]"
    , "        type       = \"stderr\""
    , "[[sink]]"
    , "    name       = \"file\""
    , "    [[sink.output]]"
    , "        type       = \"file\""
    , "        path       = \"file.log\""
    , "    [[sink.output]]"
    , "        type       = \"rotating-file\""
    , "        path       = \"rotate\""
    , "        extension  = \"log\""
    , "        max_size   = \"1024M\""
    , "        keep       = 3"
    , "    [[sink.output]]"
    , "        type       = \"daily-file\""
    , "        path       = \"daily\""
    , "        extension  = \"log\""
    , "        refresh_on = \"12:00\""
    , ""
    , "[[channel]]"
    , "    name  = \"global\""
    , "    level = \"info\""
    , "    sink  = \"default\""
    , ""
    , "[[channel]]"
    , "    name  = \"var\""
    , "    level = \"debug\""
    , "    sink  = \"file\""
    , nullptr } ;

static void test_logger () {
    std::stringstream  S ;
    for (auto p = toml_text ; *p != nullptr ; ++p) {
        S << *p << std::endl ;
    }
    S.seekg (0) ;
    configure_logger (S) ;
    spdlog::get ("global")->info ("Logged") ;
    spdlog::get ("var")->debug ("debug") ;
}

int main (int argc, char * const argv[]) {
    // global setup...

    int result = Catch::Session ().run (argc, argv);

    // global clean-up...
    //test_logger () ;
    return result;
}
