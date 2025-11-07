#pragma once
#include "Point.h"
#include "DynamicArray.h"  // Thay thế <vector>

// Struct luu trang thai mot nuoc di de phuc vu Undo
class MoveState {
public:
    Point playerPosition;
    DynamicArray<Point> boxPositions; 

    MoveState() {}

    MoveState(const Point& playerPos, const DynamicArray<Point>& boxPos)
        : playerPosition(playerPos), boxPositions(boxPos) {
    }
};