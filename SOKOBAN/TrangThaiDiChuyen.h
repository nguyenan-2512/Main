#pragma once
#include "Diem.h"
#include "DynamicArray.h"

class TrangThaiDiChuyen {
public:
    Diem viTriNguoiChoi;
    DynamicArray<Diem> cacViTriThung;

    TrangThaiDiChuyen() {}

    TrangThaiDiChuyen(const Diem& viTriNguoiChoi, const DynamicArray<Diem>& viTriThung)
        : viTriNguoiChoi(viTriNguoiChoi), cacViTriThung(viTriThung) {
    }
};