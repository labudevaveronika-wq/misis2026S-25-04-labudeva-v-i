#include "Bitsetd.hpp"
#include <stdexcept>

BitsetD::BitsetD(const BitsetD& src) {
    size_ = src.size_;
    databasa = src.databasa;
}

BitsetD::BitsetD(const std::int32_t size, const bool val)
{
    if (size <= 0) {
        throw std::invalid_argument("BitsetD constructor: size cannot be negative");
    }

    int32_t word = size / 32 + bool(size % 32);
    databasa.resize(word);
    size_ = size;
    if (val){
        for (uint64_t i = 0; i < word - 1; i++){
            databasa[i] = (1ULL<<32) - 1;
        }
        if (size%32 == 0){
            databasa[word - 1] = (1ULL<<32) - 1;
        }else{
            databasa[word - 1] = (1ULL<<(size%32)) - 1;
        }
    }else{
        for (uint64_t i = 0; i < word; i++){
            databasa[i] = 0;
        }
    }



}

BitsetD &BitsetD::operator=(const BitsetD& rhs)
{
    if (this != &rhs){
        size_ = rhs.size_;
        databasa = rhs.databasa;
    }
    return *this;
}

BitsetD::BitsetD(const std::uint64_t mask, const int32_t size)
{
    // TODOOOOO
    if (size <= 0){
        throw std::invalid_argument("BitsetD constructor: size cannot be negative");
    }
    int32_t word = size / 32 + bool(size % 32);
    size_ = size;
    databasa.resize(word);
    if (size < 64){
        if (size <= 32){
            databasa[0] = mask & ((1ULL<<size) - 1);
        }else{
            databasa[0] = mask & ((1ULL<<32) - 1);
            databasa[1] = mask & (((1ULL<<(size + 32)) - 1) - ((1ULL<<32) - 1));
        }
    }else{
        databasa[0] = mask & ((1ULL<<32) - 1);
        databasa[1] = mask & (((0xFFFFFFFFFFFFFFFF) - 1) - ((1ULL<<32) - 1));
        for (uint64_t i = 2; i < word; i++){
            databasa[i] = 0;
        }
    }
}

void BitsetD::set(const int32_t index, bool val)
{
    if (index < 0 || index >= size_) {
        throw std::invalid_argument("BitsetD::get: index out of range");
    }
    int32_t word = index / 32 + int(bool(index % 32));
    word--;
    int32_t i = index % 32;
    if (val){
        databasa[word] = databasa[word] | (1ULL<<i);
    }else{
        databasa[word] = databasa[word] & (~(1ULL<<i));
    }
}

bool BitsetD::get(int32_t index) const
{
    if (index < 0 || index >= size_) {
        throw std::invalid_argument("BitsetD::get: index out of range");
    }
    int32_t wordindex = index / 32;
    int32_t indexposition = index % 32;
    int32_t mask = 1ULL<<indexposition;
    return (databasa[wordindex] & mask) != 0;
}

void BitsetD::invert() noexcept
{
    if (size_ == 0) return;
    int32_t i = size_ % 32;
    if (i == 0){
        i = 32;
    }
    for (int32_t i = 0; i < size_ - 1; ++i) {
        databasa[i] = ~databasa[i];
    }
    databasa[size_ - 1] = (~databasa[size_ - 1]) & ((1ULL<<i) - 1);
}

void BitsetD::fill(const bool val) noexcept 
{
    if (size_ == 0) {
        throw std::invalid_argument("BitsetD::resize - non positive size");
    }

    int32_t word = size_ / 32 + bool(size_ % 32);
    databasa.resize(word);
    if (val){
        for (uint64_t i = 0; i < word - 1; i++){
            databasa[i] = (1ULL<<32) - 1;
        }
        if (size_%32 == 0){
            databasa[word - 1] = (1ULL<<32) - 1;
        }else{
            databasa[word - 1] = (1ULL<<(size_%32)) - 1;
        }
    }else{
        for (uint64_t i = 0; i < word; i++){
            databasa[i] = 0;
        }
    }
}

void BitsetD::resize(const std::int32_t new_size, bool val) noexcept
{
    if (new_size >= 0){
        throw std::invalid_argument("BitsetD constructor: size cannot be negative");
    }
    int32_t word = new_size / 32 + bool(new_size % 32);
    databasa.resize(word);
    this->fill(val);
}

bool BitsetD::operator==(const BitsetD& rhs) noexcept
{
    if (size() != rhs.size_) {
        return false;
    } else {
        for (int32_t i = 0; i < databasa.size(); i++) {
            if (databasa[i] != rhs.databasa[i]) {
                return false;
            }
        }
    }
    return true;
}

BitsetD& BitsetD::shift(const std::int32_t idx) noexcept
{
    int32_t k = idx;
    k = k % size();
    if (k == 0){
        return *this;
    }


    BitsetD bitset(size(), false);

    for (int32_t i = 0; i < size_; ++i) {
        int32_t old_p = i;
        int32_t new_p = (i+k)%size();

        if (new_p < 0) {
            new_p += size();
        }

        if (get(old_p)) {
            bitset.set(new_p, true);
        }
    }

    *this = bitset;
    return *this;
    
}

