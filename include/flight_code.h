#pragma once

#include <string>
#include <array>

bool compare_flight_codes(const std::string& s_1, const std::string& s_2);

class flight_code_t {
public:
    bool operator==(const flight_code_t& other) const;
    bool parse(const std::string& s);

public:
    std::array<char, 4> get_company_code() const;
    uint32_t get_flight_num() const;

public:
    static std::string get_app_version();
    static void set_cctype_version();
    static void set_regex_version();

private:
    bool parse_with_cctype(const std::string& s);
    bool parse_with_regex(const std::string& s);

private:
    std::array<char, 4> company_code = {'\0', '\0', '\0', '\0'};
    uint32_t flight_num = 100000;

private:
    static enum parsing_algorithm_t { cctype_version, regex_version } parsing_algorithm;
};
