#pragma once
#include <utility>  // để dùng std::forward

template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int count;  // ✅ đổi tên từ "size" để không trùng với hàm size()

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
    // ✅ Constructor mặc định
    DynamicArray() : data(nullptr), capacity(0), count(0) {}

    // ✅ Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // ✅ Copy constructor
    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (int i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    // ✅ Assignment operator
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

    // ✅ emplace_back (chuyển tiếp tham số linh hoạt)
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (count >= capacity) resize();
        data[count++] = T(std::forward<Args>(args)...);
    }

    // ✅ push_back (thêm phần tử theo kiểu copy)
    void push_back(const T& value) {
        if (count >= capacity) resize();
        data[count++] = value;
    }

    // ✅ Truy cập phần tử cuối cùng
    T& back() {
        return data[count - 1];
    }
    const T& back() const {
        return data[count - 1];
    }

    // ✅ Truy cập theo chỉ số
    T& operator[](int index) {
        return data[index];
    }
    const T& operator[](int index) const {
        return data[index];
    }

    // ✅ Hàm trả kích thước
    int size() const {   // giờ không trùng biến nữa
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

    // ✅ Hỗ trợ iterator (cho range-based for)
    T* begin() { return data; }
    T* end() { return data + count; }
    const T* begin() const { return data; }
    const T* end() const { return data + count; }
};
