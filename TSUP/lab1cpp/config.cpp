#include "config.h"
#include <stdexcept>


Config::Config(
    std::string knp_filename,
    std::string param_xml_filename,
    std::string dimensions_filename,
    std::string output_filename
)
    : knp_filename(knp_filename)
    , param_xml_filename(param_xml_filename)
    , dimensions_filename(dimensions_filename)
    , output_filename(output_filename)
{};

// static
Config Config::from_argv(int argc, char **argv) {
    if (argc != 5) {
        throw std::invalid_argument("Wrong number of arguments");
    }

    return Config(
        argv[1],
        argv[2],
        argv[3],
        argv[4]
    );
}
