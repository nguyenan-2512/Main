#include "BanDo.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
// ✅ THÊM: Include các lớp con để tạo đối tượng động
#include "Tuong.h"
#include "Nen.h"
#include "Nuoc.h"
#include "Cat.h"
#include "Cau.h"
#include "VatCan.h"

BanDo::BanDo(const std::string& tenFile, int kichThuocO)
    : kichThuocO(kichThuocO), nguoiChoi(nullptr), trangThaiThua(false){

    // ✅ GIỮ NGUYÊN: Load tất cả texture (200+ dòng)
    if (!ketCauTuong.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\da1.png")) {
        std::cerr << "Khong the tai texture tuong!" << std::endl;
    }
    if (!bangAnhNguoiChoi.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\playersheet2.png")) {
        std::cerr << "Khong the tai texture nguoi choi!" << std::endl;
    }
    if (!ketCauNen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\co.png")) {
        std::cerr << "Khong the tai texture nen!" << std::endl;
    }
    if (!ketCauThungGo.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thunggo.png")) {
        std::cerr << "Khong the tai texture thung go!" << std::endl;
    }
    if (!ketCauThungSat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thungsat.png")) {
        std::cerr << "Khong the tai texture thung sat!" << std::endl;
        ketCauThungSat = ketCauThungGo;
    }
    if (!ketCauNuoc.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nuoc222.png")) {
        std::cerr << "Khong the tai texture nuoc!" << std::endl;
    }
    if (!ketCauCau.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\caudoc.png")) {
        std::cerr << "Khong the tai texture cau!" << std::endl;
    }
    if (!ketCauCat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\cat.png")) {
        std::cerr << "Khong the tai texture cat!" << std::endl;
    }
    if (!ketCauBayKichHoat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Khong the tai texture bay kich hoat!" << std::endl;
    }
    if (!ketCauBayKhongKichHoat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\huynutbam.png")) {
        std::cerr << "Khong the tai texture bay khong kich hoat!" << std::endl;
    }
    if (!ketCauNutChuaNhan.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\konutbam1.png")) {
        std::cerr << "Khong the tai texture nut chua nhan!" << std::endl;
    }
    if (!ketCauNutDaNhan.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nutbam1.png")) {
        std::cerr << "Khong the tai texture nut da nhan!" << std::endl;
    }
    if (!ketCauThungGoTrenViTriDat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\godung.png")) {
        std::cerr << "Khong the tai texture thung go tren vi tri dat!" << std::endl;
        ketCauThungGoTrenViTriDat = ketCauThungGo;
    }
    if (!ketCauViTriDat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\vitridat.png")) {
        std::cerr << "Khong the tai texture vi tri dat!" << std::endl;
    }
    if (!ketCauVatCan.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Khong the tai texture vat can!" << std::endl;
    }
    if (!ketCauDichChuyen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_active.jpg")) {
        std::cerr << "Khong the tai texture dich chuyen!" << std::endl;
    }

    // ✅ THAY ĐỔI: Đọc file map với cách tiếp cận mới
    std::ifstream file(tenFile);
    std::string dong;
    int y = 0;

    while (std::getline(file, dong)) {
        for (int x = 0; x < (int)dong.size(); x++) {
            char kyTu = dong[x];

            if (kyTu == '#') {
                // ✅ TẠO ĐỐI TƯỢNG ĐỘNG
                Tuong* tuongMoi = new Tuong(x, y, kichThuocO);
                tuongMoi->datKetCau(ketCauTuong);
                cacDoiTuong.push_back(tuongMoi);  // ✅ Thêm vào mảng chung
            }
            else if (kyTu == '=') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                Cau* cauMoi = new Cau(x, y, kichThuocO);
                cauMoi->datKetCau(ketCauCau);
                cacDoiTuong.push_back(cauMoi);
            }
            else if (kyTu == '?') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                Cat* catMoi = new Cat(x, y, kichThuocO);
                catMoi->datKetCau(ketCauCat);
                cacDoiTuong.push_back(catMoi);
            }
            else if (kyTu == '~') {
                Nuoc* nuocMoi = new Nuoc(x, y, kichThuocO);
                nuocMoi->datKetCau(ketCauNuoc);
                cacDoiTuong.push_back(nuocMoi);
            }
            else if (kyTu == '@') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                nguoiChoi = new NguoiChoi(x, y, kichThuocO);
                nguoiChoi->khoiTaoHoatHinh(bangAnhNguoiChoi, 32, 32, 4);
            }
            else if (kyTu == '$') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                ThungGo* thungMoi = new ThungGo(x, y, kichThuocO);
                thungMoi->datKetCauBinhThuong(ketCauThungGo);
                thungMoi->datKetCauTrenViTriDat(ketCauThungGoTrenViTriDat);
                cacDoiTuong.push_back(thungMoi);
                cacThungGoPtr.push_back(thungMoi);  
            }
            else if (kyTu == 'I') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                ThungSat* thungSatMoi = new ThungSat(x, y, kichThuocO);
                thungSatMoi->datKetCauThungSat(ketCauThungSat);
                cacDoiTuong.push_back(thungSatMoi);
                cacThungSatPtr.push_back(thungSatMoi);
            }
            else if (kyTu == 'X' || kyTu == 'x') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                ViTriDat* viTriDatMoi = new ViTriDat(x, y, kichThuocO);
                viTriDatMoi->datKetCau(ketCauViTriDat);
                cacDoiTuong.push_back(viTriDatMoi);
                cacViTriDatPtr.push_back(viTriDatMoi);
            }
            else if (kyTu == 'O' || kyTu == 'o') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                VatCan* vatCanMoi = new VatCan(x, y, kichThuocO);
                vatCanMoi->datKetCau(ketCauVatCan);
                cacDoiTuong.push_back(vatCanMoi);
            }
            else if (kyTu == '+') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                ViTriDat* viTriDatMoi = new ViTriDat(x, y, kichThuocO);
                viTriDatMoi->datKetCau(ketCauViTriDat);
                cacDoiTuong.push_back(viTriDatMoi);
                cacViTriDatPtr.push_back(viTriDatMoi);

                nguoiChoi = new NguoiChoi(x, y, kichThuocO);
                nguoiChoi->khoiTaoHoatHinh(bangAnhNguoiChoi, 32, 32, 4);
            }
            else if (kyTu == '*') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                ViTriDat* viTriDatMoi = new ViTriDat(x, y, kichThuocO);
                viTriDatMoi->datKetCau(ketCauViTriDat);
                cacDoiTuong.push_back(viTriDatMoi);
                cacViTriDatPtr.push_back(viTriDatMoi);

                ThungGo* thungMoi = new ThungGo(x, y, kichThuocO);
                thungMoi->datKetCauBinhThuong(ketCauThungGo);
                thungMoi->datKetCauTrenViTriDat(ketCauThungGoTrenViTriDat);
                thungMoi->datTrangThaiTrenViTriDat(true);
                cacDoiTuong.push_back(thungMoi);
                cacThungGoPtr.push_back(thungMoi);
            }
            else if (kyTu == '.' || kyTu == ' ') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);
            }
            else if (kyTu == 'T') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                Bay* bayMoi = new Bay(x, y, kichThuocO);
                bayMoi->datKetCauKichHoat(ketCauBayKichHoat);
                bayMoi->datKetCauKhongKichHoat(ketCauBayKhongKichHoat);
                cacDoiTuong.push_back(bayMoi);
                cacBayPtr.push_back(bayMoi);
            }
            else if (kyTu == 'B') {
                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                NutBam* nutMoi = new NutBam(x, y, kichThuocO);
                nutMoi->datKetCauChuaNhan(ketCauNutChuaNhan);
                nutMoi->datKetCauDaNhan(ketCauNutDaNhan);
                cacDoiTuong.push_back(nutMoi);
                cacNutBamPtr.push_back(nutMoi);
            }
            else if (isdigit(kyTu)) {
                int maSo = kyTu - '0';

                Nen* nenMoi = new Nen(x, y, kichThuocO);
                nenMoi->datKetCau(ketCauNen);
                cacDoiTuong.push_back(nenMoi);

                CongDichChuyen* congMoi = new CongDichChuyen(x, y, kichThuocO, maSo);
                congMoi->datKetCau(ketCauDichChuyen);
                cacDoiTuong.push_back(congMoi);

                mangDichChuyen.themCongDichChuyen(Diem(x, y), maSo);
            }
        }
        y++;
    }
    file.close();

    int soNutBam = cacNutBamPtr.size();
    int soBay = cacBayPtr.size();

    if (soNutBam > 0 && soBay > 0) {
        int bayMoiNut = soBay / soNutBam;
        int soDu = soBay % soNutBam;
        int chiSoBay = 0;
        for (int i = 0; i < soNutBam; i++) {
            int soBayChoNutNay = bayMoiNut + (i < soDu ? 1 : 0);
            for (int j = 0; j < soBayChoNutNay && chiSoBay < soBay; j++) {
                cacNutBamPtr[i]->themBayLienKet(cacBayPtr[chiSoBay]->layX(), cacBayPtr[chiSoBay]->layY());
                chiSoBay++;
            }
        }
    }
}

