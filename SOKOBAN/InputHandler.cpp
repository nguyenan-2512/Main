#include "InputHandler.h"

HanhDongGame InputHandler::xuLyPhimChoiGame(const sf::Event& suKien) {
    if (suKien.type != sf::Event::KeyPressed) {
        return HanhDongGame::KHONG;
    }

    switch (suKien.key.code) {
        // Di chuyển
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
        return HanhDongGame::DI_LEN;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
        return HanhDongGame::DI_XUONG;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
        return HanhDongGame::DI_TRAI;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
        return HanhDongGame::DI_PHAI;

        // Chức năng
    case sf::Keyboard::U:
        return HanhDongGame::UNDO;

    case sf::Keyboard::R:
        return HanhDongGame::RESTART;

    case sf::Keyboard::T:
        return HanhDongGame::TELEPORT;

    case sf::Keyboard::H:
        return HanhDongGame::HINT;

    case sf::Keyboard::J:
        return HanhDongGame::DUNG_AUTO_SOLVE;

    case sf::Keyboard::Escape:
        return HanhDongGame::PAUSE;

    default:
        return HanhDongGame::KHONG;
    }
}

bool InputHandler::xuLyPhimWinLose(const sf::Event& suKien) {
    // Bất kỳ phím nào cũng quay về menu
    return (suKien.type == sf::Event::KeyPressed);
}