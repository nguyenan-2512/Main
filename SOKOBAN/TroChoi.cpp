#include "TroChoi.h"
#include <iostream>
using namespace std;

TroChoi::TroChoi() :
    cuaSo(sf::VideoMode::getDesktopMode(), "Sokoban", sf::Style::Fullscreen),
    banDoHienTai(nullptr),
    trangThaiTroChoi(TrangThaiTroChoi::MENU),
    hienThiThang(false),
    hienThiThua(false),
    kichThuocGoc(800, 800),
    tyLeX(1.0f),
    tyLeY(1.0f),
    cheDoX(0.0f),
    cheDoY(0.0f) {

    cuaSo.setFramerateLimit(60);
    HoatHinh::tocDoHoatHinh = 0.1f;

    thieLapManHinhDay();

    // Load tài nguyên
    if (!nhacNen.openFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\hi.ogg")) {
        cerr << "Khong the tai nhac nen!" << endl;
    }

    if (!boNhoAmThanhBuocDi.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg")) {
        cerr << "Khong the tai am thanh buoc di!" << endl;
    }
    amThanhBuocDi.setBuffer(boNhoAmThanhBuocDi);

    if (!boNhoAmThanhChienThang.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg")) {
        cerr << "Khong the tai am thanh chien thang!" << endl;
    }
    amThanhChienThang.setBuffer(boNhoAmThanhChienThang);

    if (!boNhoAmThanhThua.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\gameover.ogg")) {
        cerr << "Khong the tai am thanh thua!" << endl;
    }
    amThanhThua.setBuffer(boNhoAmThanhThua);

    if (!ketCauThang.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win.png")) {
        cerr << "Khong the tai anh thang!" << endl;
    }
    anhThang.setTexture(ketCauThang);
    anhThang.setPosition(0, 0);

    if (!ketCauThua.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\gameover.png")) {
        cerr << "Khong the tai anh thua!" << endl;
    }
    anhThua.setTexture(ketCauThua);
    anhThua.setPosition(0, 0);

    GiaoDien.taiTaiNguyen();
}

TroChoi::~TroChoi() {
    xoaTroChoi();
}

void TroChoi::thieLapManHinhDay() {
    sf::Vector2u kichThuocManHinh = cuaSo.getSize();

    float tyLeManHinh = static_cast<float>(kichThuocManHinh.x) / static_cast<float>(kichThuocManHinh.y);
    float tyLeTroChoi = static_cast<float>(kichThuocGoc.x) / static_cast<float>(kichThuocGoc.y);

    if (tyLeManHinh > tyLeTroChoi) {
        tyLeY = static_cast<float>(kichThuocManHinh.y) / static_cast<float>(kichThuocGoc.y);
        tyLeX = tyLeY;
        cheDoX = (kichThuocManHinh.x - (kichThuocGoc.x * tyLeX)) / 2.0f;
        cheDoY = 0.0f;
    }
    else {
        tyLeX = static_cast<float>(kichThuocManHinh.x) / static_cast<float>(kichThuocGoc.x);
        tyLeY = tyLeX;
        cheDoX = 0.0f;
        cheDoY = (kichThuocManHinh.y - (kichThuocGoc.y * tyLeY)) / 2.0f;
    }

    tamNhinTroChoi.setSize(static_cast<float>(kichThuocGoc.x), static_cast<float>(kichThuocGoc.y));
    tamNhinTroChoi.setCenter(static_cast<float>(kichThuocGoc.x) / 2.0f, static_cast<float>(kichThuocGoc.y) / 2.0f);

    float khungNhinX = cheDoX / static_cast<float>(kichThuocManHinh.x);
    float khungNhinY = cheDoY / static_cast<float>(kichThuocManHinh.y);
    float chieuRongKhungNhin = (kichThuocGoc.x * tyLeX) / static_cast<float>(kichThuocManHinh.x);
    float chieuCaoKhungNhin = (kichThuocGoc.y * tyLeY) / static_cast<float>(kichThuocManHinh.y);

    tamNhinTroChoi.setViewport(sf::FloatRect(khungNhinX, khungNhinY, chieuRongKhungNhin, chieuCaoKhungNhin));

    cuaSo.setView(tamNhinTroChoi);
}

void TroChoi::capNhatTamNhin() {
    cuaSo.setView(tamNhinTroChoi);
}

sf::Vector2i TroChoi::layViTriChuotDaTyLe(const sf::Vector2i& viTriChuot) {
    float xDaTyLe = (viTriChuot.x - cheDoX) / tyLeX;
    float yDaTyLe = (viTriChuot.y - cheDoY) / tyLeY;

    xDaTyLe = std::max(0.0f, std::min(xDaTyLe, static_cast<float>(kichThuocGoc.x)));
    yDaTyLe = std::max(0.0f, std::min(yDaTyLe, static_cast<float>(kichThuocGoc.y)));

    return sf::Vector2i(static_cast<int>(xDaTyLe), static_cast<int>(yDaTyLe));
}

