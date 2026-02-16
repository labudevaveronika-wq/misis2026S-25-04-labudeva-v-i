#pragma once
#pragma once
#ifndef QUEUEA_QUEUEA_HPP
#define QUEUEA_QUEUEA_HPP


#include<cstdint>
#include<stdexcept>
#include<iostream>

class Queuea {
    private:
        int64_t* data_ = nullptr;
        int16_t size_ = 0;
        int16_t capacity_ = 0;
        int16_t startindex = 0;
    public:
        Queuea();
        Queuea(const Queuea& src);
        Queuea& operator=(const Queuea& src);
        bool is_empty() const noexcept;
        void pop();
        void push(const int16_t val);
        int64_t& top();
        int64_t top() const;
        void clear() noexcept;
        ~Queuea() noexcept;      
};
#endif