BanDo::~BanDo() {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        delete cacDoiTuong[i];
    }
    delete nguoiChoi;
}

void BanDo::ve(sf::RenderWindow& cuaSo) {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        cacDoiTuong[i]->ve(cuaSo);  // ✅ Tự động gọi đúng hàm ve() của từng lớp con
    }
    if (nguoiChoi) nguoiChoi->ve(cuaSo);
}
NguoiChoi* BanDo::layNguoiChoi() {
    return nguoiChoi;
}

bool BanDo::laBay(int x, int y) const {
    for (int i = 0; i < cacBayPtr.size(); i++) {
        if (cacBayPtr[i]->layX() == x && cacBayPtr[i]->layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laNutBam(int x, int y) const {
    for (int i = 0; i < cacNutBamPtr.size(); i++) {
        if (cacNutBamPtr[i]->layX() == x && cacNutBamPtr[i]->layY() == y) {
            return true;
        }
    }
    return false;
}

Bay* BanDo::timBayTai(int x, int y) {
    for (int i = 0; i < cacBayPtr.size(); i++) {
        if (cacBayPtr[i]->layX() == x && cacBayPtr[i]->layY() == y) {
            return cacBayPtr[i];
        }
    }
    return nullptr;
}

NutBam* BanDo::timNutBamTai(int x, int y) {
    for (int i = 0; i < cacNutBamPtr.size(); i++) {
        if (cacNutBamPtr[i]->layX() == x && cacNutBamPtr[i]->layY() == y) {
            return cacNutBamPtr[i];
        }
    }
    return nullptr;
}

bool BanDo::laCongDichChuyen(int x, int y) const {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        if (cacDoiTuong[i]->layX() == x && cacDoiTuong[i]->layY() == y) {
            if (cacDoiTuong[i]->layLoai() == LoaiDoiTuong::CONG_DICH_CHUYEN) {
                return true;
            }
        }
    }
    return false;
}

CongDichChuyen* BanDo::timCongDichChuyenTai(int x, int y) {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        if (cacDoiTuong[i]->layX() == x && cacDoiTuong[i]->layY() == y) {
            if (cacDoiTuong[i]->layLoai() == LoaiDoiTuong::CONG_DICH_CHUYEN) {
                return static_cast<CongDichChuyen*>(cacDoiTuong[i]);
            }
        }
    }
    return nullptr;
}

bool BanDo::kiemTraVatCanTai(int x, int y) const {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        if (cacDoiTuong[i]->layX() == x && cacDoiTuong[i]->layY() == y) {
            if (cacDoiTuong[i]->laVatCanDiChuyen()) {
                return true;
            }
        }
    }
    return false;
}

