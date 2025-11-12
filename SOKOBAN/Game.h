#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Menu.h"
#include "Map.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
private:
    sf::RenderWindow window;
    Menu menu;
    Map* BanDoHienTai;
    GameState gameState;
    sf::Music NhacNen;
    sf::SoundBuffer moveSoundBuffer;
    sf::Sound AmThanhBuocDi;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound AmThanhChienThang;
    sf::SoundBuffer gameOverSoundBuffer;
    sf::Sound AmThanhThua;

    sf::Texture winTexture;
    sf::Sprite AnhThang;
    sf::Texture gameOverTexture;
    sf::Sprite AnhThua;

    bool HienThiThang;
    bool HienThiThua;

    sf::Clock deltaClock;


    sf::View gameView;              // View cho game (800x800)
    sf::Vector2u originalSize;      // Kích thước gốc (800x800)
    float scaleX;                   // Tỷ lệ scale X
    float scaleY;                   // Tỷ lệ scale Y
    float offsetX;                  // Offset X (letterbox)
    float offsetY;                  // Offset Y (letterbox)

public:
    Game();
    ~Game();
    void run();

private:
    void XuLySuKiens();
    void CapNhat();
    void render();
    void KhoiTaoGame();
    void XoaGame();
    void PhatAmThanhBuocDi();

    // THÊM: Fullscreen helper functions
    void setupFullscreen();
    void CapNhatView();
    sf::Vector2i getScaledMousePosition(const sf::Vector2i& mousePos);
};