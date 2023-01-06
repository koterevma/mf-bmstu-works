#pragma once
#include "config.h"
#include "tm_dat.h"
#include <cstdint>
#include <fstream>
#include <map>

class BinaryReader {
public:
    BinaryReader(const Config& config);

    void parse_to(std::map<int, TmDat>& tm_fields);

    inline static constexpr int16_t SYSTEM_FIELD_NUM = 0xFFFF;

private:
    std::ifstream knp_file;
    std::ifstream param_xml_file;
    std::ifstream dimensions_file;
    std::ofstream output_file;
    char* knp_data;
    size_t knp_data_size;

    struct Statistics {
        size_t system_messages_num = 0ul;
        size_t useful_messages_num = 0ul;
        size_t bytes_read = 0ul;
    };

    Statistics statistics;

};
