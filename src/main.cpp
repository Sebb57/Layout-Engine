#include <iostream>
#include "Layout.hpp"

int main()
{
    Layout::Layout layout;
    layout.load("example.layout");
    std::cout << "Layout Engine" << std::endl;
    return 0;
}
