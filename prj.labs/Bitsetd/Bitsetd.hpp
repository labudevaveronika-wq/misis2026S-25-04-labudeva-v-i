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
        BitsetD(BitsetD&& src) noexcept;


        BitsetD(const std::int32_t size, const bool val);
        BitsetD(const std::uint64_t mask, const int32_t size = 64);

        BitsetD& operator=(const BitsetD& rhs) = default;
        BitsetD& operator=(BitsetD&& rhs) noexcept;

        void set(const int32_t index, const bool val = true);
        [[nodiscard]] bool get(const int32_t index) const;

        BitsetD& invert() noexcept;
        void fill(const bool val) noexcept;
        void resize(const std::int32_t new_size, bool val = false); 

        BitsetD& shift(const std::int32_t idx) noexcept;
        BitsetD& operator<<=(const std::int32_t shift);
        BitsetD& operator>>=(const std::int32_t shift);
        BitsetD& operator&=(const BitsetD& rhs);
        BitsetD& operator|=(const BitsetD& rhs);
        BitsetD& operator^=(const BitsetD& rhs);

        bool operator==(const BitsetD& rhs) const noexcept;

        explicit operator std::uint64_t() const;
        explicit operator std::uint32_t() const;

        std::ostream& write_to(std::ostream& strm) const;
        std::istream& read_from(std::istream& strm);

        enum class StrFormat : int32_t {
            Bin = 1,     
            BinNoPreSep,  
            Oct,
            Hex,
            Def = Bin,
            Default = Def
        };

        std::string to_string(const StrFormat fmt = StrFormat::Def, const int32_t len = 0) const;

        [[nodiscard]] std::int32_t size() const noexcept;

        class BitProxC {
            friend class BitsetD;
        public:
            ~BitProxC() = default;
            operator bool() const noexcept { return val_; }
        private:
            BitProxC(const BitsetD& bs, const int32_t idx) : val_(bs.get(idx)) {}
            bool val_ = false;
            BitProxC() = delete;
            BitProxC(const BitProxC&) = delete;
            BitProxC& operator=(const BitProxC&) = delete;
        };
        class BitProx {
            friend class BitsetD;
        public:
            ~BitProx() = default;
            operator bool() const noexcept { return bs_.get(idx_); }
            void operator=(const bool val) noexcept { bs_.set(idx_, val); }
            void operator=(const BitProx& rhs) noexcept { operator=(rhs.operator bool()); }
        private:
            BitProx(BitsetD& bs, const int32_t idx) : bs_(bs), idx_(idx) {}
            BitsetD& bs_;
            const int32_t idx_;
            BitProx() = delete;
            BitProx(const BitProx&) = delete;
        };
        BitProx operator[](const std::int32_t idx) & { return BitProx(*this, idx); }
        BitProxC operator[](const std::int32_t idx) const & { return BitProxC(*this, idx); }

    private:
        std::int32_t size_ = 0;
        std::vector<std::uint32_t> bits_{};
};


 
inline BitsetD operator~(const BitsetD& rhs) noexcept  { auto A = rhs; A.invert(); return A; };

BitsetD operator<<(BitsetD& lhs, const std::int32_t shift);
  
BitsetD operator>>(BitsetD& lhs, const std::int32_t shift);

BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs);

BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs);

BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs);

#endif