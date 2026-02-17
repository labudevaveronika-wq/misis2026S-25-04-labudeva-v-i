#pragma once
#ifndef QUEUEA_QUEUEL_HPP
#define QUEUEA_QUEUEL_HPP

#include<cstdint>
#include<stdexcept>
#include<iostream>

class Queuel {
    public:
        Queuel();
        Queuel(const Queuel& src);
        ~Queuel() = default;
        Queuel operator=(const Queuel& src);

        void clear() noexcept;
        void puch(const int64_t vaL);
        void pop() noexcept;

        [[nodiscard]] bool is_empty() const noexcept; 
        [[nodiscard]] int64_t& top();
        [[nodiscard]] int64_t& top() const noexcept;
 

    private:
        struct Node
        {
            int64_t val; 
            Node* next = nullptr;
        };

        Node* head_ = nullptr;
        Node* first_ = nullptr;
};


#endif