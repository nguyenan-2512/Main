#pragma once
#include "GameObject.h"
#include "DynamicArray.h"  

class Button : public GameObject {
private:
    bool isPressed;
    DynamicArray<std::pair<int, int>> linkedTraps; 
    const sf::Texture* unpressedTexture;
    const sf::Texture* pressedTexture;

public:
	Button();
    Button(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;

    void setPressed(bool pressed);
    bool getIsPressed() const { return isPressed; }

    void addLinkedTrap(int x, int y) {
        linkedTraps.push_back(std::make_pair(x, y));
    }

    const DynamicArray<std::pair<int, int>>& getLinkedTraps() const {
        return linkedTraps;
    }

    void setUnpressedTexture(const sf::Texture& texture);
    void setPressedTexture(const sf::Texture& texture);
    void updateTexture();
};