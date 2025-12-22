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
    winUI(nullptr),
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
    if (winUI) {
        delete winUI;
        winUI = nullptr;
    }
}

bool GameUI::khoiTao() {

    menuUI = new MenuUI();
    if (!menuUI->taiTaiNguyen()) {
        return false;
    }

    mapSelectUI = new MapSelectUI();
    if (!mapSelectUI->taiTaiNguyen()) {
        return false;
    }

    huongDanUI = new HuongDan();
    if (!huongDanUI->taiTaiNguyen()) {
        return false;
    }

    nutPause = new NutUI();
    if (!nutPause->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\pause_button.png")) {
        return false;
    }
    nutPause->datViTri(730, 43);
    nutPause->datKichThuoc(50, 50);

    nutGoiY = new NutUI();
    if (!nutGoiY->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\hint_button.png")) {
        return false;
    }
    nutGoiY->datViTri(665, 43);
    nutGoiY->datKichThuoc(50, 50);

    lopPhuPause = new LopPhuPause();
    if (!lopPhuPause->khoiTao("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\menupause.png")) {
        return false;
    }

    winUI = new WinUI();
    if (!winUI->khoiTao(
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win3.3.png",  
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win2.2.png",  
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win1.1.png"    
    )) {
        return false;
    }

    if (!ketCauThua.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\gameover.png")) {
        return false;
    }
    anhThua.setTexture(ketCauThua);
    anhThua.setPosition(0, 0);

    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        return false;
    }

    gameStatsUI = new GameStatsUI();
    if (!gameStatsUI->khoiTao(
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\timer_frame.png",
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\steps_frame.png"
    )) {
        return false;
    }
    return true;


}

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
            trangThaiHienTai = TrangThaiUI::MENU;
        }
        else if (result >= 0) {
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
        if (suKien.type == sf::Event::MouseButtonPressed &&
            suKien.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);
            WinUI::HanhDongWin hanhDong = winUI->kiemTraClick(viTriChuot);

            if (hanhDong == WinUI::HanhDongWin::HOME) {
                troChoi->quayVeMenu();
            }
            else if (hanhDong == WinUI::HanhDongWin::NEXT) {
                troChoi->chuyenSangManTiepTheo();  
            }
        }
        break;

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
    if (nutPause && nutPause->kiemTraClick(viTriChuot)) {
        troChoi->xuLyClickNutPause();
        return true;
    }

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
        if (winUI) {
            winUI->ve(cuaSo);
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

void GameUI::luuStatsWin(int soBuoc, float thoiGian) {
    soBuocWin = soBuoc;
    thoiGianWin = thoiGian;
}