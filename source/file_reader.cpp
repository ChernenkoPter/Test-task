#include "file_reader.h"

file_reader_t::file_reader_t(const std::vector<std::string>& input_files, const std::vector<std::string>& output_files) :
    input_files(input_files), output_files(output_files) {}

bool file_reader_t::read_files() { return false; }

bool file_reader_t::write_files() { return false; }
