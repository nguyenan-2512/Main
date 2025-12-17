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

    // ===== ✅ THÊM: LOAD ÂM THANH =====
    std::cout << "[TroChoi] Dang load am thanh..." << std::endl;

    if (!nhacNen.openFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\hi.ogg")) {
        std::cerr << "[TroChoi] Khong the tai nhac nen!" << std::endl;
    }
    else {
        std::cout << "[TroChoi] + Nhac nen: OK" << std::endl;
    }

    if (!boNhoAmThanhBuocDi.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg")) {
        std::cerr << "[TroChoi] Khong the tai am thanh buoc di!" << std::endl;
    }
    else {
        amThanhBuocDi.setBuffer(boNhoAmThanhBuocDi);
        std::cout << "[TroChoi] + Am thanh buoc di: OK" << std::endl;
    }

    if (!boNhoAmThanhChienThang.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg")) {
        std::cerr << "[TroChoi] Khong the tai am thanh chien thang!" << std::endl;
    }
    else {
        amThanhChienThang.setBuffer(boNhoAmThanhChienThang);
        std::cout << "[TroChoi] + Am thanh chien thang: OK" << std::endl;
    }

    if (!boNhoAmThanhThua.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\gameover.ogg")) {
        std::cerr << "[TroChoi] Khong the tai am thanh thua!" << std::endl;
    }
    else {
        amThanhThua.setBuffer(boNhoAmThanhThua);
        std::cout << "[TroChoi] + Am thanh thua: OK" << std::endl;
    }

    std::cout << "[TroChoi] Load am thanh xong!" << std::endl;

    // ===== KHỞI TẠO GAMEUI =====
    std::cout << "[TroChoi] Dang khoi tao GameUI..." << std::endl;
    gameUI = new GameUI();
    if (!gameUI->khoiTao()) {
        std::cerr << "[TroChoi] Loi khoi tao GameUI!" << std::endl;
    }
    std::cout << "[TroChoi] Khoi tao hoan tat!" << std::endl;
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
    // Kiểm tra đang ở màn hình chơi game
    if (gameUI->layTrangThaiUI() != TrangThaiUI::DANG_CHOI) {
        return;
    }

    std::cout << "\n>>> MO PAUSE MENU <<<" << std::endl;

    // Hiển thị pause menu thông qua GameUI
    gameUI->hienThiPauseMenu();

    // Tạm dừng nhạc nền
    nhacNen.pause();
    // Tạm dừng timer trong GameStatsUI
    if (gameUI && gameUI->layGameStatsUI()) {
        gameUI->layGameStatsUI()->tamDungTimer();
    }
}

void TroChoi::xuLyClickNutGoiY() {
    // Kiểm tra gameController và trạng thái UI
    if (!gameController) {
        std::cout << "\nKhong co gameController!" << std::endl;
        return;
    }

    // Kiểm tra đang ở màn hình chơi game
    if (gameUI->layTrangThaiUI() != TrangThaiUI::DANG_CHOI) {
        std::cout << "\nKhong o trang thai DANG_CHOI!" << std::endl;
        return;
    }

    // Kiểm tra đã đang tự động giải chưa
    if (dangTuDongGiai) {
        std::cout << "\nDang tu dong giai. Nhan phim J de dung." << std::endl;
        return;
    }

    // Kiểm tra đã đang tìm kiếm chưa
    if (dangTimKiemBFS) {
        std::cout << "\nDang tim kiem loi giai..." << std::endl;
        return;
    }

    // ✅ BẮT ĐẦU TÌM KIẾM BFS NGAY LẬP TỨC
    std::cout << "\n=== BAT DAU TIM LOI GIAI ===" << std::endl;

    // ✅ QUAN TRỌNG: Timer vẫn chạy trong khi tìm kiếm
    bool timThay = gameController->timLoiGiaiBFS(50);

    if (timThay) {
        std::cout << ">>> TIM THAY LOI GIAI! Bat dau tu dong chay..." << std::endl;
        gameController->batDauTuDongGiai();
        dangTuDongGiai = true;
    }
    else {
        std::cout << ">>> KHONG TIM THAY LOI GIAI!" << std::endl;
    }
}

