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
    Map* currentMap;
    GameState gameState;
    sf::Music backgroundMusic;
    sf::SoundBuffer moveSoundBuffer;
    sf::Sound moveSound;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;
    sf::SoundBuffer gameOverSoundBuffer;
    sf::Sound gameOverSound;

    sf::Texture winTexture;
    sf::Sprite winSprite;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;

    bool showWinMessage;
    bool showGameOverMessage;

    sf::Clock deltaClock;

    // THÊM: Fullscreen support
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
    void handleEvents();
    void update();
    void render();
    void initializeGame();
    void cleanupGame();
    void playMoveSound();

    // THÊM: Fullscreen helper functions
    void setupFullscreen();
    void updateView();
    sf::Vector2i getScaledMousePosition(const sf::Vector2i& mousePos);
};