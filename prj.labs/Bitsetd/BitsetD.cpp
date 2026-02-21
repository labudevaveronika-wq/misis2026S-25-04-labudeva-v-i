#include "Bitsetd.hpp"
#include <stdexcept>

BitsetD::BitsetD(const BitsetD& src) {
    size_ = src.size_;
    databasa = src.databasa;
}

BitsetD::BitsetD(const std::int32_t size)
{
}

BitsetD &BitsetD::operator=(const BitsetD& rhs)
{
    if (this != &rhs){
        size_ = rhs.size_;
        databasa = rhs.databasa;
    }
    return *this;
}


void BitsetD::set(const int32_t index, bool val)
{

}

bool BitsetD::get(int32_t index) const
{
    return false;
}

void BitsetD::invert() noexcept
{
    
}

void BitsetD::fill(bool val)
{
    if (size_ == 0) {
        throw std::invalid_argument("BitsetD::resize - non positive size");
    }

    std::fill(databasa.begin(), databasa.end(), val);
}

int32_t BitsetD::size()
{
    return 0;
}

void BitsetD::resize()
{
}

bool BitsetD::operator==(const BitsetD& rhs) noexcept
{
    if (size_ != rhs.size_) {
        return false;
    } else {
        for (int32_t i = 0; i < databasa.size(); i++) {
            if (databasa[i] == rhs.databasa[i]) {
                return true;
            }
        }
    }
}
