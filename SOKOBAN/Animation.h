#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class Animation {
private:
    sf::Sprite* sprite;                      
    sf::Texture spriteSheet;               

    int frameWidth;                       
    int frameHeight;                        
    int currentFrame;                    
    int currentState;                      
    bool loop;                              

    sf::Clock frameClock;                 

    DynamicArray<sf::IntRect> MoveUp_frames;
    DynamicArray<sf::IntRect> MoveDown_frames;
    DynamicArray<sf::IntRect> MoveLeft_frames;
    DynamicArray<sf::IntRect> MoveRight_frames;

public:
    static float animationSpeed;           

   
    enum State {
        MOVE_UP = 0,
        MOVE_DOWN = 1,
        MOVE_LEFT = 2,
        MOVE_RIGHT = 3
    };

   
    Animation();


    Animation(sf::Sprite* sprite,
        const sf::Texture& spriteSheet,
        int frameWidth,
        int frameHeight,
        int numFrames,
        bool loop = true);


    void update(const int& state, float deltaTime);


    void reset();

    int getCurrentFrame() const { return currentFrame; }
    int getCurrentState() const { return currentState; }
}; 
