#pragma once
#include "BanDo.h"
#include "HistoryManager.h"
#include "BFSSolver.h"
#include "TrangThaiBFS.h"
#include "TrangThaiDiChuyen.h"
#include "BoxTriggerUpdater.h"

// ✅ Class quản lý TOÀN BỘ logic game
class GameController {
private:
    BanDo* map;                          // Reference đến map (không sở hữu)
    HistoryManager* historyManager;      // Quản lý undo
    BFSSolver* bfsSolver;                // Tìm lời giải BFS
    
    // BFS auto-solve state
    DynamicArray<int> loiGiaiHienTai;
    int buocGiaiHienTai;
    bool dangTuDongGiai;
    
    // ✅ Helper methods (private)
    TrangThaiDiChuyen layTrangThaiHienTai() const;
    void phucHoiTrangThai(const TrangThaiDiChuyen& trangThai);
    TrangThaiBFS taoTrangThaiBFS() const;

    BoxTriggerUpdater boxTriggerUpdater;
    
public:
    GameController(BanDo* banDo);
    ~GameController();
    
    // ========================
    // ✅ DI CHUYỂN & GAME LOGIC
    // ========================
    bool diChuyenNguoiChoi(int dx, int dy);
    bool diChuyenThungGo(ThungGo* thung, int dx, int dy);
    bool diChuyenThungSat(ThungSat* thungSat, int dx, int dy);
    bool thucHienDichChuyen();  // Teleport
    
    bool kiemTraThang() const;
    bool kiemTraThua() const;
    
    // ========================
    // ✅ UNDO/REDO
    // ========================
    void undo();
    int laySoBuoc() const;
    bool coTheLui() const;
    
    // ========================
    // ✅ BFS AUTO-SOLVE
    // ========================
    bool timLoiGiaiBFS(int doSauToiDa = 100);
    void batDauTuDongGiai();
    void dungTuDongGiai();
    bool thucHienBuocGiai();
    bool layTrangThaiTuDongGiai() const;
    
    // ========================
    // ✅ RESET (khi restart game)
    // ========================
    void reset();
};