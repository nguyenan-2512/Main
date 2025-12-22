#pragma once	
#include <cstddef> 

class Diem {
private:
    int x;
    int y;
public:
    Diem(int = 0, int = 0);
    ~Diem();

    int layX() const;
    int layY() const;

    void datX(int);
    void datY(int);
    void datXY(int, int);

    bool operator==(const Diem& khac) const;
    bool operator!=(const Diem& khac) const;
};

struct DiemHash {
    std::size_t operator()(const Diem& d) const {
        int x = d.layX();
        int y = d.layY();

        unsigned int ux = (x >= 0) ? (2 * x) : (-2 * x - 1);
        unsigned int uy = (y >= 0) ? (2 * y) : (-2 * y - 1);

        if (ux >= uy) {
            return ux * ux + ux + uy;
        }
        else {
            return uy * uy + ux;
        }
    }
};

struct SoNguyenHash {
    std::size_t operator()(int x) const {
        unsigned int ux = (x >= 0) ? static_cast<unsigned int>(x) : static_cast<unsigned int>(-x);
        ux = ((ux >> 16) ^ ux) * 0x45d9f3b;
        ux = ((ux >> 16) ^ ux) * 0x45d9f3b;
        ux = (ux >> 16) ^ ux;
        return ux;
    }
};