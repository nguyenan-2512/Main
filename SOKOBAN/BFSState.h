#pragma once
#include "Point.h"
#include "DynamicArray.h"

// Tr?ng thái c?a game trong BFS
class BFSState {
public:
    Point playerPos;                    // V? trí ng??i ch?i
    DynamicArray<Point> boxPositions;   // V? trí các h?p
    DynamicArray<int> path;             // ???ng ?i (0=Up, 1=Down, 2=Left, 3=Right)
    int depth;                          // ?? sâu (s? b??c ?i)

    BFSState() : depth(0) {}

    BFSState(const Point& player, const DynamicArray<Point>& boxes, int d = 0)
        : playerPos(player), boxPositions(boxes), depth(d) {
    }

    // So sánh hai tr?ng thái
    bool operator==(const BFSState& other) const {
        if (playerPos != other.playerPos) return false;
        if (boxPositions.size() != other.boxPositions.size()) return false;

        for (int i = 0; i < boxPositions.size(); ++i) {
            bool found = false;
            for (int j = 0; j < other.boxPositions.size(); ++j) {
                if (boxPositions[i] == other.boxPositions[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
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

        // Hash v? trí player
        hash ^= PointHash()(state.playerPos);

        // Hash v? trí các h?p
        for (int i = 0; i < state.boxPositions.size(); ++i) {
            hash ^= (PointHash()(state.boxPositions[i]) << (i % 16));
        }

        return hash;
    }
};
