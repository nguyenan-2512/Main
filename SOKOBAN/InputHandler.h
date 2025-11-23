#pragma once
#include <SFML/Graphics.hpp>

// Forward declarations
class GameController;

// Enum định nghĩa các hành động game
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

// Class chỉ chịu trách nhiệm xử lý input
class InputHandler {
public:
    InputHandler() = default;

    // Xử lý sự kiện phím bấm khi đang chơi
    HanhDongGame xuLyPhimChoiGame(const sf::Event& suKien);

    // Xử lý sự kiện phím bấm khi win/lose
    bool xuLyPhimWinLose(const sf::Event& suKien);
};