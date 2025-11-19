#include "TroChoi.h"
#include <iostream>
using namespace std;

TroChoi::TroChoi() :
    cuaSo(sf::VideoMode::getDesktopMode(), "Sokoban", sf::Style::Fullscreen),
    banDoHienTai(nullptr),
    trangThaiTroChoi(TrangThaiTroChoi::MENU),
    trangThaiTruoc(TrangThaiTroChoi::MENU),
    hienThiThang(false),
    hienThiThua(false),
    kichThuocGoc(800, 800),
    tyLeX(1.0f),
    tyLeY(1.0f),
    cheDoX(0.0f),
    cheDoY(0.0f),
    nutPause(nullptr),
    nutGoiY(nullptr),
    lopPhuPause(nullptr),
    huongDan(nullptr),
    dangTuDongGiai(false) {

    cuaSo.setFramerateLimit(60);
    HoatHinh::tocDoHoatHinh = 0.1f;

    thieLapManHinhDay();

    // Load tài nguyên âm thanh
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

    // Load texture win/gameover
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

    // Load giao diện
    GiaoDien.taiTaiNguyen();

    // Khởi tạo UI
    khoiTaoUI();
}

TroChoi::~TroChoi() {
    xoaTroChoi();
    xoaUI();
}

void TroChoi::khoiTaoUI() {
    cout << "\n=== KHOI TAO UI ===" << endl;


    // Nút Pause (góc trên phải)
    nutPause = new NutUI();
    if (nutPause->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\pause_button.png")) {
        nutPause->datViTri(730, 10);  // Dịch sang phải và lên cao hơn
        nutPause->datKichThuoc(50, 50);  // Giảm từ 60x60 xuống 50x50
        cout << "Da tao nut Pause" << endl;
    }

    // Nút Gợi ý (bên trái nút pause - CHỈNH LẠI)
    nutGoiY = new NutUI();
    if (nutGoiY->taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\hint_button.png")) {
        nutGoiY->datViTri(665, 10);  // Cách nút pause 15px, cùng độ cao
        nutGoiY->datKichThuoc(50, 50);  // Cùng kích thước với nút pause
        cout << "Da tao nut Goi Y" << endl;
    }

    // Lớp phủ Pause
    lopPhuPause = new LopPhuPause();
    if (lopPhuPause->khoiTao(
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\pause_menu.png",
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\resume_button.png",
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\restart_button.png",
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\options_button.png",
        "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\exit_button.png"
    )) {
        cout << "Da tao Lop Phu Pause" << endl;
    }
    else {
        cerr << "Loi khoi tao lop phu pause!" << endl;
    }
    cout << "Hoan thanh khoi tao UI!" << endl;
}

void TroChoi::xoaUI() {
    if (nutPause) {
        delete nutPause;
        nutPause = nullptr;
    }
    if (nutGoiY) {
        delete nutGoiY;
        nutGoiY = nullptr;
    }
    if (lopPhuPause) {
        delete lopPhuPause;
        lopPhuPause = nullptr;
    }
    if (huongDan) {
        delete huongDan;
        huongDan = nullptr;
    }
}

void TroChoi::xuLyClickNutPause() {
    if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
        cout << "\n>>> MO PAUSE MENU <<<" << endl;
        trangThaiTroChoi = TrangThaiTroChoi::TAM_DUNG;
        if (lopPhuPause) {
            lopPhuPause->hienThi();
        }
        nhacNen.pause();
    }
}

void TroChoi::xuLyClickNutGoiY() {
    if (!gameController || trangThaiTroChoi != TrangThaiTroChoi::DANG_CHOI) {
        return;
    }

    if (dangTuDongGiai) {
        cout << "\nDang tu dong giai. Nhan phim J de dung." << endl;
        return;
    }

    cout << "\n=== BAT DAU TU DONG GIAI ===" << endl;
    cout << "Tim kiem loi giai voi BFS..." << endl;

    // ✅ THAY ĐỔI: Dùng gameController
    if (gameController->timLoiGiaiBFS(200)) {
        gameController->batDauTuDongGiai();
        dangTuDongGiai = true;
        cout << ">>> TIM THAY LOI GIAI! Dang tu dong chay..." << endl;
        cout << "Nhan phim J de dung." << endl;
    }
    else {
        cout << ">>> KHONG TIM THAY LOI GIAI!" << endl;
    }
}

