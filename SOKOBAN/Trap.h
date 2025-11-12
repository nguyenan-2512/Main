#pragma once
#include "GameObject.h"

class Trap : public GameObject {
private:
    bool isActive; 
    const sf::Texture* activeTexture;   
    const sf::Texture* inactiveTexture; 

public:
	Trap();
    Trap(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;

    void setActive(bool active);
    bool getIsActive() const { return isActive; }

    void setActiveTexture(const sf::Texture& texture);
    void setInactiveTexture(const sf::Texture& texture);
    void CapNhatTexture();
}; 