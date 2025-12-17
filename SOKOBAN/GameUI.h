#pragma once
#include <SFML/Graphics.hpp>
#include "MenuUI.h"
#include "MapSelectUI.h"
#include "HuongDan.h"
#include "NutUI.h"
#include "LopPhuPause.h"
#include "GameStatsUI.h"

// Forward declaration
class TroChoi;

enum class TrangThaiUI {
    MENU,
    CHON_BAN_DO,
    HUONG_DAN,
    DANG_CHOI,
    TAM_DUNG,
    THANG,
    THUA
};

class GameUI {
private:
    MenuUI* menuUI;
    MapSelectUI* mapSelectUI;
    HuongDan* huongDanUI;

    NutUI* nutPause;
    NutUI* nutGoiY;

    LopPhuPause* lopPhuPause;
    GameStatsUI* gameStatsUI;

    sf::Texture ketCauThang;
    sf::Sprite anhThang;
    sf::Texture ketCauThua;
    sf::Sprite anhThua;
    sf::Font chuPhong;
    sf::Texture ketCauSao;
    sf::Texture ketCauSaoRong;

    TrangThaiUI trangThaiHienTai;

    
    int soBuocWin;
    float thoiGianWin;

    void veStatsWin(sf::RenderWindow& cuaSo);
    void veStatsLose(sf::RenderWindow& cuaSo);
    int tinhSoSao(int soBuoc, float thoiGian) const;
    std::string dinhDangThoiGian(float giay) const;

public:
    GameUI();
    ~GameUI();

    bool khoiTao();

    TrangThaiUI layTrangThaiUI() const { return trangThaiHienTai; }
    void datTrangThaiUI(TrangThaiUI trangThai) { trangThaiHienTai = trangThai; }

    void xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo, TroChoi* troChoi);
    bool xuLyClickChuotTrongGame(const sf::Vector2i& viTriChuot, TroChoi* troChoi);
    bool xuLyPhimWinLose(const sf::Event& suKien);

    void capNhat(const sf::Vector2i& viTriChuot);
    void ve(sf::RenderWindow& cuaSo);

    void hienThiPauseMenu();
    void anPauseMenu();
    bool pauseMenuDangHienThi() const;
    HanhDongPause xuLyClickPauseMenu(const sf::Vector2i& viTriChuot);

    int layMapDaChon() const;
    
    GameStatsUI* layGameStatsUI() { return gameStatsUI; }
    
    // ✅ THÊM: Method lưu stats
    void luuStatsWin(int soBuoc, float thoiGian);
};