#include <iostream>
#include <libconfig.h++>
#include "Layout.hpp"

int main()
{
    Layout::Layout layout;

    try {
        layout.load("example.layout");
        while (true) {
            layout.draw();
        }
        std::cout << "Layout Engine" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
