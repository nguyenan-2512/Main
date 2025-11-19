#pragma once
#include "Diem.h"
#include "DynamicArray.h"  
#include "HashTable.h"

class MangDichChuyen {
private:
    // Map từ vị trí → Mã số dịch chuyển
    HashTable<Diem, int, DiemHash> viTriDenMaSo;

    // Map từ mã số → danh sách các vị trí cùng mã số (cổng liên kết)
    HashTable<int, DynamicArray<Diem>, SoNguyenHash> maSoDenCacViTri;

public:
    MangDichChuyen();

    // Thêm cổng dịch chuyển
    void themCongDichChuyen(const Diem& viTri, int maSoDichChuyen);

    // Lấy điểm đến khi đi vào cổng
    Diem layDiemDen(const Diem& tuViTri) const;

    // Kiểm tra xem vị trí có phải cổng dịch chuyển không
    bool laCongDichChuyen(const Diem& viTri) const;

    // Lấy mã số của cổng tại vị trí
    int layMaSoDichChuyen(const Diem& viTri) const;

    // Lấy tất cả cổng cùng mã số
    DynamicArray<Diem> layCacCongLienKet(int maSoDichChuyen) const;

    // Xóa tất cả
    void xoa();

    // Debug: in thông tin mạng
    void inThongTinMang() const;
};