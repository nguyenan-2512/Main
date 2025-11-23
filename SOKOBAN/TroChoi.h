#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BanDo.h"
#include "GameController.h"
#include "MapRenderer.h"
#include "InputHandler.h"
#include "GameUI.h"

class TroChoi {
private:
    // UI & Input
    GameUI* gameUI;
    InputHandler inputHandler;
    MapRenderer mapRenderer;

    // Window & View
    sf::RenderWindow cuaSo;
    sf::View tamNhinTroChoi;
    sf::Vector2u kichThuocGoc;
    float tyLeX;
    float tyLeY;
    float cheDoX;
    float cheDoY;

    // Game objects
    BanDo* banDoHienTai;
    GameController* gameController;

    // Audio
    sf::Music nhacNen;
    sf::SoundBuffer boNhoAmThanhBuocDi;
    sf::Sound amThanhBuocDi;
    sf::SoundBuffer boNhoAmThanhChienThang;
    sf::Sound amThanhChienThang;
    sf::SoundBuffer boNhoAmThanhThua;
    sf::Sound amThanhThua;

    // State
    bool hienThiThang;
    bool hienThiThua;
    bool dangTuDongGiai;
    sf::Clock dongHoDelta;

public:
    TroChoi();
    ~TroChoi();
    void chay();

    // Callbacks cho GameUI
    void xuLyClickNutPause();
    void xuLyClickNutGoiY();
    void xuLyHanhDongPause(HanhDongPause hanhDong);
    void quayVeMenu();

private:
    void xuLySuKien();
    void capNhat();
    void veHinh();
    void khoiTaoTroChoi();
    void xoaTroChoi();
    void phatAmThanhBuocDi();
    void thieLapManHinhDay();
    void capNhatTamNhin();
    sf::Vector2i layViTriChuotDaTyLe(const sf::Vector2i& viTriChuot);
    void xuLyHanhDongGame(HanhDongGame hanhDong);
};