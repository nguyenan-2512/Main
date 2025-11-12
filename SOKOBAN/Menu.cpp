#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() : selectedItem(0), currentState(MenuState::MENU) {
}

Menu::~Menu() {
}

bool Menu::TaiTaiNguyen() {
    // Load background texture
    if (!backgroundTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\menutext.png")) {
        std::cerr << "Failed to load menu background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundTexture.setSmooth(true);

    // Load select map background
    if (!selectMapBackgroundTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\selectmaptext.png")) {
        std::cerr << "Failed to load select map background!" << std::endl;
    }
    selectMapBackgroundSprite.setTexture(selectMapBackgroundTexture);

    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Failed to load font, using default font" << std::endl;
    }

    ThietLapCacNut();

    return true;
}

void Menu::ThietLapCacNut() {
    backButton.setRadius(50.f);
    backButton.setOrigin(50.f, 50.f);
    backButton.setPosition(88.f, 711.f);
    backButton.setFillColor(sf::Color(0, 0, 0, 0));
    backButton.setOutlineThickness(0.f);
    backClicked = false;
    // Setup Play button
    playButton.setSize(sf::Vector2f(270, 90));
    playButton.setPosition(275, 300);
    playButton.setFillColor(sf::Color(0, 0, 0, 0));
    playButton.setOutlineThickness(0);

    // Setup Guide button
    guideButton.setSize(sf::Vector2f(270, 90));
    guideButton.setPosition(275, 454);
    guideButton.setFillColor(sf::Color(0, 0, 0, 0));
    guideButton.setOutlineThickness(0);

    // Setup Exit button
    exitButton.setSize(sf::Vector2f(270, 90));
    exitButton.setPosition(275, 610);
    exitButton.setFillColor(sf::Color(0, 0, 0, 0));
    exitButton.setOutlineThickness(0);
}

void Menu::XuLySuKien(const sf::Event& event, sf::RenderWindow& window) {

    if (currentState == MenuState::MENU) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Sử dụng trực tiếp từ event (đã được scale)
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            if (ChuoiDeLenNut (playButton, mousePos)) {
                currentState = MenuState::SELECTION_MAP;
                ThietLapChonMap(window);
            }
            else if (ChuoiDeLenNut (guideButton, mousePos)) {
                currentState = MenuState::GUIDE;
                guide.reset();
                guide.TaiTaiNguyen();
            }
            else if (ChuoiDeLenNut (exitButton, mousePos)) {
                currentState = MenuState::EXIT;
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up:
                selectedItem = (selectedItem - 1 + 3) % 3;
                break;
            case sf::Keyboard::Down:
                selectedItem = (selectedItem + 1) % 3;
                break;
            case sf::Keyboard::Enter:
                if (selectedItem == 0) {
                    currentState = MenuState::SELECTION_MAP;
                    ThietLapChonMap(window);
                }
                else if (selectedItem == 1) {
                    currentState = MenuState::GUIDE;
                    guide.reset();
                    guide.TaiTaiNguyen();
                }
                else {
                    currentState = MenuState::EXIT;
                }
                break;
            case sf::Keyboard::Escape:
                currentState = MenuState::EXIT;
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);

            if (ChuoiDeLenNut (playButton, mousePos)) {
                selectedItem = 0;
                playButton.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                playButton.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (ChuoiDeLenNut (guideButton, mousePos)) {
                selectedItem = 1;
                guideButton.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                guideButton.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (ChuoiDeLenNut (exitButton, mousePos)) {
                selectedItem = 2;
                exitButton.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                exitButton.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (ChuoiDeLenNutTron (backButton, mousePos)) {
                backButton.setFillColor(sf::Color(255, 255, 255, 60));
            }
            else {
                backButton.setFillColor(sf::Color(0, 0, 0, 0));
            }
        }
    }
    else if (currentState == MenuState::SELECTION_MAP) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            float dx = mousePos.x - backButton.getPosition().x;
            float dy = mousePos.y - backButton.getPosition().y;
            if (dx * dx + dy * dy <= backButton.getRadius() * backButton.getRadius()) {
                std::cout << "Back to main menu\n";
                currentState = MenuState::MENU;
                return;
            }

            for (int i = 0; i < mapButtons.getSize(); ++i) {
                if (ChuoiDeLenNut (mapButtons[i], mousePos)) {
                    selectedMap = i;
                    std::cout << "Selected Map: " << (i + 1) << std::endl;
                    currentState = MenuState::PLAYING;
                    break;
                }
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            const int numMaps = 10;

            switch (event.key.code) {
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                if (highlightedMapIndex % 4 > 0) {
                    highlightedMapIndex--;
                }
                break;

            case sf::Keyboard::Right:
            case sf::Keyboard::D:
                if (highlightedMapIndex % 4 < 3 && highlightedMapIndex < numMaps - 1) {
                    highlightedMapIndex++;
                }
                break;

            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                if (highlightedMapIndex >= 4) {
                    highlightedMapIndex -= 4;
                }
                break;

            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                if (highlightedMapIndex < 4 && highlightedMapIndex + 4 < numMaps) {
                    highlightedMapIndex += 4;
                }
                else if (highlightedMapIndex >= 4 && highlightedMapIndex < 8) {
                    highlightedMapIndex = std::min(highlightedMapIndex + 4, numMaps - 1);
                }
                break;

            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                selectedMap = highlightedMapIndex;
                std::cout << "Selected Map: " << (selectedMap + 1) << std::endl;
                currentState = MenuState::PLAYING;
                break;

            case sf::Keyboard::Escape:
                currentState = MenuState::MENU;
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);

            for (int i = 0; i < mapButtons.getSize(); ++i) {
                if (ChuoiDeLenNut (mapButtons[i], mousePos)) {
                    highlightedMapIndex = i;
                    break;
                }
            }
        }
    }
    else if (currentState == MenuState::GUIDE) {
        if (guide.shouldReturnToMenu()) {
            guide.resetBackFlag();
            DatTrangThai(MenuState::MENU);
        }
        guide.XuLySuKien(event, window);
    }
}