void TroChoi::chay() {
    nhacNen.setLoop(true);
    nhacNen.play();

    while (cuaSo.isOpen()) {
        xuLySuKien();
        capNhat();
        veHinh();
    }
}

void TroChoi::xuLySuKien() {
    sf::Event suKien;
    while (cuaSo.pollEvent(suKien)) {
        if (suKien.type == sf::Event::Closed) {
            cuaSo.close();
        }

        if (suKien.type == sf::Event::KeyPressed && suKien.key.code == sf::Keyboard::Escape) {
            if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
                cuaSo.close();
            }
        }

        if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
            if (suKien.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i viTriDaTyLe = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
                sf::Event suKienDaTyLe = suKien;
                suKienDaTyLe.mouseButton.x = viTriDaTyLe.x;
                suKienDaTyLe.mouseButton.y = viTriDaTyLe.y;
                GiaoDien.xuLySuKien(suKienDaTyLe, cuaSo);
            }
            else if (suKien.type == sf::Event::MouseMoved) {
                sf::Vector2i viTriDaTyLe = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
                sf::Event suKienDaTyLe = suKien;
                suKienDaTyLe.mouseMove.x = viTriDaTyLe.x;
                suKienDaTyLe.mouseMove.y = viTriDaTyLe.y;
                GiaoDien.xuLySuKien(suKienDaTyLe, cuaSo);
            }
            else {
                GiaoDien.xuLySuKien(suKien, cuaSo);
            }
        }
        else if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
            if (hienThiThang || hienThiThua) {
                if (suKien.type == sf::Event::KeyPressed) {
                    trangThaiTroChoi = TrangThaiTroChoi::MENU;
                    GiaoDien.datTrangThai(TrangThaiGiaoDien::MENU);
                    xoaTroChoi();
                    hienThiThang = false;
                    hienThiThua = false;
                    nhacNen.play();
                }
            }
            else {
                if (suKien.type == sf::Event::KeyPressed) {
                    if (suKien.key.code == sf::Keyboard::Escape) {
                        trangThaiTroChoi = TrangThaiTroChoi::MENU;
                        GiaoDien.datTrangThai(TrangThaiGiaoDien::MENU);
                        xoaTroChoi();
                    }
                    else if (suKien.key.code == sf::Keyboard::R) {
                        khoiTaoTroChoi();
                    }
                    else if (suKien.key.code == sf::Keyboard::U) {
                        if (banDoHienTai) {
                            banDoHienTai->luiBuoc();
                            cout << "Lui buoc! Con lai " << banDoHienTai->laySoBuoc() << " nuoc di." << endl;
                        }
                    }
                    else if (suKien.key.code == sf::Keyboard::T) {
                        if (banDoHienTai) {
                            bool daDichChuyen = banDoHienTai->thuDichChuyen();
                            if (daDichChuyen) {
                                phatAmThanhBuocDi();
                            }
                        }
                    }
                    else if (banDoHienTai) {
                        bool daDiChuyen = false;
                        if (suKien.key.code == sf::Keyboard::Up || suKien.key.code == sf::Keyboard::W) {
                            daDiChuyen = banDoHienTai->thuDiChuyenNguoiChoi(0, -1);
                        }
                        else if (suKien.key.code == sf::Keyboard::Down || suKien.key.code == sf::Keyboard::S) {
                            daDiChuyen = banDoHienTai->thuDiChuyenNguoiChoi(0, 1);
                        }
                        else if (suKien.key.code == sf::Keyboard::Left || suKien.key.code == sf::Keyboard::A) {
                            daDiChuyen = banDoHienTai->thuDiChuyenNguoiChoi(-1, 0);
                        }
                        else if (suKien.key.code == sf::Keyboard::Right || suKien.key.code == sf::Keyboard::D) {
                            daDiChuyen = banDoHienTai->thuDiChuyenNguoiChoi(1, 0);
                        }
                        else if (suKien.key.code == sf::Keyboard::H) {
                            if (banDoHienTai && !banDoHienTai->layTrangThaiTuDongGiai()) {
                                std::cout << "\nDang tim kiem loi giai bang BFS..." << std::endl;
                                if (banDoHienTai->timLoiGiaiBFS(200)) {
                                    banDoHienTai->batDauTuDongGiai();
                                }
                                else {
                                    std::cout << "Khong tim thay loi giai!" << std::endl;
                                }
                            }
                        }
                        else if (suKien.key.code == sf::Keyboard::J) {
                            if (banDoHienTai) {
                                banDoHienTai->dungTuDongGiai();
                                std::cout << "Da dung tu dong giai" << std::endl;
                            }
                        }

                        if (daDiChuyen) {
                            phatAmThanhBuocDi();
                        }
                    }
                }
            }
        }
    }
}

