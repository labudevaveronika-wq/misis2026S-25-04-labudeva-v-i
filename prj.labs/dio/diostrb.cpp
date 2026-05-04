#include "dio.hpp"

void DioStrb::save(const std::string& str) {
    str_string = str;
}

std::ostream& DioStrb::writeti(std::ostream& out) const {
    size_t len = str_string.length();
    out.write((char*)&len, sizeof(len));
    out.write(str_string.c_str(), len);
    return out; 
}

std::istream& DioStrb::readfrom(std::istream& in) {
    size_t len = 0;
    if (in.read((char*)&len, sizeof(len))) {
        str_string.resize(len);
        in.read(&str_string[0], len);
    }
    return in; 
}

const std::string& DioStrb::val() const { return str_string; }
std::string& DioStrb::val() { return str_string; }
