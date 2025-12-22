#include "MapRenderer.h"

void MapRenderer::ve(sf::RenderWindow& cuaSo, const BanDo* map) {
    if (!map) return;

    for (int i = 0; i < map->cacDoiTuong.size(); ++i) {
        LoaiDoiTuong loai = map->cacDoiTuong[i]->layLoai();
        if (loai != LoaiDoiTuong::THUNG_GO &&
            loai != LoaiDoiTuong::THUNG_SAT) {
            map->cacDoiTuong[i]->ve(cuaSo);
        }
    }
    for (int i = 0; i < map->cacThungGoPtr.size(); ++i) {
        map->cacThungGoPtr[i]->ve(cuaSo);
    }
    for (int i = 0; i < map->cacThungSatPtr.size(); ++i) {
        map->cacThungSatPtr[i]->ve(cuaSo);
    }

    if (map->nguoiChoi) {
        map->nguoiChoi->ve(cuaSo);
    }
}