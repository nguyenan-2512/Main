#include "MangDichChuyen.h"
#include <iostream>

MangDichChuyen::MangDichChuyen() {
}

void MangDichChuyen::themCongDichChuyen(const Diem& viTri, int maSoDichChuyen) {
    viTriDenMaSo.insert(viTri, maSoDichChuyen);

    DynamicArray<Diem> cacViTri;
    if (maSoDenCacViTri.find(maSoDichChuyen, cacViTri)) {
        cacViTri.push_back(viTri);
        maSoDenCacViTri.insert(maSoDichChuyen, cacViTri);
    }
    else {
        DynamicArray<Diem> viTriMoi;
        viTriMoi.push_back(viTri);
        maSoDenCacViTri.insert(maSoDichChuyen, viTriMoi);
    }
}

Diem MangDichChuyen::layDiemDen(const Diem& tuViTri) const {
    int maSo;
    if (!viTriDenMaSo.find(tuViTri, maSo)) {
        return tuViTri;
    }

    DynamicArray<Diem> cacDiemDen;
    if (!maSoDenCacViTri.find(maSo, cacDiemDen) || cacDiemDen.size() <= 1) {
        return tuViTri;
    }

    for (int i = 0; i < cacDiemDen.size(); i++) {
        if (cacDiemDen[i] != tuViTri) {
            return cacDiemDen[i];
        }
    }

    return tuViTri;
}

bool MangDichChuyen::laCongDichChuyen(const Diem& viTri) const {
    return viTriDenMaSo.contains(viTri);
}

int MangDichChuyen::layMaSoDichChuyen(const Diem& viTri) const {
    int maSo;
    if (viTriDenMaSo.find(viTri, maSo)) {
        return maSo;
    }
    return -1;
}

DynamicArray<Diem> MangDichChuyen::layCacCongLienKet(int maSoDichChuyen) const {
    DynamicArray<Diem> ketQua;
    maSoDenCacViTri.find(maSoDichChuyen, ketQua);
    return ketQua;
}

void MangDichChuyen::xoa() {
    viTriDenMaSo.clear();
    maSoDenCacViTri.clear();
}

void MangDichChuyen::inThongTinMang() const {
    for (auto it = maSoDenCacViTri.begin(); it != maSoDenCacViTri.end(); ++it) {
        const DynamicArray<Diem>& cacViTri = it->value;
    }
}