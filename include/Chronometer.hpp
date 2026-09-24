/**
 * @file Chronometer.hpp
 * @brief Chronometer Class Header
 *
 * @author SkyReox
 * @date 2026-09-24
**/

#pragma once
#ifndef CHRONOMETER_HPP_
    #define CHRONOMETER_HPP_

    #include <chrono>

namespace Layout {

class Chronometer {
    std::chrono::steady_clock::time_point _start;

    public:
        Chronometer() : _start(std::chrono::steady_clock::now()) {}
        ~Chronometer() = default;

        std::chrono::milliseconds getElapsedTime() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->_start);
        }

        void reset()
        {
            this->_start = std::chrono::steady_clock::now();
        }
};

}

#endif /* CHRONOMETER_HPP_ */
