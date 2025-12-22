#include "BFSSolver.h"
#include "BanDo.h"

BFSSolver::BFSSolver(const BanDo* map) : banDo(map) {}

bool BFSSolver::timLoiGiai(TrangThaiBFS trangThaiBanDau,
    DynamicArray<int>& loiGiai,
    int doSauToiDa) {
    loiGiai.clear();

    Queue<TrangThaiBFS> hangDoi;
    hangDoi.push(trangThaiBanDau);

    HashTable<TrangThaiBFS, bool, TrangThaiBFSHash> daThamQua(50000);
    daThamQua.insert(trangThaiBanDau, true);

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    int soTrangThaiDaKhamPha = 0;
    const int SO_TRANG_THAI_TOI_DA = 1000000;

    while (!hangDoi.empty() && soTrangThaiDaKhamPha < SO_TRANG_THAI_TOI_DA) {
        TrangThaiBFS trangThaiHienTai = hangDoi.front();
        hangDoi.pop();
        soTrangThaiDaKhamPha++;

        int soThungTrenViTriDat = 0;
        for (int i = 0; i < trangThaiHienTai.cacViTriThung.size(); i++) {
            if (banDo->laViTriDat(trangThaiHienTai.cacViTriThung[i].layX(),
                trangThaiHienTai.cacViTriThung[i].layY())) {
                soThungTrenViTriDat++;
            }
        }

        int soViTriDat = banDo->laySoViTriDat();

        if (soThungTrenViTriDat == trangThaiHienTai.cacViTriThung.size() &&
            trangThaiHienTai.cacViTriThung.size() == soViTriDat) {
            loiGiai = trangThaiHienTai.duongDi;
            return true;
        }

        if (trangThaiHienTai.doSau >= doSauToiDa) {
            continue;
        }

        if (banDo->laCongDichChuyen(trangThaiHienTai.viTriNguoiChoi.layX(),
            trangThaiHienTai.viTriNguoiChoi.layY())) {
            Diem viTriNguoiChoiMoi = trangThaiHienTai.viTriNguoiChoi;
            if (thuDichChuyenTrongBFS(viTriNguoiChoiMoi)) {
                if (laBuocDiHopLeBFS(viTriNguoiChoiMoi,
                    trangThaiHienTai.cacViTriThung,
                    trangThaiHienTai.cacViTriThungSat)) {
                    TrangThaiBFS trangThaiMoi(viTriNguoiChoiMoi,
                        trangThaiHienTai.cacViTriThung,
                        trangThaiHienTai.cacViTriThungSat,
                        trangThaiHienTai.doSau + 1);
                    trangThaiMoi.duongDi = trangThaiHienTai.duongDi;
                    trangThaiMoi.duongDi.push_back(4);  

                    if (!daThamQua.contains(trangThaiMoi)) {
                        daThamQua.insert(trangThaiMoi, true);
                        hangDoi.push(trangThaiMoi);
                    }
                }
            }
        }

        for (int huong = 0; huong < 4; huong++) {
            int xNguoiChoiMoi = trangThaiHienTai.viTriNguoiChoi.layX() + dx[huong];
            int yNguoiChoiMoi = trangThaiHienTai.viTriNguoiChoi.layY() + dy[huong];
            Diem viTriNguoiChoiMoi(xNguoiChoiMoi, yNguoiChoiMoi);

            DynamicArray<Diem> cacThungMoi = trangThaiHienTai.cacViTriThung;
            DynamicArray<Diem> cacThungSatMoi = trangThaiHienTai.cacViTriThungSat;

            int chiSoThung = -1;
            for (int i = 0; i < cacThungMoi.size(); i++) {
                if (cacThungMoi[i] == viTriNguoiChoiMoi) {
                    chiSoThung = i;
                    break;
                }
            }

            int chiSoThungSat = -1;
            for (int i = 0; i < cacThungSatMoi.size(); i++) {
                if (cacThungSatMoi[i] == viTriNguoiChoiMoi) {
                    chiSoThungSat = i;
                    break;
                }
            }

            if (chiSoThung != -1) {
                int xThungMoi = viTriNguoiChoiMoi.layX() + dx[huong];
                int yThungMoi = viTriNguoiChoiMoi.layY() + dy[huong];
                Diem viTriThungMoi(xThungMoi, yThungMoi);

                if (!laBuocDiHopLeBFS(viTriThungMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
                cacThungMoi[chiSoThung] = viTriThungMoi;
                if (laViTriChet(viTriThungMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
            }
            else if (chiSoThungSat != -1) {
                int xThungSatMoi = viTriNguoiChoiMoi.layX() + dx[huong];
                int yThungSatMoi = viTriNguoiChoiMoi.layY() + dy[huong];
                Diem viTriThungSatMoi(xThungSatMoi, yThungSatMoi);

                if (!laBuocDiHopLeBFS(viTriThungSatMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
                if (laThungSatChet(viTriThungSatMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
                cacThungSatMoi[chiSoThungSat] = viTriThungSatMoi;
            }
            else {
                if (!laBuocDiHopLeBFS(viTriNguoiChoiMoi, cacThungMoi, cacThungSatMoi)) {
                    continue;
                }
            }

            TrangThaiBFS trangThaiMoi(viTriNguoiChoiMoi, cacThungMoi, cacThungSatMoi,
                trangThaiHienTai.doSau + 1);
            trangThaiMoi.duongDi = trangThaiHienTai.duongDi;
            trangThaiMoi.duongDi.push_back(huong);

            if (!daThamQua.contains(trangThaiMoi)) {
                daThamQua.insert(trangThaiMoi, true);
                hangDoi.push(trangThaiMoi);
            }
        }
    }

    return false;
}
bool BFSSolver::laBuocDiHopLeBFS(const Diem& viTri,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTri.layX();
    int y = viTri.layY();

    if (banDo->laTuong(x, y) || banDo->laNuoc(x, y) || banDo->laVatCan(x, y)) {
        return false;
    }
    if (banDo->laBay(x, y)) {
        if (bayKichHoatTrongBFS(viTri, cacThung, cacThungSat)) {
            return false;
        }
    }
    if (coThungTai(viTri, cacThung, cacThungSat)) {
        return false;
    }

    return true;
}

bool BFSSolver::laViTriChet(const Diem& viTriThung,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTriThung.layX();
    int y = viTriThung.layY();

    if (banDo->laViTriDat(x, y) || banDo->laNutBam(x, y)) {
        return false;
    }

    bool traiChan = banDo->laTuong(x - 1, y) || banDo->laVatCan(x - 1, y);
    bool phaiChan = banDo->laTuong(x + 1, y) || banDo->laVatCan(x + 1, y);
    bool trenChan = banDo->laTuong(x, y - 1) || banDo->laVatCan(x, y - 1);
    bool duoiChan = banDo->laTuong(x, y + 1) || banDo->laVatCan(x, y + 1);

    if ((traiChan && trenChan) || (phaiChan && trenChan) ||
        (traiChan && duoiChan) || (phaiChan && duoiChan)) {
        return true;
    }

    if (cacThung.size() >= 4) {
        Diem keCanh[3] = {
            Diem(x + 1, y),
            Diem(x, y + 1),
            Diem(x + 1, y + 1)
        };

        int soThungKeCanh = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < cacThung.size(); j++) {
                if (cacThung[j] == keCanh[i]) {
                    soThungKeCanh++;
                    break;
                }
            }
        }

        if (soThungKeCanh == 3) {
            bool coViTriDatTrong2x2 = banDo->laViTriDat(x, y) ||
                banDo->laViTriDat(x + 1, y) ||
                banDo->laViTriDat(x, y + 1) ||
                banDo->laViTriDat(x + 1, y + 1);

            bool coNutTrong2x2 = banDo->laNutBam(x, y) ||
                banDo->laNutBam(x + 1, y) ||
                banDo->laNutBam(x, y + 1) ||
                banDo->laNutBam(x + 1, y + 1);

            if (!coViTriDatTrong2x2 && !coNutTrong2x2) {
                return true;
            }
        }
    }

    return false;
}

bool BFSSolver::laThungSatChet(const Diem& viTriThungSat,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTriThungSat.layX();
    int y = viTriThungSat.layY();

    if (banDo->laNutBam(x, y)) {
        return false;
    }

    if (banDo->laViTriDat(x, y)) {
        return true;
    }

    bool traiChan = banDo->laTuong(x - 1, y) || banDo->laVatCan(x - 1, y);
    bool phaiChan = banDo->laTuong(x + 1, y) || banDo->laVatCan(x + 1, y);
    bool trenChan = banDo->laTuong(x, y - 1) || banDo->laVatCan(x, y - 1);
    bool duoiChan = banDo->laTuong(x, y + 1) || banDo->laVatCan(x, y + 1);

    if ((traiChan && trenChan) || (phaiChan && trenChan) ||
        (traiChan && duoiChan) || (phaiChan && duoiChan)) {
        return true;
    }

    return false;
}

bool BFSSolver::nutBiNhanTrongBFS(const Diem& viTriNut,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    for (int i = 0; i < cacThung.size(); i++) {
        if (cacThung[i] == viTriNut) return true;
    }
    for (int i = 0; i < cacThungSat.size(); i++) {
        if (cacThungSat[i] == viTriNut) return true;
    }
    return false;
}

bool BFSSolver::bayKichHoatTrongBFS(const Diem& viTriBay,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    return kiemTraBayKichHoat(viTriBay, cacThung, cacThungSat);
}

bool BFSSolver::coThungTai(const Diem& viTri,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    for (int i = 0; i < cacThung.size(); i++) {
        if (cacThung[i] == viTri) return true;
    }
    for (int i = 0; i < cacThungSat.size(); i++) {
        if (cacThungSat[i] == viTri) return true;
    }
    return false;
}

bool BFSSolver::thuDichChuyenTrongBFS(Diem& viTriNguoiChoi) const {
    if (!banDo->laCongDichChuyen(viTriNguoiChoi.layX(), viTriNguoiChoi.layY())) {
        return false;
    }

    Diem diemDen = layDiemDenDichChuyen(viTriNguoiChoi);

    if (diemDen == viTriNguoiChoi) {
        return false;
    }

    viTriNguoiChoi = diemDen;
    return true;
}

Diem BFSSolver::layDiemDenDichChuyen(const Diem& viTri) const {
    return banDo->mangDichChuyen.layDiemDen(viTri);
}

bool BFSSolver::kiemTraBayKichHoat(const Diem& viTriBay,
    const DynamicArray<Diem>& cacThung,
    const DynamicArray<Diem>& cacThungSat) const {
    int x = viTriBay.layX();
    int y = viTriBay.layY();

    const auto& cacNutBam = banDo->cacNutBamPtr;

    for (int i = 0; i < cacNutBam.size(); i++) {
        const auto& cacBayLienKet = cacNutBam[i]->layCacBayLienKet();
        for (int j = 0; j < cacBayLienKet.size(); j++) {
            if (cacBayLienKet[j].first == x && cacBayLienKet[j].second == y) {
                Diem viTriNut(cacNutBam[i]->layX(), cacNutBam[i]->layY());
                bool nutDuocNhan = false;
                for (int k = 0; k < cacThung.size(); k++) {
                    if (cacThung[k] == viTriNut) {
                        nutDuocNhan = true;
                        break;
                    }
                }
                if (!nutDuocNhan) {
                    for (int k = 0; k < cacThungSat.size(); k++) {
                        if (cacThungSat[k] == viTriNut) {
                            nutDuocNhan = true;
                            break;
                        }
                    }
                }

                return !nutDuocNhan;
            }
        }
    }

    return true;
}
