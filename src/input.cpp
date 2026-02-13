#include "input.h"

Surface io::readSurface(const std::string& filename) {
  std::filesystem::path path = getSurfacesPath() / filename;
  std::wifstream stream(path);
  if(!stream) {
    std::cerr << "Couldn't open " << filename << " (surface)." << std::endl;
    return Surface();
  }
  stream.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
  int width, height, frames;
  stream >> width >> height >> frames;
  Surface surface{width, height, frames};
    
  std::wstring line;

  stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for(int frame = 1; frame < frames + 1; frame++)
  {
    for(int y = 0; y < height; y++) {
      std::getline(stream, line);

      if(line.size() < width) {
        line.resize(width, L' ');
      }
      for(int x = 0; x < width; x++) {
        surface.putAt(line[x], Vei2(x,y), frame);
      }
    }
  }
  return surface;
}
bool io::readConfig(float& xFactor, int& updateInterval, int& selectedTimezone) {
  std::wifstream stream(getConfigPath());
  std::wstring name;
  wchar_t symbol;
  float value;
  while(stream >> name >> symbol >> value) {
    if(symbol == L'=') {
      if(name == L"xFactor") {
        xFactor = value;
      }
      if(name == L"timezone") {
        selectedTimezone = value;
      } 
      if(name == L"updateInterval") {
        updateInterval = value;
      } 
    }
  }
  bool state = stream.good();
  stream.close();
  return state;
}
bool io::writeConfig(const std::string& data) {
  return writeFile(data, getConfigPath());
};
bool io::fileExists(const std::filesystem::path path) {
  std::ifstream stream(path);
  return stream.good();
}
bool io::fileExists(const std::string& filename) {
  std::ifstream stream(filename);
  return stream.good();
}
bool io::writeFile(const std::string& data, const std::string& filename) {
  std::ofstream output;
  output.open(filename);
  output << data;
  output.close();
  return output.good();
}
bool io::writeFile(const std::wstring& data, const std::string& filename) {
  std::wofstream output;
  output.open(filename);
  output << data;
  output.close();
  return output.good();
}
bool io::writeFile(const std::string& data, const std::filesystem::path path) {
  std::ofstream output;
  output.open(path);
  output << data;
  output.close();
  return output.good();
}
bool io::writeFile(const std::wstring& data, const std::filesystem::path path) {
  std::wofstream output;
  output.open(path);
  output << data;
  output.close();
  return output.good();
}
std::filesystem::path io::getConfigPath() {
  std::string home = std::getenv("HOME");
#if defined(__APPLE__)
  std::string pathString = home + "/Library/Application Support/asciiclock/asciiclock.cfg";
#elif defined(__linux__)
  std::string pathString = home + "/.config/asciiclock/asciiclock.cfg";
#endif
  std::filesystem::path path(pathString);
  return path;
}
std::filesystem::path io::getSurfacesPath() {
  std::string home = std::getenv("HOME");
#if defined(__APPLE__)
  std::string pathString = home + "/Library/Application Support/asciiclock/dependencies/art/";
#elif defined(__linux__)
  std::string pathString = home + "/.local/share/asciiclock/dependencies/art/";
#endif
  std::filesystem::path path(pathString);
  return path;
}
