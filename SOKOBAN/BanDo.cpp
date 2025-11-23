#include "BanDo.h"
#include <iostream>

BanDo::BanDo(int kichThuocO)
    : kichThuocO(kichThuocO), nguoiChoi(nullptr), trangThaiThua(false) {
}

BanDo::~BanDo() {
    for (int i = 0; i < cacDoiTuong.size(); i++) {
        delete cacDoiTuong[i];
    }
    delete nguoiChoi;
}

void BanDo::themDoiTuong(DoiTuongTroChoi* obj) {
    cacDoiTuong.push_back(obj);

    LoaiDoiTuong loai = obj->layLoai();
    if (loai == LoaiDoiTuong::THUNG_GO) {
        cacThungGoPtr.push_back(static_cast<ThungGo*>(obj));
    }
    else if (loai == LoaiDoiTuong::THUNG_SAT) {
        cacThungSatPtr.push_back(static_cast<ThungSat*>(obj));
    }
    else if (loai == LoaiDoiTuong::VI_TRI_DAT) {
        cacViTriDatPtr.push_back(static_cast<ViTriDat*>(obj));
    }
    else if (loai == LoaiDoiTuong::BAY) {
        cacBayPtr.push_back(static_cast<Bay*>(obj));
    }
    else if (loai == LoaiDoiTuong::NUT_BAM) {
        cacNutBamPtr.push_back(static_cast<NutBam*>(obj));
    }
}

void BanDo::datNguoiChoi(NguoiChoi* player) {
    nguoiChoi = player;
}

MangDichChuyen& BanDo::layMangDichChuyen() {
    return mangDichChuyen;
}

void BanDo::linkButtonsToTraps() {
    int soNutBam = cacNutBamPtr.size();
    int soBay = cacBayPtr.size();

    if (soNutBam > 0 && soBay > 0) {
        int bayMoiNut = soBay / soNutBam;
        int soDu = soBay % soNutBam;
        int chiSoBay = 0;

        for (int i = 0; i < soNutBam; i++) {
            int soBayChoNutNay = bayMoiNut + (i < soDu ? 1 : 0);
            for (int j = 0; j < soBayChoNutNay && chiSoBay < soBay; j++) {
                cacNutBamPtr[i]->themBayLienKet(
                    cacBayPtr[chiSoBay]->layX(),
                    cacBayPtr[chiSoBay]->layY()
                );
                chiSoBay++;
            }
        }
    }
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

bool BanDo::laTuong(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::TUONG); }
bool BanDo::laNuoc(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::NUOC); }
bool BanDo::laVatCan(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::VAT_CAN); }
bool BanDo::laCat(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::CAT); }
bool BanDo::laViTriDat(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::VI_TRI_DAT); }
bool BanDo::laThungGo(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::THUNG_GO); }
bool BanDo::laThungSat(int x, int y) const { return laLoaiDoiTuong(x, y, LoaiDoiTuong::THUNG_SAT); }

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
