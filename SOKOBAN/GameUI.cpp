#include "GameUI.h"
#include "TroChoi.h"
#include <iostream>

GameUI::GameUI()
    : menuUI(nullptr),
    mapSelectUI(nullptr),
    huongDanUI(nullptr),
    nutPause(nullptr),
    nutGoiY(nullptr),
    lopPhuPause(nullptr),
    trangThaiHienTai(TrangThaiUI::MENU) {
}

GameUI::~GameUI() {
    if (menuUI) {
        delete menuUI;
        menuUI = nullptr;
    }
    if (mapSelectUI) {
        delete mapSelectUI;
        mapSelectUI = nullptr;
    }
    if (huongDanUI) {
        delete huongDanUI;
        huongDanUI = nullptr;
    }
    if (nutPause) {
        delete nutPause;
        nutPause = nullptr;
    }
    if (nutGoiY) {
        delete nutGoiY;
        nutGoiY = nullptr;
    }
    if (lopPhuPause) {
        delete lopPhuPause;
        lopPhuPause = nullptr;
    }
}

bool GameUI::khoiTao() {
    std::cout << "\n[GameUI] ===== KHOI TAO TOAN BO UI =====" << std::endl;

    // ===== 1. KHỞI TẠO MENU =====
    menuUI = new MenuUI();
    if (!menuUI->taiTaiNguyen()) {
        std::cerr << "[GameUI] Loi tai Menu!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Menu: OK" << std::endl;

    // ===== 2. KHỞI TẠO MAP SELECT =====
    mapSelectUI = new MapSelectUI();
    if (!mapSelectUI->taiTaiNguyen()) {
        std::cerr << "[GameUI] Loi tai Map Select!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Map Select: OK" << std::endl;

    // ===== 3. KHỞI TẠO HƯỚNG DẪN =====
    huongDanUI = new HuongDan();
    if (!huongDanUI->taiTaiNguyen()) {
        std::cerr << "[GameUI] Loi tai Huong Dan!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Huong Dan: OK" << std::endl;

    // ❌ XÓA: Code cũ dùng giaoDien

    // ===== 4. KHỞI TẠO NÚT PAUSE =====
    nutPause = new NutUI();
    if (!nutPause->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\pause_button.png")) {
        std::cerr << "[GameUI] Loi tai nut Pause!" << std::endl;
        return false;
    }
    nutPause->datViTri(730, 10);
    nutPause->datKichThuoc(50, 50);
    std::cout << "[GameUI] + Nut Pause: OK" << std::endl;

    // ===== 5. KHỞI TẠO NÚT GỢI Ý =====
    nutGoiY = new NutUI();
    if (!nutGoiY->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\hint_button.png")) {
        std::cerr << "[GameUI] Loi tai nut Goi Y!" << std::endl;
        return false;
    }
    nutGoiY->datViTri(665, 10);
    nutGoiY->datKichThuoc(50, 50);
    std::cout << "[GameUI] + Nut Goi Y: OK" << std::endl;

    // ===== 6. KHỞI TẠO PAUSE MENU =====
    lopPhuPause = new LopPhuPause();
    if (!lopPhuPause->khoiTao("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\pause_menu.png")) {
        std::cerr << "[GameUI] Loi tai Pause Menu!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Pause Menu: OK" << std::endl;

    // ===== 7. LOAD TEXTURE WIN =====
    if (!ketCauThang.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win.png")) {
        std::cerr << "[GameUI] Loi tai anh thang!" << std::endl;
        return false;
    }
    anhThang.setTexture(ketCauThang);
    anhThang.setPosition(0, 0);
    std::cout << "[GameUI] + Win Overlay: OK" << std::endl;

    // ===== 8. LOAD TEXTURE LOSE =====
    if (!ketCauThua.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\gameover.png")) {
        std::cerr << "[GameUI] Loi tai anh thua!" << std::endl;
        return false;
    }
    anhThua.setTexture(ketCauThua);
    anhThua.setPosition(0, 0);
    std::cout << "[GameUI] + Lose Overlay: OK" << std::endl;

    // ===== 9. LOAD FONT =====
    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "[GameUI] Loi tai font!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Font: OK" << std::endl;

    std::cout << "[GameUI] ===== KHOI TAO THANH CONG =====" << std::endl;
    return true;
}

// ===== XỬ LÝ SỰ KIỆN =====
void GameUI::xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo, TroChoi* troChoi) {
    switch (trangThaiHienTai) {
    case TrangThaiUI::MENU: {
        MenuAction action = menuUI->xuLySuKien(suKien);
        if (action == MenuAction::CHOI) {
            trangThaiHienTai = TrangThaiUI::CHON_BAN_DO;
            mapSelectUI->datLai();
        }
        else if (action == MenuAction::HUONG_DAN) {
            trangThaiHienTai = TrangThaiUI::HUONG_DAN;
            huongDanUI->datLai();
        }
        else if (action == MenuAction::THOAT) {
            cuaSo.close();
        }
        break;
    }

    case TrangThaiUI::CHON_BAN_DO: {
        int result = mapSelectUI->xuLySuKien(suKien);
        if (result == -1) {
            // Quay lại menu
            trangThaiHienTai = TrangThaiUI::MENU;
        }
        else if (result >= 0) {
            // Chọn map thành công
            // (TroChoi sẽ xử lý khi kiểm tra trạng thái)
        }
        break;
    }

    case TrangThaiUI::HUONG_DAN:
        huongDanUI->xuLySuKien(suKien, cuaSo);
        if (huongDanUI->nenQuayLaiThucDon()) {
            huongDanUI->datLaiCoQuayLai();
            trangThaiHienTai = TrangThaiUI::MENU;
        }
        break;

    case TrangThaiUI::TAM_DUNG:
        if (suKien.type == sf::Event::MouseButtonPressed &&
            suKien.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);
            HanhDongPause hanhDong = xuLyClickPauseMenu(viTriChuot);
            if (hanhDong != HanhDongPause::KHONG) {
                troChoi->xuLyHanhDongPause(hanhDong);
            }
        }
        break;

    case TrangThaiUI::DANG_CHOI:
        if (suKien.type == sf::Event::MouseButtonPressed &&
            suKien.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);
            xuLyClickChuotTrongGame(viTriChuot, troChoi);
        }
        break;

    case TrangThaiUI::THANG:
    case TrangThaiUI::THUA:
        if (xuLyPhimWinLose(suKien)) {
            troChoi->quayVeMenu();
        }
        break;

    default:
        break;
    }
}


bool GameUI::xuLyClickChuotTrongGame(const sf::Vector2i& viTriChuot, TroChoi* troChoi) {
    // Kiểm tra click vào nút Pause
    if (nutPause && nutPause->kiemTraClick(viTriChuot)) {
        troChoi->xuLyClickNutPause();
        return true;
    }

    // Kiểm tra click vào nút Gợi Ý
    if (nutGoiY && nutGoiY->kiemTraClick(viTriChuot)) {
        troChoi->xuLyClickNutGoiY();
        return true;
    }

    return false;
}

bool GameUI::xuLyPhimWinLose(const sf::Event& suKien) {
    return (suKien.type == sf::Event::KeyPressed);
}
void GameUI::capNhat(const sf::Vector2i& viTriChuot) {
    switch (trangThaiHienTai) {
    case TrangThaiUI::MENU:
        menuUI->capNhat();
        break;

    case TrangThaiUI::CHON_BAN_DO:
        mapSelectUI->capNhat(viTriChuot);
        break;

    case TrangThaiUI::HUONG_DAN:
        huongDanUI->capNhat(0.0f);
        break;

    case TrangThaiUI::DANG_CHOI:
        if (nutPause) nutPause->capNhat(viTriChuot);
        if (nutGoiY) nutGoiY->capNhat(viTriChuot);
        break;

    case TrangThaiUI::TAM_DUNG:
        if (lopPhuPause) lopPhuPause->capNhat(viTriChuot);
        break;

    default:
        break;
    }
}

// ===== VẼ =====
void GameUI::ve(sf::RenderWindow& cuaSo) {
    switch (trangThaiHienTai) {
    case TrangThaiUI::MENU:
        menuUI->ve(cuaSo);
        break;

    case TrangThaiUI::CHON_BAN_DO:
        mapSelectUI->ve(cuaSo);
        break;

    case TrangThaiUI::HUONG_DAN:
        huongDanUI->ve(cuaSo);
        break;

    case TrangThaiUI::DANG_CHOI:
        if (nutPause) nutPause->ve(cuaSo);
        if (nutGoiY) nutGoiY->ve(cuaSo);
        break;

    case TrangThaiUI::TAM_DUNG:
        if (lopPhuPause) lopPhuPause->ve(cuaSo);
        break;

    case TrangThaiUI::THANG:
    {
        sf::RectangleShape lop(sf::Vector2f(800, 800));
        lop.setFillColor(sf::Color(0, 0, 0, 150));
        cuaSo.draw(lop);
        cuaSo.draw(anhThang);

        sf::Text text;
        text.setFont(chuPhong);
        text.setString("Nhan phim bat ky de quay lai Menu");
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::Green);
        text.setPosition(280, 765);
        cuaSo.draw(text);
    }
    break;

    case TrangThaiUI::THUA:
    {
        sf::RectangleShape lop(sf::Vector2f(800, 800));
        lop.setFillColor(sf::Color(0, 0, 0, 180));
        cuaSo.draw(lop);
        cuaSo.draw(anhThua);

        sf::Text text;
        text.setFont(chuPhong);
        text.setString("Nhan phim bat ky de quay lai Menu");
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::Red);
        text.setPosition(270, 765);
        cuaSo.draw(text);
    }
    break;

    default:
        break;
    }
}
// ===== PAUSE MENU =====
void GameUI::hienThiPauseMenu() {
    if (lopPhuPause) {
        lopPhuPause->hienThi();
        trangThaiHienTai = TrangThaiUI::TAM_DUNG;
    }
}

void GameUI::anPauseMenu() {
    if (lopPhuPause) {
        lopPhuPause->an();
        trangThaiHienTai = TrangThaiUI::DANG_CHOI;
    }
}

bool GameUI::pauseMenuDangHienThi() const {
    return (trangThaiHienTai == TrangThaiUI::TAM_DUNG);
}

HanhDongPause GameUI::xuLyClickPauseMenu(const sf::Vector2i& viTriChuot) {
    if (lopPhuPause) {
        return lopPhuPause->kiemTraClick(viTriChuot);
    }
    return HanhDongPause::KHONG;
}

int GameUI::layMapDaChon() const {
    if (mapSelectUI) {
        return mapSelectUI->layMapDaChon();
    }
    return 0;
}