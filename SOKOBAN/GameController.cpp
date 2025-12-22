#include "GameController.h"
#include <iostream>

GameController::GameController(BanDo* banDo) 
    : map(banDo), buocGiaiHienTai(0), dangTuDongGiai(false) {
    
    historyManager = new HistoryManager();
    bfsSolver = new BFSSolver(map);
    

    boxTriggerUpdater.capNhatThung(map);
    boxTriggerUpdater.capNhatNutVaBay(map);
}

GameController::~GameController() {
    delete historyManager;
    delete bfsSolver;
}
bool GameController::diChuyenNguoiChoi(int dx, int dy) {
    NguoiChoi* nguoiChoi = map->layNguoiChoi();
    if (!nguoiChoi || map->layTrangThaiThua()) return false;

    int xMoi = nguoiChoi->layX() + dx;
    int yMoi = nguoiChoi->layY() + dy;

    ThungGo* thung = map->timThungGoTai(xMoi, yMoi);
    if (thung) {
        if (!diChuyenThungGo(thung, dx, dy)) {
            return false;
        }
        TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
        historyManager->luuTrangThai(trangThai);
        nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
        boxTriggerUpdater.capNhatNutVaBay(map);
        return true;
    }
    ThungSat* thungSat = map->timThungSatTai(xMoi, yMoi);
    if (thungSat) {
        if (!diChuyenThungSat(thungSat, dx, dy)) {
            return false;
        }
        TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
        historyManager->luuTrangThai(trangThai);
        nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
        boxTriggerUpdater.capNhatNutVaBay(map);
        return true;
    }

    if (map->kiemTraVatCanTai(xMoi, yMoi)) {
        return false;
    }

    Bay* bay = map->timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        map->datTrangThaiThua(true);
        return false;
    }
    TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
    historyManager->luuTrangThai(trangThai);
    nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
    boxTriggerUpdater.capNhatNutVaBay(map);

    return true;
}

bool GameController::diChuyenThungGo(ThungGo* thung, int dx, int dy) {
    int xMoi = thung->layX() + dx;
    int yMoi = thung->layY() + dy;

    Bay* bay = map->timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        return false;
    }

    if (!map->kiemTraVatCanTai(xMoi, yMoi) &&
        !map->laThungGo(xMoi, yMoi) &&
        !map->laThungSat(xMoi, yMoi)) {
        
        thung->datViTri(xMoi, yMoi);
        boxTriggerUpdater.capNhatThung(map);
        boxTriggerUpdater.capNhatNutVaBay(map);
        return true;
    }
    return false;
}

bool GameController::diChuyenThungSat(ThungSat* thungSat, int dx, int dy) {
    int xMoi = thungSat->layX() + dx;
    int yMoi = thungSat->layY() + dy;

    Bay* bay = map->timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        return false;
    }

    if (!map->kiemTraVatCanTai(xMoi, yMoi) &&
        !map->laThungGo(xMoi, yMoi) &&
        !map->laThungSat(xMoi, yMoi)) {

        thungSat->datViTri(xMoi, yMoi);
        boxTriggerUpdater.capNhatThung(map);
        boxTriggerUpdater.capNhatNutVaBay(map);
        return true;
    }
    return false;
}

bool GameController::thucHienDichChuyen() {
    NguoiChoi* nguoiChoi = map->layNguoiChoi();
    if (!nguoiChoi || map->layTrangThaiThua()) return false;

    int px = nguoiChoi->layX();
    int py = nguoiChoi->layY();

    if (!map->laCongDichChuyen(px, py)) {
        return false;
    }

    Diem viTriHienTai(px, py);
    Diem diemDen = map->layMangDichChuyen().layDiemDen(viTriHienTai);

    if (diemDen == viTriHienTai) {
        return false;
    }

    int xDich = diemDen.layX();
    int yDich = diemDen.layY();

    if (map->kiemTraVatCanTai(xDich, yDich) ||
        map->laThungGo(xDich, yDich) ||
        map->laThungSat(xDich, yDich)) {
        return false;
    }

    Bay* bay = map->timBayTai(xDich, yDich);
    if (bay && bay->layTrangThaiKichHoat()) {
        map->datTrangThaiThua(true);
        return false;
    }

    TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
    historyManager->luuTrangThai(trangThai);
    
    nguoiChoi->datViTri(xDich, yDich, 0, 0);
    return true;
}

