#include "LopPhuPause.h"
#include <iostream>
using namespace std; // Thêm using namespace std cho tiện

LopPhuPause::LopPhuPause()
    : dangHienThi(false),
    anhMenuPause(nullptr),
    nutTiepTuc(nullptr),
    nutChoiLai(nullptr),
    nutThoat(nullptr) {

    // 1. THIẾT LẬP LỚP PHỦ NỀN TRONG SUỐT (COVER TOÀN BỘ MÀN HÌNH 800x800)
    lopPhu.setSize(sf::Vector2f(800, 800));
    lopPhu.setFillColor(sf::Color(0, 0, 0, 150)); // Giảm xuống 150 để thấy ảnh khung
    lopPhu.setPosition(0, 0);
}

LopPhuPause::~LopPhuPause() {
    if (anhMenuPause) delete anhMenuPause;
    if (nutTiepTuc) delete nutTiepTuc;
    if (nutChoiLai) delete nutChoiLai;
    if (nutThoat) delete nutThoat;
}
bool LopPhuPause::khoiTao(
    const std::string& duongDanAnhMenuPause,
    const std::string& duongDanAnhTiepTuc,
    const std::string& duongDanAnhChoiLai,
    const std::string& duongDanAnhTuyChon,
    const std::string& duongDanAnhThoat) {

    anhMenuPause = new NutUI();
    if (!anhMenuPause->taiAnh(duongDanAnhMenuPause)) {
        std::cerr << "Khong the tai anh khung menu pause!" << std::endl;
    }

    anhMenuPause->datViTri(90.0f, 90.0f);
    anhMenuPause->datKichThuoc(600.0f, 680.0f);

    nutTiepTuc = new NutUI();
    if (!nutTiepTuc->taiAnh(duongDanAnhTiepTuc)) {
        std::cerr << "Khong the tai anh nut Tiep Tuc!" << std::endl;
        return false;
    }

    nutTiepTuc->datViTri(260.0f, 180.0f);
    nutTiepTuc->datKichThuoc(240.0f, 176.0f);
    nutChoiLai = new NutUI();
    if (!nutChoiLai->taiAnh(duongDanAnhChoiLai)) {
        std::cerr << "Khong the tai anh nut Choi Lai!" << std::endl;
        return false;
    }
    nutChoiLai->datViTri(260.0f, 280.0f);
    nutChoiLai->datKichThuoc(245.0f, 176.0f);

    nutThoat = new NutUI();
    if (!nutThoat->taiAnh(duongDanAnhThoat)) {
        std::cerr << "Khong the tai anh nut Thoat!" << std::endl;
        return false;
    }
    nutThoat->datViTri(260.0f, 380.0f);
    nutThoat->datKichThuoc(240.0f, 176.0f);

    std::cout << "Da khoi tao Lop Phu Pause thanh cong!" << endl;
    return true;
}
void LopPhuPause::hienThi() {
    dangHienThi = true;
}

void LopPhuPause::an() {
    dangHienThi = false;
}

HanhDongPause LopPhuPause::kiemTraClick(const sf::Vector2i& viTriChuot) {
    if (!dangHienThi) return HanhDongPause::KHONG;

    if (nutTiepTuc && nutTiepTuc->kiemTraClick(viTriChuot)) {
        std::cout << "Click nut Tiep Tuc!" << std::endl;
        return HanhDongPause::TIEP_TUC;
    }

    if (nutChoiLai && nutChoiLai->kiemTraClick(viTriChuot)) {
        std::cout << "Click nut Choi Lai!" << std::endl;
        return HanhDongPause::CHOI_LAI;
    }

    if (nutThoat && nutThoat->kiemTraClick(viTriChuot)) {
        std::cout << "Click nut Thoat!" << std::endl;
        return HanhDongPause::THOAT;
    }

    return HanhDongPause::KHONG;
}

void LopPhuPause::capNhat(const sf::Vector2i& viTriChuot) {
    if (!dangHienThi) return;

    if (nutTiepTuc) nutTiepTuc->capNhat(viTriChuot);
    if (nutChoiLai) nutChoiLai->capNhat(viTriChuot);
    if (nutThoat) nutThoat->capNhat(viTriChuot);
}

void LopPhuPause::ve(sf::RenderWindow& cuaSo) {
    if (!dangHienThi) return;
    cuaSo.draw(lopPhu);
    if (anhMenuPause) anhMenuPause->ve(cuaSo);
    if (nutTiepTuc) nutTiepTuc->ve(cuaSo);
    if (nutChoiLai) nutChoiLai->ve(cuaSo);
    if (nutThoat) nutThoat->ve(cuaSo);
}