#include "TroChoi.h"
#include <iostream>
#include "ResourceManager.h"  
#include "MapLoader.h"
using namespace std;

TroChoi::TroChoi() :
    cuaSo(sf::VideoMode::getDesktopMode(), "Sokoban", sf::Style::Fullscreen),
    banDoHienTai(nullptr),
    gameController(nullptr),
    gameUI(nullptr),
    hienThiThang(false),
    hienThiThua(false),
    kichThuocGoc(800, 800),
    tyLeX(1.0f),
    tyLeY(1.0f),
    cheDoX(0.0f),
    cheDoY(0.0f),
    dangTuDongGiai(false),
    dangTimKiemBFS(false) {

    cuaSo.setFramerateLimit(60);
    HoatHinh::tocDoHoatHinh = 0.1f;

    thieLapManHinhDay();

    if (!nhacNen.openFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\hi.ogg")) {
    }

    if (!boNhoAmThanhBuocDi.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg")) {
    }
    else {
        amThanhBuocDi.setBuffer(boNhoAmThanhBuocDi);
    }

    if (!boNhoAmThanhChienThang.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg")) {
    }
    else {
        amThanhChienThang.setBuffer(boNhoAmThanhChienThang);
    }

    if (!boNhoAmThanhThua.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\gameover.ogg")) {
    }
    else {
        amThanhThua.setBuffer(boNhoAmThanhThua);
    }

    gameUI = new GameUI();
    if (!gameUI->khoiTao()) {
    }

}
TroChoi::~TroChoi() {
    xoaTroChoi();
    if (gameUI) {
        delete gameUI;
        gameUI = nullptr;
    }

    ResourceManager::destroy();
}

void TroChoi::xuLyClickNutPause() {
    if (gameUI->layTrangThaiUI() != TrangThaiUI::DANG_CHOI) {
        return;
    }

    gameUI->hienThiPauseMenu();
    nhacNen.pause();
    if (gameUI && gameUI->layGameStatsUI()) {
        gameUI->layGameStatsUI()->tamDungTimer();
    }
}

void TroChoi::xuLyClickNutGoiY() {
    if (!gameController) {
        return;
    }

    if (gameUI->layTrangThaiUI() != TrangThaiUI::DANG_CHOI) {
        return;
    }
    if (dangTuDongGiai) {
        return;
    }
    if (dangTimKiemBFS) {
        return;
    }

    bool timThay = gameController->timLoiGiaiBFS(150);

    if (timThay) {
        gameController->batDauTuDongGiai();
        dangTuDongGiai = true;
    }
}

void TroChoi::xuLyHanhDongPause(HanhDongPause hanhDong) {
    switch (hanhDong) {
    case HanhDongPause::TIEP_TUC:
        gameUI->anPauseMenu();
        nhacNen.play();
        if (gameUI && gameUI->layGameStatsUI()) {
            gameUI->layGameStatsUI()->tiepTucTimer();
        }
        break;

    case HanhDongPause::CHOI_LAI:
        gameUI->anPauseMenu();
        khoiTaoTroChoi();
        dangTuDongGiai = false;
        nhacNen.play();
        break;

    case HanhDongPause::THOAT:
        quayVeMenu();
        break;

    default:
        break;
    }
}

