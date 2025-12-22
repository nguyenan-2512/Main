#include "HistoryManager.h"

HistoryManager::HistoryManager() {
}

HistoryManager::~HistoryManager() {
    xoaLichSu();
}

void HistoryManager::luuTrangThai(const TrangThaiDiChuyen& trangThai) {
    lichSuDiChuyen.push(trangThai);
}

TrangThaiDiChuyen HistoryManager::layTrangThaiTruoc() {
    if (lichSuDiChuyen.empty()) {
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