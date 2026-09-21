#include <iostream>
#include <libconfig.h++>
#include <vector>
#include "Component.hpp"
#include "Layout.hpp"

int main()
{
    Layout::Layout layout;

    try {
        layout.load("example.layout");

        while (true) {
            layout.handleEvents();
            if (!layout.isOpen())
                break;

            layout.update();

            // if (event.type == Layout::Event::Type::KeyPressed && event.key == Layout::Event::Key::T) {
            //     std::vector<std::string> data = layout.getData("main", {"helloWorld"});
            //     if (!data.empty())
            //         std::cout << data.front() << std::endl;
            // }
            layout.draw();
        }
    } catch (const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
