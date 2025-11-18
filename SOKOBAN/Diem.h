// Diem.h - Lớp đại diện cho điểm tọa độ (x, y)
#pragma once	
#include <cstddef> 

class Diem {
private:
    int x;
    int y;
public:
    Diem(int = 0, int = 0);
    ~Diem();

    // Getter - Lấy giá trị
    int layX() const;
    int layY() const;

    // Setter - Đặt giá trị
    void datX(int);
    void datY(int);
    void datXY(int, int);

    // Toán tử so sánh
    bool operator==(const Diem& khac) const;
    bool operator!=(const Diem& khac) const;
};

// Struct để hash Điểm (dùng trong HashTable)
struct DiemHash {
    std::size_t operator()(const Diem& d) const {
        int x = d.layX();
        int y = d.layY();

        unsigned int ux = (x >= 0) ? (2 * x) : (-2 * x - 1);// 
        unsigned int uy = (y >= 0) ? (2 * y) : (-2 * y - 1);
		//cantor pairing function
        if (ux >= uy) {
            return ux * ux + ux + uy;
        }
        else {
            return uy * uy + ux;
        }
    }
};

// Struct để hash số nguyên
struct SoNguyenHash {
     static const size_t PRIME = 2147483647; // Số nguyên tố lớn 2^31-1
    
    std::size_t operator()(int x) const {
        // Chuyển đổi số âm thành dương
        unsigned int ux = (x >= 0) ? static_cast<unsigned int>(x) 
                                  : static_cast<unsigned int>(-x);
        return ux % PRIME;
    }
};