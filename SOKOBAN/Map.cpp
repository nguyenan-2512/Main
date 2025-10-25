#include "Map.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Map::Map(const std::string& filename, int tileSize)
    : tileSize(tileSize), player(nullptr), isGameOver(false) {

    // Load textures (giữ nguyên)
    if (!wallTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\da1.png")) {
        std::cerr << "Failed to load wall texture!" << std::endl;
    }
    if (!playerSpriteSheet.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\playersheet2.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
    }
    if (!floorTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\co.png")) {
        std::cerr << "Failed to load floor texture!" << std::endl;
    }
    if (!boxTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thunggo.png")) {
        std::cerr << "Failed to load box texture!" << std::endl;
    }
    if (!ironBoxTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thungsat.png")) {
        std::cerr << "Failed to load iron box texture!" << std::endl;
        ironBoxTexture = boxTexture;
    }
    if (!waterTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nuoc222.png")) {
        std::cerr << "Failed to load water texture!" << std::endl;
    }
    if (!bridgeTTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\caudoc.png")) {
        std::cerr << "Failed to load caudoc texture!" << std::endl;
    }
    if (!sandTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\cat.png")) {
        std::cerr << "Failed to load cat texture!" << std::endl;
    }
    if (!trapActiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load bay texture!" << std::endl;
    }
    if (!trapInactiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\huynutbam.png")) {
        std::cerr << "Failed to load ko bay texture!" << std::endl;
    }
    if (!buttonUnpressedTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\konutbam1.png")) {
        std::cerr << "Failed to load khong nut bam texture!" << std::endl;
    }
    if (!buttonPressedTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nutbam1.png")) {
        std::cerr << "Failed to load nut bam texture!" << std::endl;
    }
    if (!boxOnGoalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\godung.png")) {
        std::cerr << "Failed to load box on goal texture!" << std::endl;
        boxOnGoalTexture = boxTexture;
    }
    if (!goalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\vitridat.png")) {
        std::cerr << "Failed to load goal texture!" << std::endl;
    }
    if (!obstacleTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load obstacle texture!" << std::endl;
    }
    if (!teleportActiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_active.png")) {
        std::cerr << "Failed to load teleport active texture!" << std::endl;
    }

    // Đọc file map
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file map: " << filename << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];

            if (c == '#') {
                Wall wall(x, y, tileSize);
                wall.setTexture(wallTexture);
                walls.push_back(wall);
            }
            else if (c == '=') {
                BridgeT bridge(x, y, tileSize);
                bridge.setTexture(bridgeTTexture);
                bridgeTs.push_back(bridge);
            }
            else if (c == '?') {
                Sand sand(x, y, tileSize);
                sand.setTexture(sandTexture);
                sands.push_back(sand);
            }
            else if (c == '~') {
                Water water(x, y, tileSize);
                water.setTexture(waterTexture);
                waters.push_back(water);
            }
            else if (c == '@') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                player = new Player(x, y, tileSize);
                player->initAnimation(playerSpriteSheet, 32, 32, 4);
            }
            else if (c == '$') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Box box(x, y, tileSize);
                box.setNormalTexture(boxTexture);
                box.setGoalTexture(boxOnGoalTexture);
                boxes.push_back(box);
            }
            else if (c == 'I') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                IronBox ironBox(x, y, tileSize);
                ironBox.setIronTexture(ironBoxTexture);
                ironBoxes.push_back(ironBox);
            }
            else if (c == 'X' || c == 'x') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Goal goal(x, y, tileSize);
                goal.setTexture(goalTexture);
                goals.push_back(goal);
            }
            else if (c == 'O' || c == 'o') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Obstacle obstacle(x, y, tileSize);
                obstacle.setTexture(obstacleTexture);
                obstacles.push_back(obstacle);
            }
            else if (c == '+') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Goal goal(x, y, tileSize);
                goal.setTexture(goalTexture);
                goals.push_back(goal);
                player = new Player(x, y, tileSize);
                player->initAnimation(playerSpriteSheet, 32, 32, 4);
            }
            else if (c == '*') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Goal goal(x, y, tileSize);
                goal.setTexture(goalTexture);
                goals.push_back(goal);
                Box box(x, y, tileSize);
                box.setNormalTexture(boxTexture);
                box.setGoalTexture(boxOnGoalTexture);
                box.setOnGoal(true);
                boxes.push_back(box);
            }
            else if (c == '.' || c == ' ') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
            }
            else if (c == 'T') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Trap trap(x, y, tileSize);
                trap.setActiveTexture(trapActiveTexture);
                trap.setInactiveTexture(trapInactiveTexture);
                traps.push_back(trap);
            }
            else if (c == 'B') {
                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);
                Button button(x, y, tileSize);
                button.setUnpressedTexture(buttonUnpressedTexture);
                button.setPressedTexture(buttonPressedTexture);
                buttons.push_back(button);
            }
            else if (isdigit(c)) {
                int id = c - '0';

                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);

                Teleport teleport(x, y, tileSize, id);
                teleport.setTexture(teleportActiveTexture);
                teleports.push_back(teleport);

                teleportNetwork.addTeleport(Point(x, y), id);

                std::cout << ">>Teleport added at (" << x << "," << y
                    << ") with ID=" << id << std::endl;
            }
        }
        y++;
    }
    file.close();

    // Liên kết button với trap
    int numButtons = buttons.getSize();
    int numTraps = traps.getSize();

    if (numButtons > 0 && numTraps > 0) {
        int trapsPerButton = numTraps / numButtons;
        int remainder = numTraps % numButtons;

        int trapIndex = 0;
        for (int i = 0; i < numButtons; i++) {
            int trapsForThisButton = trapsPerButton + (i < remainder ? 1 : 0);

            for (int j = 0; j < trapsForThisButton && trapIndex < numTraps; j++) {
                buttons[i].addLinkedTrap(traps[trapIndex].getX(), traps[trapIndex].getY());
                trapIndex++;
            }

            std::cout << "Button " << (i + 1) << " dieu khien " << trapsForThisButton << " trap" << std::endl;
        }
    }

    updateBoxStates();
    checkButtonStates();
}

