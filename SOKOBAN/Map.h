// Map.h - Phiên bản hoàn chỉnh
#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"  
#include <string>
#include "Stack.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Box.h"
#include "Goal.h"
#include "Obstacle.h"
#include "Water.h"
#include "Sand.h"
#include "BridgeT.h"
#include "Trap.h"
#include "Button.h"
#include "IronBox.h"
#include "Teleport.h"
#include "TeleportNetwork.h"
#include "MoveState.h"
#include "Queue.h"           
#include "BFSState.h"  

class Map {
private:
    int tileSize;
    Player* player;

    DynamicArray<Wall> walls;
    DynamicArray<Floor> floors;
    DynamicArray<Box> boxes;
    DynamicArray<IronBox> ironBoxes;
    DynamicArray<Goal> goals;
    DynamicArray<Obstacle> obstacles;
    DynamicArray<Water> waters;
    DynamicArray<Sand> sands;
    DynamicArray<BridgeT> bridgeTs;
    DynamicArray<Trap> traps;
    DynamicArray<Button> buttons;
    DynamicArray<Teleport> teleports;

    TeleportNetwork teleportNetwork;

    sf::Texture wallTexture;
    sf::Texture playerSpriteSheet;
    sf::Texture floorTexture;
    sf::Texture boxTexture;
    sf::Texture ironBoxTexture;
    sf::Texture boxOnGoalTexture;
    sf::Texture goalTexture;
    sf::Texture obstacleTexture;
    sf::Texture waterTexture;
    sf::Texture sandTexture;
    sf::Texture bridgeTTexture;
    sf::Texture trapActiveTexture;
    sf::Texture trapInactiveTexture;
    sf::Texture buttonUnpressedTexture;
    sf::Texture buttonPressedTexture;
    sf::Texture teleportActiveTexture;

    Stack<MoveState> moveHistory;

    // BFS solving variables
    DynamicArray<int> currentSolution;
    int currentSolutionStep;
    bool m_isAutoSolving;

    void updateBoxStates();
    void checkButtonStates();

    // ========== BFS Helper Functions ==========

    // Kiểm tra vị trí có hợp lệ trong BFS không
    bool isValidBFSMove(const Point& pos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    // Kiểm tra deadlock cho normal box
    bool isDeadlock(const Point& boxPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    // THÊM: Kiểm tra deadlock cho iron box (QUAN TRỌNG)
    bool isIronBoxDeadlock(const Point& ironBoxPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    // Tạo BFS state từ trạng thái hiện tại
    BFSState createCurrentBFSState() const;

    // Kiểm tra button có được nhấn không trong state cụ thể
    bool isButtonPressedInState(const Point& buttonPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    // Kiểm tra trap có active không trong state cụ thể
    bool isTrapActiveInState(const Point& trapPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    // Kiểm tra có box tại vị trí không
    bool hasBoxAt(const Point& pos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    // Thử teleport trong BFS
    bool tryTeleportInBFS(Point& playerPos) const;

    // THÊM: Đánh giá state (để ưu tiên các state tốt hơn)
    int evaluateState(const BFSState& state) const;

public:
    Map(const std::string& filename, int tileSize);
    ~Map();

    void draw(sf::RenderWindow& window);
    bool tryMovePlayer(int dx, int dy);
    bool checkWin() const;
    Player* getPlayer();

    bool isTrap(int x, int y) const;
    bool isButton(int x, int y) const;
    Trap* getTrapAt(int x, int y);
    Button* getButtonAt(int x, int y);

    bool isTeleport(int x, int y) const;
    Teleport* getTeleportAt(int x, int y);
    bool tryTeleport();
    TeleportNetwork& getTeleportNetwork() { return teleportNetwork; }

    bool isSand(int x, int y) const;
    bool isWall(int x, int y) const;
    bool isWater(int x, int y) const;
    bool isBox(int x, int y) const;
    bool isIronBox(int x, int y) const;
    bool isObstacle(int x, int y) const;
    bool isGoal(int x, int y) const;
    bool isValidMove(int x, int y);

    Box* getBoxAt(int x, int y);
    IronBox* getIronBoxAt(int x, int y);
    bool moveBox(Box* box, int dx, int dy);
    bool moveIronBox(IronBox* ironBox, int dx, int dy);

    void saveState();
    MoveState getCurrentState() const;
    void restoreState(const MoveState& state);
    void undo();
    int getMoveCount() const;

    // BFS solving functions
    bool solveBFS(int maxDepth = 100);
    bool executeNextSolutionStep();
    void startAutoSolve();
    void stopAutoSolve();
    bool getIsAutoSolving() const { return m_isAutoSolving; }

    bool isGameOver;
    void setGameOver(bool value) { isGameOver = value; }
    bool getGameOver() const { return isGameOver; }
};