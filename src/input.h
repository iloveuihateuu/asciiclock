#pragma once

#include <string>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <filesystem>
#if defined(__APPLE__)
  #include <mach-o/dyld.h>
#elif defined(__linux__)
  #include <unistd.h> 
#endif

#include "surface.h"

class io {
  public:
    io()
    {}
    static bool writeFile(const std::string& data, const std::string& filename);
    static bool writeFile(const std::wstring& data, const std::string& filename);
    static bool fileExists(const std::string& filename);
    static bool readConfig(float& xFactor, int& selectedTimezone);

    static Surface readSurface(const std::string& filename);
};
