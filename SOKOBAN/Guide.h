#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class Guide {
private:
    DynamicArray<sf::Texture*> pageTextures; // Mảng texture các trang
    DynamicArray<sf::Sprite> pageSprites;     // Mảng sprite hiển thị 

    bool backToMenu; // true nếu người dùng click nút quay lại menu
    int currentPage;   // Trang hiện tại
    int totalPages;    // Tổng số trang

    // Vùng click của nút trái/phải (mô phỏng nút trong ảnh)
    sf::CircleShape prevButton;
    sf::CircleShape nextButton;

public:
    Guide();

    bool loadResources();                     // Tải slide
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void reset();

    bool shouldReturnToMenu() const { return backToMenu; }
    void resetBackFlag() { backToMenu = false; }

    bool isMouseOverButton(const sf::CircleShape& button, sf::Vector2i mousePos);
};
