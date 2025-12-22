#pragma once
#include "Diem.h"
#include "DynamicArray.h"
#include <cstddef>

class TrangThaiBFS {
public:
    Diem viTriNguoiChoi;                 
    DynamicArray<Diem> cacViTriThung;       
    DynamicArray<Diem> cacViTriThungSat;    
    DynamicArray<int> duongDi;              
    int doSau;                              

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

struct TrangThaiBFSHash {
    std::size_t operator()(const TrangThaiBFS& trangThai) const {
        std::size_t hash = 0;

        DiemHash diemHash;
        hash = diemHash(trangThai.viTriNguoiChoi);
        for (int i = 0; i < trangThai.cacViTriThung.size(); i++) {
            std::size_t thungHash = diemHash(trangThai.cacViTriThung[i]);
            hash ^= (thungHash << (i % 16));
        }
        for (int i = 0; i < trangThai.cacViTriThungSat.size(); i++) {
            std::size_t thungSatHash = diemHash(trangThai.cacViTriThungSat[i]);
            hash ^= (thungSatHash << ((i + 8) % 16));
        }

        return hash;
    }
};