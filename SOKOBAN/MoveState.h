#pragma once
#include "Point.h"
#include "DynamicArray.h"  // Thay thế <vector>

// Struct luu trang thai mot nuoc di de phuc vu Undo
struct MoveState {
    Point playerPosition;
    DynamicArray<Point> boxPositions;  // Đã đổi từ std::vector

    MoveState() {}

    MoveState(const Point& playerPos, const DynamicArray<Point>& boxPos)
        : playerPosition(playerPos), boxPositions(boxPos) {
    }
};