void Menu::CapNhat() {
    if (currentState == MenuState::MENU) {
        if (selectedItem == 0) {
            playButton.setFillColor(sf::Color(255, 255, 255, 50));
            guideButton.setFillColor(sf::Color(0, 0, 0, 0));
            exitButton.setFillColor(sf::Color(0, 0, 0, 0));
        }
        else if (selectedItem == 1) {
            playButton.setFillColor(sf::Color(0, 0, 0, 0));
            guideButton.setFillColor(sf::Color(255, 255, 255, 50));
            exitButton.setFillColor(sf::Color(0, 0, 0, 0));
        }
        else {
            playButton.setFillColor(sf::Color(0, 0, 0, 0));
            guideButton.setFillColor(sf::Color(0, 0, 0, 0));
            exitButton.setFillColor(sf::Color(255, 255, 255, 50));
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    if (currentState == MenuState::MENU) {
        window.draw(backgroundSprite);
        window.draw(playButton);
        window.draw(guideButton);
        window.draw(exitButton);
    }
    else if (currentState == MenuState::SELECTION_MAP) {
        VeManHinhChonMap(window);
    }
    else if (currentState == MenuState::GUIDE) {
        guide.draw(window);
    }
}

MenuState Menu::LayTrangThai() const {
    return currentState;
}

void Menu::DatTrangThai(MenuState state) {
    currentState = state;
}

void Menu::reset() {
    currentState = MenuState::MENU;
    selectedItem = 0;
}

int Menu::LayMapDaChon() const {
    return selectedMap;
}

bool Menu::ChuoiDeLenNut (const sf::RectangleShape& button, sf::Vector2i mousePos) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool Menu::ChuoiDeLenNutTron (const sf::CircleShape& button, sf::Vector2i mousePos) {
    sf::Vector2f pos = button.getPosition();
    float dx = mousePos.x - pos.x;
    float dy = mousePos.y - pos.y;
    return (dx * dx + dy * dy <= button.getRadius() * button.getRadius());
}

void Menu::ThietLapChonMap(sf::RenderWindow& window) {
    mapButtons.clear();
    highlightedMapIndex = 0;

    const int numMaps = 10;
    const float buttonRadius = 50.f;

    DynamicArray<sf::Vector2f> positions;
    positions.push_back(sf::Vector2f(181.f, 302.f));  // Map 1
    positions.push_back(sf::Vector2f(325.f, 302.f));  // Map 2
    positions.push_back(sf::Vector2f(469.f, 302.f));  // Map 3
    positions.push_back(sf::Vector2f(613.f, 302.f));  // Map 4
    positions.push_back(sf::Vector2f(181.f, 481.f));  // Map 5
    positions.push_back(sf::Vector2f(325.f, 481.f));  // Map 6
    positions.push_back(sf::Vector2f(469.f, 481.f));  // Map 7
    positions.push_back(sf::Vector2f(613.f, 481.f));  // Map 8

    for (int i = 0; i < numMaps && i < 8; ++i) {
        sf::RectangleShape rectBtn;
        rectBtn.setSize(sf::Vector2f(buttonRadius * 2, buttonRadius * 2));
        rectBtn.setFillColor(sf::Color(0, 0, 0, 0));
        rectBtn.setOutlineColor(sf::Color::Yellow);
        rectBtn.setOutlineThickness(0.f);
        rectBtn.setOrigin(buttonRadius, buttonRadius);
        rectBtn.setPosition(positions[i]);
        mapButtons.push_back(rectBtn);
    }
}

void Menu::VeManHinhChonMap(sf::RenderWindow& window) {
    window.draw(selectMapBackgroundSprite);



    if (highlightedMapIndex >= 0 && highlightedMapIndex < mapButtons.getSize()) {
        sf::Vector2f btnPos = mapButtons[highlightedMapIndex].getPosition();
        float radius = 55.f;
        for (int i = 0; i < 3; ++i) {
            sf::CircleShape highlight(radius + i * 8.f);
            highlight.setOrigin(radius + i * 8.f, radius + i * 8.f);
            highlight.setPosition(btnPos);
            highlight.setFillColor(sf::Color(255, 255, 0, 50 - i * 15));
            highlight.setOutlineThickness(3.f - i);
            highlight.setOutlineColor(sf::Color(255, 255, 0, 150 - i * 40));
            window.draw(highlight);
        }

        // Vòng tròn chính
        sf::CircleShape mainHighlight(radius);
        mainHighlight.setOrigin(radius, radius);
        mainHighlight.setPosition(btnPos);
        mainHighlight.setFillColor(sf::Color(255, 255, 100, 80));
        mainHighlight.setOutlineThickness(4.f);
        mainHighlight.setOutlineColor(sf::Color::Yellow);
        window.draw(mainHighlight);
    }

    window.draw(backButton);

}