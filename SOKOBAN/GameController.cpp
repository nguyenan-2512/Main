#include "GameController.h"
#include <iostream>

GameController::GameController(BanDo* banDo) 
    : map(banDo), buocGiaiHienTai(0), dangTuDongGiai(false) {
    
    historyManager = new HistoryManager();
    bfsSolver = new BFSSolver(map);
    
    // ✅ Cập nhật ban đầu
    capNhatThung();
    capNhatNutVaBay();
}

GameController::~GameController() {
    delete historyManager;
    delete bfsSolver;
}

// ========================
// ✅ DI CHUYỂN NGƯỜI CHƠI
// ========================
bool GameController::diChuyenNguoiChoi(int dx, int dy) {
    NguoiChoi* nguoiChoi = map->layNguoiChoi();
    if (!nguoiChoi || map->layTrangThaiThua()) return false;

    int xNguoiChoiHienTai = nguoiChoi->layX();
    int yNguoiChoiHienTai = nguoiChoi->layY();
    int xMoi = xNguoiChoiHienTai + dx;
    int yMoi = yNguoiChoiHienTai + dy;

    // ✅ BƯỚC 1: Kiểm tra vật cản TRƯỚC (tường, nước, chướng ngại vật)
    // Nhưng KHÔNG tính thùng là vật cản
    if (map->laTuong(xMoi, yMoi) ||
        map->laNuoc(xMoi, yMoi) ||
        map->laVatCan(xMoi, yMoi)) {
        return false;
    }

    // ✅ BƯỚC 2: Kiểm tra bẫy
    Bay* bay = map->timBayTai(xMoi, yMoi);
    if (bay && bay->layTrangThaiKichHoat()) {
        map->datTrangThaiThua(true);
        return false;
    }

    // ✅ BƯỚC 3: Xử lý đẩy thùng gỗ
    ThungGo* thung = map->timThungGoTai(xMoi, yMoi);
    if (thung) {
        // Tính vị trí mới của thùng (đẩy theo hướng người chơi đang đi)
        int xThungMoi = xMoi + dx;  // Vị trí thùng hiện tại + hướng đẩy
        int yThungMoi = yMoi + dy;

        // Kiểm tra vị trí mới của thùng có hợp lệ không
        if (!kiemTraViTriHopLeChoThung(xThungMoi, yThungMoi)) {
            return false;  // Không thể đẩy
        }

        // ✅ Lưu trạng thái TRƯỚC KHI đẩy
        TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
        historyManager->luuTrangThai(trangThai);

        // Đẩy thùng
        thung->datViTri(xThungMoi, yThungMoi);
        capNhatThung();
        capNhatNutVaBay();

        // Di chuyển người chơi vào vị trí thùng cũ
        nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
        return true;
    }

    // ✅ BƯỚC 4: Xử lý đẩy thùng sắt
    ThungSat* thungSat = map->timThungSatTai(xMoi, yMoi);
    if (thungSat) {
        int xThungSatMoi = xMoi + dx;
        int yThungSatMoi = yMoi + dy;

        if (!kiemTraViTriHopLeChoThung(xThungSatMoi, yThungSatMoi)) {
            return false;
        }

        // ✅ Lưu trạng thái
        TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
        historyManager->luuTrangThai(trangThai);

        // Đẩy thùng sắt
        thungSat->datViTri(xThungSatMoi, yThungSatMoi);
        capNhatNutVaBay();

        // Di chuyển người chơi
        nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
        return true;
    }

    // ✅ BƯỚC 5: Di chuyển người chơi bình thường (không có thùng)
    TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
    historyManager->luuTrangThai(trangThai);

    nguoiChoi->datViTri(xMoi, yMoi, dx, dy);
    capNhatNutVaBay();

    return true;
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

    // Lưu trạng thái
    TrangThaiDiChuyen trangThai = layTrangThaiHienTai();
    historyManager->luuTrangThai(trangThai);
    
    nguoiChoi->datViTri(xDich, yDich, 0, 0);
    return true;
}

// ========================
// ✅ HELPER METHODS
// ========================

bool GameController::kiemTraViTriHopLeChoThung(int x, int y) const {
    // 1. Không được là tường, nước, vật cản
    if (map->laTuong(x, y) ||
        map->laNuoc(x, y) ||
        map->laVatCan(x, y)) {
        return false;
    }

    // 2. Không được có thùng khác
    if (map->laThungGo(x, y) || map->laThungSat(x, y)) {
        return false;
    }

    // 3. Không được là bẫy đang kích hoạt
    Bay* bay = map->timBayTai(x, y);
    if (bay && bay->layTrangThaiKichHoat()) {
        return false;
    }

    return true;
}

void GameController::capNhatThung() {
    for (int i = 0; i < map->cacThungGoPtr.size(); i++) {
        bool trenViTriDat = map->laViTriDat(
            map->cacThungGoPtr[i]->layX(), 
            map->cacThungGoPtr[i]->layY()
        );
        map->cacThungGoPtr[i]->datTrangThaiTrenViTriDat(trenViTriDat);
    }
}

void GameController::capNhatNutVaBay() {
    for (int i = 0; i < map->cacNutBamPtr.size(); i++) {
        int nx = map->cacNutBamPtr[i]->layX();
        int ny = map->cacNutBamPtr[i]->layY();

        bool coThung = map->laThungGo(nx, ny);
        bool coThungSat = map->laThungSat(nx, ny);
        bool duocNhan = coThung || coThungSat;

        map->cacNutBamPtr[i]->datTrangThaiNhan(duocNhan);

        const auto& cacBayLienKet = map->cacNutBamPtr[i]->layCacBayLienKet();
        for (int j = 0; j < cacBayLienKet.size(); j++) {
            Bay* bay = map->timBayTai(
                cacBayLienKet[j].first, 
                cacBayLienKet[j].second
            );
            if (bay) {
                bay->datKichHoat(!duocNhan);
            }
        }
    }
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

// ========================
// ✅ UNDO/REDO
// ========================
void GameController::undo() {
    if (!historyManager->coTheLui()) {
        std::cout << "Khong the lui!" << std::endl;
        return;
    }

    TrangThaiDiChuyen trangThaiTruoc = historyManager->layTrangThaiTruoc();
    phucHoiTrangThai(trangThaiTruoc);
    
    std::cout << "Da lui buoc! Con lai " << historyManager->laySoBuoc() << " buoc." << std::endl;
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

    capNhatThung();
    capNhatNutVaBay();
}

// ========================
// ✅ BFS AUTO-SOLVE
// ========================
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
    
    std::cout << "Dang tim loi giai bang BFS..." << std::endl;
    bool timThay = bfsSolver->timLoiGiai(trangThaiBanDau, loiGiaiHienTai, doSauToiDa);
    
    if (timThay) {
        std::cout << "Tim thay! So buoc: " << loiGiaiHienTai.size() << std::endl;
    } else {
        std::cout << "Khong tim thay loi giai!" << std::endl;
    }
    
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
        // Teleport
        bool daDichChuyen = thucHienDichChuyen();
        if (daDichChuyen) {
            buocGiaiHienTai++;
            return true;
        }
        return false;
    }
    else {
        // Di chuyển thường
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