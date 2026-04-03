#include "DioStrB.hpp"
#include <sstream>


void DioStrB::save(const std::string& str) {
    str_string = str;
}


std::ostream& DioStrB::writeti(std::ostream& out) const {
    out << str_string;
    return out; 
}

std::istream& DioStrB::readfrom(std::istream& in) {
    in >> str_string;
    return in; 
}

const std::string& DioStrB::val() const { return str_string; }
std::string& DioStrB::val() { return str_string; }
