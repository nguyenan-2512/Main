#include "BanDo.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

BanDo::BanDo(const std::string& tenFile, int kichThuocO)
    : kichThuocO(kichThuocO), nguoiChoi(nullptr), trangThaiThua(false),
    dangTuDongGiai(false), buocGiaiHienTai(0) {

    // Load tất cả texture
    if (!ketCauTuong.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\da1.png")) {
        std::cerr << "Khong the tai texture tuong!" << std::endl;
    }
    if (!bangAnhNguoiChoi.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\playersheet2.png")) {
        std::cerr << "Khong the tai texture nguoi choi!" << std::endl;
    }
    if (!bangAnhNen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\co_animation.png")) {
        std::cerr << "Khong the tai sprite sheet nen animation!" << std::endl;
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

    // Đọc file map
    std::ifstream file(tenFile);
    std::string dong;
    int y = 0;
    while (std::getline(file, dong)) {
        for (int x = 0; x < (int)dong.size(); x++) {
            char kyTu = dong[x];

            if (kyTu == '#') {
                cacTuong.emplace_back(x, y, kichThuocO);
                cacTuong.back().datKetCau(ketCauTuong);
            }
            else if (kyTu == '=') {
                cacCau.emplace_back(x, y, kichThuocO);
                cacCau.back().datKetCau(ketCauCau);
            }
            else if (kyTu == '?') {
                cacCat.emplace_back(x, y, kichThuocO);
                cacCat.back().datKetCau(ketCauCat);
            }
            else if (kyTu == '~') {
                cacNuoc.emplace_back(x, y, kichThuocO);
                cacNuoc.back().datKetCau(ketCauNuoc);
            }
            else if (kyTu == '@') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                nguoiChoi = new NguoiChoi(x, y, kichThuocO);
                nguoiChoi->khoiTaoHoatHinh(bangAnhNguoiChoi, 32, 32, 4);
            }
            else if (kyTu == '$') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacThungGo.emplace_back(x, y, kichThuocO);
                cacThungGo.back().datKetCauBinhThuong(ketCauThungGo);
                cacThungGo.back().datKetCauTrenViTriDat(ketCauThungGoTrenViTriDat);
            }
            else if (kyTu == 'I') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacThungSat.emplace_back(x, y, kichThuocO);
                cacThungSat.back().datKetCauThungSat(ketCauThungSat);
            }
            else if (kyTu == 'X' || kyTu == 'x') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacViTriDat.emplace_back(x, y, kichThuocO);
                cacViTriDat.back().datKetCau(ketCauViTriDat);
            }
            else if (kyTu == 'O' || kyTu == 'o') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacVatCan.emplace_back(x, y, kichThuocO);
                cacVatCan.back().datKetCau(ketCauVatCan);
            }
            else if (kyTu == '+') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacViTriDat.emplace_back(x, y, kichThuocO);
                cacViTriDat.back().datKetCau(ketCauViTriDat);
                nguoiChoi = new NguoiChoi(x, y, kichThuocO);
                nguoiChoi->khoiTaoHoatHinh(bangAnhNguoiChoi, 32, 32, 4);
            }
            else if (kyTu == '*') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacViTriDat.emplace_back(x, y, kichThuocO);
                cacViTriDat.back().datKetCau(ketCauViTriDat);
                cacThungGo.emplace_back(x, y, kichThuocO);
                cacThungGo.back().datKetCauBinhThuong(ketCauThungGo);
                cacThungGo.back().datKetCauTrenViTriDat(ketCauThungGoTrenViTriDat);
                cacThungGo.back().datTrangThaiTrenViTriDat(true);
            }
            else if (kyTu == '.' || kyTu == ' ') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
            }
            else if (kyTu == 'T') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacBay.emplace_back(x, y, kichThuocO);
                cacBay.back().datKetCauKichHoat(ketCauBayKichHoat);
                cacBay.back().datKetCauKhongKichHoat(ketCauBayKhongKichHoat);
            }
            else if (kyTu == 'B') {
                cacNen.emplace_back(x, y, kichThuocO);
                cacNen.back().khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacNutBam.emplace_back(x, y, kichThuocO);
                cacNutBam.back().datKetCauChuaNhan(ketCauNutChuaNhan);
                cacNutBam.back().datKetCauDaNhan(ketCauNutDaNhan);
            }
            else if (isdigit(kyTu)) {
                int maSo = kyTu - '0';

                Nen nen(x, y, kichThuocO);
                nen.khoiTaoHoatHinh(bangAnhNen, 32, 32, 5);
                cacNen.push_back(nen);

                CongDichChuyen congDichChuyen(x, y, kichThuocO, maSo);
                congDichChuyen.datKetCau(ketCauDichChuyen);
                cacCongDichChuyen.push_back(congDichChuyen);

                mangDichChuyen.themCongDichChuyen(Diem(x, y), maSo);
            }
        }
        y++;
    }
    file.close();

    int soNutBam = cacNutBam.size();
    int soBay = cacBay.size();

    if (soNutBam > 0 && soBay > 0) {
        int bayMoiNut = soBay / soNutBam;
        int soDu = soBay % soNutBam;
        int chiSoBay = 0;
        for (int i = 0; i < soNutBam; i++) {
            int soBayChoNutNay = bayMoiNut + (i < soDu ? 1 : 0);
            for (int j = 0; j < soBayChoNutNay && chiSoBay < soBay; j++) {
                cacNutBam[i].themBayLienKet(cacBay[chiSoBay].layX(), cacBay[chiSoBay].layY());
                chiSoBay++;
            }
        }
    }
    capNhatThung();
    kiemTraNut();
}

