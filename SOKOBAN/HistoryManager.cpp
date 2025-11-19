#include "HistoryManager.h"

HistoryManager::HistoryManager() {
    // Constructor rỗng
}

HistoryManager::~HistoryManager() {
    xoaLichSu();
}

void HistoryManager::luuTrangThai(const TrangThaiDiChuyen& trangThai) {
    lichSuDiChuyen.push(trangThai);
}

TrangThaiDiChuyen HistoryManager::layTrangThaiTruoc() {
    if (lichSuDiChuyen.empty()) {
        // ✅ Trả về trạng thái rỗng nếu không có lịch sử
        return TrangThaiDiChuyen(Diem(0, 0), DynamicArray<Diem>());
    }
    
    TrangThaiDiChuyen trangThai = lichSuDiChuyen.top();
    lichSuDiChuyen.pop();
    return trangThai;
}

bool HistoryManager::coTheLui() const {
    return !lichSuDiChuyen.empty();
}

int HistoryManager::laySoBuoc() const {
    return lichSuDiChuyen.size();
}

void HistoryManager::xoaLichSu() {
    while (!lichSuDiChuyen.empty()) {
        lichSuDiChuyen.pop();
    }
}