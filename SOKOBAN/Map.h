
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
    sf::Texture textureBayKichHoat;
    sf::Texture textureBayKoKichHoat;
    sf::Texture textureNutChuaNhan;
    sf::Texture textureNutDaNhan;
    sf::Texture textureDichChuyen;

    Stack<MoveState> LichSuDiChuyen;

    DynamicArray<int> LoiGiaiHienTai;
    int LoiGiaiHienTaiStep;
    bool m_isAutoSolving;

    void CapNhatThung();
    void KiemTraNut();

    bool LaBuocDiHopLeBFS(const Point& pos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    bool isDeadlock(const Point& boxPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    bool isIronBoxDeadlock(const Point& ironBoxPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    BFSState TaoTrangThaiBFS() const;

    bool NutBiNhanTrongBFS(const Point& buttonPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    bool BayKichHoatTrongBFS(const Point& trapPos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    bool CoThungTai(const Point& pos,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes) const;

    bool ThuDichChuyenInBFS(Point& playerPos) const;

public:
    Map(const std::string& filename, int tileSize);
    ~Map();

    void draw(sf::RenderWindow& window);
    bool tryMovePlayer(int dx, int dy);
    bool checkWin() const;
    Player* getPlayer();

    bool isTrap(int x, int y) const;
    bool isButton(int x, int y) const;
    Trap* TimBayTai(int x, int y);
    Button* TimNutBamTai(int x, int y);

    bool isTeleport(int x, int y) const;
    Teleport* TimDichChuyenTai(int x, int y);
    bool ThuDichChuyen();
    TeleportNetwork& getTeleportNetwork() { return teleportNetwork; }

    bool isSand(int x, int y) const;
    bool isWall(int x, int y) const;
    bool isWater(int x, int y) const;
    bool isBox(int x, int y) const;
    bool isIronBox(int x, int y) const;
    bool isObstacle(int x, int y) const;
    bool isGoal(int x, int y) const;
    bool isValidMove(int x, int y);

    Box* TimThungGoTai(int x, int y);
    IronBox* TimThungSatTai(int x, int y);
    bool DiChuyenThungGo(Box* box, int dx, int dy);
    bool DiChuyenThungSat(IronBox* ironBox, int dx, int dy);

    void LuuTrangThai();
    MoveState LayTrangThaiHienTai() const;
    void PhucHoiTrangThai(const MoveState& state);
    void LuiBuoc();
    int LaySoBuoc() const;

    // BFS solving functions
    bool TimLoiGiaiBFS(int maxDepth = 100);
    bool ThucHIenBuocGiai();
    void BatDauTuDongGiai();
    void DungTuDongGiai();
    bool LayTrangThaiTuDongGiai() const { return m_isAutoSolving; }

    bool isGameOver;
    void setGameOver(bool value) { isGameOver = value; }
    bool getGameOver() const { return isGameOver; }
};