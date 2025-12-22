#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"  
#include <string>

#include "DoiTuongTroChoi.h"
#include "NguoiChoi.h"
#include "ThungGo.h"
#include "ThungSat.h"
#include "Bay.h"
#include "NutBam.h"
#include "ViTriDat.h"
#include "CongDichChuyen.h"
#include "MangDichChuyen.h"

class BanDo {
    friend class BFSSolver;
    friend class MapLoader; 
    friend class MapRenderer;

public:
    DynamicArray<ThungGo*> cacThungGoPtr;
    DynamicArray<ThungSat*> cacThungSatPtr;
    DynamicArray<ViTriDat*> cacViTriDatPtr;
    DynamicArray<Bay*> cacBayPtr;
    DynamicArray<NutBam*> cacNutBamPtr;

private:
    int kichThuocO;
    NguoiChoi* nguoiChoi;
    DynamicArray<DoiTuongTroChoi*> cacDoiTuong;
    MangDichChuyen mangDichChuyen;
    bool trangThaiThua;



public:
  
    BanDo(int kichThuocO);
    ~BanDo();
    void themDoiTuong(DoiTuongTroChoi* obj);
    void datNguoiChoi(NguoiChoi* player);
    MangDichChuyen& layMangDichChuyen();
    void linkButtonsToTraps();  

    NguoiChoi* layNguoiChoi();
    int laySoViTriDat() const { return cacViTriDatPtr.size(); }
    const MangDichChuyen& layMangDichChuyen() const { return mangDichChuyen; }
    bool layTrangThaiThua() const { return trangThaiThua; }

    void datTrangThaiThua(bool giaTri) { trangThaiThua = giaTri; }

    bool laBay(int x, int y) const;
    bool laNutBam(int x, int y) const;
    bool laCongDichChuyen(int x, int y) const;
    bool kiemTraVatCanTai(int x, int y) const;
    bool laLoaiDoiTuong(int x, int y, LoaiDoiTuong loai) const;
    bool laCat(int x, int y) const;
    bool laThungGo(int x, int y) const;
    bool laThungSat(int x, int y) const;
    bool laViTriDat(int x, int y) const;
    bool laTuong(int x, int y) const;
    bool laNuoc(int x, int y) const;
    bool laVatCan(int x, int y) const;

    Bay* timBayTai(int x, int y);
    NutBam* timNutBamTai(int x, int y);
    ThungGo* timThungGoTai(int x, int y);
    ThungSat* timThungSatTai(int x, int y);
    CongDichChuyen* timCongDichChuyenTai(int x, int y);
};