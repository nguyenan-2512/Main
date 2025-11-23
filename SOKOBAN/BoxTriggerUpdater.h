#pragma once
#include "BanDo.h"

// Class chịu trách nhiệm cập nhật trạng thái thùng + nút + bẫy
class BoxTriggerUpdater {
public:
    BoxTriggerUpdater() = default;

    // Cập nhật trạng thái "thùng trên vị trí đặt"
    void capNhatThung(BanDo* map);

    // Cập nhật nút bấm và bẫy liên kết
    void capNhatNutVaBay(BanDo* map);
};