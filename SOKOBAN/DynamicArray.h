#pragma once
#include <utility>  

template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int count; 

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), count(0) {}

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            count = other.count;
            data = new T[capacity];
            for (int i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (count >= capacity) resize();
        data[count++] = T(std::forward<Args>(args)...);
    }

    void push_back(const T& value) {
        if (count >= capacity) resize();
        data[count++] = value;
    }

    T& back() {
        return data[count - 1];
    }
    const T& back() const {
        return data[count - 1];
    }

    T& operator[](int index) {
        return data[index];
    }
    const T& operator[](int index) const {
        return data[index];
    }

    int size() const {  
        return count;
    }

    int getSize() const {
        return count; 
    }
    bool empty() const {
        return count == 0;
    }

    void clear() {
        count = 0;
    }

    T* begin() { return data; }
    T* end() { return data + count; }
    const T* begin() const { return data; }
    const T* end() const { return data + count; }
};
