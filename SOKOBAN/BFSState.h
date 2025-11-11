// BFSState.h
#pragma once
#include "Point.h"
#include "DynamicArray.h"
#include <cstddef>

// Struct lưu trạng thái cho BFS solver
class BFSState {
public:
    Point playerPos;                    // Vị trí player
    DynamicArray<Point> boxPositions;   // Vị trí các boxes
    DynamicArray<int> path;             // Đường đi (0=Up, 1=Down, 2=Left, 3=Right)
    int depth;                          // Độ sâu (số bước đi)

    BFSState() : playerPos(0, 0), depth(0) {}

    BFSState(const Point& playerPosition, const DynamicArray<Point>& boxes, int d = 0)
        : playerPos(playerPosition), boxPositions(boxes), depth(d) {
    }

    // Operator == để so sánh 2 trạng thái
    bool operator==(const BFSState& other) const {
        // Kiểm tra vị trí player
        if (playerPos != other.playerPos) {
            return false;
        }

        // Kiểm tra số lượng boxes
        if (boxPositions.size() != other.boxPositions.size()) {
            return false;
        }

        // Kiểm tra vị trí từng box (không cần quan tâm thứ tự)
        for (int i = 0; i < boxPositions.size(); i++) {
            bool found = false;
            for (int j = 0; j < other.boxPositions.size(); j++) {
                if (boxPositions[i] == other.boxPositions[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const BFSState& other) const {
        return !(*this == other);
    }
};

// Hash function cho BFSState
struct BFSStateHash {
    std::size_t operator()(const BFSState& state) const {
        std::size_t hash = 0;

        // Hash vị trí player
        PointHash pointHash;
        hash = pointHash(state.playerPos);

        // Hash các vị trí boxes (sử dụng XOR để không phụ thuộc thứ tự)
        for (int i = 0; i < state.boxPositions.size(); i++) {
            std::size_t boxHash = pointHash(state.boxPositions[i]);
            hash ^= (boxHash << (i % 16)); // Shift để tạo sự khác biệt
        }

        return hash;
    }
};