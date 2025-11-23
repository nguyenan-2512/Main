#pragma once
#pragma once
#include <string>

class PathConfig {
public:
    static const std::string ROOT_PATH;

 
    static std::string getImagePath(const std::string& fileName) {
        return ROOT_PATH + "images\\" + fileName;
    }

    static std::string getSoundPath(const std::string& fileName) {
        return ROOT_PATH + fileName;
    }

    static std::string getMapPath(const std::string& fileName) {
        return fileName; // Map ? th? m?c g?c d? án
    }
    static const std::string FONT_PATH;
};

const std::string PathConfig::ROOT_PATH = "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\";
const std::string PathConfig::FONT_PATH = "C:\\Windows\\Fonts\\arial.ttf";