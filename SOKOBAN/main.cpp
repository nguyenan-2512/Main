#include <SFML/Graphics.hpp>
#include "TroChoi.h"
#include <iostream>

int main() {
    try {
        TroChoi troChoi;
        troChoi.chay();
    }
    catch (const std::exception& e) {
        std::cerr << "Loi: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}