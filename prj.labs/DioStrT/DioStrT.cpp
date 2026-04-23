#include "DioStrT.hpp"

void DioStrT::save(const std::string& str) {
    str_string = str;
}

std::ostream& DioStrT::writeti(std::ostream& out) const {
    out << "\""; // Начальная кавычка
    for (size_t i = 0; i < str_string.length(); ++i) {
        char c = str_string[i];
        if (c == '\n') out << "\\n";      
        else if (c == '\\') out << "\\\\"; 
        else out << c;
    }
    out << "\""; 
    return out;
}

std::istream& DioStrT::readfrom(std::istream& in) {
    char ch;
    str_string = "";
    
    
    while (in.get(ch) && ch != '\"');

    // Читаем содержимое
    while (in.get(ch) && ch != '\"') {
        if (ch == '\\') { // Если встретили слэш, смотрим на следующий символ
            char next;
            if (in.get(next)) {
                if (next == 'n') str_string += '\n';
                else if (next == '\\') str_string += '\\';
                else str_string += next;
            }
        } else {
            str_string += ch;
        }
    }
    return in;
}

const std::string& DioStrT::val() const { return str_string; }

