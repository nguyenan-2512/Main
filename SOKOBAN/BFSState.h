// BFSState.h - Enhanced version
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

        // Kiểm tra số lượng iron boxes
        if (ironBoxPositions.size() != other.ironBoxPositions.size()) {
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

        // Kiểm tra vị trí từng iron box
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

// Hash function cho BFSState
struct BFSStateHash {
    std::size_t operator()(const BFSState& state) const {
        std::size_t hash = 0;

        // Hash vị trí player
        PointHash pointHash;
        hash = pointHash(state.playerPos);

        // Hash các vị trí boxes
        for (int i = 0; i < state.boxPositions.size(); i++) {
            std::size_t boxHash = pointHash(state.boxPositions[i]);
            hash ^= (boxHash << (i % 16));
        }

        // Hash các vị trí iron boxes
        for (int i = 0; i < state.ironBoxPositions.size(); i++) {
            std::size_t ironHash = pointHash(state.ironBoxPositions[i]);
            hash ^= (ironHash << ((i + 8) % 16));
        }

        return hash;
    }
};