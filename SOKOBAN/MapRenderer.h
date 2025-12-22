#pragma once
#include <SFML/Graphics.hpp>
#include "BanDo.h"

class MapRenderer {
public:
    MapRenderer() = default;
    void ve(sf::RenderWindow& cuaSo, const BanDo* map);
};