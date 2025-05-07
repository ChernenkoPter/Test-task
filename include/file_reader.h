#pragma once

#include "flight_code.h"
#include <vector>
#include <unordered_set>

class file_reader_t {
public:
    file_reader_t(const std::vector<std::string>& input_files, const std::vector<std::string>& output_files);
    bool read_files();
    bool write_files();

private:
    std::vector<std::string> input_files;
    std::vector<std::string> output_files;
};