void TroChoi::thieLapManHinhDay() {
    sf::Vector2u kichThuocManHinh = cuaSo.getSize();

    float tyLeManHinh = static_cast<float>(kichThuocManHinh.x) / static_cast<float>(kichThuocManHinh.y);
    float tyLeTroChoi = static_cast<float>(kichThuocGoc.x) / static_cast<float>(kichThuocGoc.y);

    if (tyLeManHinh > tyLeTroChoi) {
        tyLeY = static_cast<float>(kichThuocManHinh.y) / static_cast<float>(kichThuocGoc.y);
        tyLeX = tyLeY;
        cheDoX = (kichThuocManHinh.x - (kichThuocGoc.x * tyLeX)) / 2.0f;
        cheDoY = 0.0f;
    }
    else {
        tyLeX = static_cast<float>(kichThuocManHinh.x) / static_cast<float>(kichThuocGoc.x);
        tyLeY = tyLeX;
        cheDoX = 0.0f;
        cheDoY = (kichThuocManHinh.y - (kichThuocGoc.y * tyLeY)) / 2.0f;
    }

    tamNhinTroChoi.setSize(static_cast<float>(kichThuocGoc.x), static_cast<float>(kichThuocGoc.y));
    tamNhinTroChoi.setCenter(static_cast<float>(kichThuocGoc.x) / 2.0f, static_cast<float>(kichThuocGoc.y) / 2.0f);

    float khungNhinX = cheDoX / static_cast<float>(kichThuocManHinh.x);
    float khungNhinY = cheDoY / static_cast<float>(kichThuocManHinh.y);
    float chieuRongKhungNhin = (kichThuocGoc.x * tyLeX) / static_cast<float>(kichThuocManHinh.x);
    float chieuCaoKhungNhin = (kichThuocGoc.y * tyLeY) / static_cast<float>(kichThuocManHinh.y);

    tamNhinTroChoi.setViewport(sf::FloatRect(khungNhinX, khungNhinY, chieuRongKhungNhin, chieuCaoKhungNhin));

    cuaSo.setView(tamNhinTroChoi);
}

void TroChoi::capNhatTamNhin() {
    cuaSo.setView(tamNhinTroChoi);
}

sf::Vector2i TroChoi::layViTriChuotDaTyLe(const sf::Vector2i& viTriChuot) {
    float xDaTyLe = (viTriChuot.x - cheDoX) / tyLeX;
    float yDaTyLe = (viTriChuot.y - cheDoY) / tyLeY;

    xDaTyLe = std::max(0.0f, std::min(xDaTyLe, static_cast<float>(kichThuocGoc.x)));
    yDaTyLe = std::max(0.0f, std::min(yDaTyLe, static_cast<float>(kichThuocGoc.y)));

    return sf::Vector2i(static_cast<int>(xDaTyLe), static_cast<int>(yDaTyLe));
}

void TroChoi::chay() {
    nhacNen.setLoop(true);
    nhacNen.play();

    while (cuaSo.isOpen()) {
        xuLySuKien();
        capNhat();
        veHinh();
    }
}

void TroChoi::xuLySuKien() {
    sf::Event suKien;
    while (cuaSo.pollEvent(suKien)) {
        if (suKien.type == sf::Event::MouseMoved) {
            sf::Vector2i viTriChuot = sf::Mouse::getPosition(cuaSo);
            sf::Vector2i viTriDaTyLe = layViTriChuotDaTyLe(viTriChuot);

            std::cout << "Toa do chuot: X=" << viTriDaTyLe.x
                << " Y=" << viTriDaTyLe.y << std::endl;
        }
        sf::Event suKienDaTyLe = suKien;
        if (suKien.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i viTriDaTyLe = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
            suKienDaTyLe.mouseButton.x = viTriDaTyLe.x;
            suKienDaTyLe.mouseButton.y = viTriDaTyLe.y;
        }
        else if (suKien.type == sf::Event::MouseMoved) {
            sf::Vector2i viTriDaTyLe = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
            suKienDaTyLe.mouseMove.x = viTriDaTyLe.x;
            suKienDaTyLe.mouseMove.y = viTriDaTyLe.y;
        }

        gameUI->xuLySuKien(suKienDaTyLe, cuaSo, this);

        if (gameUI->layTrangThaiUI() == TrangThaiUI::DANG_CHOI) {
            HanhDongGame hanhDong = inputHandler.xuLyPhimChoiGame(suKien);
            xuLyHanhDongGame(hanhDong);
        }
    }
}

void TroChoi::phatAmThanhBuocDi() {
    amThanhBuocDi.play();
}