BanDo::~BanDo() {
    delete nguoiChoi;
}

void BanDo::ve(sf::RenderWindow& cuaSo) {
    for (int i = 0; i < cacNen.getSize(); i++) cacNen[i].ve(cuaSo);
    for (int i = 0; i < cacNuoc.getSize(); i++) cacNuoc[i].ve(cuaSo);
    for (int i = 0; i < cacCat.getSize(); i++) cacCat[i].ve(cuaSo);
    for (int i = 0; i < cacCau.getSize(); i++) cacCau[i].ve(cuaSo);
    for (int i = 0; i < cacViTriDat.getSize(); i++) cacViTriDat[i].ve(cuaSo);
    for (int i = 0; i < cacCongDichChuyen.getSize(); i++) cacCongDichChuyen[i].ve(cuaSo);
    for (int i = 0; i < cacNutBam.getSize(); i++) cacNutBam[i].ve(cuaSo);
    for (int i = 0; i < cacBay.getSize(); i++) cacBay[i].ve(cuaSo);
    for (int i = 0; i < cacVatCan.getSize(); i++) cacVatCan[i].ve(cuaSo);
    for (int i = 0; i < cacTuong.getSize(); i++) cacTuong[i].ve(cuaSo);
    for (int i = 0; i < cacThungGo.getSize(); i++) cacThungGo[i].ve(cuaSo);
    for (int i = 0; i < cacThungSat.getSize(); i++) cacThungSat[i].ve(cuaSo);

    if (nguoiChoi) nguoiChoi->ve(cuaSo);
}

NguoiChoi* BanDo::layNguoiChoi() {
    return nguoiChoi;
}

