#pragma once

#include <string>
#include <array>

bool compare_flight_codes(const std::string& s_1, const std::string& s_2);

class flight_code_t {
public:
    bool operator==(const flight_code_t& other) const;
    bool parse_with_cctype(const std::string& s);
    bool parse_with_regex(const std::string& s);

public:
    std::array<char, 4> get_company_code() const;
    uint32_t get_flight_num() const;

private:
    std::array<char, 4> company_code;
    uint32_t flight_num;
};
