#include "input.h"
bool Input::openFile(const std::string& newFilename) {
  filename = newFilename;
  stream.close();
  stream.open(filename);
  return stream.is_open();
}
const std::string Input::getFilename() {
  return filename;
}
std::wifstream& Input::read() {
  return stream;
}
std::wifstream& Input::read(const std::string& inFilename) {
  openFile(inFilename);

  return stream;
}
bool Input::readSurface(Surface& surface) {
  int width, height, frames;
  stream >> width >> height >> frames;
  surface.setFrames(frames);
  surface.resize(Vei2(width,height));  

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
  return stream.good();
}
