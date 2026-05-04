#pragma once
#ifndef DIOSTR_HPP
#define DIOSTR_HPP

#include <iostream>
#include <string>

class DioStrb {
    public:
        DioStrb() = default;
        ~DioStrb() = default;
        DioStrb(const DioStrb&) = default;
        void save(const std::string& str);
        std::ostream& writeti(std::ostream& out) const;
        std::istream& readfrom(std::istream& in);
        const std::string& val() const;
        std::string& val();

    private:
        std::string str_string;
};

inline std::ostream& operator<<(std::ostream& ostrm, const DioStrb& rhs) {
    return rhs.writeti(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, DioStrb& rhs) {
    return rhs.readfrom(istrm);
}


class DioStrt {
    private:
        std::string str_string;
    public:
        DioStrt() = default;
        ~DioStrt() = default;
        DioStrt(const DioStrt&) = default;
        void save(const std::string& str);
        std::ostream& writeti(std::ostream& out) const;
        std::istream& readfrom(std::istream& in);
        const std::string& val() const;
};

inline std::ostream& operator<<(std::ostream& ostrm, const DioStrt& rhs) {
    return rhs.writeti(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, DioStrt& rhs) {
    return rhs.readfrom(istrm);
}

#endif