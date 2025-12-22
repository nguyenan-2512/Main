#pragma once
#include <SFML/Graphics.hpp>

class GameController;

enum class HanhDongGame {
    KHONG,
    DI_LEN,
    DI_XUONG,
    DI_TRAI,
    DI_PHAI,
    UNDO,
    RESTART,
    TELEPORT,
    HINT,
    DUNG_AUTO_SOLVE,
    PAUSE,
    THOAT
};

class InputHandler {
public:
    InputHandler() = default;
    HanhDongGame xuLyPhimChoiGame(const sf::Event& suKien);
    bool xuLyPhimWinLose(const sf::Event& suKien);
};