#pragma once
#include "GameObject.h"

class Goal : public GameObject {
public:
	Goal();
    Goal(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};
