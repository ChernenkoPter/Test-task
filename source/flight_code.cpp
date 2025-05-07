#include <regex>
#include "flight_code.h"

bool compare_flight_codes(const std::string& s_1, const std::string& s_2) { return false; }


bool flight_code_t::operator==(const flight_code_t& other) const { return false; }

bool flight_code_t::parse_with_cctype(const std::string& s) { return false; }

bool flight_code_t::parse_with_regex(const std::string& s) { return false; }


std::array<char, 4> flight_code_t::get_company_code() const { return company_code; }

uint32_t flight_code_t::get_flight_num() const { return flight_num; }
