#include "Map.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

Map::Map(const std::string& filename, int tileSize)
    : tileSize(tileSize), player(nullptr), isGameOver(false), m_isAutoSolving(false), LoiGiaiHienTaiStep(0) {

    // Load tất cả textures
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
        std::cerr << "Failed to load iron box texture! Using normal box texture." << std::endl;
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

    if (!textureBayKichHoat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load bay texture!" << std::endl;
    }
    if (!textureBayKoKichHoat.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\huynutbam.png")) {
        std::cerr << "Failed to load ko bay texture!" << std::endl;
    }

    if (!textureNutChuaNhan.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\konutbam1.png")) {
        std::cerr << "Failed to load khong nut bam texture!" << std::endl;
    }
    if (!textureNutDaNhan.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nutbam1.png")) {
        std::cerr << "Failed to load nut bam texture!" << std::endl;
    }

    if (!boxOnGoalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\godung.png")) {
        std::cerr << "Failed to load box on goal texture! Using normal box texture." << std::endl;
        boxOnGoalTexture = boxTexture;
    }

    if (!goalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\vitridat.png")) {
        std::cerr << "Failed to load goal texture!" << std::endl;
    }

    if (!obstacleTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load obstacle texture!" << std::endl;
    }
    if (!textureDichChuyen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_active.jpg")) {
        std::cerr << "Failed to load teleport active texture!" << std::endl;
    }

    // Đọc file map
    std::ifstream file(filename);
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];

            if (c == '#') {
                walls.emplace_back(x, y, tileSize);
                walls.back().setTexture(wallTexture);
            }
            else if (c == '=') {
                bridgeTs.emplace_back(x, y, tileSize);
                bridgeTs.back().setTexture(bridgeTTexture);
            }
            else if (c == '?') {
                sands.emplace_back(x, y, tileSize);
                sands.back().setTexture(sandTexture);
            }
            else if (c == '~') {
                waters.emplace_back(x, y, tileSize);
                waters.back().setTexture(waterTexture);
            }
            else if (c == '@') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                player = new Player(x, y, tileSize);
                player->initAnimation(playerSpriteSheet, 32, 32, 4);
            }
            else if (c == '$') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setNormalTexture(boxTexture);
                boxes.back().setGoalTexture(boxOnGoalTexture);
            }
            else if (c == 'I') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                ironBoxes.emplace_back(x, y, tileSize);
                ironBoxes.back().setIronTexture(ironBoxTexture);
            }
            else if (c == 'X' || c == 'x') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
            }
            else if (c == 'O' || c == 'o') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                obstacles.emplace_back(x, y, tileSize);
                obstacles.back().setTexture(obstacleTexture);
            }
            else if (c == '+') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
                player = new Player(x, y, tileSize);
                player->initAnimation(playerSpriteSheet, 32, 32, 4);
            }
            else if (c == '*') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setNormalTexture(boxTexture);
                boxes.back().setGoalTexture(boxOnGoalTexture);
                boxes.back().setOnGoal(true);
            }
            else if (c == '.' || c == ' ') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
            }
            else if (c == 'T') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                traps.emplace_back(x, y, tileSize);
                traps.back().setActiveTexture(textureBayKichHoat);
                traps.back().setInactiveTexture(textureBayKoKichHoat);
            }
            else if (c == 'B') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                buttons.emplace_back(x, y, tileSize);
                buttons.back().setUnpressedTexture(textureNutChuaNhan);
                buttons.back().setPressedTexture(textureNutDaNhan);
            }
            else if (isdigit(c)) {
                int id = c - '0';

                Floor floor(x, y, tileSize);
                floor.setTexture(floorTexture);
                floors.push_back(floor);

                Teleport teleport(x, y, tileSize, id);
                teleport.setTexture(textureDichChuyen);
                teleports.push_back(teleport);

                teleportNetwork.addTeleport(Point(x, y), id);
            }
        }
        y++;
    }
    file.close();

    int numButtons = buttons.size();
    int numTraps = traps.size();

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
        }
    }
    CapNhatThung();
    KiemTraNut();
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
    for (const Trap& trap : traps) {
        if (trap.getX() == x && trap.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isButton(int x, int y) const {
    for (const Button& button : buttons) {
        if (button.getX() == x && button.getY() == y) {
            return true;
        }
    }
    return false;
}

Trap* Map::TimBayTai(int x, int y) {
    for (auto& trap : traps) {
        if (trap.getX() == x && trap.getY() == y) {
            return &trap;
        }
    }
    return nullptr;
}

Button* Map::TimNutBamTai(int x, int y) {
    for (auto& button : buttons) {
        if (button.getX() == x && button.getY() == y) {
            return &button;
        }
    }
    return nullptr;
}

void Map::KiemTraNut() {
    for (auto& button : buttons) {
        int bx = button.getX();
        int by = button.getY();

        bool hasBox = isBox(bx, by);
        bool hasIronBox = isIronBox(bx, by);
        bool isPressed = hasBox || hasIronBox;

        button.setPressed(isPressed);

        const auto& linkedTraps = button.getLinkedTraps();

        for (const auto& trapPos : linkedTraps) {
            Trap* trap = TimBayTai(trapPos.first, trapPos.second);
            if (trap) {
                trap->setActive(!isPressed);
            }
        }
    }
}

bool Map::isTeleport(int x, int y) const {
    for (const Teleport& tp : teleports) {
        if (tp.getX() == x && tp.getY() == y) {
            return true;
        }
    }
    return false;
}

Teleport* Map::TimDichChuyenTai(int x, int y) {
    for (auto& teleport : teleports) {
        if (teleport.getX() == x && teleport.getY() == y) {
            return &teleport;
        }
    }
    return nullptr;
}

bool Map::ThuDichChuyen() {
    if (!player || isGameOver) return false;

    int px = player->getX();
    int py = player->getY();

    if (!isTeleport(px, py)) {
        std::cout << "Khong co cong teleport tai vi tri nay!" << std::endl;
        return false;
    }

    Point currentPos(px, py);
    Point destination = teleportNetwork.getDestination(currentPos);

    if (destination == currentPos) {
        std::cout << "Khong the teleport!" << std::endl;
        return false;
    }

    int destX = destination.getX();
    int destY = destination.getY();

    if (isWall(destX, destY) || isObstacle(destX, destY) ||
        isBox(destX, destY) || isIronBox(destX, destY) || isWater(destX, destY)) {
        std::cout << "Diem den bi chan, khong the teleport!" << std::endl;
        return false;
    }

    Trap* trap = TimBayTai(destX, destY);
    if (trap && trap->getIsActive()) {
        std::cout << "Ban da teleport vao bay! Game Over!" << std::endl;
        isGameOver = true;
        return false;
    }

    LuuTrangThai();

    player->setPosition(destX, destY, 0, 0);

    std::cout << "Teleport thanh cong tu (" << px << "," << py
        << ") den (" << destX << "," << destY << ")!" << std::endl;

    return true;
}

bool Map::isWall(int x, int y) const {
    for (const Wall& wall : walls) {
        if (wall.getX() == x && wall.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isWater(int x, int y) const {
    for (const Water& water : waters) {
        if (water.getX() == x && water.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isSand(int x, int y) const {
    for (const Sand& sand : sands) {
        if (sand.getX() == x && sand.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isBox(int x, int y) const {
    for (const Box& box : boxes) {
        if (box.getX() == x && box.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isIronBox(int x, int y) const {
    for (const IronBox& ironBox : ironBoxes) {
        if (ironBox.getX() == x && ironBox.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isObstacle(int x, int y) const {
    for (const Obstacle& obstacle : obstacles) {
        if (obstacle.getX() == x && obstacle.getY() == y) {
            return true;
        }
    }
    return false;
}

bool Map::isGoal(int x, int y) const {
    for (const Goal& goal : goals) {
        if (goal.getX() == x && goal.getY() == y) {
            return true;
        }
    }
    return false;
}

Box* Map::TimThungGoTai(int x, int y) {
    for (auto& box : boxes) {
        if (box.getX() == x && box.getY() == y) {
            return &box;
        }
    }
    return nullptr;
}

IronBox* Map::TimThungSatTai(int x, int y) {
    for (auto& ironBox : ironBoxes) {
        if (ironBox.getX() == x && ironBox.getY() == y) {
            return &ironBox;
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

bool Map::DiChuyenThungGo(Box* box, int dx, int dy) {
    int newX = box->getX() + dx;
    int newY = box->getY() + dy;

    Trap* trap = TimBayTai(newX, newY);
    if (trap && trap->getIsActive()) {
        return false;
    }

    if (!isWall(newX, newY) && !isObstacle(newX, newY) &&
        !isBox(newX, newY) && !isIronBox(newX, newY) && !isWater(newX, newY)) {
        box->setPosition(newX, newY);
        CapNhatThung();
        KiemTraNut();
        return true;
    }
    return false;
}

bool Map::DiChuyenThungSat(IronBox* ironBox, int dx, int dy) {
    int newX = ironBox->getX() + dx;
    int newY = ironBox->getY() + dy;

    Trap* trap = TimBayTai(newX, newY);
    if (trap && trap->getIsActive()) {
        return false;
    }

    if (!isWall(newX, newY) && !isObstacle(newX, newY) &&
        !isBox(newX, newY) && !isIronBox(newX, newY) && !isWater(newX, newY)) {
        ironBox->setPosition(newX, newY);
        KiemTraNut();
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

    Trap* trap = TimBayTai(newX, newY);
    if (trap && trap->getIsActive()) {
        isGameOver = true;
        return false;
    }

    Box* box = TimThungGoTai(newX, newY);
    if (box) {
        if (!DiChuyenThungGo(box, dx, dy)) {
            return false;
        }
    }

    IronBox* ironBox = TimThungSatTai(newX, newY);
    if (ironBox) {
        if (!DiChuyenThungSat(ironBox, dx, dy)) {
            return false;
        }
    }

    LuuTrangThai();
    player->setPosition(newX, newY, dx, dy);
    KiemTraNut();

    return true;
}

void Map::CapNhatThung() {
    for (auto& box : boxes) {
        bool onGoal = isGoal(box.getX(), box.getY());
        box.setOnGoal(onGoal);
    }
}

bool Map::checkWin() const {
    for (const auto& box : boxes) {
        bool onGoal = false;
        for (const auto& goal : goals) {
            if (box.getX() == goal.getX() && box.getY() == goal.getY()) {
                onGoal = true;
                break;
            }
        }
        if (!onGoal) return false;
    }
    return boxes.size() > 0 && boxes.size() == goals.size();
}

void Map::LuuTrangThai() {
    MoveState state = LayTrangThaiHienTai();
    LichSuDiChuyen.push(state);
}

MoveState Map::LayTrangThaiHienTai() const {
    Point playerPos = player->getPosition();
    DynamicArray<Point> boxPos;

    for (const auto& box : boxes) {
        boxPos.push_back(box.getPosition());
    }

    return MoveState(playerPos, boxPos);
}

void Map::PhucHoiTrangThai(const MoveState& state) {
    player->setPosition(state.playerPosition.getX(), state.playerPosition.getY(), 0, 0);

    for (size_t i = 0; i < boxes.size() && i < state.boxPositions.size(); i++) {
        boxes[i].setPosition(state.boxPositions[i].getX(), state.boxPositions[i].getY());
    }

    CapNhatThung();
}

void Map::LuiBuoc() {
    if (LichSuDiChuyen.empty()) {
        return;
    }

    MoveState previousState = LichSuDiChuyen.top();
    LichSuDiChuyen.pop();
    PhucHoiTrangThai(previousState);
}

int Map::LaySoBuoc() const {
    return (int)LichSuDiChuyen.size();
}

bool Map::NutBiNhanTrongBFS(const Point& buttonPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i] == buttonPos) return true;
    }
    for (int i = 0; i < ironBoxes.size(); i++) {
        if (ironBoxes[i] == buttonPos) return true;
    }
    return false;
}

bool Map::BayKichHoatTrongBFS(const Point& trapPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    // Tìm button điều khiển trap này
    for (int i = 0; i < buttons.size(); i++) {
        const auto& linkedTraps = buttons[i].getLinkedTraps();

        for (int j = 0; j < linkedTraps.size(); j++) {
            if (linkedTraps[j].first == trapPos.getX() &&
                linkedTraps[j].second == trapPos.getY()) {
                Point buttonPos(buttons[i].getX(), buttons[i].getY());
                bool buttonPressed = NutBiNhanTrongBFS(buttonPos, boxes, ironBoxes);
                return !buttonPressed;
            }
        }
    }
    return true;
}

bool Map::CoThungTai(const Point& pos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i] == pos) return true;
    }
    for (int i = 0; i < ironBoxes.size(); i++) {
        if (ironBoxes[i] == pos) return true;
    }
    return false;
}

bool Map::LaBuocDiHopLeBFS(const Point& pos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    int x = pos.getX();
    int y = pos.getY();

    if (isWall(x, y) || isWater(x, y) || isObstacle(x, y)) {
        return false;
    }
    if (isTrap(x, y)) {
        Point trapPos(x, y);
        if (BayKichHoatTrongBFS(trapPos, boxes, ironBoxes)) {
            return false; 
        }
    }
    if (CoThungTai(pos, boxes, ironBoxes)) {
        return false;
    }

    return true;
}

bool Map::isDeadlock(const Point& boxPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    int x = boxPos.getX();
    int y = boxPos.getY();

    if (isGoal(x, y)) {
        return false;
    }
    if (isButton(x, y)) {
        return false;
    }
    bool leftBlocked = isWall(x - 1, y) || isObstacle(x - 1, y);
    bool rightBlocked = isWall(x + 1, y) || isObstacle(x + 1, y);
    bool upBlocked = isWall(x, y - 1) || isObstacle(x, y - 1);
    bool downBlocked = isWall(x, y + 1) || isObstacle(x, y + 1);

    if ((leftBlocked && upBlocked) || (rightBlocked && upBlocked) ||
        (leftBlocked && downBlocked) || (rightBlocked && downBlocked)) {
        return true;
    }

    if (boxes.size() >= 4) {
        Point adjacent[3] = {
            Point(x + 1, y),      // Phải
            Point(x, y + 1),      // Dưới
            Point(x + 1, y + 1)   // Phải-Dưới
        };

        int adjacentBoxCount = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < boxes.size(); j++) {
                if (boxes[j] == adjacent[i]) {
                    adjacentBoxCount++;
                    break;
                }
            }
        }

        if (adjacentBoxCount == 3) {
            bool hasGoalIn2x2 = isGoal(x, y) ||
                isGoal(x + 1, y) ||
                isGoal(x, y + 1) ||
                isGoal(x + 1, y + 1);

            bool hasButtonIn2x2 = isButton(x, y) ||
                isButton(x + 1, y) ||
                isButton(x, y + 1) ||
                isButton(x + 1, y + 1);

            if (!hasGoalIn2x2 && !hasButtonIn2x2) {
                return true;
            }
        }
    }

    return false;
}

bool Map::isIronBoxDeadlock(const Point& ironBoxPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    int x = ironBoxPos.getX();
    int y = ironBoxPos.getY();

    if (isButton(x, y)) {
        return false;
    }

    if (isGoal(x, y)) {
        return true;
    }

    bool leftBlocked = isWall(x - 1, y) || isObstacle(x - 1, y);
    bool rightBlocked = isWall(x + 1, y) || isObstacle(x + 1, y);
    bool upBlocked = isWall(x, y - 1) || isObstacle(x, y - 1);
    bool downBlocked = isWall(x, y + 1) || isObstacle(x, y + 1);

    if ((leftBlocked && upBlocked) || (rightBlocked && upBlocked) ||
        (leftBlocked && downBlocked) || (rightBlocked && downBlocked)) {
        return true;
    }

    return false;
}

bool Map::ThuDichChuyenInBFS(Point& playerPos) const {
    if (!isTeleport(playerPos.getX(), playerPos.getY())) {
        return false;
    }

    Point destination = const_cast<Map*>(this)->teleportNetwork.getDestination(playerPos);

    if (destination == playerPos) {
        return false;
    }

    playerPos = destination;
    return true;
}

BFSState Map::TaoTrangThaiBFS() const {
    Point playerPos = player->getPosition();
    DynamicArray<Point> boxPos;
    DynamicArray<Point> ironPos;

    for (int i = 0; i < boxes.size(); i++) {
        boxPos.push_back(boxes[i].getPosition());
    }

    for (int i = 0; i < ironBoxes.size(); i++) {
        ironPos.push_back(ironBoxes[i].getPosition());
    }

    return BFSState(playerPos, boxPos, ironPos, 0);
}

bool Map::TimLoiGiaiBFS(int maxDepth) {
    LoiGiaiHienTai.clear();
    LoiGiaiHienTaiStep = 0;

    BFSState initialState = TaoTrangThaiBFS();

    Queue<BFSState> queue;
    queue.push(initialState);

    HashTable<BFSState, bool, BFSStateHash> visited(50000);
    visited.insert(initialState, true);

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    int statesExplored = 0; 
    const int MAX_STATES = 1000000; 


    while (!queue.empty() && statesExplored < MAX_STATES) { 

        BFSState current = queue.front();
        queue.pop();
        statesExplored++; 
        int boxesOnGoals = 0;
        for (int i = 0; i < current.boxPositions.size(); i++) {
            if (isGoal(current.boxPositions[i].getX(), current.boxPositions[i].getY())) {
                boxesOnGoals++;
            }
        }

        if (boxesOnGoals == current.boxPositions.size() &&
            current.boxPositions.size() == goals.size()) {

            LoiGiaiHienTai = current.path;
            return true;
        }

        if (current.depth >= maxDepth) {
            continue;
        }

        if (isTeleport(current.playerPos.getX(), current.playerPos.getY())) {
            Point newPlayerPos = current.playerPos;
            if (ThuDichChuyenInBFS(newPlayerPos)) {
                if (LaBuocDiHopLeBFS(newPlayerPos, current.boxPositions, current.ironBoxPositions)) {
                    BFSState newState(newPlayerPos, current.boxPositions,
                        current.ironBoxPositions, current.depth + 1);
                    newState.path = current.path;
                    newState.path.push_back(4); 

                    if (!visited.contains(newState)) {
                        visited.insert(newState, true);
                        queue.push(newState);
                    }
                }
            }
        }
        for (int dir = 0; dir < 4; dir++) {
            int newPlayerX = current.playerPos.getX() + dx[dir];
            int newPlayerY = current.playerPos.getY() + dy[dir];
            Point newPlayerPos(newPlayerX, newPlayerY);

            DynamicArray<Point> newBoxes = current.boxPositions;
            DynamicArray<Point> newIronBoxes = current.ironBoxPositions;
            int boxIndex = -1;
            for (int i = 0; i < newBoxes.size(); i++) {
                if (newBoxes[i] == newPlayerPos) {
                    boxIndex = i;
                    break;
                }
            }
            int ironBoxIndex = -1;
            for (int i = 0; i < newIronBoxes.size(); i++) {
                if (newIronBoxes[i] == newPlayerPos) {
                    ironBoxIndex = i;
                    break;
                }
            }

            if (boxIndex != -1) {
                int newBoxX = newPlayerPos.getX() + dx[dir];
                int newBoxY = newPlayerPos.getY() + dy[dir];
                Point newBoxPos(newBoxX, newBoxY);

                if (!LaBuocDiHopLeBFS(newBoxPos, newBoxes, newIronBoxes)) {
                    continue;
                }
                newBoxes[boxIndex] = newBoxPos;
                if (isDeadlock(newBoxPos, newBoxes, newIronBoxes)) {
                    continue;
                }
            }
            else if (ironBoxIndex != -1) {
                int newIronX = newPlayerPos.getX() + dx[dir];
                int newIronY = newPlayerPos.getY() + dy[dir];
                Point newIronPos(newIronX, newIronY);

                if (!LaBuocDiHopLeBFS(newIronPos, newBoxes, newIronBoxes)) {
                    continue;
                }
                if (isIronBoxDeadlock(newIronPos, newBoxes, newIronBoxes)) {
                    continue;
                }
                newIronBoxes[ironBoxIndex] = newIronPos;
            }
            else {
                if (!LaBuocDiHopLeBFS(newPlayerPos, newBoxes, newIronBoxes)) {
                    continue;
                }
            }

            BFSState newState(newPlayerPos, newBoxes, newIronBoxes, current.depth + 1);
            newState.path = current.path;
            newState.path.push_back(dir);

            if (!visited.contains(newState)) {
                visited.insert(newState, true);
                queue.push(newState);
            }
        }
    }

    return false;
}

bool Map::ThucHIenBuocGiai() {
    if (LoiGiaiHienTaiStep >= LoiGiaiHienTai.size()) {
        DungTuDongGiai();
        return false;
    }
    int action = LoiGiaiHienTai[LoiGiaiHienTaiStep];
    if (action == 4) {
        bool teleported = ThuDichChuyen();
        if (teleported) {
            LoiGiaiHienTaiStep++;
            return true;
        }
        return false;
    }
    else {
        int dx[] = { 0, 0, -1, 1 };
        int dy[] = { -1, 1, 0, 0 };

        bool moved = tryMovePlayer(dx[action], dy[action]);

        if (moved) {
            LoiGiaiHienTaiStep++;
        }

        return moved;
    }
}

void Map::BatDauTuDongGiai() {
    m_isAutoSolving = true;
    LoiGiaiHienTaiStep = 0;
}

void Map::DungTuDongGiai() {
    m_isAutoSolving = false;
}