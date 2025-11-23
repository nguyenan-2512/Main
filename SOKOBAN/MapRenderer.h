#pragma once
#include <SFML/Graphics.hpp>
#include "BanDo.h"

// Class chỉ chịu trách nhiệm VẼ bản đồ
class MapRenderer {
public:
    MapRenderer() = default;

    // Vẽ toàn bộ map theo đúng layer
    void ve(sf::RenderWindow& cuaSo, const BanDo* map);
};