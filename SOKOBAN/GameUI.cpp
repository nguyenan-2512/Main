#include "GameUI.h"
#include "TroChoi.h"
#include <iostream>
#include <sstream>   
#include <iomanip> 


GameUI::GameUI()
    : menuUI(nullptr),
    mapSelectUI(nullptr),
    huongDanUI(nullptr),
    nutPause(nullptr),
    nutGoiY(nullptr),
    lopPhuPause(nullptr),
    gameStatsUI(nullptr),
    soBuocWin(0),       
    thoiGianWin(0.0f),   
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
    if (gameStatsUI) {
        delete gameStatsUI;
        gameStatsUI = nullptr;
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
    nutPause->datViTri(730, 43);
    nutPause->datKichThuoc(50, 50);
    std::cout << "[GameUI] + Nut Pause: OK" << std::endl;

    // ===== 5. KHỞI TẠO NÚT GỢI Ý =====
    nutGoiY = new NutUI();
    if (!nutGoiY->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\hint_button.png")) {
        std::cerr << "[GameUI] Loi tai nut Goi Y!" << std::endl;
        return false;
    }
    nutGoiY->datViTri(665, 43);
    nutGoiY->datKichThuoc(50, 50);
    std::cout << "[GameUI] + Nut Goi Y: OK" << std::endl;

    // ===== 6. KHỞI TẠO PAUSE MENU =====
    lopPhuPause = new LopPhuPause();
    if (!lopPhuPause->khoiTao("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\menupause.png")) {
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

    // ===== 9. LOAD TEXTURE SAO ⭐ =====
    if (!ketCauSao.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\star.png")) {
        std::cerr << "[GameUI] Loi tai anh sao!" << std::endl;
        return false;
    }
    if (!ketCauSaoRong.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\star_empty.png")) {
        std::cerr << "[GameUI] Loi tai anh sao rong!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Star textures: OK" << std::endl;

    // ===== 10. LOAD FONT =====
    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "[GameUI] Loi tai font!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + Font: OK" << std::endl;

    // ===== 11. KHỞI TẠO GAME STATS UI =====
    gameStatsUI = new GameStatsUI();
    if (!gameStatsUI->khoiTao(
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\timer_frame.png",
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\steps_frame.png"
    )) {
        std::cerr << "[GameUI] Loi tai GameStatsUI!" << std::endl;
        return false;
    }
    std::cout << "[GameUI] + GameStatsUI: OK" << std::endl;

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
        if (gameStatsUI) gameStatsUI->capNhat();
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
        if (gameStatsUI) gameStatsUI->ve(cuaSo);
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

        veStatsWin(cuaSo);
    }
    break;

    case TrangThaiUI::THUA:
    {
        sf::RectangleShape lop(sf::Vector2f(800, 800));
        lop.setFillColor(sf::Color(0, 0, 0, 180));
        cuaSo.draw(lop);
        cuaSo.draw(anhThua);

        veStatsLose(cuaSo);
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


// ✅ THÊM: Method lưu stats khi win
void GameUI::luuStatsWin(int soBuoc, float thoiGian) {
    soBuocWin = soBuoc;
    thoiGianWin = thoiGian;
}

void GameUI::veStatsWin(sf::RenderWindow& cuaSo) {
    // 1. Tính số sao
    int soSao = tinhSoSao(soBuocWin, thoiGianWin);

    // 2. Vẽ sao (vị trí: giữa màn hình, phía trên)
    float xBatDau = 25.0f;  // Bạn tự điều chỉnh
    float ySao = 570.0f;     // Bạn tự điều chỉnh
    float khoangCachSao = 80.0f;

    for (int i = 0; i < 3; i++) {
        sf::Sprite spriteSao;
        if (i < soSao) {
            spriteSao.setTexture(ketCauSao);
        }
        else {
            spriteSao.setTexture(ketCauSaoRong);
        }

        // Scale sao cho phù hợp (giả sử ảnh sao 64x64)
        spriteSao.setScale(1.0f, 1.0f);
        spriteSao.setPosition(xBatDau + i * khoangCachSao, ySao);
        cuaSo.draw(spriteSao);
    }

    // 3. Vẽ text số bước
    sf::Text textBuoc;
    textBuoc.setFont(chuPhong);
    textBuoc.setCharacterSize(28);
    textBuoc.setFillColor(sf::Color::Blue);
    textBuoc.setStyle(sf::Text::Bold);
    textBuoc.setString("Steps: " + std::to_string(soBuocWin));
    textBuoc.setPosition(300.0f, 480.0f);  // Tự điều chỉnh vị trí
    cuaSo.draw(textBuoc);

    // 4. Vẽ text thời gian
    sf::Text textThoiGian;
    textThoiGian.setFont(chuPhong);
    textThoiGian.setCharacterSize(28);
    textThoiGian.setFillColor(sf::Color::White);
    textThoiGian.setStyle(sf::Text::Bold);
    textThoiGian.setString("Time: " + dinhDangThoiGian(thoiGianWin));
    textThoiGian.setPosition(300.0f, 520.0f);  // Tự điều chỉnh vị trí
    cuaSo.draw(textThoiGian);

    // 5. Hướng dẫn
    sf::Text textHuongDan;
    textHuongDan.setFont(chuPhong);
    textHuongDan.setString("Press any key to return to Menu");
    textHuongDan.setCharacterSize(18);
    textHuongDan.setFillColor(sf::Color::Green);
    textHuongDan.setPosition(240.0f, 700.0f);
    cuaSo.draw(textHuongDan);
}

// ===== VẼ STATS KHI THUA =====
void GameUI::veStatsLose(sf::RenderWindow& cuaSo) {
    // Lấy stats hiện tại từ GameStatsUI
    int soBuoc = 0;
    float thoiGian = 0.0f;

    if (gameStatsUI) {
        soBuoc = gameStatsUI->laySoBuoc();
        thoiGian = gameStatsUI->layThoiGian();
    }

    // ✅ VẼ 3 SAO RỖNG (☆☆☆) KHI THUA
    float xBatDau = 250.0f;
    float ySao = 350.0f;
    float khoangCachSao = 80.0f;

    for (int i = 0; i < 3; i++) {
        sf::Sprite spriteSao;
        // Thua rồi nên tất cả đều là sao rỗng
        spriteSao.setTexture(ketCauSaoRong);
        spriteSao.setScale(1.0f, 1.0f);
        spriteSao.setPosition(xBatDau + i * khoangCachSao, ySao);
        cuaSo.draw(spriteSao);
    }

    // Vẽ số bước
    sf::Text textBuoc;
    textBuoc.setFont(chuPhong);
    textBuoc.setCharacterSize(28);
    textBuoc.setFillColor(sf::Color::White);
    textBuoc.setStyle(sf::Text::Bold);
    textBuoc.setString("Steps: " + std::to_string(soBuoc));
    textBuoc.setPosition(300.0f, 480.0f);
    cuaSo.draw(textBuoc);

    // Vẽ thời gian
    sf::Text textThoiGian;
    textThoiGian.setFont(chuPhong);
    textThoiGian.setCharacterSize(28);
    textThoiGian.setFillColor(sf::Color::White);
    textThoiGian.setStyle(sf::Text::Bold);
    textThoiGian.setString("Time: " + dinhDangThoiGian(thoiGian));
    textThoiGian.setPosition(300.0f, 520.0f);
    cuaSo.draw(textThoiGian);

    // Hướng dẫn
    sf::Text textHuongDan;
    textHuongDan.setFont(chuPhong);
    textHuongDan.setString("Press any key to return to Menu");
    textHuongDan.setCharacterSize(18);
    textHuongDan.setFillColor(sf::Color::Red);
    textHuongDan.setPosition(240.0f, 700.0f);
    cuaSo.draw(textHuongDan);
}

// ===== TÍNH SỐ SAO (3 SAO, 2 SAO, 1 SAO) =====
int GameUI::tinhSoSao(int soBuoc, float thoiGian) const {
    // TODO: Bạn tự định nghĩa tiêu chí
    // Ví dụ: 
    // - 3 sao: <= 50 bước và <= 60 giây
    // - 2 sao: <= 80 bước và <= 120 giây
    // - 1 sao: hoàn thành

    if (soBuoc <= 50 && thoiGian <= 60.0f) {
        return 3;
    }
    else if (soBuoc <= 80 && thoiGian <= 120.0f) {
        return 2;
    }
    else {
        return 1;
    }
}

// ===== ĐỊNH DẠNG THỜI GIAN =====
std::string GameUI::dinhDangThoiGian(float giay) const {
    int phut = static_cast<int>(giay) / 60;
    int giayConLai = static_cast<int>(giay) % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << phut << ":"
        << std::setfill('0') << std::setw(2) << giayConLai;
    return oss.str();
}