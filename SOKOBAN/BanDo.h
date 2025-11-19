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

    // ✅ Textures (sẽ chuyển sang ResourceManager sau)
    sf::Texture ketCauTuong;
    sf::Texture bangAnhNguoiChoi;
    sf::Texture ketCauNen;
    sf::Texture ketCauThungGo;
    sf::Texture ketCauThungSat;
    sf::Texture ketCauThungGoTrenViTriDat;
    sf::Texture ketCauViTriDat;
    sf::Texture ketCauVatCan;
    sf::Texture ketCauNuoc;
    sf::Texture ketCauCat;
    sf::Texture ketCauCau;
    sf::Texture ketCauBayKichHoat;
    sf::Texture ketCauBayKhongKichHoat;
    sf::Texture ketCauNutChuaNhan;
    sf::Texture ketCauNutDaNhan;
    sf::Texture ketCauDichChuyen;

    // ❌ XÓA TẤT CẢ:
    // HistoryManager* historyManager;
    // DynamicArray<int> loiGiaiHienTai;
    // int buocGiaiHienTai;
    // bool dangTuDongGiai;

    bool trangThaiThua;

public:
    BanDo(const std::string& tenFile, int kichThuocO);
    ~BanDo();

    void ve(sf::RenderWindow& cuaSo);

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

    // ✅ Find objects
    Bay* timBayTai(int x, int y);
    NutBam* timNutBamTai(int x, int y);
    ThungGo* timThungGoTai(int x, int y);
    ThungSat* timThungSatTai(int x, int y);
    CongDichChuyen* timCongDichChuyenTai(int x, int y);

};