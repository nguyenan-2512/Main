#include "Map.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

// Debug mode
#define DEBUG_BFS 1  // Set = 0 để tắt debug

#if DEBUG_BFS
#define DEBUG_PRINT(x) std::cout << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

Map::Map(const std::string& filename, int tileSize)
    : tileSize(tileSize), player(nullptr), isGameOver(false), m_isAutoSolving(false), currentSolutionStep(0) {

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
        std::cerr << "Failed to load box on goal texture! Using normal box texture." << std::endl;
        boxOnGoalTexture = boxTexture;
    }

    if (!goalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\vitridat.png")) {
        std::cerr << "Failed to load goal texture!" << std::endl;
    }

    if (!obstacleTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load obstacle texture!" << std::endl;
    }
    if (!teleportActiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_active.jpg")) {
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
                traps.back().setActiveTexture(trapActiveTexture);
                traps.back().setInactiveTexture(trapInactiveTexture);
            }
            else if (c == 'B') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                buttons.emplace_back(x, y, tileSize);
                buttons.back().setUnpressedTexture(buttonUnpressedTexture);
                buttons.back().setPressedTexture(buttonPressedTexture);
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

Trap* Map::getTrapAt(int x, int y) {
    for (auto& trap : traps) {
        if (trap.getX() == x && trap.getY() == y) {
            return &trap;
        }
    }
    return nullptr;
}

Button* Map::getButtonAt(int x, int y) {
    for (auto& button : buttons) {
        if (button.getX() == x && button.getY() == y) {
            return &button;
        }
    }
    return nullptr;
}