void TroChoi::capNhat() {
    float thoiGianDelta = dongHoDelta.restart().asSeconds();

    sf::Vector2i viTriChuot = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
    gameUI->capNhat(viTriChuot);

    TrangThaiUI trangThaiUI = gameUI->layTrangThaiUI();

    if (trangThaiUI == TrangThaiUI::CHON_BAN_DO && gameUI->layMapDaChon() >= 0) {
        gameUI->datTrangThaiUI(TrangThaiUI::DANG_CHOI);
        khoiTaoTroChoi();
        hienThiThang = false;
        hienThiThua = false;
        dangTuDongGiai = false;
    }

    if (trangThaiUI == TrangThaiUI::DANG_CHOI) {
        if (banDoHienTai && banDoHienTai->layNguoiChoi()) {
            banDoHienTai->layNguoiChoi()->capNhat(thoiGianDelta);
        }

        if (gameController && dangTuDongGiai) {
            if (gameController->layTrangThaiTuDongGiai()) {
                static sf::Clock dongHoTuDongGiai;
                if (dongHoTuDongGiai.getElapsedTime().asSeconds() >= 0.3f) {
                    bool thanhCong = gameController->thucHienBuocGiai();
                    if (thanhCong) {
                        if (gameUI && gameUI->layGameStatsUI()) {
                            gameUI->layGameStatsUI()->tangSoBuoc();
                        }
                    }
                    else {
                        dangTuDongGiai = false;
                    }
                    dongHoTuDongGiai.restart();
                }
            }
            else {
                dangTuDongGiai = false;
            }
        }

        if (banDoHienTai && banDoHienTai->layTrangThaiThua() && !hienThiThua) {
            hienThiThua = true;
            gameUI->datTrangThaiUI(TrangThaiUI::THUA);
            amThanhThua.play();
            nhacNen.stop();
            dangTuDongGiai = false;
            if (gameUI && gameUI->layGameStatsUI()) {
                gameUI->layGameStatsUI()->tamDungTimer();
            }
        }

        if (gameController && gameController->kiemTraThang() && !hienThiThang && !hienThiThua) {
            hienThiThang = true;

            if (gameUI && gameUI->layGameStatsUI()) {
                int soBuoc = gameUI->layGameStatsUI()->laySoBuoc();
                float thoiGian = gameUI->layGameStatsUI()->layThoiGian();
                gameUI->luuStatsWin(soBuoc, thoiGian);
                gameUI->layGameStatsUI()->tamDungTimer();
                gameUI->layWinUI()->hienThi(thoiGian, soBuoc);
            }

            gameUI->datTrangThaiUI(TrangThaiUI::THANG);
            amThanhChienThang.play();
            nhacNen.stop();
            dangTuDongGiai = false;
        }
    }
}

void TroChoi::chuyenSangManTiepTheo() {

    int manHienTai = gameUI->layMapDaChon();
    int manTiepTheo = manHienTai + 1;

    const int SO_MAN_TOI_DA = 8;

    if (manTiepTheo >= SO_MAN_TOI_DA) {
        quayVeMenu();
        return;
    }

    gameUI->layMapSelectUI()->datMapDaChon(manTiepTheo);

    gameUI->datTrangThaiUI(TrangThaiUI::DANG_CHOI);

    khoiTaoTroChoi(); 
    hienThiThang = false;
    hienThiThua = false;
    dangTuDongGiai = false;
    nhacNen.play();
}

void TroChoi::veHinh() {
    cuaSo.clear(sf::Color::Black);
    capNhatTamNhin();

    TrangThaiUI trangThaiUI = gameUI->layTrangThaiUI();

    if (trangThaiUI == TrangThaiUI::DANG_CHOI ||
        trangThaiUI == TrangThaiUI::TAM_DUNG ||
        trangThaiUI == TrangThaiUI::THANG ||
        trangThaiUI == TrangThaiUI::THUA) {
        if (banDoHienTai) {
            mapRenderer.ve(cuaSo, banDoHienTai);
        }
    }

    gameUI->ve(cuaSo);

    cuaSo.display();
}

