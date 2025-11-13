#pragma once
#include "Diem.h"
#include "DynamicArray.h"
#include <cstddef>

class TrangThaiBFS {
public:
    Diem viTriNguoiChoi;                    // Vị trí người chơi
    DynamicArray<Diem> cacViTriThung;       // Vị trí các thùng gỗ thường
    DynamicArray<Diem> cacViTriThungSat;    // Vị trí các thùng sắt
    DynamicArray<int> duongDi;              // Đường đi (0=Lên, 1=Xuống, 2=Trái, 3=Phải, 4=DichChuyen)
    int doSau;                              // Độ sâu (số bước đi)

    TrangThaiBFS() : viTriNguoiChoi(0, 0), doSau(0) {}

    TrangThaiBFS(const Diem& viTriNguoiChoi,
        const DynamicArray<Diem>& viTriThung,
        const DynamicArray<Diem>& viTriThungSat,
        int doSau = 0)
        : viTriNguoiChoi(viTriNguoiChoi),
        cacViTriThung(viTriThung),
        cacViTriThungSat(viTriThungSat),
        doSau(doSau) {
    }

    bool operator==(const TrangThaiBFS& khac) const {
        if (viTriNguoiChoi != khac.viTriNguoiChoi) {
            return false;
        }

        if (cacViTriThung.size() != khac.cacViTriThung.size()) {
            return false;
        }

        if (cacViTriThungSat.size() != khac.cacViTriThungSat.size()) {
            return false;
        }

        // Kiểm tra tất cả thùng gỗ có trong danh sách không
        for (int i = 0; i < cacViTriThung.size(); i++) {
            bool timThay = false;
            for (int j = 0; j < khac.cacViTriThung.size(); j++) {
                if (cacViTriThung[i] == khac.cacViTriThung[j]) {
                    timThay = true;
                    break;
                }
            }
            if (!timThay) {
                return false;
            }
        }

        // Kiểm tra tất cả thùng sắt có trong danh sách không
        for (int i = 0; i < cacViTriThungSat.size(); i++) {
            bool timThay = false;
            for (int j = 0; j < khac.cacViTriThungSat.size(); j++) {
                if (cacViTriThungSat[i] == khac.cacViTriThungSat[j]) {
                    timThay = true;
                    break;
                }
            }
            if (!timThay) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const TrangThaiBFS& khac) const {
        return !(*this == khac);
    }
};

// Struct để hash TrangThaiBFS
struct TrangThaiBFSHash {
    std::size_t operator()(const TrangThaiBFS& trangThai) const {
        std::size_t hash = 0;

        DiemHash diemHash;
        hash = diemHash(trangThai.viTriNguoiChoi);

        // Hash các vị trí thùng gỗ
        for (int i = 0; i < trangThai.cacViTriThung.size(); i++) {
            std::size_t thungHash = diemHash(trangThai.cacViTriThung[i]);
            hash ^= (thungHash << (i % 16));
        }

        // Hash các vị trí thùng sắt
        for (int i = 0; i < trangThai.cacViTriThungSat.size(); i++) {
            std::size_t thungSatHash = diemHash(trangThai.cacViTriThungSat[i]);
            hash ^= (thungSatHash << ((i + 8) % 16));
        }

        return hash;
    }
};