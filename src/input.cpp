#include "input.h"

Surface io::readSurface(const std::string& filename) {
  std::wifstream stream(filename);
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
bool io::readConfig(float& xFactor, int& selectedTimezone) {
  std::wifstream stream("config");
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
      } }
  }
  bool state = stream.good();
  stream.close();
  return state;
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
