#include "MangDichChuyen.h"
#include <iostream>

MangDichChuyen::MangDichChuyen() {
}

void MangDichChuyen::themCongDichChuyen(const Diem& viTri, int maSoDichChuyen) {
    viTriDenMaSo.insert(viTri, maSoDichChuyen);

    // Lấy danh sách hiện tại hoặc tạo mới
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

    std::cout << "Da them cong dich chuyen tai (" << viTri.layX() << "," << viTri.layY()
        << ") voi ma so: " << maSoDichChuyen << std::endl;
}

Diem MangDichChuyen::layDiemDen(const Diem& tuViTri) const {
    int maSo;
    if (!viTriDenMaSo.find(tuViTri, maSo)) {
        return tuViTri; // Không phải cổng dịch chuyển
    }

    DynamicArray<Diem> cacDiemDen;
    if (!maSoDenCacViTri.find(maSo, cacDiemDen) || cacDiemDen.size() <= 1) {
        std::cout << "Khong co cong dich den!" << std::endl;
        return tuViTri;
    }

    // Tìm cổng đích (không phải cổng hiện tại)
    for (int i = 0; i < cacDiemDen.size(); i++) {
        if (cacDiemDen[i] != tuViTri) {
            std::cout << "Dich chuyen tu (" << tuViTri.layX() << "," << tuViTri.layY()
                << ") den (" << cacDiemDen[i].layX() << "," << cacDiemDen[i].layY()
                << ")" << std::endl;
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
    std::cout << "\n=== Mang Dich Chuyen ===" << std::endl;

    // Duyệt qua maSoDenCacViTri
    for (auto it = maSoDenCacViTri.begin(); it != maSoDenCacViTri.end(); ++it) {
        std::cout << "Ma so " << it->key << ": ";
        const DynamicArray<Diem>& cacViTri = it->value;
        for (int i = 0; i < cacViTri.size(); i++) {
            std::cout << "(" << cacViTri[i].layX() << "," << cacViTri[i].layY() << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "========================\n" << std::endl;
}