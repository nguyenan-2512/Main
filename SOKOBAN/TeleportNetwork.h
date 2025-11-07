#pragma once
#include "Point.h"
#include "DynamicArray.h"  
#include "HashTable.h"   

// Hàm băm cho Point
struct PointHash {
    size_t operator()(const Point& p) const {
        int x = p.getX();
        int y = p.getY();
        return (x * 73856093) ^ (y * 19349663);
    }
};

// Hàm băm cho int
struct IntHash {
    size_t operator()(int key) const {
        return key * 2654435761 % 4294967296;
    }
};

class TeleportNetwork {
private:
    // Map từ vị trí -> Teleport ID
    HashTable<Point, int, PointHash> locationToID;

    // Map từ ID -> danh sách các vị trí cùng ID (cổng liên kết)
    HashTable<int, DynamicArray<Point>, IntHash> idToLocations;

public:
    TeleportNetwork();

    // Thêm cổng teleport
    void addTeleport(const Point& location, int teleportID);

    // Lấy điểm đến khi đi vào cổng
   Point getDestination(const Point& from);

    // Kiểm tra xem vị trí có phải cổng teleport không
    bool isTeleport(const Point& location) const;

    // Lấy ID của cổng tại vị trí
    int getTeleportID(const Point& location) const;

    // Lấy tất cả cổng cùng ID
    DynamicArray<Point> getLinkedTeleports(int teleportID) const;

    // Clear all
    void clear();

    // Debug: in thông tin mạng
    void printNetwork() const;
};