#pragma once

template<typename T>
class Queue {
private:
    T* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

    void resize() {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];

        for (int i = 0; i < count; ++i) {
            newData[i] = data[(frontIndex + i) % capacity];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count;
    }

public:
    Queue() : data(nullptr), capacity(0), frontIndex(0), rearIndex(0), count(0) {}

    ~Queue() {
        delete[] data;
    }

    Queue(const Queue& other)
        : capacity(other.capacity), frontIndex(0), rearIndex(other.count), count(other.count) {
        data = new T[capacity];
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[(other.frontIndex + i) % other.capacity];
        }
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            count = other.count;
            frontIndex = 0;
            rearIndex = count;
            data = new T[capacity];
            for (int i = 0; i < count; ++i) {
                data[i] = other.data[(other.frontIndex + i) % other.capacity];
            }
        }
        return *this;
    }

    void push(const T& value) {
        if (count >= capacity) {
            resize();
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }

    void pop() {
        if (!empty()) {
            frontIndex = (frontIndex + 1) % capacity;
            count--;
        }
    }

    T& front() {
        return data[frontIndex];
    }

    const T& front() const {
        return data[frontIndex];
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void clear() {
        frontIndex = 0;
        rearIndex = 0;
        count = 0;
    }
};
