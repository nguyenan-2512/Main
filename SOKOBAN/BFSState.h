
#pragma once
#include "Point.h"
#include "DynamicArray.h"
#include <cstddef>

// Struct lưu trạng thái mở rộng cho BFS solver
class BFSState {
public:
    Point playerPos;                    // Vị trí player
    DynamicArray<Point> boxPositions;   // Vị trí các boxes thường
    DynamicArray<Point> ironBoxPositions; // Vị trí các iron boxes
    DynamicArray<int> path;             // Đường đi (0=Up, 1=Down, 2=Left, 3=Right, 4=Teleport)
    int depth;                          // Độ sâu (số bước đi)

    BFSState() : playerPos(0, 0), depth(0) {}

    BFSState(const Point& playerPosition,
        const DynamicArray<Point>& boxes,
        const DynamicArray<Point>& ironBoxes,
        int d = 0)
        : playerPos(playerPosition),
        boxPositions(boxes),
        ironBoxPositions(ironBoxes),
        depth(d) {
    }

    bool operator==(const BFSState& other) const {
        if (playerPos != other.playerPos) {
            return false;
        }

        if (boxPositions.size() != other.boxPositions.size()) {
            return false;
        }

        if (ironBoxPositions.size() != other.ironBoxPositions.size()) {
            return false;
        }

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

        for (int i = 0; i < ironBoxPositions.size(); i++) {
            bool found = false;
            for (int j = 0; j < other.ironBoxPositions.size(); j++) {
                if (ironBoxPositions[i] == other.ironBoxPositions[j]) {
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


struct BFSStateHash {
    std::size_t operator()(const BFSState& state) const {
        std::size_t hash = 0;

        PointHash pointHash;
        hash = pointHash(state.playerPos);

        for (int i = 0; i < state.boxPositions.size(); i++) {
            std::size_t boxHash = pointHash(state.boxPositions[i]);
            hash ^= (boxHash << (i % 16));
        }

        for (int i = 0; i < state.ironBoxPositions.size(); i++) {
            std::size_t ironHash = pointHash(state.ironBoxPositions[i]);
            hash ^= (ironHash << ((i + 8) % 16));
        }

        return hash;
    }
};