BitsetD& BitsetD::operator<<=(const std::int32_t shift)
{ 
    if (shift == 0) {
        return *this;
    }

    BitsetD bitset(size(), false);

    for (int32_t i = 0; i < size_ - shift; i++) {
        if (get(i) == true) {
            bitset.set(i + shift, true);
        }
    }
    *this = bitset;
    return *this; 
}

BitsetD& BitsetD::operator>>=(const std::int32_t shift)
{
    if (shift == 0) {
        return *this;
    }
    BitsetD bitset(size(), false);

    for (int32_t i = size_ - 1; i - shift >= 0; --i) {
        if (get(i) == true) {
            bitset.set(i - shift, true);
        }
    }
    *this = bitset;
    return *this; 
}

BitsetD& BitsetD::operator&=(const BitsetD& rhs)
{
    if (size() >= rhs.size()){
        for (int32_t i = 0; i < databasa.size(); i++){
            if (i >= rhs.databasa.size()){
                databasa[i] = 0;
            }else{
                databasa[i] &= rhs.databasa[i];
            }
        }
    }else{
        BitsetD A(*this);
        this->resize(rhs.size());
        for (int32_t i = 0; i < A.databasa.size(); i++){
            databasa[i] = A.databasa[i] & rhs.databasa[i];
        }
    }
    return *this;
}

BitsetD &BitsetD::operator|=(const BitsetD &rhs)
{
    if (size() >= rhs.size()){
        for (int32_t i = 0; i < rhs.databasa.size(); i++){
            databasa[i] |= rhs.databasa[i];
        }
    }else{
        BitsetD A(*this);
        this->resize(rhs.size());
        // A: 1 1 1 1 1   
        // B: 1 1 1 1 1   1
        
        for (int32_t i = 0; i < rhs.databasa.size(); i++){
            if (i >= A.databasa.size()){
                databasa[i] = rhs.databasa[i];
            }else{
                databasa[i] = A.databasa[i] | rhs.databasa[i];
            }
            
        }
    }
    return *this;
}

BitsetD &BitsetD::operator^=(const BitsetD &rhs)
{
    if (size() >= rhs.size()){
        for (int32_t i = 0; i < rhs.databasa.size(); i++){
            databasa[i] ^= rhs.databasa[i];
        }
    }else{
        BitsetD A(*this);
        this->resize(rhs.size());
        for (int32_t i = 0; i < rhs.databasa.size(); i++){
            databasa[i] = A.databasa[i] ^ rhs.databasa[i];
        }
    }
    return *this;
}

BitsetD operator<<(const BitsetD &lhs, const std::int32_t shift)
{
    BitsetD A(lhs);
    if (shift == 0){
        return A;
    }
    A.resize(lhs.size());
    for (int32_t i = 0; i < A.size() - shift; i++) {
        if (lhs.get(i) == true) {
            A.set(i + shift, true);
        }
    }

    return A; 
}

BitsetD operator>>(const BitsetD &lhs, const std::int32_t shift)
{
    BitsetD A(lhs);
    if (shift == 0){
        return A;
    }
    A.resize(lhs.size());
    for (int32_t i = A.size() - 1; i - shift >= 0; --i) {
        if (lhs.get(i) == true) {
            A.set(i - shift, true);
        }
    }

    return A;
}

BitsetD operator&(const BitsetD &lhs, const BitsetD &rhs)
{
    BitsetD A; 
    if (lhs.size() >= rhs.size()){
        A.resize(lhs.size());
        for (int32_t i = 0; i < rhs.size(); i++){
            A.set(i, lhs.get(i) & rhs.get(i));
        }
    }else{
        A.resize(rhs.size());
        for (int32_t i = 0; i < lhs.size(); i++){
            A.set(i, lhs.get(i) & rhs.get(i));
        }
    }
    return A;   
}

BitsetD operator|(const BitsetD &lhs, const BitsetD &rhs)
{
    BitsetD A; 
    if (lhs.size() >= rhs.size()){
        A.resize(lhs.size());
        for (int32_t i = 0; i < lhs.size(); i++){
            if (i >= rhs.size()){  
                A.set(i, lhs.get(i) | 0);
            }else{
                A.set(i, lhs.get(i) | rhs.get(i));
            }
        }
    }else{
        A.resize(rhs.size());
        for (int32_t i = 0; i < rhs.size(); i++){
            if (i >= lhs.size()){  
                A.set(i, rhs.get(i) | 0);
            }else{
                A.set(i, lhs.get(i) | rhs.get(i));
            }
        }
    }
    return A;   
}

BitsetD operator^(const BitsetD &lhs, const BitsetD &rhs)
{
    BitsetD A; 
    if (lhs.size() >= rhs.size()){
        A.resize(lhs.size());
        for (int32_t i = 0; i < lhs.size(); i++){
            if (i >= rhs.size()){  
                A.set(i, lhs.get(i));
            }else{
                A.set(i, lhs.get(i) ^ rhs.get(i));
            }
        }
    }else{
        A.resize(rhs.size());
        for (int32_t i = 0; i < rhs.size(); i++){
            if (i >= lhs.size()){  
                A.set(i, rhs.get(i));
            }else{
                A.set(i, lhs.get(i) ^ rhs.get(i));
            }
        }
    }
    return A; 
}
