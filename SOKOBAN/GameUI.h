#pragma once
#include <SFML/Graphics.hpp>
#include "MenuUI.h"
#include "MapSelectUI.h"
#include "HuongDan.h"
#include "NutUI.h"
#include "LopPhuPause.h"


// Forward declaration
class TroChoi;

// ===== ENUM TRẠNG THÁI UI =====
enum class TrangThaiUI {
    MENU,           // Menu chính
    CHON_BAN_DO,    // Chọn map
    HUONG_DAN,      // Hướng dẫn
    DANG_CHOI,      // Đang chơi (hiện nút UI)
    TAM_DUNG,       // Pause menu
    THANG,          // Win screen
    THUA            // Lose screen
};

// ===== CLASS QUẢN LÝ TOÀN BỘ UI =====
class GameUI {
private:
    MenuUI* menuUI;
    MapSelectUI* mapSelectUI;
    HuongDan* huongDanUI;

    // ===== IN-GAME UI (Nút Pause, Hint) =====
    NutUI* nutPause;
    NutUI* nutGoiY;

    // ===== PAUSE MENU =====
    LopPhuPause* lopPhuPause;

    // ===== WIN/LOSE OVERLAY =====
    sf::Texture ketCauThang;
    sf::Sprite anhThang;
    sf::Texture ketCauThua;
    sf::Sprite anhThua;
    sf::Font chuPhong;

    // ===== TRẠNG THÁI UI =====
    TrangThaiUI trangThaiHienTai;

public:
    GameUI();
    ~GameUI();

    // ===== KHỞI TẠO =====
    bool khoiTao();

    // ===== QUẢN LÝ TRẠNG THÁI =====
    TrangThaiUI layTrangThaiUI() const { return trangThaiHienTai; }
    void datTrangThaiUI(TrangThaiUI trangThai) { trangThaiHienTai = trangThai; }

    // ===== XỬ LÝ SỰ KIỆN =====
    // Xử lý sự kiện theo trạng thái UI
    void xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo, TroChoi* troChoi);

    // Xử lý click chuột khi đang chơi
    bool xuLyClickChuotTrongGame(const sf::Vector2i& viTriChuot, TroChoi* troChoi);

    // Xử lý phím Win/Lose
    bool xuLyPhimWinLose(const sf::Event& suKien);

    // Cập nhật hover
    void capNhat(const sf::Vector2i& viTriChuot);

    // ===== VẼ =====
    void ve(sf::RenderWindow& cuaSo);

    // ===== PAUSE MENU =====
    void hienThiPauseMenu();
    void anPauseMenu();
    bool pauseMenuDangHienThi() const;
    HanhDongPause xuLyClickPauseMenu(const sf::Vector2i& viTriChuot);

    int layMapDaChon() const;
};