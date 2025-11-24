#include <string>
#include <fstream>

#include "surface.h"

class Input {
  public:
    Input(std::string& inFilename)
      : filename(inFilename), stream(filename)
    {
      stream.imbue(std::locale("en_US.UTF-8"));
    }
    bool openFile(const std::string& newFilename);
    const std::string getFilename();
    std::wifstream& read();
    std::wifstream& read(const std::string& inFilename);
    bool readSurface(Surface& surface);
  private:
    std::string filename;
    std::wifstream stream;
};
