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
        ~BitsetD() = default;

        BitsetD(const BitsetD& src);
        BitsetD(const std::int32_t size);
        BitsetD& operator=(const BitsetD& rhs);

        void set(const int32_t index, const bool val);
        bool get(int32_t index) const;

        void invert() noexcept;
        void fill(bool val) noexcept;
        void resize(const BitsetD& val) noexcept;

        BitsetD& shift(const std::int32_t idx) noexcept;
        BitsetD& operator<<=(const std::int32_t shift);
        BitsetD& operator>>=(const std::int32_t shift);
        BitsetD& operator&=(const BitsetD& rhs);
        BitsetD& operator|=(const BitsetD& rhs);
        BitsetD& operator^=(const BitsetD& rhs);

        std::int32_t size() const {
            return size_;
        };

        bool operator==(const BitsetD& rhs) noexcept;


        BitsetD operator~(const BitsetD& rhs) noexcept;

        BitsetD operator<<(const BitsetD& lhs, const std::int32_t shift);
  
        BitsetD operator>>(const BitsetD& lhs, const std::int32_t shift);

        BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs);

        BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs);

        BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs);


    private:
        std::int32_t size_ = 0;
        std::vector<std::uint32_t> databasa;


};
#endif