void Map::checkButtonStates() {
    for (auto& button : buttons) {
        int bx = button.getX();
        int by = button.getY();

        bool hasBox = isBox(bx, by);
        bool hasIronBox = isIronBox(bx, by);
        bool isPressed = hasBox || hasIronBox;

        button.setPressed(isPressed);

        const auto& linkedTraps = button.getLinkedTraps();

        for (const auto& trapPos : linkedTraps) {
            Trap* trap = getTrapAt(trapPos.first, trapPos.second);
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

Teleport* Map::getTeleportAt(int x, int y) {
    for (auto& teleport : teleports) {
        if (teleport.getX() == x && teleport.getY() == y) {
            return &teleport;
        }
    }
    return nullptr;
}

bool Map::tryTeleport() {
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

    Trap* trap = getTrapAt(destX, destY);
    if (trap && trap->getIsActive()) {
        std::cout << "Ban da teleport vao bay! Game Over!" << std::endl;
        isGameOver = true;
        return false;
    }

    saveState();

    player->setPosition(destX, destY, 0, 0);

    std::cout << "Teleport thanh cong tu (" << px << "," << py
        << ") den (" << destX << "," << destY << ")!" << std::endl;

    return true;
}

bool Map::isWall(int x, int y) const {
    return std::any_of(walls.begin(), walls.end(),
        [x, y](const Wall& wall) {
            return wall.getX() == x && wall.getY() == y;
        });
}

bool Map::isWater(int x, int y) const {
    return std::any_of(waters.begin(), waters.end(),
        [x, y](const Water& water) {
            return water.getX() == x && water.getY() == y;
        });
}

bool Map::isSand(int x, int y) const {
    return std::any_of(sands.begin(), sands.end(),
        [x, y](const Sand& sand) {
            return sand.getX() == x && sand.getY() == y;
        });
}

bool Map::isBox(int x, int y) const {
    return std::any_of(boxes.begin(), boxes.end(),
        [x, y](const Box& box) {
            return box.getX() == x && box.getY() == y;
        });
}

bool Map::isIronBox(int x, int y) const {
    return std::any_of(ironBoxes.begin(), ironBoxes.end(),
        [x, y](const IronBox& ironBox) {
            return ironBox.getX() == x && ironBox.getY() == y;
        });
}

bool Map::isObstacle(int x, int y) const {
    return std::any_of(obstacles.begin(), obstacles.end(),
        [x, y](const Obstacle& obstacle) {
            return obstacle.getX() == x && obstacle.getY() == y;
        });
}

bool Map::isGoal(int x, int y) const {
    return std::any_of(goals.begin(), goals.end(),
        [x, y](const Goal& goal) {
            return goal.getX() == x && goal.getY() == y;
        });
}

Box* Map::getBoxAt(int x, int y) {
    for (auto& box : boxes) {
        if (box.getX() == x && box.getY() == y) {
            return &box;
        }
    }
    return nullptr;
}

IronBox* Map::getIronBoxAt(int x, int y) {
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

    IronBox* ironBox = getIronBoxAt(newX, newY);
    if (ironBox) {
        if (!moveIronBox(ironBox, dx, dy)) {
            return false;
        }
    }

    saveState();
    player->setPosition(newX, newY, dx, dy);
    checkButtonStates();

    return true;
}

void Map::updateBoxStates() {
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

void Map::saveState() {
    MoveState state = getCurrentState();
    moveHistory.push(state);
}

MoveState Map::getCurrentState() const {
    Point playerPos = player->getPosition();
    DynamicArray<Point> boxPos;

    for (const auto& box : boxes) {
        boxPos.push_back(box.getPosition());
    }

    return MoveState(playerPos, boxPos);
}

void Map::restoreState(const MoveState& state) {
    player->setPosition(state.playerPosition.getX(), state.playerPosition.getY(), 0, 0);

    for (size_t i = 0; i < boxes.size() && i < state.boxPositions.size(); i++) {
        boxes[i].setPosition(state.boxPositions[i].getX(), state.boxPositions[i].getY());
    }

    updateBoxStates();
}

void Map::undo() {
    if (moveHistory.empty()) {
        std::cout << "Khong co nuoc di nao de undo!" << std::endl;
        return;
    }

    MoveState previousState = moveHistory.top();
    moveHistory.pop();

    restoreState(previousState);

    std::cout << "Da undo! Con lai " << moveHistory.size() << " nuoc di trong lich su." << std::endl;
}

int Map::getMoveCount() const {
    return (int)moveHistory.size();
}

// ==================== ENHANCED BFS SOLVER ====================

// Thay thế phần BFS trong Map.cpp bằng code này
// Các hàm helper cải tiến

bool Map::isButtonPressedInState(const Point& buttonPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    // Kiểm tra box thường
    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i] == buttonPos) return true;
    }
    // Kiểm tra iron box
    for (int i = 0; i < ironBoxes.size(); i++) {
        if (ironBoxes[i] == buttonPos) return true;
    }
    return false;
}

bool Map::isTrapActiveInState(const Point& trapPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    // Tìm button điều khiển trap này
    for (int i = 0; i < buttons.size(); i++) {
        const auto& linkedTraps = buttons[i].getLinkedTraps();

        for (int j = 0; j < linkedTraps.size(); j++) {
            if (linkedTraps[j].first == trapPos.getX() &&
                linkedTraps[j].second == trapPos.getY()) {

                Point buttonPos(buttons[i].getX(), buttons[i].getY());
                bool buttonPressed = isButtonPressedInState(buttonPos, boxes, ironBoxes);

                // Trap active khi button KHÔNG được nhấn
                return !buttonPressed;
            }
        }
    }

    // Nếu không có button điều khiển, trap luôn active
    return true;
}

bool Map::hasBoxAt(const Point& pos,
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

bool Map::isValidBFSMove(const Point& pos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    int x = pos.getX();
    int y = pos.getY();

    // Kiểm tra tường, nước, obstacle
    if (isWall(x, y) || isWater(x, y) || isObstacle(x, y)) {
        return false;
    }

    // Kiểm tra trap
    if (isTrap(x, y)) {
        Point trapPos(x, y);
        if (isTrapActiveInState(trapPos, boxes, ironBoxes)) {
            return false; // Trap đang active, không thể đi vào
        }
    }

    // Kiểm tra box
    if (hasBoxAt(pos, boxes, ironBoxes)) {
        return false;
    }

    return true;
}

bool Map::isDeadlock(const Point& boxPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    int x = boxPos.getX();
    int y = boxPos.getY();

    // Box đã ở goal -> không phải deadlock
    if (isGoal(x, y)) {
        return false;
    }

    // Box ở button -> không phải deadlock (cần để vô hiệu hóa trap)
    if (isButton(x, y)) {
        return false;
    }

    // Kiểm tra góc
    bool leftBlocked = isWall(x - 1, y) || isObstacle(x - 1, y);
    bool rightBlocked = isWall(x + 1, y) || isObstacle(x + 1, y);
    bool upBlocked = isWall(x, y - 1) || isObstacle(x, y - 1);
    bool downBlocked = isWall(x, y + 1) || isObstacle(x, y + 1);

    // Deadlock tại góc
    if ((leftBlocked && upBlocked) || (rightBlocked && upBlocked) ||
        (leftBlocked && downBlocked) || (rightBlocked && downBlocked)) {
        return true;
    }

    // Kiểm tra deadlock 2x2 (4 boxes tạo thành hình vuông)
    if (boxes.size() >= 4) {
        // Kiểm tra 3 vị trí còn lại của hình vuông 2x2
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

        // Nếu có 3 boxes kề nhau tạo thành 2x2
        if (adjacentBoxCount == 3) {
            // Kiểm tra có goal nào trong vùng 2x2 không
            bool hasGoalIn2x2 = isGoal(x, y) ||
                isGoal(x + 1, y) ||
                isGoal(x, y + 1) ||
                isGoal(x + 1, y + 1);

            // Kiểm tra có button nào trong vùng 2x2 không
            bool hasButtonIn2x2 = isButton(x, y) ||
                isButton(x + 1, y) ||
                isButton(x, y + 1) ||
                isButton(x + 1, y + 1);

            // Nếu không có goal và không có button -> deadlock
            if (!hasGoalIn2x2 && !hasButtonIn2x2) {
                return true;
            }
        }
    }

    return false;
}

// Deadlock cho iron box - QUAN TRỌNG
bool Map::isIronBoxDeadlock(const Point& ironBoxPos,
    const DynamicArray<Point>& boxes,
    const DynamicArray<Point>& ironBoxes) const {
    int x = ironBoxPos.getX();
    int y = ironBoxPos.getY();

    // Iron box ở button -> OK (mục đích chính)
    if (isButton(x, y)) {
        return false;
    }

    // Iron box ở goal -> DEADLOCK (iron box không được đưa lên goal)
    if (isGoal(x, y)) {
        return true;
    }

    // Kiểm tra góc
    bool leftBlocked = isWall(x - 1, y) || isObstacle(x - 1, y);
    bool rightBlocked = isWall(x + 1, y) || isObstacle(x + 1, y);
    bool upBlocked = isWall(x, y - 1) || isObstacle(x, y - 1);
    bool downBlocked = isWall(x, y + 1) || isObstacle(x, y + 1);

    // Deadlock tại góc và không phải button
    if ((leftBlocked && upBlocked) || (rightBlocked && upBlocked) ||
        (leftBlocked && downBlocked) || (rightBlocked && downBlocked)) {
        return true;
    }

    return false;
}

bool Map::tryTeleportInBFS(Point& playerPos) const {
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

BFSState Map::createCurrentBFSState() const {
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

// Đánh giá state - ưu tiên những state tốt hơn
int Map::evaluateState(const BFSState& state) const {
    int score = 0;

    // Tính số box đã ở goal
    for (int i = 0; i < state.boxPositions.size(); i++) {
        if (isGoal(state.boxPositions[i].getX(), state.boxPositions[i].getY())) {
            score += 100;
        }
    }

    // Tính số button đã được nhấn
    for (int i = 0; i < buttons.size(); i++) {
        Point buttonPos(buttons[i].getX(), buttons[i].getY());
        if (isButtonPressedInState(buttonPos, state.boxPositions, state.ironBoxPositions)) {
            score += 50; // Button được nhấn -> trap vô hiệu
        }
    }

    // Tính khoảng cách từ box đến goal gần nhất
    for (int i = 0; i < state.boxPositions.size(); i++) {
        int minDist = 9999;
        for (int j = 0; j < goals.size(); j++) {
            int dist = abs(state.boxPositions[i].getX() - goals[j].getX()) +
                abs(state.boxPositions[i].getY() - goals[j].getY());
            if (dist < minDist) {
                minDist = dist;
            }
        }
        score -= minDist; // Càng gần goal càng tốt
    }

    return score;
}

bool Map::solveBFS(int maxDepth) {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║   BFS SOLVER v3.0 - Button-Trap Ready ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;

    currentSolution.clear();
    currentSolutionStep = 0;

    BFSState initialState = createCurrentBFSState();

    std::cout << "\n📍 INITIAL STATE:" << std::endl;
    std::cout << "   Player: (" << initialState.playerPos.getX()
        << "," << initialState.playerPos.getY() << ")" << std::endl;
    std::cout << "   Normal Boxes: " << initialState.boxPositions.size() << std::endl;
    for (int i = 0; i < initialState.boxPositions.size(); i++) {
        std::cout << "      Box " << (i + 1) << ": ("
            << initialState.boxPositions[i].getX() << ","
            << initialState.boxPositions[i].getY() << ")";
        if (isGoal(initialState.boxPositions[i].getX(),
            initialState.boxPositions[i].getY())) {
            std::cout << " ✓ ON GOAL";
        }
        std::cout << std::endl;
    }

    std::cout << "   Iron Boxes: " << initialState.ironBoxPositions.size() << std::endl;
    for (int i = 0; i < initialState.ironBoxPositions.size(); i++) {
        std::cout << "      IronBox " << (i + 1) << ": ("
            << initialState.ironBoxPositions[i].getX() << ","
            << initialState.ironBoxPositions[i].getY() << ")";
        if (isButton(initialState.ironBoxPositions[i].getX(),
            initialState.ironBoxPositions[i].getY())) {
            std::cout << " ✓ ON BUTTON";
        }
        std::cout << std::endl;
    }

    std::cout << "   Goals: " << goals.size() << std::endl;

    std::cout << "\n🔘 BUTTON-TRAP SYSTEM:" << std::endl;
    for (int i = 0; i < buttons.size(); i++) {
        Point buttonPos(buttons[i].getX(), buttons[i].getY());
        bool pressed = isButtonPressedInState(buttonPos,
            initialState.boxPositions,
            initialState.ironBoxPositions);
        std::cout << "   Button " << (i + 1) << " at ("
            << buttons[i].getX() << "," << buttons[i].getY() << "): "
            << (pressed ? "🟢 PRESSED" : "⚪ NOT PRESSED") << std::endl;

        const auto& traps = buttons[i].getLinkedTraps();
        for (int j = 0; j < traps.size(); j++) {
            Point trapPos(traps[j].first, traps[j].second);
            bool trapActive = isTrapActiveInState(trapPos,
                initialState.boxPositions,
                initialState.ironBoxPositions);
            std::cout << "      → Trap at (" << traps[j].first
                << "," << traps[j].second << "): "
                << (trapActive ? "🔴 ACTIVE" : "🟢 SAFE") << std::endl;
        }
    }

    Queue<BFSState> queue;
    queue.push(initialState);

    HashTable<BFSState, bool, BFSStateHash> visited(50000);
    visited.insert(initialState, true);

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };
    const char* dirNames[] = { "UP", "DOWN", "LEFT", "RIGHT", "TELEPORT" };

    int statesExplored = 0;
    int maxQueueSize = 0;
    const int MAX_STATES = 1000000;

    std::cout << "\n🔍 STARTING SEARCH..." << std::endl;
    std::cout << "   Max Depth: " << maxDepth << std::endl;

    auto startTime = std::chrono::steady_clock::now();

    while (!queue.empty() && statesExplored < MAX_STATES) {
        if (queue.size() > maxQueueSize) {
            maxQueueSize = queue.size();
        }

        BFSState current = queue.front();
        queue.pop();
        statesExplored++;

        if (statesExplored % 10000 == 0) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
            std::cout << "   [" << elapsed << "s] States: " << statesExplored
                << " | Queue: " << queue.size()
                << " | Depth: " << current.depth << std::endl;
        }

        // Kiểm tra win condition
        int boxesOnGoals = 0;
        for (int i = 0; i < current.boxPositions.size(); i++) {
            if (isGoal(current.boxPositions[i].getX(), current.boxPositions[i].getY())) {
                boxesOnGoals++;
            }
        }

        if (boxesOnGoals == current.boxPositions.size() &&
            current.boxPositions.size() == goals.size()) {

            auto endTime = std::chrono::steady_clock::now();
            auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

            std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
            std::cout << "║          ✨ SOLUTION FOUND! ✨         ║" << std::endl;
            std::cout << "╚════════════════════════════════════════╝" << std::endl;
            std::cout << "📊 Statistics:" << std::endl;
            std::cout << "   Solution Length: " << current.path.size() << " steps" << std::endl;
            std::cout << "   States Explored: " << statesExplored << std::endl;
            std::cout << "   Max Queue Size: " << maxQueueSize << std::endl;
            std::cout << "   Time: " << totalTime << " seconds" << std::endl;

            std::cout << "\n🎯 Solution Path:" << std::endl;
            std::cout << "   ";
            for (int i = 0; i < current.path.size(); i++) {
                std::cout << dirNames[current.path[i]] << " ";
                if ((i + 1) % 10 == 0) std::cout << "\n   ";
            }
            std::cout << std::endl;

            currentSolution = current.path;
            return true;
        }

        if (current.depth >= maxDepth) {
            continue;
        }

        // Try teleport
        if (isTeleport(current.playerPos.getX(), current.playerPos.getY())) {
            Point newPlayerPos = current.playerPos;
            if (tryTeleportInBFS(newPlayerPos)) {
                if (isValidBFSMove(newPlayerPos, current.boxPositions, current.ironBoxPositions)) {
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

        // Try 4 directions
        for (int dir = 0; dir < 4; dir++) {
            int newPlayerX = current.playerPos.getX() + dx[dir];
            int newPlayerY = current.playerPos.getY() + dy[dir];
            Point newPlayerPos(newPlayerX, newPlayerY);

            DynamicArray<Point> newBoxes = current.boxPositions;
            DynamicArray<Point> newIronBoxes = current.ironBoxPositions;

            // Kiểm tra đẩy normal box
            int boxIndex = -1;
            for (int i = 0; i < newBoxes.size(); i++) {
                if (newBoxes[i] == newPlayerPos) {
                    boxIndex = i;
                    break;
                }
            }

            // Kiểm tra đẩy iron box
            int ironBoxIndex = -1;
            for (int i = 0; i < newIronBoxes.size(); i++) {
                if (newIronBoxes[i] == newPlayerPos) {
                    ironBoxIndex = i;
                    break;
                }
            }

            if (boxIndex != -1) {
                // Đẩy normal box
                int newBoxX = newPlayerPos.getX() + dx[dir];
                int newBoxY = newPlayerPos.getY() + dy[dir];
                Point newBoxPos(newBoxX, newBoxY);

                if (!isValidBFSMove(newBoxPos, newBoxes, newIronBoxes)) {
                    continue;
                }

                newBoxes[boxIndex] = newBoxPos;

                if (isDeadlock(newBoxPos, newBoxes, newIronBoxes)) {
                    continue;
                }
            }
            else if (ironBoxIndex != -1) {
                // Đẩy iron box
                int newIronX = newPlayerPos.getX() + dx[dir];
                int newIronY = newPlayerPos.getY() + dy[dir];
                Point newIronPos(newIronX, newIronY);

                if (!isValidBFSMove(newIronPos, newBoxes, newIronBoxes)) {
                    continue;
                }

                // QUAN TRỌNG: Kiểm tra deadlock cho iron box
                if (isIronBoxDeadlock(newIronPos, newBoxes, newIronBoxes)) {
                    continue;
                }

                newIronBoxes[ironBoxIndex] = newIronPos;
            }
            else {
                // Di chuyển tự do
                if (!isValidBFSMove(newPlayerPos, newBoxes, newIronBoxes)) {
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

    auto endTime = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║       ❌ NO SOLUTION FOUND ❌          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    std::cout << "📊 Statistics:" << std::endl;
    std::cout << "   States Explored: " << statesExplored << std::endl;
    std::cout << "   Max Queue Size: " << maxQueueSize << std::endl;
    std::cout << "   Time: " << totalTime << " seconds" << std::endl;

    if (statesExplored >= MAX_STATES) {
        std::cout << "\n⚠️  Reached state limit!" << std::endl;
        std::cout << "   Solution might exist but search space too large" << std::endl;
        std::cout << "   Try: simpler map or increase MAX_STATES" << std::endl;
    }

    return false;
}

bool Map::executeNextSolutionStep() {
    if (currentSolutionStep >= currentSolution.size()) {
        stopAutoSolve();
        return false;
    }

    int action = currentSolution[currentSolutionStep];

    if (action == 4) {
        // Teleport
        bool teleported = tryTeleport();
        if (teleported) {
            currentSolutionStep++;
            return true;
        }
        return false;
    }
    else {
        // Normal move
        int dx[] = { 0, 0, -1, 1 };
        int dy[] = { -1, 1, 0, 0 };

        bool moved = tryMovePlayer(dx[action], dy[action]);

        if (moved) {
            currentSolutionStep++;
        }

        return moved;
    }
}

void Map::startAutoSolve() {
    m_isAutoSolving = true;
    currentSolutionStep = 0;
}

void Map::stopAutoSolve() {
    m_isAutoSolving = false;
}