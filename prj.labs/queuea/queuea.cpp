#include "queuea.hpp"
#include<cstdint>
#include<stdexcept>
#include<iostream>

Queuea::Queuea()
{
    data_ = new int64_t[20];
    size_ = 0;
    capacity_ = 20;
    startindex = 0;

}

Queuea::Queuea(const Queuea& src)
{
    data_ = new int64_t[src.capacity_];
    capacity_ = src.capacity_;
    size_ = src.size_;
    startindex = 0;
    for (int64_t t = 0; t < src.size_; t++) {
        data_[t] = src.data_[src.startindex + t];
    }
}

Queuea &Queuea::operator=(const Queuea& src)
{
    if (this == &src){
        return *this;
    }
    if (this != nullptr){
        delete[] data_;
        data_ = nullptr; 
    }

    data_ = new int64_t[src.capacity_];
    capacity_ = src.capacity_;
    size_ = src.size_;
    startindex = 0;
    for (int64_t t = 0; t < src.size_; t++) {
        data_[t] = src.data_[src.startindex + t];
    }
}

bool Queuea::is_empty() const noexcept
{
    return size_ == 0;
}

void Queuea::pop()
{
    if (size_ == 0){
        throw std::invalid_argument("pop on epmty queue");
    } else {
        size_--;
        startindex++;
    }
}

void Queuea::push(const int16_t val)
{
    if (size_ + startindex == capacity_) {
        int64_t* new_data_ = new int64_t[capacity_ + 10];
        for (int64_t t = 0; t < size_; t++) {
            new_data_[t] = data_[t + startindex];
        }
        capacity_ += 10;
        delete[] data_;
        data_ = new_data_;
        startindex = 0;
    }
}

int64_t& Queuea::top()
{
    if (size_ == 0) {
        throw std::invalid_argument("Top of an EMPTY queue");
    }
    return data_[startindex];
}

int64_t Queuea::top() const
{
    return 0;
}

void Queuea::clear() noexcept
{
}

Queuea::~Queuea() noexcept
{
}
