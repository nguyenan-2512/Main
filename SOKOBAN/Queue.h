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

        // Copy dữ liệu từ queue cũ sang queue mới
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

    // Copy constructor
    Queue(const Queue& other)
        : capacity(other.capacity), frontIndex(0), rearIndex(other.count), count(other.count) {
        data = new T[capacity];
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[(other.frontIndex + i) % other.capacity];
        }
    }

    // Assignment operator
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

    // Thêm phần tử vào cuối queue
    void push(const T& value) {
        if (count >= capacity) {
            resize();
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }

    // Xóa phần tử ở đầu queue
    void pop() {
        if (!empty()) {
            frontIndex = (frontIndex + 1) % capacity;
            count--;
        }
    }

    // Lấy phần tử đầu tiên
    T& front() {
        return data[frontIndex];
    }

    const T& front() const {
        return data[frontIndex];
    }

    // Kiểm tra queue có rỗng không
    bool empty() const {
        return count == 0;
    }

    // Lấy số lượng phần tử
    int size() const {
        return count;
    }

    // Xóa tất cả phần tử
    void clear() {
        frontIndex = 0;
        rearIndex = 0;
        count = 0;
    }
};
