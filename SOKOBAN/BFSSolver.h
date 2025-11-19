#pragma once
#include "DynamicArray.h"
#include "Queue.h"
#include "HashTable.h"
#include "TrangThaiBFS.h"
#include "Diem.h"

// Forward declaration để tránh circular dependency
class BanDo;

class BFSSolver {
private:
    const BanDo* banDo;  // ✅ Con trỏ const để truy cập map (chỉ đọc)

    // ✅ Helper methods cho BFS
    bool laBuocDiHopLeBFS(const Diem& viTri,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool laViTriChet(const Diem& viTriThung,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool laThungSatChet(const Diem& viTriThungSat,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool nutBiNhanTrongBFS(const Diem& viTriNut,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool bayKichHoatTrongBFS(const Diem& viTriBay,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool coThungTai(const Diem& viTri,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    Diem layDiemDenDichChuyen(const Diem& viTri) const;

    bool kiemTraBayKichHoat(const Diem& viTriBay,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool thuDichChuyenTrongBFS(Diem& viTriNguoiChoi) const;

public:
    // ✅ Constructor nhận con trỏ BanDo
    BFSSolver(const BanDo* map);

    // ✅ Hàm chính: Tìm lời giải BFS
    bool timLoiGiai(TrangThaiBFS trangThaiBanDau,
        DynamicArray<int>& loiGiai,
        int doSauToiDa = 100);
};