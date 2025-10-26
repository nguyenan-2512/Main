#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall();
    Wall(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};