void TroChoi::xuLyHanhDongPause(HanhDongPause hanhDong) {
    switch (hanhDong) {
    case HanhDongPause::TIEP_TUC:
        cout << ">>> TIEP TUC CHOI <<<" << endl;
        trangThaiTroChoi = TrangThaiTroChoi::DANG_CHOI;
        if (lopPhuPause) {
            lopPhuPause->an();
        }
        nhacNen.play();
        break;

    case HanhDongPause::CHOI_LAI:
        cout << ">>> CHOI LAI <<<" << endl;
        if (lopPhuPause) {
            lopPhuPause->an();
        }
        trangThaiTroChoi = TrangThaiTroChoi::DANG_CHOI;
        khoiTaoTroChoi();
        dangTuDongGiai = false;
        nhacNen.play();
        break;
    case HanhDongPause::THOAT:
        cout << ">>> TRO VE MENU <<<" << endl;
        if (lopPhuPause) {
            lopPhuPause->an();
        }
        trangThaiTroChoi = TrangThaiTroChoi::MENU;
        GiaoDien.datTrangThai(TrangThaiGiaoDien::MENU);
        xoaTroChoi();
        dangTuDongGiai = false;
        nhacNen.play();
        break;

    default:
        break;
    }
}

void TroChoi::veNutUI() {
    if (nutPause) {
        nutPause->ve(cuaSo);
    }
    if (nutGoiY) {
        nutGoiY->ve(cuaSo);
    }
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

        // Xử lý phím ESC
        if (suKien.type == sf::Event::KeyPressed && suKien.key.code == sf::Keyboard::Escape) {
            if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
                cuaSo.close();
            }
            else if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
                xuLyClickNutPause();
            }
            else if (trangThaiTroChoi == TrangThaiTroChoi::TAM_DUNG) {
                xuLyHanhDongPause(HanhDongPause::TIEP_TUC);
            }
        }

        else if (trangThaiTroChoi == TrangThaiTroChoi::TAM_DUNG) {
            if (suKien.type == sf::Event::MouseButtonPressed &&
                suKien.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2i viTriChuot = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));

                if (lopPhuPause) {
                    HanhDongPause hanhDong = lopPhuPause->kiemTraClick(viTriChuot);
                    if (hanhDong != HanhDongPause::KHONG) {
                        xuLyHanhDongPause(hanhDong);
                    }
                }
            }
        }
        else if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
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
            // Xử lý click vào UI buttons
            if (suKien.type == sf::Event::MouseButtonPressed &&
                suKien.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2i viTriChuot = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));

                if (nutPause && nutPause->kiemTraClick(viTriChuot)) {
                    xuLyClickNutPause();
                    continue;
                }

                if (nutGoiY && nutGoiY->kiemTraClick(viTriChuot)) {
                    xuLyClickNutGoiY();
                    continue;
                }
            }

            // Xử lý win/lose screen
            if (hienThiThang || hienThiThua) {
                if (suKien.type == sf::Event::KeyPressed) {
                    trangThaiTroChoi = TrangThaiTroChoi::MENU;
                    GiaoDien.datTrangThai(TrangThaiGiaoDien::MENU);
                    xoaTroChoi();
                    hienThiThang = false;
                    hienThiThua = false;
                    dangTuDongGiai = false;
                    nhacNen.play();
                }
            }
            else {
                // Xử lý phím điều khiển
                if (suKien.type == sf::Event::KeyPressed) {
                    if (suKien.key.code == sf::Keyboard::R) {
                        khoiTaoTroChoi();
                        dangTuDongGiai = false;
                    }
                    else if (suKien.key.code == sf::Keyboard::U) {
                        // ✅ THAY ĐỔI: Dùng gameController
                        if (gameController) {
                            gameController->undo();
                        }
                    }
                    else if (suKien.key.code == sf::Keyboard::J) {
                        // ✅ THAY ĐỔI: Dùng gameController
                        if (gameController && dangTuDongGiai) {
                            gameController->dungTuDongGiai();
                            dangTuDongGiai = false;
                            cout << "Da dung tu dong giai!" << endl;
                        }
                    }
                    else if (suKien.key.code == sf::Keyboard::T) {
                        // ✅ THAY ĐỔI: Dùng gameController
                        if (gameController) {
                            bool daDichChuyen = gameController->thucHienDichChuyen();
                            if (daDichChuyen) {
                                phatAmThanhBuocDi();
                            }
                        }
                    }
                    else if (suKien.key.code == sf::Keyboard::H) {
                        // ✅ THAY ĐỔI: Dùng gameController
                        if (gameController && !gameController->layTrangThaiTuDongGiai()) {
                            xuLyClickNutGoiY();
                        }
                    }
                    else if (gameController && !dangTuDongGiai) {
                        bool daDiChuyen = false;

                        // ✅ THAY ĐỔI: Dùng gameController->diChuyenNguoiChoi()
                        if (suKien.key.code == sf::Keyboard::Up || suKien.key.code == sf::Keyboard::W) {
                            daDiChuyen = gameController->diChuyenNguoiChoi(0, -1);
                        }
                        else if (suKien.key.code == sf::Keyboard::Down || suKien.key.code == sf::Keyboard::S) {
                            daDiChuyen = gameController->diChuyenNguoiChoi(0, 1);
                        }
                        else if (suKien.key.code == sf::Keyboard::Left || suKien.key.code == sf::Keyboard::A) {
                            daDiChuyen = gameController->diChuyenNguoiChoi(-1, 0);
                        }
                        else if (suKien.key.code == sf::Keyboard::Right || suKien.key.code == sf::Keyboard::D) {
                            daDiChuyen = gameController->diChuyenNguoiChoi(1, 0);
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
            dangTuDongGiai = false;
        }
        else if (trangThaiThucDon == TrangThaiGiaoDien::THOAT) {
            cuaSo.close();
        }
    }
    else if (trangThaiTroChoi == TrangThaiTroChoi::TAM_DUNG) {
        sf::Vector2i viTriChuot = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
        if (lopPhuPause) {
            lopPhuPause->capNhat(viTriChuot);
        }
    }
    else if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
        sf::Vector2i viTriChuot = layViTriChuotDaTyLe(sf::Mouse::getPosition(cuaSo));
        if (nutPause) {
            nutPause->capNhat(viTriChuot);
        }
        if (nutGoiY) {
            nutGoiY->capNhat(viTriChuot);
        }

        if (banDoHienTai && banDoHienTai->layNguoiChoi()) {
            banDoHienTai->layNguoiChoi()->capNhat(thoiGianDelta);
        }

        if (gameController && dangTuDongGiai) {
            if (gameController->layTrangThaiTuDongGiai()) {
                static sf::Clock dongHoTuDongGiai;
                if (dongHoTuDongGiai.getElapsedTime().asSeconds() >= 0.3f) {
                    bool thanhCong = gameController->thucHienBuocGiai();
                    if (!thanhCong) {
                        dangTuDongGiai = false;
                        cout << "Hoan thanh tu dong giai!" << endl;
                    }
                    dongHoTuDongGiai.restart();
                }
            }
            else {
                dangTuDongGiai = false;
            }
        }

        if (banDoHienTai && banDoHienTai->layTrangThaiThua() && !hienThiThua) {
            hienThiThua = true;
            amThanhThua.play();
            nhacNen.stop();
            dangTuDongGiai = false;
            cout << "Thua cuoc! Nhan phim bat ky de quay lai Menu." << endl;
        }

        if (gameController && gameController->kiemTraThang() && !hienThiThang && !hienThiThua) {
            hienThiThang = true;
            amThanhChienThang.play();
            nhacNen.stop();
            dangTuDongGiai = false;
            cout << "Chuc mung! Ban da chien thang!" << endl;
        }
    }
}