void TroChoi::xuLyHanhDongPause(HanhDongPause hanhDong) {
    switch (hanhDong) {
    case HanhDongPause::TIEP_TUC:
        std::cout << ">>> TIEP TUC CHOI <<<" << std::endl;
        gameUI->anPauseMenu();
        nhacNen.play();
        if (gameUI && gameUI->layGameStatsUI()) {
            gameUI->layGameStatsUI()->tiepTucTimer();
        }
        break;

    case HanhDongPause::CHOI_LAI:
        std::cout << ">>> CHOI LAI <<<" << std::endl;
        gameUI->anPauseMenu();
        khoiTaoTroChoi();
        dangTuDongGiai = false;
        nhacNen.play();
        break;

    case HanhDongPause::THOAT:
        std::cout << ">>> TRO VE MENU <<<" << std::endl;
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
        if (suKien.type == sf::Event::Closed) {
            cuaSo.close();
        }
        // ===== 🔴 DEBUG: IN TỌA ĐỘ CHUỘT =====
        if (suKien.type == sf::Event::MouseMoved) {
            sf::Vector2i viTriChuot = sf::Mouse::getPosition(cuaSo);
            sf::Vector2i viTriDaTyLe = layViTriChuotDaTyLe(viTriChuot);

            std::cout << "Toa do chuot: X=" << viTriDaTyLe.x
                << " Y=" << viTriDaTyLe.y << std::endl;
        }

        // Xử lý ESC
        if (suKien.type == sf::Event::KeyPressed && suKien.key.code == sf::Keyboard::Escape) {
            TrangThaiUI trangThaiUI = gameUI->layTrangThaiUI();

            if (trangThaiUI == TrangThaiUI::MENU) {
                cuaSo.close();
            }
            else if (trangThaiUI == TrangThaiUI::DANG_CHOI) {
                xuLyClickNutPause();
            }
            else if (trangThaiUI == TrangThaiUI::TAM_DUNG) {
                xuLyHanhDongPause(HanhDongPause::TIEP_TUC);
            }
        }

        // Scale tọa độ chuột cho sự kiện
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

        // GameUI xử lý sự kiện
        gameUI->xuLySuKien(suKienDaTyLe, cuaSo, this);

        // Xử lý phím game (di chuyển, undo...)
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

    // Cập nhật hover UI
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

        // ✅ Auto-solve: Thực thi từng bước BFS đã tìm được
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
                        std::cout << "Hoan thanh tu dong giai!" << std::endl;
                    }
                    dongHoTuDongGiai.restart();
                }
            }
            else {
                dangTuDongGiai = false;
            }
        }

        // Kiểm tra thua
        if (banDoHienTai && banDoHienTai->layTrangThaiThua() && !hienThiThua) {
            hienThiThua = true;
            gameUI->datTrangThaiUI(TrangThaiUI::THUA);
            amThanhThua.play();
            nhacNen.stop();
            dangTuDongGiai = false;
            if (gameUI && gameUI->layGameStatsUI()) {
                gameUI->layGameStatsUI()->tamDungTimer();
            }
            std::cout << "Thua cuoc!" << std::endl;
        }

        // Kiểm tra thắng
        if (gameController && gameController->kiemTraThang() && !hienThiThang && !hienThiThua) {
            hienThiThang = true;

            // Lưu stats
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
            std::cout << "Chuc mung!" << std::endl;
        }
    }
}

void TroChoi::chuyenSangManTiepTheo() {
    std::cout << "[TroChoi] Chuyen sang man tiep theo..." << std::endl;

    int manHienTai = gameUI->layMapDaChon();
    int manTiepTheo = manHienTai + 1;

    const int SO_MAN_TOI_DA = 8;

    if (manTiepTheo >= SO_MAN_TOI_DA) {
        std::cout << "[TroChoi] Da hoan thanh tat ca cac man!" << std::endl;
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

    std::cout << "[TroChoi] Da chuyen sang map " << (manTiepTheo + 1) << std::endl;
}

void TroChoi::veHinh() {
    cuaSo.clear(sf::Color::Black);
    capNhatTamNhin();

    TrangThaiUI trangThaiUI = gameUI->layTrangThaiUI();

    // Vẽ map khi đang chơi
    if (trangThaiUI == TrangThaiUI::DANG_CHOI ||
        trangThaiUI == TrangThaiUI::TAM_DUNG ||
        trangThaiUI == TrangThaiUI::THANG ||
        trangThaiUI == TrangThaiUI::THUA) {
        if (banDoHienTai) {
            mapRenderer.ve(cuaSo, banDoHienTai);
        }
    }

    // Vẽ UI
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
    std::cout << "[TroChoi] Dang tai: " << tenFileBanDo << std::endl;

    banDoHienTai = MapLoader::loadFromFile(tenFileBanDo, 32);

    if (!banDoHienTai) {
        std::cerr << "[TroChoi] LOI LOAD MAP!" << std::endl;
        return;
    }

    gameController = new GameController(banDoHienTai);
    dangTuDongGiai = false;

    if (gameUI && gameUI->layGameStatsUI()) {
        gameUI->layGameStatsUI()->datLaiTimer();
        gameUI->layGameStatsUI()->datLaiSoBuoc();
        gameUI->layGameStatsUI()->batDauTimer();
    }

    std::cout << "[TroChoi] Khoi tao thanh cong!" << std::endl;
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
    // Kiểm tra gameController có tồn tại không
    if (!gameController) return;

    switch (hanhDong) {
        // ========== RESTART ==========
    case HanhDongGame::RESTART:
        khoiTaoTroChoi();
        dangTuDongGiai = false;
        std::cout << "Da khoi tao lai game!" << std::endl;
        break;

        // ========== UNDO ==========
    case HanhDongGame::UNDO:
        gameController->undo();
        if (gameUI && gameUI->layGameStatsUI()) {
            int soBuocHienTai = gameController->laySoBuoc();
            gameUI->layGameStatsUI()->datSoBuoc(soBuocHienTai);
        }
        break;

        // ========== DỪNG AUTO-SOLVE ==========
    case HanhDongGame::DUNG_AUTO_SOLVE:
        if (dangTuDongGiai) {
            gameController->dungTuDongGiai();
            dangTuDongGiai = false;
            std::cout << "Da dung tu dong giai!" << std::endl;
        }
        break;

        // ========== TELEPORT ==========
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

        // ========== PAUSE ==========
    case HanhDongGame::PAUSE:
        xuLyClickNutPause();
        break;

        // ========== DI CHUYỂN (4 HƯỚNG) ==========
    case HanhDongGame::DI_LEN:
    case HanhDongGame::DI_XUONG:
    case HanhDongGame::DI_TRAI:
    case HanhDongGame::DI_PHAI: {
        // Chỉ di chuyển khi KHÔNG đang auto-solve
        if (!dangTuDongGiai) {
            bool daDiChuyen = false;

            // Xác định hướng di chuyển
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

            // Phát âm thanh nếu di chuyển thành công
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