#pragma once
#include "GameObject.h"

class IronBox : public GameObject {
private:
    const sf::Texture* texture;

public:
	IronBox();  
    IronBox(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
    void setIronTexture(const sf::Texture& texture);
}; 