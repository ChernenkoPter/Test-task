#include <regex>
#include "flight_code.h"

bool compare_flight_codes(const std::string& s_1, const std::string& s_2) { return false; }


bool flight_code_t::operator==(const flight_code_t& other) const {
    return company_code == other.company_code && flight_num == other.flight_num;
}


bool flight_code_t::parse_with_cctype(const std::string& s) { return false; }
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


std::array<char, 4> flight_code_t::get_company_code() const { return company_code; }

uint32_t flight_code_t::get_flight_num() const { return flight_num; }
