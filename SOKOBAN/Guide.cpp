#include "Guide.h"
#include <iostream>

Guide::Guide()
    : currentPage(0), totalPages(0)
{
    backToMenu = false;

    prevButton.setRadius(37.f);
    prevButton.setOrigin(37.f, 37.f);
    prevButton.setPosition(77.f, 63.f);
    prevButton.setFillColor(sf::Color(255, 255, 0, 80));    // hơi trong suốt thôi
    prevButton.setOutlineColor(sf::Color(255, 255, 0, 255)); // viền vàng đậm
    prevButton.setOutlineThickness(3.f);

    nextButton.setRadius(35.f);
    nextButton.setOrigin(35.f, 35.f);
    nextButton.setPosition(713.f, 58.f);
    nextButton.setFillColor(sf::Color(255, 255, 0, 80));
    nextButton.setOutlineColor(sf::Color(255, 255, 0, 255));
    nextButton.setOutlineThickness(3.f);
}

bool Guide::loadResources() {
    // Dọn sạch cũ
    pageTextures.clear();
    pageSprites.clear();
    totalPages = 0;

    DynamicArray<std::string> slides;
    slides.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide1.5.png");
    slides.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide2.11.png");
    slides.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide3.1.png");
    slides.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide4.1.png");
    slides.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide5.1.png");
    slides.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide6.1.png");

    for (int i = 0; i < slides.getSize(); ++i) {
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(slides[i])) {
            std::cerr << " khong load duoc anh: " << slides[i] << std::endl;
            delete texture;
            continue;
        }

        std::cout << "da load anh " << slides[i] << std::endl;
        pageTextures.push_back(texture);

        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setPosition(0.f, 0.f); 
        pageSprites.push_back(sprite);
    }

    totalPages = pageSprites.getSize();

    if (totalPages == 0) {
        std::cerr << "khong co slide nao load duoc \n";
        return false;
    }

    std::cout << "Tong so slide: " << totalPages << std::endl;
    return true;
}

void Guide::reset() {
    currentPage = 0;
}

bool Guide::isMouseOverButton(const sf::CircleShape& button, sf::Vector2i mousePos) {
    sf::Vector2f pos = button.getPosition();
    float dx = mousePos.x - pos.x;
    float dy = mousePos.y - pos.y;
    return (dx * dx + dy * dy <= button.getRadius() * button.getRadius());
}

void Guide::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        // Sử dụng tọa độ đã được scale từ event
        sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

        if (isMouseOverButton(prevButton, mousePos)) {
            if (currentPage == 0) {
                backToMenu = true;
                std::cout << "Guide: Quay lai menu\n";
            }
            else {
                currentPage--;
            }
        }

        if (isMouseOverButton(nextButton, mousePos) && currentPage < totalPages - 1) {
            currentPage++;
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);

        // === HOVER NÚT TRÁI ===
        if (isMouseOverButton(prevButton, mousePos)) {
            if (currentPage == 0) {
                prevButton.setOutlineColor(sf::Color(255, 120, 120, 255));
                prevButton.setFillColor(sf::Color(255, 0, 0, 160));
            }
            else {
                prevButton.setOutlineColor(sf::Color(255, 255, 0, 255));
            }
        }
        else {
            if (currentPage == 0) {
                prevButton.setOutlineColor(sf::Color(255, 255, 0, 80));
                prevButton.setFillColor(sf::Color(255, 255, 0, 80));
            }
            else {
                prevButton.setOutlineColor(sf::Color(255, 255, 0, 80));
            }
        }

        // Hover nút PHẢI
        if (isMouseOverButton(nextButton, mousePos)) {
            nextButton.setOutlineColor(sf::Color(255, 255, 0, 255));
        }
        else {
            nextButton.setOutlineColor(sf::Color(255, 255, 0, 0));
        }
    }
}

void Guide::update(float deltaTime) {}

void Guide::draw(sf::RenderWindow& window) {
    if (totalPages == 0) return;

    window.draw(pageSprites[currentPage]);

    window.draw(prevButton);
    if (currentPage < totalPages - 1)
        window.draw(nextButton);
}
