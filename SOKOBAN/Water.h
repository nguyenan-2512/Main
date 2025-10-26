#pragma once
#include "GameObject.h"

class Water : public GameObject {
public:
	Water();
    Water(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};