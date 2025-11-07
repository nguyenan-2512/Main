#pragma once
#include "GameObject.h"
#include "Animation.h"

class Player : public GameObject {
private:
    Animation animation; 

    int currentState;  

public:
    Player(int x = 0, int y = 0, int tileSize = 32);

    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime);  

    void initAnimation(const sf::Texture& spriteSheet,
        int frameWidth,
        int frameHeight,
        int numFrames);

    void move(int dx, int dy);
    void setPosition(int x, int y, int dx, int dy);
};