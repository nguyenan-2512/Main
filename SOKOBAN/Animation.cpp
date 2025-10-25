#include "Animation.h"
#include <iostream>

float Animation::animationSpeed = 0.1f;

Animation::Animation()
    : sprite(nullptr),
    frameWidth(0),
    frameHeight(0),
    currentFrame(0),
    currentState(-1),
    loop(true) {
}

Animation::Animation(sf::Sprite* sprite,
    const sf::Texture& spriteSheet,
    int frameWidth,
    int frameHeight,
    int numFrames,
    bool loop)
    : sprite(sprite),
    spriteSheet(spriteSheet),
    frameWidth(frameWidth),
    frameHeight(frameHeight),
    currentFrame(0),
    currentState(-1),
    loop(loop) {

    // Chia spriteSheet thành các frame cho từng hướng
    for (int i = 0; i < numFrames; ++i) {
        // Hàng 0: Di chuyển XUỐNG (mặt)
        MoveDown_frames.push_back(
            sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight)
        );

        // Hàng 1: Di chuyển LÊN (lưng)
        MoveUp_frames.push_back(
            sf::IntRect(i * frameWidth, frameHeight, frameWidth, frameHeight)
        );

        // Hàng 2: Di chuyển trái
        MoveLeft_frames.push_back(
            sf::IntRect(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight)
        );

        // Hàng 3: Di chuyển phải
        MoveRight_frames.push_back(
            sf::IntRect(i * frameWidth, 3 * frameHeight, frameWidth, frameHeight)
        );
    }

    // Thiết lập texture và frame ban đầu
    if (sprite) {
        sprite->setTexture(spriteSheet);
        sprite->setTextureRect(MoveDown_frames[0]);
    }
}

void Animation::update(const int& state, float deltaTime) {
    if (!sprite) return;

    // Nếu trạng thái thay đổi → Reset animation
    if (state != currentState) {
        currentState = state;
        currentFrame = 0;
        frameClock.restart();
    }

    // Cập nhật frame dựa trên thời gian
    if (frameClock.getElapsedTime().asSeconds() >= animationSpeed) {
        currentFrame++;
        frameClock.restart();

        // Chọn DynamicArray frame tương ứng với state
        DynamicArray<sf::IntRect>* frames = nullptr;
        switch (currentState) {
        case MOVE_UP:    frames = &MoveUp_frames; break;
        case MOVE_DOWN:  frames = &MoveDown_frames; break;
        case MOVE_LEFT:  frames = &MoveLeft_frames; break;
        case MOVE_RIGHT: frames = &MoveRight_frames; break;
        default:         frames = &MoveDown_frames; break;
        }

        if (frames && !frames->empty()) {
            // Kiểm tra nếu vượt quá số frame
            if (currentFrame >= frames->getSize()) {
                if (loop) {
                    currentFrame = 0;
                }
                else {
                    currentFrame = frames->getSize() - 1;
                }
            }

            // Cập nhật texture rect
            sprite->setTextureRect((*frames)[currentFrame]);
        }
    }
}

void Animation::reset() {
    currentFrame = 0;
    frameClock.restart();
}