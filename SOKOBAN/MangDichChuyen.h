#pragma once
#include "Diem.h"
#include "DynamicArray.h"  
#include "HashTable.h"

class MangDichChuyen {
private:
    HashTable<Diem, int, DiemHash> viTriDenMaSo;
    HashTable<int, DynamicArray<Diem>, SoNguyenHash> maSoDenCacViTri;

public:
    MangDichChuyen();
    void themCongDichChuyen(const Diem& viTri, int maSoDichChuyen);
    Diem layDiemDen(const Diem& tuViTri) const;
    bool laCongDichChuyen(const Diem& viTri) const;
    int layMaSoDichChuyen(const Diem& viTri) const;
    DynamicArray<Diem> layCacCongLienKet(int maSoDichChuyen) const;
    void xoa();
    void inThongTinMang() const;
};