void TroChoi::phatAmThanhBuocDi() {
    amThanhBuocDi.play();
}

void TroChoi::capNhat() {
    float thoiGianDelta = dongHoDelta.restart().asSeconds();

    if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
        GiaoDien.capNhat();

        TrangThaiGiaoDien trangThaiThucDon = GiaoDien.layTrangThai();
        if (trangThaiThucDon == TrangThaiGiaoDien::DANG_CHOI) {
            trangThaiTroChoi = TrangThaiTroChoi::DANG_CHOI;
            khoiTaoTroChoi();
            if (banDoHienTai && banDoHienTai->layNguoiChoi()) {
                banDoHienTai->layNguoiChoi()->capNhat(thoiGianDelta);
            }
            hienThiThang = false;
            hienThiThua = false;
        }
        else if (trangThaiThucDon == TrangThaiGiaoDien::THOAT) {
            cuaSo.close();
        }
    }
    else if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
        if (banDoHienTai) {
            banDoHienTai->capNhatNen(thoiGianDelta);
        }

        if (banDoHienTai && banDoHienTai->layNguoiChoi()) {
            banDoHienTai->layNguoiChoi()->capNhat(thoiGianDelta);
        }

        if (banDoHienTai && banDoHienTai->layTrangThaiThua() && !hienThiThua) {
            hienThiThua = true;
            amThanhThua.play();
            nhacNen.stop();
            cout << "Thua cuoc! Nhan R de choi lai hoac ESC de quay lai Menu." << endl;
        }

        if (banDoHienTai && banDoHienTai->kiemTraThang() && !hienThiThang && !hienThiThua) {
            hienThiThang = true;
            amThanhChienThang.play();
            nhacNen.stop();
            cout << "Chuc mung! Ban da chien thang!" << endl;
        }

        if (banDoHienTai && banDoHienTai->layTrangThaiTuDongGiai()) {
            static sf::Clock dongHoTuDongGiai;
            if (dongHoTuDongGiai.getElapsedTime().asSeconds() >= 0.3f) {
                banDoHienTai->thucHienBuocGiai();
                dongHoTuDongGiai.restart();
            }
        }
    }
}

void TroChoi::veHinh() {
    cuaSo.clear(sf::Color::Black);
    capNhatTamNhin();

    if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
        GiaoDien.ve(cuaSo);
    }
    else if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
        if (banDoHienTai) {
            banDoHienTai->ve(cuaSo);

            if (hienThiThua) {
                sf::RectangleShape lop(sf::Vector2f(800, 800));
                lop.setFillColor(sf::Color(0, 0, 0, 180));
                cuaSo.draw(lop);

                cuaSo.draw(anhThua);

                sf::Font chuPhong;
                if (chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text huongDan;
                    huongDan.setFont(chuPhong);
                    huongDan.setString("Nhan R de choi lai | ESC de quay lai Menu");
                    huongDan.setCharacterSize(18);
                    huongDan.setFillColor(sf::Color::Red);
                    huongDan.setPosition(270, 765);
                    cuaSo.draw(huongDan);
                }
            }

            if (hienThiThang) {
                sf::RectangleShape lop(sf::Vector2f(800, 800));
                lop.setFillColor(sf::Color(0, 0, 0, 150));
                cuaSo.draw(lop);

                cuaSo.draw(anhThang);

                sf::Font chuPhong;
                if (chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text huongDan;
                    huongDan.setFont(chuPhong);
                    huongDan.setString("Nhan phim bat ky de quay lai Menu");
                    huongDan.setCharacterSize(18);
                    huongDan.setFillColor(sf::Color::Green);
                    huongDan.setPosition(280, 765);
                    cuaSo.draw(huongDan);
                }
            }
        }
    }

    cuaSo.display();
}

void TroChoi::khoiTaoTroChoi() {
    xoaTroChoi();

    int banDoChon = GiaoDien.layMapDaChon();
    if (banDoChon < 0) {
        banDoChon = 0;
    }

    std::string tenFileBanDo = "map" + std::to_string(banDoChon + 1) + ".txt";
    std::cout << "Dang tai ban do: " << tenFileBanDo << std::endl;

    banDoHienTai = new BanDo(tenFileBanDo, 32);
    std::cout << "Tro choi da duoc khoi tao voi " << tenFileBanDo << "!" << std::endl;
}

void TroChoi::xoaTroChoi() {
    if (banDoHienTai) {
        delete banDoHienTai;
        banDoHienTai = nullptr;
    }
}