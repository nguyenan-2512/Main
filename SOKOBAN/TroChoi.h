#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "GiaoDien.h"
#include "BanDo.h"

enum class TrangThaiTroChoi {
    MENU,
    DANG_CHOI,
    TAM_DUNG,
    KET_THUC
};

class TroChoi {
private:
    sf::RenderWindow cuaSo;
    GiaoDien GiaoDien;
    BanDo* banDoHienTai;
    TrangThaiTroChoi trangThaiTroChoi;
    sf::Music nhacNen;
    sf::SoundBuffer boNhoAmThanhBuocDi;
    sf::Sound amThanhBuocDi;
    sf::SoundBuffer boNhoAmThanhChienThang;
    sf::Sound amThanhChienThang;
    sf::SoundBuffer boNhoAmThanhThua;
    sf::Sound amThanhThua;

    sf::Texture ketCauThang;
    sf::Sprite anhThang;
    sf::Texture ketCauThua;
    sf::Sprite anhThua;

    bool hienThiThang;
    bool hienThiThua;

    sf::Clock dongHoDelta;

    sf::View tamNhinTroChoi;        // View cho game (800x800)
    sf::Vector2u kichThuocGoc;      // Kích thước gốc (800x800)
    float tyLeX;                    // Tỷ lệ scale X
    float tyLeY;                    // Tỷ lệ scale Y
    float cheDoX;                   // Offset X (letterbox)
    float cheDoY;                   // Offset Y (letterbox)

public:
    TroChoi();
    ~TroChoi();
    void chay();

private:
    void xuLySuKien();
    void capNhat();
    void veHinh();
    void khoiTaoTroChoi();
    void xoaTroChoi();
    void phatAmThanhBuocDi();

    // Các hàm hỗ trợ fullscreen
    void thieLapManHinhDay();
    void capNhatTamNhin();
    sf::Vector2i layViTriChuotDaTyLe(const sf::Vector2i& viTriChuot);
};