#include "BoxTriggerUpdater.h"

void BoxTriggerUpdater::capNhatThung(BanDo* map) {
    if (!map) return;

    for (int i = 0; i < map->cacThungGoPtr.size(); i++) {
        bool trenViTriDat = map->laViTriDat(
            map->cacThungGoPtr[i]->layX(),
            map->cacThungGoPtr[i]->layY()
        );
        map->cacThungGoPtr[i]->datTrangThaiTrenViTriDat(trenViTriDat);
    }
}

void BoxTriggerUpdater::capNhatNutVaBay(BanDo* map) {
    if (!map) return;

    for (int i = 0; i < map->cacNutBamPtr.size(); i++) {
        int nx = map->cacNutBamPtr[i]->layX();
        int ny = map->cacNutBamPtr[i]->layY();

        bool coThung = map->laThungGo(nx, ny);
        bool coThungSat = map->laThungSat(nx, ny);
        bool duocNhan = coThung || coThungSat;

        map->cacNutBamPtr[i]->datTrangThaiNhan(duocNhan);

        const auto& cacBayLienKet = map->cacNutBamPtr[i]->layCacBayLienKet();
        for (int j = 0; j < cacBayLienKet.size(); j++) {
            Bay* bay = map->timBayTai(
                cacBayLienKet[j].first,
                cacBayLienKet[j].second
            );
            if (bay) {
                bay->datKichHoat(!duocNhan);
            }
        }
    }
}