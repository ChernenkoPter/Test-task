#include <algorithm>
#include <cctype>
#include <regex>
#include "flight_code.h"

bool compare_flight_codes(const std::string& s_1, const std::string& s_2) {
    flight_code_t fc_1, fc_2;
    return fc_1.parse(s_1) && fc_2.parse(s_2) && fc_1 == fc_2;
}


bool flight_code_t::operator==(const flight_code_t& other) const {
    return company_code == other.company_code && flight_num == other.flight_num;
}

bool flight_code_t::parse(const std::string& s) {
    switch (comparison_version) {
    case regex_version:
        return parse_with_regex(s);
    default:
        return parse_with_cctype(s);
    }
}

std::array<char, 4> flight_code_t::get_company_code() const { return company_code; }

uint32_t flight_code_t::get_flight_num() const { return flight_num; }

std::string flight_code_t::get_app_version() {
    switch (comparison_version) {
    case regex_version:
        return {"regex"};
    default:
        return {"cctype"};
    }
}

void flight_code_t::set_cctype_version() { comparison_version = cctype_version; }

void flight_code_t::set_regex_version() { comparison_version = regex_version; }


bool flight_code_t::parse_with_cctype(const std::string& s) {
    if (s.empty() || s.length() > 7)
        return false;
    using std::isupper, std::isdigit;

    std::string_view flight_num_s = s;

    bool company_code_is_three_letters = s.length() > 3 && isupper(s[0]) && isupper(s[1]) && isupper(s[2]);
    bool company_code_is_two_alnum = s.length() > 2 &&
        (isdigit(s[0]) || isupper(s[0])) &&
        (isdigit(s[1]) || isupper(s[1])) &&
        (isupper(s[0]) || isupper(s[1]));
    bool company_code_has_space = s.length() > 2 && s[2] == ' ';

    if (company_code_is_three_letters) {
        company_code[0] = s[0];
        company_code[1] = s[1];
        company_code[2] = s[2];
        flight_num_s = flight_num_s.substr(3);
    } else if (company_code_is_two_alnum) {
        company_code[0] = s[0];
        company_code[1] = s[1];
        flight_num_s = flight_num_s.substr(2 + company_code_has_space);
    }

    bool valid_flight_number = !flight_num_s.empty()
        && flight_num_s.length() <= 5
        && std::all_of(flight_num_s.begin(), flight_num_s.end(), [](const char c) { return isdigit(c);});

    if (valid_flight_number) {
        flight_num = std::stoi(flight_num_s.data());
        return true;
    }

    return false;
}

bool flight_code_t::parse_with_regex(const std::string& s) {
    static const std::regex company_patterns{"([A-Z]{3})|([A-Z][0-9A-Z] ?)|([0-9A-Z][A-Z] ?)"};
    if (s.empty() || s.length() > 7)
        return false;

    std::smatch sm;
    std::string company_code_s;
    if (std::regex_search(s, sm, company_patterns, std::regex_constants::match_continuous)) {
        company_code_s = sm[0].str();
        company_code[0] = company_code_s[0];
        company_code[1] = company_code_s[1];
        if (company_code_s.back() != ' ')
            company_code[2] = company_code_s[2];
    }

    std::string flight_num_s = s.substr(company_code_s.length());
    bool valid_flight_number = !flight_num_s.empty()
                             && flight_num_s.length() <= 5
                             && std::all_of(flight_num_s.begin(), flight_num_s.end(), [](char c) { return isdigit(c);});
    if (valid_flight_number) {
        flight_num = std::stoi(flight_num_s);
        return true;
    }

    return false;
}