#pragma once
#include "Stack.h"
#include "TrangThaiDiChuyen.h"
#include "Diem.h"
#include "DynamicArray.h"

class HistoryManager {
private:
    Stack<TrangThaiDiChuyen> lichSuDiChuyen;
    
public:
    HistoryManager();
    ~HistoryManager();
    void luuTrangThai(const TrangThaiDiChuyen& trangThai);
    TrangThaiDiChuyen layTrangThaiTruoc();
    bool coTheLui() const;
    int laySoBuoc() const;
    void xoaLichSu();
};