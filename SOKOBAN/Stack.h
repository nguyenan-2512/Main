#pragma once

template<typename T>
class Stack {
private:
    T* data;
    int capacity;
    int topIndex; 

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < topIndex; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    Stack() : data(nullptr), capacity(0), topIndex(0) {}

    ~Stack() {
        delete[] data;
    }

    Stack(const Stack& other)
        : capacity(other.capacity), topIndex(other.topIndex) {
        data = new T[capacity];
        for (int i = 0; i < topIndex; ++i) {
            data[i] = other.data[i];
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            topIndex = other.topIndex;
            data = new T[capacity];
            for (int i = 0; i < topIndex; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push(const T& value) {
        if (topIndex >= capacity) {
            resize();
        }
        data[topIndex++] = value;
    }

    void pop() {
        if (!empty()) {
            topIndex--;
        }
    }

    T& top() {
        return data[topIndex - 1];
    }

    const T& top() const {
        return data[topIndex - 1];
    }

    bool empty() const {
        return topIndex == 0;
    }

    int size() const {
        return topIndex;
    }

    void clear() {
        topIndex = 0;
    }
};