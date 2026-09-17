/**
 * @file DynamicLibrary.cpp
 * @brief Dynamic Library
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#include "DynamicLibrary.hpp"
#include <dlfcn.h>

DynamicLibrary::DynamicLibrary(const std::string& path) : _path(path)
{
    this->_handle = dlopen(path.c_str(), RTLD_NOW);
    if (!this->_handle)
        throw LibraryLoadFailed(path, dlerror());

    try {
        this->type = this->loadFunction<std::size_t (*)()>("type");
    } catch (const DynamicLibraryException& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

DynamicLibrary::~DynamicLibrary() noexcept
{
    dlclose(this->_handle);
}
