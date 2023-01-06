#pragma once
#include <string>

struct Config {
    Config() = default;

    Config(
        std::string knp_filename,
        std::string param_xml_filename,
        std::string dimensions_filename,
        std::string output_filename
    );

    /// Initialize config from argv
    static Config from_argv(int argc, char** argv);

    inline const std::string& get_knp_filename() const {
        return knp_filename;
    }

    inline const std::string& get_param_xml_filename() const {
        return param_xml_filename;
    }

    inline const std::string& get_dimensions_filename() const {
        return dimensions_filename;
    }

    inline const std::string& get_output_filename() const {
        return output_filename;
    }


private:
    std::string knp_filename;
    std::string param_xml_filename;
    std::string dimensions_filename;
    std::string output_filename;

};
