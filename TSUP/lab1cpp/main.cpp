#include <cstdlib>
#include <exception>
#include <iostream>
#include "config.h"
#include "binary_reader.h"

int main(int argc, char* argv[]) {
    Config config;

    try {
        config = Config::from_argv(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cerr << "Usage:\n\t" << argv[0] << " <knp_filename> <param_xml_filename> <dimensions_filename> <output_filename>\n";
        return EXIT_FAILURE;
    }

    BinaryReader reader(config);
    std::map<int, TmDat> tm_fields;
    reader.parse_to(tm_fields);

    return 0;
}
