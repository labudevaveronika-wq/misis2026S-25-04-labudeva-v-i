#include "stacka.hpp"
#include <iostream>
#include <utility>
#include <cstring>


stacka::stacka(const stacka &src)
     {
    if (src.data != nullptr && src.capacity > 0) {
        capacity = src.capacity;
        size = src.size;
        data = new int64_t[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = src.data[i];
        }
    }
}

stacka::~stacka() {
    clear();
}

stacka& stacka::operator=(const stacka &rhs) {
    if (this != &rhs) {
        delete[] data;

        size = 0;
        capacity = 0;
        data = nullptr;

        if (rhs.data != nullptr && rhs.capacity > 0) {
            capacity = rhs.capacity;
            size = rhs.size;
            data = new int64_t[capacity];
            for (size_t i = 0; i < size; i++) {
                data[i] = rhs.data[i];
            }
        }
    }
    return *this;
}

bool stacka::is_empty() const noexcept {
    return size == 0;
}

void stacka::pop() noexcept {
    if (size > 0) {
        size--;
    }
}

void stacka::resize(size_t new_size) {
    if (new_size > capacity) {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        if (new_capacity < new_size) {
            new_capacity = new_size;
        }

        int64_t* new_data = new int64_t[new_capacity];

        if (data != nullptr) {
            for (size_t i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
        }

        data = new_data;
        capacity = new_capacity;
    }

    if (new_size > size) {
        for (size_t i = size; i < new_size; i++) {
            data[i] = 0;
        }
    }

    size = new_size;
}

void stacka::push(const int64_t val) {
    if (size >= capacity) {
        size_t new_capacity = (capacity == 0) ? 1 : capacity + 1;

        int64_t* new_data = new int64_t[new_capacity];

        if (data != nullptr) {
            std::memcpy(new_data, data, size * sizeof(int64_t));
            delete[] data;
        }

        data = new_data;
        capacity = new_capacity;
    }

    data[size] = val;
    size++;
}
int64_t stacka::top() const {
    if (size == 0) throw std::runtime_error("Stack is empty");
    return data[size-1];
}

int64_t& stacka::top() {
    if (size == 0) throw std::runtime_error("Stack is empty");
    return data[size-1];
}

void stacka::clear() noexcept {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}