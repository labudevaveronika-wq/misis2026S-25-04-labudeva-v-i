#pragma once
#ifndef BITSETD_BITSETD_2026
#define BITSETD_BITSETD_2026

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

class BitsetD {
    public:
        BitsetD() = default;
        BitsetD(const BitsetD&);
        BitsetD(const std::int32_t size);
        ~BitsetD() = default;
        BitsetD& operator=(const BitsetD& rhs);

        void set(const int32_t index, const bool val);
        bool get(int32_t index) const;
        
        void fill(bool val);

        std::int32_t size() const {
            return size_;
        };

        int32_t resize();



    private:
        std::int32_t size_ = 0;
        std::vector<std::uint32_t> databasa;


};
#endif