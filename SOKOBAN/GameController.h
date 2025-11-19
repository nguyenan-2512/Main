// GameController.h - UPDATED VERSION
#pragma once
#include "BanDo.h"
#include "HistoryManager.h"
#include "BFSSolver.h"
#include "TrangThaiBFS.h"
#include "TrangThaiDiChuyen.h"

class GameController {
private:
    BanDo* map;
    HistoryManager* historyManager;
    BFSSolver* bfsSolver;

    // BFS auto-solve state
    DynamicArray<int> loiGiaiHienTai;
    int buocGiaiHienTai;
    bool dangTuDongGiai;

    // ✅ Helper methods (private)
    void capNhatThung();
    void capNhatNutVaBay();
    TrangThaiDiChuyen layTrangThaiHienTai() const;
    void phucHoiTrangThai(const TrangThaiDiChuyen& trangThai);
    TrangThaiBFS taoTrangThaiBFS() const;

    // ✅ THÊM MỚI: Kiểm tra vị trí hợp lệ cho thùng
    bool kiemTraViTriHopLeChoThung(int x, int y) const;

public:
    GameController(BanDo* banDo);
    ~GameController();

    // ========================
    // ✅ DI CHUYỂN & GAME LOGIC
    // ========================
    bool diChuyenNguoiChoi(int dx, int dy);

    // ❌ XÓA: diChuyenThungGo() - Không cần nữa
    // ❌ XÓA: diChuyenThungSat() - Không cần nữa

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
    // ✅ RESET
    // ========================
    void reset();
};