void TroChoi::khoiTaoTroChoi() {
    xoaTroChoi();
    static bool resourcesLoaded = false;
    if (!resourcesLoaded) {
        ResourceManager::getInstance()->loadAllGameResources();
        resourcesLoaded = true;
    }

    int banDoChon = gameUI->layMapDaChon();
    if (banDoChon < 0) banDoChon = 0;

    std::string tenFileBanDo = "map" + std::to_string(banDoChon + 1) + ".txt";

    banDoHienTai = MapLoader::loadFromFile(tenFileBanDo, 32);

    if (!banDoHienTai) {
        return;
    }

    gameController = new GameController(banDoHienTai);
    dangTuDongGiai = false;

    if (gameUI && gameUI->layGameStatsUI()) {
        gameUI->layGameStatsUI()->datLaiTimer();
        gameUI->layGameStatsUI()->datLaiSoBuoc();
        gameUI->layGameStatsUI()->batDauTimer();
    }

}

void TroChoi::xoaTroChoi() {
    if (gameController) {
        delete gameController;
        gameController = nullptr;
    }
    if (banDoHienTai) {
        delete banDoHienTai;
        banDoHienTai = nullptr;
    }
}

void TroChoi::xuLyHanhDongGame(HanhDongGame hanhDong) {
    if (!gameController) return;

    switch (hanhDong) {
    case HanhDongGame::RESTART:
        khoiTaoTroChoi();
        dangTuDongGiai = false;
        break;

    case HanhDongGame::UNDO:
        gameController->undo();
        if (gameUI && gameUI->layGameStatsUI()) {
            int soBuocHienTai = gameController->laySoBuoc();
            gameUI->layGameStatsUI()->datSoBuoc(soBuocHienTai);
        }
        break;

    case HanhDongGame::DUNG_AUTO_SOLVE:
        if (dangTuDongGiai) {
            gameController->dungTuDongGiai();
            dangTuDongGiai = false;
        }
        break;

    case HanhDongGame::TELEPORT: {
        bool daDichChuyen = gameController->thucHienDichChuyen();
        if (daDichChuyen) {
            phatAmThanhBuocDi();
            if (gameUI && gameUI->layGameStatsUI()) {
                gameUI->layGameStatsUI()->tangSoBuoc();
            }
        }
        break;
    }
    case HanhDongGame::HINT:
        if (!gameController->layTrangThaiTuDongGiai()) {
            xuLyClickNutGoiY();
        }
        break;

    case HanhDongGame::PAUSE:
        xuLyClickNutPause();
        break;

    case HanhDongGame::DI_LEN:
    case HanhDongGame::DI_XUONG:
    case HanhDongGame::DI_TRAI:
    case HanhDongGame::DI_PHAI: {
        if (!dangTuDongGiai) {
            bool daDiChuyen = false;

            if (hanhDong == HanhDongGame::DI_LEN) {
                daDiChuyen = gameController->diChuyenNguoiChoi(0, -1);
            }
            else if (hanhDong == HanhDongGame::DI_XUONG) {
                daDiChuyen = gameController->diChuyenNguoiChoi(0, 1);
            }
            else if (hanhDong == HanhDongGame::DI_TRAI) {
                daDiChuyen = gameController->diChuyenNguoiChoi(-1, 0);
            }
            else if (hanhDong == HanhDongGame::DI_PHAI) {
                daDiChuyen = gameController->diChuyenNguoiChoi(1, 0);
            }

            if (daDiChuyen) {
                phatAmThanhBuocDi();
                if (gameUI && gameUI->layGameStatsUI()) {
                    gameUI->layGameStatsUI()->tangSoBuoc();
                }
            }
        }
        break;
    }
    default:
        break;
    }
}

void TroChoi::quayVeMenu() {
    gameUI->datTrangThaiUI(TrangThaiUI::MENU);
    xoaTroChoi();
    hienThiThang = false;
    hienThiThua = false;
    dangTuDongGiai = false;
    nhacNen.play();
}