bool GameController::kiemTraThang() const {
    for (int i = 0; i < map->cacThungGoPtr.size(); i++) {
        bool trenViTriDat = false;
        for (int j = 0; j < map->cacViTriDatPtr.size(); j++) {
            if (map->cacThungGoPtr[i]->layX() == map->cacViTriDatPtr[j]->layX() &&
                map->cacThungGoPtr[i]->layY() == map->cacViTriDatPtr[j]->layY()) {
                trenViTriDat = true;
                break;
            }
        }
        if (!trenViTriDat) return false;
    }
    return map->cacThungGoPtr.size() > 0 && 
           map->cacThungGoPtr.size() == map->cacViTriDatPtr.size();
}

bool GameController::kiemTraThua() const {
    return map->layTrangThaiThua();
}

void GameController::undo() {
    if (!historyManager->coTheLui()) {
        return;
    }

    TrangThaiDiChuyen trangThaiTruoc = historyManager->layTrangThaiTruoc();
    phucHoiTrangThai(trangThaiTruoc);
}

int GameController::laySoBuoc() const {
    return historyManager->laySoBuoc();
}

bool GameController::coTheLui() const {
    return historyManager->coTheLui();
}

TrangThaiDiChuyen GameController::layTrangThaiHienTai() const {
    NguoiChoi* nguoiChoi = map->layNguoiChoi();
    Diem viTriNguoiChoi = nguoiChoi->layViTri();
    DynamicArray<Diem> cacViTriThung;

    for (int i = 0; i < map->cacThungGoPtr.size(); i++) {
        cacViTriThung.push_back(map->cacThungGoPtr[i]->layViTri());
    }

    return TrangThaiDiChuyen(viTriNguoiChoi, cacViTriThung);
}

void GameController::phucHoiTrangThai(const TrangThaiDiChuyen& trangThai) {
    NguoiChoi* nguoiChoi = map->layNguoiChoi();
    nguoiChoi->datViTri(trangThai.viTriNguoiChoi.layX(),
                        trangThai.viTriNguoiChoi.layY(), 0, 0);

    for (int i = 0; i < map->cacThungGoPtr.size() && i < trangThai.cacViTriThung.size(); i++) {
        map->cacThungGoPtr[i]->datViTri(
            trangThai.cacViTriThung[i].layX(),
            trangThai.cacViTriThung[i].layY()
        );
    }

    boxTriggerUpdater.capNhatThung(map);
    boxTriggerUpdater.capNhatNutVaBay(map);
}

TrangThaiBFS GameController::taoTrangThaiBFS() const {
    NguoiChoi* nguoiChoi = map->layNguoiChoi();
    Diem viTriNguoiChoi = nguoiChoi->layViTri();
    DynamicArray<Diem> cacViTriThung;
    DynamicArray<Diem> cacViTriThungSat;

    for (int i = 0; i < map->cacThungGoPtr.size(); i++) {
        cacViTriThung.push_back(map->cacThungGoPtr[i]->layViTri());
    }

    for (int i = 0; i < map->cacThungSatPtr.size(); i++) {
        cacViTriThungSat.push_back(map->cacThungSatPtr[i]->layViTri());
    }

    return TrangThaiBFS(viTriNguoiChoi, cacViTriThung, cacViTriThungSat, 0);
}

bool GameController::timLoiGiaiBFS(int doSauToiDa) {
    loiGiaiHienTai.clear();
    buocGiaiHienTai = 0;

    TrangThaiBFS trangThaiBanDau = taoTrangThaiBFS();
    bool timThay = bfsSolver->timLoiGiai(trangThaiBanDau, loiGiaiHienTai, doSauToiDa);
    return timThay;
}

void GameController::batDauTuDongGiai() {
    dangTuDongGiai = true;
    buocGiaiHienTai = 0;
}

void GameController::dungTuDongGiai() {
    dangTuDongGiai = false;
}

bool GameController::thucHienBuocGiai() {
    if (buocGiaiHienTai >= loiGiaiHienTai.size()) {
        dungTuDongGiai();
        return false;
    }

    int hanhDong = loiGiaiHienTai[buocGiaiHienTai];
    
    if (hanhDong == 4) {
        bool daDichChuyen = thucHienDichChuyen();
        if (daDichChuyen) {
            buocGiaiHienTai++;
            return true;
        }
        return false;
    }
    else {
        int dx[] = { 0, 0, -1, 1 };
        int dy[] = { -1, 1, 0, 0 };

        bool daDiChuyen = diChuyenNguoiChoi(dx[hanhDong], dy[hanhDong]);
        if (daDiChuyen) {
            buocGiaiHienTai++;
        }
        return daDiChuyen;
    }
}

bool GameController::layTrangThaiTuDongGiai() const {
    return dangTuDongGiai;
}

void GameController::reset() {
    loiGiaiHienTai.clear();
    buocGiaiHienTai = 0;
    dangTuDongGiai = false;
    historyManager->xoaLichSu();
}