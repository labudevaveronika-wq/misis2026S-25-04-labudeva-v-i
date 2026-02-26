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
    if (val){
        for (uint64_t i = 0; i < word - 1; i++){
            databasa[i] = (1<<32) - 1;
        }
        if (size%32 == 0){
            databasa[word - 1] = (1<<32) - 1;
        }else{
            databasa[word - 1] = (1<<(size%32)) - 1;
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
    // TODOOOOOO
    if (size <= 0){
        throw std::invalid_argument("BitsetD constructor: size cannot be negative");
    }
    int32_t word = size / 32 + bool(size % 32);
    databasa.resize(word);
    if (size < 64){
        if (size <= 32){
            databasa[0] = mask & ((1<<size) - 1);
        }else{
            databasa[0] = mask & ((1<<32) - 1);
            databasa[1] = mask & (((1<<(size + 32)) - 1) - ((1<<32) - 1));
        }
    }else{
        databasa[0] = mask & ((1<<32) - 1);
        databasa[1] = mask & (((1<<64) - 1) - ((1<<32) - 1));
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
    int32_t word = index / 32 + bool(index % 32);
    int32_t i = index % 32;
    i--;
    if (i == -1){
        i = 31;
    }

    if (val){
        databasa[word - 1] = databasa[word - 1] | (1 << i);
    }else{
        databasa[word - 1] = databasa[word - 1] & (~(1<<i));
    }
}

bool BitsetD::get(int32_t index) const
{
    if (index < 0 || index >= size_) {
        throw std::invalid_argument("BitsetD::get: index out of range");
    }
    int32_t wordindex = index / 32;
    int32_t indexposition = index % 32;
    indexposition--;
    if (indexposition == -1){
        indexposition = 31;
    }
    int32_t mask = 1 << indexposition;
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
    databasa[size_ - 1] = (~databasa[size_ - 1]) & ((1<<i) - 1);
}

void BitsetD::fill(bool val)
{
    if (size_ == 0) {
        throw std::invalid_argument("BitsetD::resize - non positive size");
    }

    int32_t word = size_ / 32 + bool(size_ % 32);
    databasa.resize(word);
    if (val){
        for (uint64_t i = 0; i < word - 1; i++){
            databasa[i] = (1<<32) - 1;
        }
        if (size_%32 == 0){
            databasa[word - 1] = (1<<32) - 1;
        }else{
            databasa[word - 1] = (1<<(size_%32)) - 1;
        }
    }else{
        for (uint64_t i = 0; i < word; i++){
            databasa[i] = 0;
        }
    }
}

void BitsetD::resize(const std::int32_t new_size, const bool val = false) noexcept
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


BitsetD &BitsetD::shift(const std::int32_t idx) noexcept
{
    // TODO: insert return statement here
}

BitsetD &BitsetD::operator<<=(const std::int32_t shift)
{
    // TODO: insert return statement here
}

BitsetD &BitsetD::operator>>=(const std::int32_t shift)
{
    // TODO: insert return statement here
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
}

BitsetD &BitsetD::operator^=(const BitsetD &rhs)
{
    // TODO: insert return statement here
}

