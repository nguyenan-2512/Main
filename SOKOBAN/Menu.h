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
    sf::RectangleShape playButton;
    sf::RectangleShape guideButton;
    sf::RectangleShape exitButton;
    int selectedItem;
    MenuState currentState;

    sf::Texture selectMapBackgroundTexture;
    sf::Sprite selectMapBackgroundSprite;
    DynamicArray<sf::RectangleShape> mapButtons;               
    int selectedMap = -1;
    int highlightedMapIndex = 0;

public:
    Menu();
    ~Menu();
    bool TaiTaiNguyen();
    void XuLySuKien(const sf::Event& event, sf::RenderWindow& window);
    void CapNhat();
    void draw(sf::RenderWindow& window);
    MenuState LayTrangThai() const;
    void DatTrangThai(MenuState state);
    void reset();
    int LayMapDaChon() const;

private:
    void ThietLapCacNut();
    bool ChuoiDeLenNut (const sf::RectangleShape& button, sf::Vector2i mousePos);
    bool ChuoiDeLenNutTron (const sf::CircleShape& button, sf::Vector2i mousePos);

    void ThietLapChonMap(sf::RenderWindow& window);
    void VeManHinhChonMap(sf::RenderWindow& window);
    bool DaNhanQuayLai() const { return backClicked; }
    void DatLaiQuayLai() { backClicked = false; }

};