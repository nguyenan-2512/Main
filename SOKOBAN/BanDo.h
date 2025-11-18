#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"  
#include <string>
#include "Stack.h"
#include "Tuong.h"
#include "Nen.h"
#include "NguoiChoi.h"
#include "ThungGo.h"
#include "ViTriDat.h"
#include "VatCan.h"
#include "Nuoc.h"
#include "Cat.h"
#include "Cau.h"
#include "Bay.h"
#include "NutBam.h"
#include "ThungSat.h"
#include "CongDichChuyen.h"
#include "MangDichChuyen.h"
#include "TrangThaiDiChuyen.h"
#include "Queue.h"           
#include "TrangThaiBFS.h"  

class BanDo {
private:
    int kichThuocO;
    NguoiChoi* nguoiChoi;

    DynamicArray<Tuong> cacTuong;
    DynamicArray<Nen> cacNen;
    DynamicArray<ThungGo> cacThungGo;
    DynamicArray<ThungSat> cacThungSat;
    DynamicArray<ViTriDat> cacViTriDat;
    DynamicArray<VatCan> cacVatCan;
    DynamicArray<Nuoc> cacNuoc;
    DynamicArray<Cat> cacCat;
    DynamicArray<Cau> cacCau;

    DynamicArray<Bay> cacBay;
    DynamicArray<NutBam> cacNutBam;
    DynamicArray<CongDichChuyen> cacCongDichChuyen;
    MangDichChuyen mangDichChuyen;

    sf::Texture ketCauTuong;
    sf::Texture bangAnhNguoiChoi;
    sf::Texture bangAnhNen;
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

    Stack<TrangThaiDiChuyen> lichSuDiChuyen;

    DynamicArray<int> loiGiaiHienTai;
    int buocGiaiHienTai;
    bool dangTuDongGiai;

    void capNhatThung();
    void kiemTraNut();
	

    bool laBuocDiHopLeBFS(const Diem& viTri,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool laViTriChet(const Diem& viTriThung,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool laThungSatChet(const Diem& viTriThungSat,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    TrangThaiBFS taoTrangThaiBFS() const;

    bool nutBiNhanTrongBFS(const Diem& viTriNut,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool bayKichHoatTrongBFS(const Diem& viTriBay,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool coThungTai(const Diem& viTri,
        const DynamicArray<Diem>& cacThung,
        const DynamicArray<Diem>& cacThungSat) const;

    bool thuDichChuyenTrongBFS(Diem& viTriNguoiChoi) const;

public:
    BanDo(const std::string& tenFile, int kichThuocO);
    ~BanDo();

    void ve(sf::RenderWindow& cuaSo);
    bool thuDiChuyenNguoiChoi(int dx, int dy);
    bool kiemTraThang() const;
    NguoiChoi* layNguoiChoi();

    bool laBay(int x, int y) const;
    bool laNutBam(int x, int y) const;
    Bay* timBayTai(int x, int y);
    NutBam* timNutBamTai(int x, int y);

    bool laCongDichChuyen(int x, int y) const;
    CongDichChuyen* timCongDichChuyenTai(int x, int y);
    bool thuDichChuyen();
    MangDichChuyen& layMangDichChuyen() { return mangDichChuyen; }

    bool laCat(int x, int y) const;
    bool laTuong(int x, int y) const;
    bool laNuoc(int x, int y) const;
    bool laThungGo(int x, int y) const;
    bool laThungSat(int x, int y) const;
    bool laVatCan(int x, int y) const;
    bool laViTriDat(int x, int y) const;
    bool laBuocDiHopLe(int x, int y);

    ThungGo* timThungGoTai(int x, int y);
    ThungSat* timThungSatTai(int x, int y);
    bool diChuyenThungGo(ThungGo* thung, int dx, int dy);
    bool diChuyenThungSat(ThungSat* thungSat, int dx, int dy);

    void luuTrangThai();
    TrangThaiDiChuyen layTrangThaiHienTai() const;
    void phucHoiTrangThai(const TrangThaiDiChuyen& trangThai);
    void luiBuoc();
    int laySoBuoc() const;

    void capNhatNen(float thoiGianDelta);
    // Các hàm giải BFS
    bool timLoiGiaiBFS(int doSauToiDa = 100);
    bool thucHienBuocGiai();
    void batDauTuDongGiai();
    void dungTuDongGiai();
    bool layTrangThaiTuDongGiai() const { return dangTuDongGiai; }

    bool trangThaiThua;
    void datTrangThaiThua(bool giaTri) { trangThaiThua = giaTri; }
    bool layTrangThaiThua() const { return trangThaiThua; }
};