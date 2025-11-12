#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class Guide {
private:
    DynamicArray<sf::Texture*> pageTextures; // Mảng texture các trang
    DynamicArray<sf::Sprite> pageSprites;     // Mảng sprite hiển thị 

    bool backToMenu; 
    int currentPage;
    int totalPages;   
    sf::CircleShape prevButton;
    sf::CircleShape nextButton;

public:
    Guide();

    bool TaiTaiNguyen();             
    void XuLySuKien(const sf::Event& event, sf::RenderWindow& window);
    void CapNhat(float deltaTime);
    void draw(sf::RenderWindow& window);
    void reset();

    bool shouldReturnToMenu() const { return backToMenu; }
    void resetBackFlag() { backToMenu = false; }

    bool ChuoiDeLenNut (const sf::CircleShape& button, sf::Vector2i mousePos);
};
