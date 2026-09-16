#include <iostream>
#include "Layout.hpp"

int main()
{
    Layout::Layout layout;

    try {
        layout.load("example.layout");
        std::cout << "Layout Engine" << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