bool BanDo::laLoaiDoiTuong(int x, int y, LoaiDoiTuong loai) const {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        if (cacDoiTuong[i]->layX() == x &&
            cacDoiTuong[i]->layY() == y &&
            cacDoiTuong[i]->layLoai() == loai) {
            return true;
        }
    }
    return false;
}

bool BanDo::laTuong(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::TUONG);
}

bool BanDo::laNuoc(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::NUOC);
}

bool BanDo::laVatCan(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::VAT_CAN);
}

bool BanDo::laCat(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::CAT);
}

bool BanDo::laViTriDat(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::VI_TRI_DAT);
}
bool BanDo::laThungGo(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::THUNG_GO);
}

bool BanDo::laThungSat(int x, int y) const {
    return laLoaiDoiTuong(x, y, LoaiDoiTuong::THUNG_SAT);
}

ThungGo* BanDo::timThungGoTai(int x, int y) {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        if (cacDoiTuong[i]->layX() == x &&
            cacDoiTuong[i]->layY() == y &&
            cacDoiTuong[i]->layLoai() == LoaiDoiTuong::THUNG_GO) {
            return static_cast<ThungGo*>(cacDoiTuong[i]);
        }
    }
    return nullptr;
}

ThungSat* BanDo::timThungSatTai(int x, int y) {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        if (cacDoiTuong[i]->layX() == x &&
            cacDoiTuong[i]->layY() == y &&
            cacDoiTuong[i]->layLoai() == LoaiDoiTuong::THUNG_SAT) {
            return static_cast<ThungSat*>(cacDoiTuong[i]);
        }
    }
    return nullptr;
}