bool BanDo::laBay(int x, int y) const {
    for (const Bay& bay : cacBay) {
        if (bay.layX() == x && bay.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laNutBam(int x, int y) const {
    for (const NutBam& nut : cacNutBam) {
        if (nut.layX() == x && nut.layY() == y) {
            return true;
        }
    }
    return false;
}

Bay* BanDo::timBayTai(int x, int y) {
    for (auto& bay : cacBay) {
        if (bay.layX() == x && bay.layY() == y) {
            return &bay;
        }
    }
    return nullptr;
}

NutBam* BanDo::timNutBamTai(int x, int y) {
    for (auto& nut : cacNutBam) {
        if (nut.layX() == x && nut.layY() == y) {
            return &nut;
        }
    }
    return nullptr;
}

void BanDo::kiemTraNut() {
    for (auto& nut : cacNutBam) {
        int nx = nut.layX();
        int ny = nut.layY();

        bool coThung = laThungGo(nx, ny);
        bool coThungSat = laThungSat(nx, ny);
        bool duocNhan = coThung || coThungSat;

        nut.datTrangThaiNhan(duocNhan);

        const auto& cacBayLienKet = nut.layCacBayLienKet();

        for (const auto& viTriBay : cacBayLienKet) {
            Bay* bay = timBayTai(viTriBay.first, viTriBay.second);
            if (bay) {
                bay->datKichHoat(!duocNhan);
            }
        }
    }
}

bool BanDo::laCongDichChuyen(int x, int y) const {
    for (const CongDichChuyen& cong : cacCongDichChuyen) {
        if (cong.layX() == x && cong.layY() == y) {
            return true;
        }
    }
    return false;
}

CongDichChuyen* BanDo::timCongDichChuyenTai(int x, int y) {
    for (auto& cong : cacCongDichChuyen) {
        if (cong.layX() == x && cong.layY() == y) {
            return &cong;
        }
    }
    return nullptr;
}

bool BanDo::thuDichChuyen() {
    if (!nguoiChoi || trangThaiThua) return false;

    int px = nguoiChoi->layX();
    int py = nguoiChoi->layY();

    if (!laCongDichChuyen(px, py)) {
        std::cout << "Khong co cong dich chuyen tai vi tri nay!" << std::endl;
        return false;
    }

    Diem viTriHienTai(px, py);
    Diem diemDen = mangDichChuyen.layDiemDen(viTriHienTai);

    if (diemDen == viTriHienTai) {
        std::cout << "Khong the dich chuyen!" << std::endl;
        return false;
    }

    int xDich = diemDen.layX();
    int yDich = diemDen.layY();

    if (laTuong(xDich, yDich) || laVatCan(xDich, yDich) ||
        laThungGo(xDich, yDich) || laThungSat(xDich, yDich) || laNuoc(xDich, yDich)) {
        std::cout << "Diem den bi chan, khong the dich chuyen!" << std::endl;
        return false;
    }

    Bay* bay = timBayTai(xDich, yDich);
    if (bay && bay->layTrangThaiKichHoat()) {
        std::cout << "Ban da dich chuyen vao bay! Thua cuoc!" << std::endl;
        trangThaiThua = true;
        return false;
    }

    luuTrangThai();

    nguoiChoi->datViTri(xDich, yDich, 0, 0);

    std::cout << "Dich chuyen thanh cong tu (" << px << "," << py
        << ") den (" << xDich << "," << yDich << ")!" << std::endl;

    return true;
}

bool BanDo::laTuong(int x, int y) const {
    for (const Tuong& tuong : cacTuong) {
        if (tuong.layX() == x && tuong.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laNuoc(int x, int y) const {
    for (const Nuoc& nuoc : cacNuoc) {
        if (nuoc.layX() == x && nuoc.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laCat(int x, int y) const {
    for (const Cat& cat : cacCat) {
        if (cat.layX() == x && cat.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laThungGo(int x, int y) const {
    for (const ThungGo& thung : cacThungGo) {
        if (thung.layX() == x && thung.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laThungSat(int x, int y) const {
    for (const ThungSat& thungSat : cacThungSat) {
        if (thungSat.layX() == x && thungSat.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laVatCan(int x, int y) const {
    for (const VatCan& vatCan : cacVatCan) {
        if (vatCan.layX() == x && vatCan.layY() == y) {
            return true;
        }
    }
    return false;
}

bool BanDo::laViTriDat(int x, int y) const {
    for (const ViTriDat& viTri : cacViTriDat) {
        if (viTri.layX() == x && viTri.layY() == y) {
            return true;
        }
    }
    return false;
}

ThungGo* BanDo::timThungGoTai(int x, int y) {
    for (auto& thung : cacThungGo) {
        if (thung.layX() == x && thung.layY() == y) {
            return &thung;
        }
    }
    return nullptr;
}
ThungSat* BanDo::timThungSatTai(int x, int y) {
    for (auto& thungSat : cacThungSat) {
        if (thungSat.layX() == x && thungSat.layY() == y) {
            return &thungSat;
        }
    }
    return nullptr;
}

bool BanDo::laBuocDiHopLe(int x, int y) {
    if (laTuong(x, y) || laVatCan(x, y) || laNuoc(x, y)) {
        return false;
    }
    return true;
}

bool BanDo::diChuyenThungGo(ThungGo* thung, int dx, int dy) {
    int xMoi = thung->layX() + dx;
    int yMoi = thung->layY() + dy;

    Bay* bay = timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        return false;
    }

    if (!laTuong(xMoi, yMoi) && !laVatCan(xMoi, yMoi) &&
        !laThungGo(xMoi, yMoi) && !laThungSat(xMoi, yMoi) && !laNuoc(xMoi, yMoi)) {
        thung->datViTri(xMoi, yMoi);
        capNhatThung();
        kiemTraNut();
        return true;
    }
    return false;
}

bool BanDo::diChuyenThungSat(ThungSat* thungSat, int dx, int dy) {
    int xMoi = thungSat->layX() + dx;
    int yMoi = thungSat->layY() + dy;

    Bay* bay = timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        return false;
    }

    if (!laTuong(xMoi, yMoi) && !laVatCan(xMoi, yMoi) &&
        !laThungGo(xMoi, yMoi) && !laThungSat(xMoi, yMoi) && !laNuoc(xMoi, yMoi)) {
        thungSat->datViTri(xMoi, yMoi);
        kiemTraNut();
        return true;
    }
    return false;
}

bool BanDo::thuDiChuyenNguoiChoi(int dx, int dy) {
    if (!nguoiChoi || trangThaiThua) return false;

    int xMoi = nguoiChoi->layX() + dx;
    int yMoi = nguoiChoi->layY() + dy;

    if (laTuong(xMoi, yMoi) || laVatCan(xMoi, yMoi) || laNuoc(xMoi, yMoi)) {
        return false;
    }

    Bay* bay = timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        trangThaiThua = true;
        return false;
    }

    ThungGo* thung = timThungGoTai(xMoi, yMoi);
    if (thung) {
        if (!diChuyenThungGo(thung, dx, dy)) {
            return false;
        }
    }

    ThungSat* thungSat = timThungSatTai(xMoi, yMoi);
    if (thungSat) {
        if (!diChuyenThungSat(thungSat, dx, dy)) {
            return false;
        }
    }

    luuTrangThai();
    nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
    kiemTraNut();

    return true;
}

void BanDo::capNhatThung() {
    for (auto& thung : cacThungGo) {
        bool trenViTriDat = laViTriDat(thung.layX(), thung.layY());
        thung.datTrangThaiTrenViTriDat(trenViTriDat);
    }
}

bool BanDo::kiemTraThang() const {
    for (const auto& thung : cacThungGo) {
        bool trenViTriDat = false;
        for (const auto& viTri : cacViTriDat) {
            if (thung.layX() == viTri.layX() && thung.layY() == viTri.layY()) {
                trenViTriDat = true;
                break;
            }
        }
        if (!trenViTriDat) return false;
    }
    return cacThungGo.size() > 0 && cacThungGo.size() == cacViTriDat.size();
}

void BanDo::luuTrangThai() {
    TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
    lichSuDiChuyen.push(trangThai);
}

TrangThaiDiChuyen BanDo::layTrangThaiHienTai() const {
    Diem viTriNguoiChoi = nguoiChoi->layViTri();
    DynamicArray<Diem> cacViTriThung;

    for (const auto& thung : cacThungGo) {
        cacViTriThung.push_back(thung.layViTri());
    }

    return TrangThaiDiChuyen(viTriNguoiChoi, cacViTriThung);
}

void BanDo::phucHoiTrangThai(const TrangThaiDiChuyen& trangThai) {
    nguoiChoi->datViTri(trangThai.viTriNguoiChoi.layX(),
        trangThai.viTriNguoiChoi.layY(), 0, 0);

    for (size_t i = 0; i < cacThungGo.size() && i < trangThai.cacViTriThung.size(); i++) {
        cacThungGo[i].datViTri(trangThai.cacViTriThung[i].layX(),
            trangThai.cacViTriThung[    i].layY());
    }

    capNhatThung();
}

void BanDo::luiBuoc() {
    if (lichSuDiChuyen.empty()) {
        return;
    }

    TrangThaiDiChuyen trangThaiTruoc = lichSuDiChuyen.top();
    lichSuDiChuyen.pop();
    phucHoiTrangThai(trangThaiTruoc);
}

int BanDo::laySoBuoc() const {
    return (int)lichSuDiChuyen.size();
}

bool BanDo::nutBiNhanTrongBFS(const Diem& viTriNut,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    for (int i = 0; i < cacThung.size(); i++) {
        if (cacThung[i] == viTriNut) return true;
    }
    for (int i = 0; i < cacThungSat.size(); i++) {
        if (cacThungSat[i] == viTriNut) return true;
    }
    return false;
}

bool BanDo::bayKichHoatTrongBFS(const Diem& viTriBay,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    // Tìm nút điều khiển bẫy này
    for (int i = 0; i < cacNutBam.size(); i++) {
        const auto& cacBayLienKet = cacNutBam[i].layCacBayLienKet();

        for (int j = 0; j < cacBayLienKet.size(); j++) {
            if (cacBayLienKet[j].first == viTriBay.layX() &&
                cacBayLienKet[j].second == viTriBay.layY()) {
                Diem viTriNut(cacNutBam[i].layX(), cacNutBam[i].layY());
                bool nutDuocNhan = nutBiNhanTrongBFS(viTriNut, cacThung, cacThungSat);
                return !nutDuocNhan;
            }
        }
    }
    return true;
}

bool BanDo::coThungTai(const Diem& viTri,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    for (int i = 0; i < cacThung.size(); i++) {
        if (cacThung[i] == viTri) return true;
    }
    for (int i = 0; i < cacThungSat.size(); i++) {
        if (cacThungSat[i] == viTri) return true;
    }
    return false;
}

bool BanDo::laBuocDiHopLeBFS(const Diem& viTri,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTri.layX();
    int y = viTri.layY();

    if (laTuong(x, y) || laNuoc(x, y) || laVatCan(x, y)) {
        return false;
    }
    if (laBay(x, y)) {
        Diem viTriBay(x, y);
        if (bayKichHoatTrongBFS(viTriBay, cacThung, cacThungSat)) {
            return false;
        }
    }
    if (coThungTai(viTri, cacThung, cacThungSat)) {
        return false;
    }

    return true;
}

bool BanDo::laViTriChet(const Diem& viTriThung,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTriThung.layX();
    int y = viTriThung.layY();

    if (laViTriDat(x, y)) {
        return false;
    }
    if (laNutBam(x, y)) {
        return false;
    }
    bool traiChan = laTuong(x - 1, y) || laVatCan(x - 1, y);
    bool phaiChan = laTuong(x + 1, y) || laVatCan(x + 1, y);
    bool trenChan = laTuong(x, y - 1) || laVatCan(x, y - 1);
    bool duoiChan = laTuong(x, y + 1) || laVatCan(x, y + 1);

    if ((traiChan && trenChan) || (phaiChan && trenChan) ||
        (traiChan && duoiChan) || (phaiChan && duoiChan)) {
        return true;
    }

    if (cacThung.size() >= 4) {
        Diem keCanh[3] = {
            Diem(x + 1, y),      // Phải
            Diem(x, y + 1),      // Dưới
            Diem(x + 1, y + 1)   // Phải-Dưới
        };

        int soThungKeCanh = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < cacThung.size(); j++) {
                if (cacThung[j] == keCanh[i]) {
                    soThungKeCanh++;
                    break;
                }
            }
        }

        if (soThungKeCanh == 3) {
            bool coViTriDatTrong2x2 = laViTriDat(x, y) ||
                laViTriDat(x + 1, y) ||
                laViTriDat(x, y + 1) ||
                laViTriDat(x + 1, y + 1);

            bool coNutTrong2x2 = laNutBam(x, y) ||
                laNutBam(x + 1, y) ||
                laNutBam(x, y + 1) ||
                laNutBam(x + 1, y + 1);

            if (!coViTriDatTrong2x2 && !coNutTrong2x2) {
                return true;
            }
        }
    }

    return false;
}

bool BanDo::laThungSatChet(const Diem& viTriThungSat,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTriThungSat.layX();
    int y = viTriThungSat.layY();

    if (laNutBam(x, y)) {
        return false;
    }

    if (laViTriDat(x, y)) {
        return true;
    }

    bool traiChan = laTuong(x - 1, y) || laVatCan(x - 1, y);
    bool phaiChan = laTuong(x + 1, y) || laVatCan(x + 1, y);
    bool trenChan = laTuong(x, y - 1) || laVatCan(x, y - 1);
    bool duoiChan = laTuong(x, y + 1) || laVatCan(x, y + 1);

    if ((traiChan && trenChan) || (phaiChan && trenChan) ||
        (traiChan && duoiChan) || (phaiChan && duoiChan)) {
        return true;
    }

    return false;
}

bool BanDo::thuDichChuyenTrongBFS(Diem& viTriNguoiChoi) const {
    if (!laCongDichChuyen(viTriNguoiChoi.layX(), viTriNguoiChoi.layY())) {
        return false;
    }

    Diem diemDen = const_cast<BanDo*>(this)->mangDichChuyen.layDiemDen(viTriNguoiChoi);

    if (diemDen == viTriNguoiChoi) {
        return false;
    }

    viTriNguoiChoi = diemDen;
    return true;
}

TrangThaiBFS BanDo::taoTrangThaiBFS() const {
    Diem viTriNguoiChoi = nguoiChoi->layViTri();
    DynamicArray<Diem> cacViTriThung;
    DynamicArray<Diem> cacViTriThungSat;

    for (int i = 0; i < cacThungGo.size(); i++) {
        cacViTriThung.push_back(cacThungGo[i].layViTri());
    }

    for (int i = 0; i < cacThungSat.size(); i++) {
        cacViTriThungSat.push_back(cacThungSat[i].layViTri());
    }

    return TrangThaiBFS(viTriNguoiChoi, cacViTriThung, cacViTriThungSat, 0);
}

bool BanDo::timLoiGiaiBFS(int doSauToiDa) {
    loiGiaiHienTai.clear();
    buocGiaiHienTai = 0;

    TrangThaiBFS trangThaiBanDau = taoTrangThaiBFS();

    Queue<TrangThaiBFS> hangDoi;
    hangDoi.push(trangThaiBanDau);

    HashTable<TrangThaiBFS, bool, TrangThaiBFSHash> daThamQua(50000);
    daThamQua.insert(trangThaiBanDau, true);

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    int soTrangThaiDaKhamPha = 0;
    const int SO_TRANG_THAI_TOI_DA = 1000000;

    while (!hangDoi.empty() && soTrangThaiDaKhamPha < SO_TRANG_THAI_TOI_DA) {

        TrangThaiBFS trangThaiHienTai = hangDoi.front();
        hangDoi.pop();
        soTrangThaiDaKhamPha++;

        int soThungTrenViTriDat = 0;
        for (int i = 0; i < trangThaiHienTai.cacViTriThung.size(); i++) {
            if (laViTriDat(trangThaiHienTai.cacViTriThung[i].layX(),
                trangThaiHienTai.cacViTriThung[i].layY())) {
                soThungTrenViTriDat++;
            }
        }

        if (soThungTrenViTriDat == trangThaiHienTai.cacViTriThung.size() &&
            trangThaiHienTai.cacViTriThung.size() == cacViTriDat.size()) {

            loiGiaiHienTai = trangThaiHienTai.duongDi;
            return true;
        }

        if (trangThaiHienTai.doSau >= doSauToiDa) {
            continue;
        }

        if (laCongDichChuyen(trangThaiHienTai.viTriNguoiChoi.layX(),
            trangThaiHienTai.viTriNguoiChoi.layY())) {
            Diem viTriNguoiChoiMoi = trangThaiHienTai.viTriNguoiChoi;
            if (thuDichChuyenTrongBFS(viTriNguoiChoiMoi)) {
                if (laBuocDiHopLeBFS(viTriNguoiChoiMoi, trangThaiHienTai.cacViTriThung,
                    trangThaiHienTai.cacViTriThungSat)) {
                    TrangThaiBFS trangThaiMoi(viTriNguoiChoiMoi, trangThaiHienTai.cacViTriThung,
                        trangThaiHienTai.cacViTriThungSat, trangThaiHienTai.doSau + 1);
                    trangThaiMoi.duongDi = trangThaiHienTai.duongDi;
                    trangThaiMoi.duongDi.push_back(4);

                    if (!daThamQua.contains(trangThaiMoi)) {
                        daThamQua.insert(trangThaiMoi, true);
                        hangDoi.push(trangThaiMoi);
                    }
                }
            }
        }

        for (int huong = 0; huong < 4; huong++) {
            int xNguoiChoiMoi = trangThaiHienTai.viTriNguoiChoi.layX() + dx[huong];
            int yNguoiChoiMoi = trangThaiHienTai.viTriNguoiChoi.layY() + dy[huong];
            Diem viTriNguoiChoiMoi(xNguoiChoiMoi, yNguoiChoiMoi);

            DynamicArray<Diem> cacThungMoi = trangThaiHienTai.cacViTriThung;
            DynamicArray<Diem> cacThungSatMoi = trangThaiHienTai.cacViTriThungSat;

            int chiSoThung = -1;
            for (int i = 0; i < cacThungMoi.size(); i++) {
                if (cacThungMoi[i] == viTriNguoiChoiMoi) {
                    chiSoThung = i;
                    break;
                }
            }

            int chiSoThungSat = -1;
            for (int i = 0; i < cacThungSatMoi.size(); i++) {
                if (cacThungSatMoi[i] == viTriNguoiChoiMoi) {
                    chiSoThungSat = i;
                    break;
                }
            }

            if (chiSoThung != -1) {
                int xThungMoi = viTriNguoiChoiMoi.layX() + dx[huong];
                int yThungMoi = viTriNguoiChoiMoi.layY() + dy[huong];
                Diem viTriThungMoi(xThungMoi, yThungMoi);

                if (!laBuocDiHopLeBFS(viTriThungMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
                cacThungMoi[chiSoThung] = viTriThungMoi;
                if (laViTriChet(viTriThungMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
            }
            else if (chiSoThungSat != -1) {
                int xThungSatMoi = viTriNguoiChoiMoi.layX() + dx[huong];
                int yThungSatMoi = viTriNguoiChoiMoi.layY() + dy[huong];
                Diem viTriThungSatMoi(xThungSatMoi, yThungSatMoi);

                if (!laBuocDiHopLeBFS(viTriThungSatMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
                if (laThungSatChet(viTriThungSatMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
                cacThungSatMoi[chiSoThungSat] = viTriThungSatMoi;
            }
            else {
                if (!laBuocDiHopLeBFS(viTriNguoiChoiMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
            }

            TrangThaiBFS trangThaiMoi(viTriNguoiChoiMoi, cacThungMoi, cacThungSatMoi,
                trangThaiHienTai.doSau + 1);
            trangThaiMoi.duongDi = trangThaiHienTai.duongDi;
            trangThaiMoi.duongDi.push_back(huong);

            if (!daThamQua.contains(trangThaiMoi)) {
                daThamQua.insert(trangThaiMoi, true);
                hangDoi.push(trangThaiMoi);
            }
        }
    }

    return false;
}

bool BanDo::thucHienBuocGiai() {
    if (buocGiaiHienTai >= loiGiaiHienTai.size()) {
        dungTuDongGiai();
        return false;
    }

    int hanhDong = loiGiaiHienTai[buocGiaiHienTai];
    if (hanhDong == 4) {
        bool daDichChuyen = thuDichChuyen();
        if (daDichChuyen) {
            buocGiaiHienTai++;
            return true;
        }
        return false;
    }
    else {
        int dx[] = { 0, 0, -1, 1 };
        int dy[] = { -1, 1, 0, 0 };

        bool daDiChuyen = thuDiChuyenNguoiChoi(dx[hanhDong], dy[hanhDong]);

        if (daDiChuyen) {
            buocGiaiHienTai++;
        }

        return daDiChuyen;
    }
}

void BanDo::batDauTuDongGiai() {
    dangTuDongGiai = true;
    buocGiaiHienTai = 0;
}

void BanDo::dungTuDongGiai() {
    dangTuDongGiai = false;
}