Map::~Map() {
    delete player;
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < floors.getSize(); i++) floors[i].draw(window);
    for (int i = 0; i < waters.getSize(); i++) waters[i].draw(window);
    for (int i = 0; i < sands.getSize(); i++) sands[i].draw(window);
    for (int i = 0; i < bridgeTs.getSize(); i++) bridgeTs[i].draw(window);
    for (int i = 0; i < goals.getSize(); i++) goals[i].draw(window);
    for (int i = 0; i < teleports.getSize(); i++) teleports[i].draw(window);
    for (int i = 0; i < buttons.getSize(); i++) buttons[i].draw(window);
    for (int i = 0; i < traps.getSize(); i++) traps[i].draw(window);
    for (int i = 0; i < obstacles.getSize(); i++) obstacles[i].draw(window);
    for (int i = 0; i < walls.getSize(); i++) walls[i].draw(window);
    for (int i = 0; i < boxes.getSize(); i++) boxes[i].draw(window);
    for (int i = 0; i < ironBoxes.getSize(); i++) ironBoxes[i].draw(window);

    if (player) player->draw(window);
}

Player* Map::getPlayer() {
    return player;
}

bool Map::isTrap(int x, int y) const {
    for (int i = 0; i < traps.getSize(); i++) {
        if (traps[i].getX() == x && traps[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isButton(int x, int y) const {
    for (int i = 0; i < buttons.getSize(); i++) {
        if (buttons[i].getX() == x && buttons[i].getY() == y) {
            return true;
        }
    }
    return false;
}

Trap* Map::getTrapAt(int x, int y) {
    for (int i = 0; i < traps.getSize(); i++) {
        if (traps[i].getX() == x && traps[i].getY() == y) {
            return &traps[i];
        }
    }
    return nullptr;
}

Button* Map::getButtonAt(int x, int y) {
    for (int i = 0; i < buttons.getSize(); i++) {
        if (buttons[i].getX() == x && buttons[i].getY() == y) {
            return &buttons[i];
        }
    }
    return nullptr;
}

void Map::checkButtonStates() {
    for (int i = 0; i < buttons.getSize(); i++) {
        int bx = buttons[i].getX();
        int by = buttons[i].getY();

        bool hasBox = isBox(bx, by);
        bool hasIronBox = isIronBox(bx, by);
        bool isPressed = hasBox || hasIronBox;

        buttons[i].setPressed(isPressed);

        const auto& linkedTraps = buttons[i].getLinkedTraps();

        for (int j = 0; j < linkedTraps.getSize(); j++) {
            Trap* trap = getTrapAt(linkedTraps[j].first, linkedTraps[j].second);
            if (trap) {
                trap->setActive(!isPressed);
            }
        }
    }
}

bool Map::isWall(int x, int y) const {
    for (int i = 0; i < walls.getSize(); i++) {
        if (walls[i].getX() == x && walls[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isWater(int x, int y) const {
    for (int i = 0; i < waters.getSize(); i++) {
        if (waters[i].getX() == x && waters[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isSand(int x, int y) const {
    for (int i = 0; i < sands.getSize(); i++) {
        if (sands[i].getX() == x && sands[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isBox(int x, int y) const {
    for (int i = 0; i < boxes.getSize(); i++) {
        if (boxes[i].getX() == x && boxes[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isIronBox(int x, int y) const {
    for (int i = 0; i < ironBoxes.getSize(); i++) {
        if (ironBoxes[i].getX() == x && ironBoxes[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isObstacle(int x, int y) const {
    for (int i = 0; i < obstacles.getSize(); i++) {
        if (obstacles[i].getX() == x && obstacles[i].getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isGoal(int x, int y) const {
    for (int i = 0; i < goals.getSize(); i++) {
        if (goals[i].getX() == x && goals[i].getY() == y) {
            return true;
        }
    }
    return false;
}

Box* Map::getBoxAt(int x, int y) {
    for (int i = 0; i < boxes.getSize(); i++) {
        if (boxes[i].getX() == x && boxes[i].getY() == y) {
            return &boxes[i];
        }
    }
    return nullptr;
}

IronBox* Map::getIronBoxAt(int x, int y) {
    for (int i = 0; i < ironBoxes.getSize(); i++) {
        if (ironBoxes[i].getX() == x && ironBoxes[i].getY() == y) {
            return &ironBoxes[i];
        }
    }
    return nullptr;
}

bool Map::isValidMove(int x, int y) {
    if (isWall(x, y) || isObstacle(x, y) || isWater(x, y)) {
        return false;
    }
    return true;
}

bool Map::moveBox(Box* box, int dx, int dy) {
    int newX = box->getX() + dx;
    int newY = box->getY() + dy;

    Trap* trap = getTrapAt(newX, newY);
    if (trap && trap->getIsActive()) {
        return false;
    }

    if (!isWall(newX, newY) && !isObstacle(newX, newY) &&
        !isBox(newX, newY) && !isIronBox(newX, newY) && !isWater(newX, newY)) {
        box->setPosition(newX, newY);
        updateBoxStates();
        checkButtonStates();
        return true;
    }
    return false;
}

bool Map::moveIronBox(IronBox* ironBox, int dx, int dy) {
    int newX = ironBox->getX() + dx;
    int newY = ironBox->getY() + dy;

    Trap* trap = getTrapAt(newX, newY);
    if (trap && trap->getIsActive()) {
        return false;
    }

    if (!isWall(newX, newY) && !isObstacle(newX, newY) &&
        !isBox(newX, newY) && !isIronBox(newX, newY) && !isWater(newX, newY)) {
        ironBox->setPosition(newX, newY);
        checkButtonStates();
        return true;
    }
    return false;
}

bool Map::tryMovePlayer(int dx, int dy) {
    if (!player || isGameOver) return false;

    int newX = player->getX() + dx;
    int newY = player->getY() + dy;

    if (isWall(newX, newY) || isObstacle(newX, newY) || isWater(newX, newY)) {
        return false;
    }

    Trap* trap = getTrapAt(newX, newY);
    if (trap && trap->getIsActive()) {
        std::cout << "Ban da bi bay! Game Over!" << std::endl;
        isGameOver = true;
        return false;
    }

    Box* box = getBoxAt(newX, newY);
    if (box) {
        if (!moveBox(box, dx, dy)) {
            return false;
        }
    }