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

    bool loadResources();             
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void reset();

    bool shouldReturnToMenu() const { return backToMenu; }
    void resetBackFlag() { backToMenu = false; }

    bool isMouseOverButton(const sf::CircleShape& button, sf::Vector2i mousePos);
};
