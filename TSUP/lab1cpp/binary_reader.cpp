#include "binary_reader.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fcntl.h>
#include <exception>
#include <fstream>
#include <iterator>
#include <string.h>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/mman.h>


BinaryReader::BinaryReader(const Config& config)
    : param_xml_file(config.get_param_xml_filename())
    , dimensions_file(config.get_dimensions_filename())
    , output_file(config.get_output_filename())
    , statistics()
{
    struct stat knp_file_stat;
    auto file_d = open(
        config.get_knp_filename().c_str(),
        O_RDONLY);

    if (file_d < 0) {
        throw std::runtime_error("Could not open knp file");
    }

    if (fstat(file_d, &knp_file_stat) < 0) {
        throw std::runtime_error("fstat failed");
    }

    knp_data_size = knp_file_stat.st_size;
    knp_data = (char*) mmap(NULL, knp_data_size, PROT_READ, MAP_PRIVATE, file_d, NULL);

    if (knp_data == MAP_FAILED) {
        throw std::runtime_error("mmap failed");
    }
}

void BinaryReader::parse_to(std::map<int, TmDat>& tm_fields) {
    size_t offset{0};
    char buffer[4096];
    while (offset < knp_data_size) {
        memcpy(buffer, knp_data + offset, 4096);
        offset += 4096;
    }
}
