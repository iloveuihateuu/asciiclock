#pragma once

#include <string>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <filesystem>
#include <cstdlib>
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
  public:
    static bool fileExists(const std::string& filename);
    static bool fileExists(const std::filesystem::path path);

    static std::filesystem::path getConfigPath();
    static std::filesystem::path getSurfacesPath();

    static bool writeConfig(const std::string& data);
    static bool readConfig(float& xFactor, int& updateInterval, int& selectedTimezone);

    static Surface readSurface(const std::string& filename);
  private:
    static bool writeFile(const std::string& data, const std::string& filename);
    static bool writeFile(const std::wstring& data, const std::string& filename);
    static bool writeFile(const std::string& data, const std::filesystem::path path);
    static bool writeFile(const std::wstring& data, const std::filesystem::path path);
};
