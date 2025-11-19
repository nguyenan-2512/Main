#pragma once
#include "Stack.h"
#include "TrangThaiDiChuyen.h"
#include "Diem.h"
#include "DynamicArray.h"

// ✅ Class quản lý lịch sử di chuyển (Undo/Redo)
class HistoryManager {
private:
    Stack<TrangThaiDiChuyen> lichSuDiChuyen;
    
public:
    HistoryManager();
    ~HistoryManager();
    
    // ✅ Lưu trạng thái
    void luuTrangThai(const TrangThaiDiChuyen& trangThai);
    
    // ✅ Lấy trạng thái trước đó (và xóa khỏi stack)
    TrangThaiDiChuyen layTrangThaiTruoc();
    
    // ✅ Kiểm tra có thể undo không
    bool coTheLui() const;
    
    // ✅ Lấy số bước đã đi
    int laySoBuoc() const;
    
    // ✅ Xóa toàn bộ lịch sử (khi restart game)
    void xoaLichSu();
};