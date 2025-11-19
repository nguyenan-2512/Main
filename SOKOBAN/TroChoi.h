#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "GiaoDien.h"
#include "BanDo.h"
#include "NutUI.h"        
#include "LopPhuPause.h"   
#include "HuongDan.h"     
#include "GameController.h"

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
    GameController* gameController;
    TrangThaiTroChoi trangThaiTroChoi;
    TrangThaiTroChoi trangThaiTruoc;
    
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

    sf::View tamNhinTroChoi;
    sf::Vector2u kichThuocGoc;
    float tyLeX;
    float tyLeY;
    float cheDoX;
    float cheDoY;

    NutUI* nutPause;
    NutUI* nutGoiY;
    LopPhuPause* lopPhuPause;
    HuongDan* huongDan;
    
    bool dangTuDongGiai;  

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

    void thieLapManHinhDay();
    void capNhatTamNhin();
    sf::Vector2i layViTriChuotDaTyLe(const sf::Vector2i& viTriChuot);
    
    // THÊM: UI Functions
    void khoiTaoUI();
    void xoaUI();
    void xuLyClickNutPause();
    void xuLyClickNutGoiY();
    void xuLyHanhDongPause(HanhDongPause hanhDong);
    void veNutUI();
};