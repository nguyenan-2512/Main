#pragma once
#include "BanDo.h"
#include "HistoryManager.h"
#include "BFSSolver.h"
#include "TrangThaiBFS.h"
#include "TrangThaiDiChuyen.h"
#include "BoxTriggerUpdater.h"

class GameController {
private:
    BanDo* map;                        
    HistoryManager* historyManager;  
    BFSSolver* bfsSolver;                
    
    DynamicArray<int> loiGiaiHienTai;
    int buocGiaiHienTai;
    bool dangTuDongGiai;
    
    TrangThaiDiChuyen layTrangThaiHienTai() const;
    void phucHoiTrangThai(const TrangThaiDiChuyen& trangThai);
    TrangThaiBFS taoTrangThaiBFS() const;

    BoxTriggerUpdater boxTriggerUpdater;
    
public:
    GameController(BanDo* banDo);
    ~GameController();
    
    bool diChuyenNguoiChoi(int dx, int dy);
    bool diChuyenThungGo(ThungGo* thung, int dx, int dy);
    bool diChuyenThungSat(ThungSat* thungSat, int dx, int dy);
    bool thucHienDichChuyen(); 
    
    bool kiemTraThang() const;
    bool kiemTraThua() const;
    
    void undo();
    int laySoBuoc() const;
    bool coTheLui() const;
    
    bool timLoiGiaiBFS(int doSauToiDa = 100);
    void batDauTuDongGiai();
    void dungTuDongGiai();
    bool thucHienBuocGiai();
    bool layTrangThaiTuDongGiai() const;
    
    void reset();
};