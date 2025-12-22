#pragma once
#include "BanDo.h"

class BoxTriggerUpdater {
public:
    BoxTriggerUpdater() = default;

    void capNhatThung(BanDo* map);

    void capNhatNutVaBay(BanDo* map);
};