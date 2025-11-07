#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"
#include "Guide.h"

enum class MenuState {
    MENU,
    SELECTION_MAP,
    GUIDE,
    PLAYING,
    EXIT
};

class Menu {
private:
    Guide guide; 

    sf::CircleShape backButton; 
    bool backClicked;            

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    DynamicArray<sf::Text> menuItems;  
    sf::RectangleShape playButton;
    sf::RectangleShape guideButton;
    sf::RectangleShape exitButton;
    sf::Text playText;
    sf::Text exitText;
    int selectedItem;
    MenuState currentState;

    sf::Texture selectMapBackgroundTexture;
    sf::Sprite selectMapBackgroundSprite;
    DynamicArray<sf::RectangleShape> mapButtons;  
    DynamicArray<sf::Text> mapItems;              
    int selectedMap = -1;
    int highlightedMapIndex = 0;

public:
    Menu();
    ~Menu();
    bool loadResources();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
    MenuState getState() const;
    void setState(MenuState state);
    void reset();
    int getSelectedMap() const;

private:
    void setupButtons();
    void setupTexts();
    bool isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos);
    bool isMouseOverCircle(const sf::CircleShape& button, sf::Vector2i mousePos);

    void setupMapItems(sf::RenderWindow& window);
    void drawSelectionMap(sf::RenderWindow& window);
    bool isBackClicked() const { return backClicked; }
    void resetBack() { backClicked = false; }

};