void TroChoi::veHinh() {
    cuaSo.clear(sf::Color::Black);
    capNhatTamNhin();

    if (trangThaiTroChoi == TrangThaiTroChoi::MENU) {
        GiaoDien.ve(cuaSo);
    }
    else if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI ||
        trangThaiTroChoi == TrangThaiTroChoi::TAM_DUNG) {
        if (banDoHienTai) {
            banDoHienTai->ve(cuaSo);

            // Vẽ UI buttons (chỉ khi đang chơi)
            if (trangThaiTroChoi == TrangThaiTroChoi::DANG_CHOI) {
                veNutUI();
            }

            // Vẽ màn hình thua
            if (hienThiThua) {
                sf::RectangleShape lop(sf::Vector2f(800, 800));
                lop.setFillColor(sf::Color(0, 0, 0, 180));
                cuaSo.draw(lop);
                cuaSo.draw(anhThua);

                sf::Font chuPhong;
                if (chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text huongDanText;
                    huongDanText.setFont(chuPhong);
                    huongDanText.setString("Nhan phim bat ky de quay lai Menu");
                    huongDanText.setCharacterSize(18);
                    huongDanText.setFillColor(sf::Color::Red);
                    huongDanText.setPosition(270, 765);
                    cuaSo.draw(huongDanText);
                }
            }

            // Vẽ màn hình thắng
            if (hienThiThang) {
                sf::RectangleShape lop(sf::Vector2f(800, 800));
                lop.setFillColor(sf::Color(0, 0, 0, 150));
                cuaSo.draw(lop);
                cuaSo.draw(anhThang);

                sf::Font chuPhong;
                if (chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text huongDanText;
                    huongDanText.setFont(chuPhong);
                    huongDanText.setString("Nhan phim bat ky de quay lai Menu");
                    huongDanText.setCharacterSize(18);
                    huongDanText.setFillColor(sf::Color::Green);
                    huongDanText.setPosition(280, 765);
                    cuaSo.draw(huongDanText);
                }
            }

            // Vẽ pause overlay
            if (trangThaiTroChoi == TrangThaiTroChoi::TAM_DUNG && lopPhuPause) {
                lopPhuPause->ve(cuaSo);
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
    gameController = new GameController(banDoHienTai);
    dangTuDongGiai = false;
    std::cout << "Tro choi da duoc khoi tao voi " << tenFileBanDo << "!" << std::endl;
}

void TroChoi::xoaTroChoi() {
    if (gameController) {
        delete gameController;
        gameController = nullptr;
    }
    if (banDoHienTai) {
        delete banDoHienTai;
        banDoHienTai = nullptr;
    }
}