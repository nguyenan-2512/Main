#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Lớp nút UI đơn giản - chỉ dùng ảnh và click chuột
class NutUI {
private:
    sf::Texture ketCau;
    sf::Sprite anhSprite;
    sf::FloatRect vungClick;
    bool dangHover;
    bool dangHienThi;

public:
    NutUI();
    ~NutUI();

    // Tải ảnh cho nút
    bool taiAnh(const std::string& duongDanAnh);
    
    // Đặt vị trí nút
    void datViTri(float x, float y);
    
    // Đặt kích thước (scale)
    void datKichThuoc(float rong, float cao);
    
    // Kiểm tra chuột có click vào nút không
    bool kiemTraClick(const sf::Vector2i& viTriChuot) const;
    
    // Kiểm tra chuột có hover trên nút không
    bool kiemTraHover(const sf::Vector2i& viTriChuot) const;
    
    // Cập nhật trạng thái hover
    void capNhat(const sf::Vector2i& viTriChuot);
    
    // Vẽ nút
    void ve(sf::RenderWindow& cuaSo);
    
    // Hiện/ẩn nút
    void hienThi() { dangHienThi = true; }
    void an() { dangHienThi = false; }
    bool coDangHienThi() const { return dangHienThi; }
    
    // Lấy vị trí và kích thước
    sf::Vector2f layViTri() const { return anhSprite.getPosition(); }
    sf::FloatRect layVungClick() const { return vungClick; }
};