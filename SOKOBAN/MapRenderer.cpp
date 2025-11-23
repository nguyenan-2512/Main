#include "MapRenderer.h"

void MapRenderer::ve(sf::RenderWindow& cuaSo, const BanDo* map) {
    if (!map) return;

    // Lớp 1: toàn bộ đối tượng tĩnh (trừ thùng)
    for (int i = 0; i < map->cacDoiTuong.size(); ++i) {
        LoaiDoiTuong loai = map->cacDoiTuong[i]->layLoai();
        if (loai != LoaiDoiTuong::THUNG_GO &&
            loai != LoaiDoiTuong::THUNG_SAT) {
            map->cacDoiTuong[i]->ve(cuaSo);
        }
    }

    // Lớp 2: thùng gỗ
    for (int i = 0; i < map->cacThungGoPtr.size(); ++i) {
        map->cacThungGoPtr[i]->ve(cuaSo);
    }

    // Lớp 3: thùng sắt
    for (int i = 0; i < map->cacThungSatPtr.size(); ++i) {
        map->cacThungSatPtr[i]->ve(cuaSo);
    }

    // Lớp 4: người chơi
    if (map->nguoiChoi) {
        map->nguoiChoi->ve(cuaSo);
    }
}