
#pragma once
#ifndef ARRAYD_HPP
#define ARRAYD_HPP

#include <iostream>
#include <cstddef>
class ArrayD {
   //поля
   public:

    ArrayD() = default;
    ArrayD(const ArrayD&);
    ArrayD(const std::ptrdiff_t size);
    ~ArrayD();
    ArrayD& operator = (const ArrayD&);


    [[nodiscard]] std::ptrdiff_t size() const noexcept { return size_; }

    void resize(const std::ptrdiff_t size);
    void remove(const std::ptrdiff_t idx);
    void insert(const std::ptrdiff_t index, const float val);


    float operator[](const std::ptrdiff_t index ) const;
    float& operator[](const std::ptrdiff_t index);

  private:
    std::ptrdiff_t size_ = 0;
    ptrdiff_t capacity_ = 0;
    float* data_ = nullptr;
};

#endif