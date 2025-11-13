#include "HuongDan.h"
#include <iostream>

HuongDan::HuongDan()
    : trangHienTai(0), tongSoTrang(0)
{
    quayLaiThucDon = false;

    // Thiết lập nút Trước (nút trái)
    nutTruoc.setRadius(37.f);
    nutTruoc.setOrigin(37.f, 37.f);
    nutTruoc.setPosition(77.f, 63.f);
    nutTruoc.setFillColor(sf::Color(255, 255, 0, 80));    // Vàng hơi trong suốt
    nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 255)); // Viền vàng đậm
    nutTruoc.setOutlineThickness(3.f);

    // Thiết lập nút Sau (nút phải)
    nutSau.setRadius(35.f);
    nutSau.setOrigin(35.f, 35.f);
    nutSau.setPosition(713.f, 58.f);
    nutSau.setFillColor(sf::Color(255, 255, 0, 80));
    nutSau.setOutlineColor(sf::Color(255, 255, 0, 255));
    nutSau.setOutlineThickness(3.f);
}

bool HuongDan::taiTaiNguyen() {
    // Dọn sạch dữ liệu cũ
    cacKetCauTrang.clear();
    cacAnhTrang.clear();
    tongSoTrang = 0;

    // Danh sách đường dẫn các ảnh slide
    DynamicArray<std::string> cacSlide;
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide1.5.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide2.11.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide3.1.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide4.1.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide5.1.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide6.1.png");

    // Load từng ảnh slide
    for (int i = 0; i < cacSlide.size(); ++i) {
        sf::Texture* ketCau = new sf::Texture();
        if (!ketCau->loadFromFile(cacSlide[i])) {
            std::cerr << "Khong load duoc anh: " << cacSlide[i] << std::endl;
            delete ketCau;
            continue;
        }

        std::cout << "Da load anh " << cacSlide[i] << std::endl;
        cacKetCauTrang.push_back(ketCau);

        // Tạo sprite từ texture
        sf::Sprite sprite;
        sprite.setTexture(*ketCau);
        sprite.setPosition(0.f, 0.f);
        cacAnhTrang.push_back(sprite);
    }

    tongSoTrang = cacAnhTrang.size();

    if (tongSoTrang == 0) {
        std::cerr << "Khong co slide nao load duoc!" << std::endl;
        return false;
    }

    std::cout << "Tong so slide: " << tongSoTrang << std::endl;
    return true;
}

void HuongDan::datLai() {
    trangHienTai = 0;
}

bool HuongDan::chuotDeLenNut(const sf::CircleShape& nut, sf::Vector2i viTriChuot) {
    sf::Vector2f viTriNut = nut.getPosition();
    float dx = viTriChuot.x - viTriNut.x;
    float dy = viTriChuot.y - viTriNut.y;
    return (dx * dx + dy * dy <= nut.getRadius() * nut.getRadius());
}

void HuongDan::xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo) {
    // Xử lý click chuột
    if (suKien.type == sf::Event::MouseButtonPressed &&
        suKien.mouseButton.button == sf::Mouse::Left) {

        // Sử dụng tọa độ đã được scale từ event
        sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);

        // Xử lý click nút Trước
        if (chuotDeLenNut(nutTruoc, viTriChuot)) {
            if (trangHienTai == 0) {
                // Nếu đang ở trang đầu → quay lại menu
                quayLaiThucDon = true;
                std::cout << "HuongDan: Quay lai menu" << std::endl;
            }
            else {
                // Chuyển về trang trước
                trangHienTai--;
            }
        }

        // Xử lý click nút Sau
        if (chuotDeLenNut(nutSau, viTriChuot) && trangHienTai < tongSoTrang - 1) {
            trangHienTai++;
        }
    }

    // Xử lý di chuyển chuột (hover effect)
    if (suKien.type == sf::Event::MouseMoved) {
        sf::Vector2i viTriChuot(suKien.mouseMove.x, suKien.mouseMove.y);

        // === HOVER NÚT TRƯỚC ===
        if (chuotDeLenNut(nutTruoc, viTriChuot)) {
            if (trangHienTai == 0) {
                // Ở trang đầu: hiển thị màu đỏ (quay lại menu)
                nutTruoc.setOutlineColor(sf::Color(255, 120, 120, 255));
                nutTruoc.setFillColor(sf::Color(255, 0, 0, 160));
            }
            else {
                // Không ở trang đầu: hiển thị màu vàng sáng
                nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 255));
            }
        }
        else {
            // Không hover: trở về màu mặc định
            if (trangHienTai == 0) {
                nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 80));
                nutTruoc.setFillColor(sf::Color(255, 255, 0, 80));
            }
            else {
                nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 80));
            }
        }

        // === HOVER NÚT SAU ===
        if (chuotDeLenNut(nutSau, viTriChuot)) {
            nutSau.setOutlineColor(sf::Color(255, 255, 0, 255));
        }
        else {
            nutSau.setOutlineColor(sf::Color(255, 255, 0, 0));
        }
    }
}

void HuongDan::capNhat(float thoiGianDelta) {
    // Hiện tại không cần cập nhật gì
}

void HuongDan::ve(sf::RenderWindow& cuaSo) {
    if (tongSoTrang == 0) return;

    // Vẽ trang hiện tại
    cuaSo.draw(cacAnhTrang[trangHienTai]);

    // Vẽ nút Trước
    cuaSo.draw(nutTruoc);

    // Vẽ nút Sau (chỉ khi chưa đến trang cuối)
    if (trangHienTai < tongSoTrang - 1) {
        cuaSo.draw(nutSau);
    }
}