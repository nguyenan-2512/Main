#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "BanDo.h"
#include "ResourceManager.h"
#include "Tuong.h"
#include "Nen.h"
#include "Nuoc.h"
#include "Cat.h"
#include "Cau.h"
#include "VatCan.h"
#include "ThungGo.h"
#include "ThungSat.h"
#include "ViTriDat.h"
#include "Bay.h"
#include "NutBam.h"
#include "CongDichChuyen.h"
#include "NguoiChoi.h"

class MapLoader {
public:
    static BanDo* loadFromFile(const std::string& filePath, int kichThuocO) {
        std::cout << "[MapLoader] Dang doc file: " << filePath << std::endl;

        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "[MapLoader] Khong mo duoc file: " << filePath << std::endl;
            return nullptr;
        }

        BanDo* map = new BanDo(kichThuocO);
        ResourceManager* rm = ResourceManager::getInstance();

        std::string line;
        int y = 0;

        while (std::getline(file, line)) {
            for (int x = 0; x < (int)line.size(); x++) {
                char c = line[x];
                if (c == '#') {
                    Tuong* tuong = new Tuong(x, y, kichThuocO);
                    sf::Texture* tex = rm->getTexture("wall");
                    if (tex) tuong->datKetCau(*tex);
                    map->themDoiTuong(tuong);
                }
                else if (c == '=') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    Cau* cau = new Cau(x, y, kichThuocO);
                    sf::Texture* texCau = rm->getTexture("bridge");
                    if (texCau) cau->datKetCau(*texCau);
                    map->themDoiTuong(cau);
                }
                else if (c == '?') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    Cat* cat = new Cat(x, y, kichThuocO);
                    sf::Texture* texCat = rm->getTexture("sand");
                    if (texCat) cat->datKetCau(*texCat);
                    map->themDoiTuong(cat);
                }
                else if (c == '~') {
                    Nuoc* nuoc = new Nuoc(x, y, kichThuocO);
                    sf::Texture* texNuoc = rm->getTexture("water");
                    if (texNuoc) nuoc->datKetCau(*texNuoc);
                    map->themDoiTuong(nuoc);
                }
                else if (c == '@') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    NguoiChoi* player = new NguoiChoi(x, y, kichThuocO);
                    sf::Texture* texPlayer = rm->getTexture("player");
                    if (texPlayer) {
                        player->khoiTaoHoatHinh(*texPlayer, 32, 32, 4);
                    }
                    map->datNguoiChoi(player);
                }
                else if (c == '$') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    ThungGo* box = new ThungGo(x, y, kichThuocO);
                    sf::Texture* texBox = rm->getTexture("box");
                    sf::Texture* texBoxOnGoal = rm->getTexture("box_on_goal");
                    if (texBox) box->datKetCauBinhThuong(*texBox);
                    if (texBoxOnGoal) box->datKetCauTrenViTriDat(*texBoxOnGoal);
                    map->themDoiTuong(box);
                }
                else if (c == 'I') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    ThungSat* steelBox = new ThungSat(x, y, kichThuocO);
                    sf::Texture* texSteel = rm->getTexture("steel_box");
                    if (texSteel) steelBox->datKetCauThungSat(*texSteel);
                    map->themDoiTuong(steelBox);
                }
                else if (c == 'X' || c == 'x') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    ViTriDat* goal = new ViTriDat(x, y, kichThuocO);
                    sf::Texture* texGoal = rm->getTexture("goal");
                    if (texGoal) goal->datKetCau(*texGoal);
                    map->themDoiTuong(goal);
                }
                else if (c == 'O' || c == 'o') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    VatCan* obstacle = new VatCan(x, y, kichThuocO);
                    sf::Texture* texObstacle = rm->getTexture("obstacle");
                    if (texObstacle) obstacle->datKetCau(*texObstacle);
                    map->themDoiTuong(obstacle);
                }
                else if (c == '+') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    ViTriDat* goal = new ViTriDat(x, y, kichThuocO);
                    sf::Texture* texGoal = rm->getTexture("goal");
                    if (texGoal) goal->datKetCau(*texGoal);
                    map->themDoiTuong(goal);

                    NguoiChoi* player = new NguoiChoi(x, y, kichThuocO);
                    sf::Texture* texPlayer = rm->getTexture("player");
                    if (texPlayer) {
                        player->khoiTaoHoatHinh(*texPlayer, 32, 32, 4);
                    }
                    map->datNguoiChoi(player);
                }
                else if (c == '*') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    ViTriDat* goal = new ViTriDat(x, y, kichThuocO);
                    sf::Texture* texGoal = rm->getTexture("goal");
                    if (texGoal) goal->datKetCau(*texGoal);
                    map->themDoiTuong(goal);

                    ThungGo* box = new ThungGo(x, y, kichThuocO);
                    sf::Texture* texBox = rm->getTexture("box");
                    sf::Texture* texBoxOnGoal = rm->getTexture("box_on_goal");
                    if (texBox) box->datKetCauBinhThuong(*texBox);
                    if (texBoxOnGoal) box->datKetCauTrenViTriDat(*texBoxOnGoal);
                    box->datTrangThaiTrenViTriDat(true);
                    map->themDoiTuong(box);
                }
                else if (c == '.' || c == ' ') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);
                }
                else if (c == 'T') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    Bay* trap = new Bay(x, y, kichThuocO);
                    sf::Texture* texActive = rm->getTexture("trap_active");
                    sf::Texture* texInactive = rm->getTexture("trap_inactive");
                    if (texActive) trap->datKetCauKichHoat(*texActive);
                    if (texInactive) trap->datKetCauKhongKichHoat(*texInactive);
                    map->themDoiTuong(trap);
                }
                else if (c == 'B') {
                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    NutBam* button = new NutBam(x, y, kichThuocO);
                    sf::Texture* texUnpressed = rm->getTexture("button_unpressed");
                    sf::Texture* texPressed = rm->getTexture("button_pressed");
                    if (texUnpressed) button->datKetCauChuaNhan(*texUnpressed);
                    if (texPressed) button->datKetCauDaNhan(*texPressed);
                    map->themDoiTuong(button);
                }
                else if (isdigit(c)) {
                    int maSo = c - '0';

                    Nen* nen = new Nen(x, y, kichThuocO);
                    sf::Texture* texNen = rm->getTexture("floor");
                    if (texNen) nen->datKetCau(*texNen);
                    map->themDoiTuong(nen);

                    CongDichChuyen* teleport = new CongDichChuyen(x, y, kichThuocO, maSo);
                    sf::Texture* texTeleport = rm->getTexture("teleport");
                    if (texTeleport) teleport->datKetCau(*texTeleport);
                    map->themDoiTuong(teleport);

                    map->layMangDichChuyen().themCongDichChuyen(Diem(x, y), maSo);
                }
            }
            y++;
        }

        file.close();
        map->linkButtonsToTraps();
        std::cout << "[MapLoader] Load thanh cong!" << std::endl;
        return map;
    }
}; 
