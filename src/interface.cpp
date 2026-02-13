#include "interface.h"
#include <string>

void Interface::draw() {
  while(loop) {
    //clear the window before rendering.
    renderer.clear();
    //get inputs from user.
    processInputs();
    initValues();

    drawClock();
    if(showStyleInfoTimer.timerDue()) {
      drawStyleInfo();
    }
    if(showArrowsTimer.timerDue()) {
      drawArrows();
    }
    if(showQuitTimer.timerDue()) drawQuitMessage();

    loopCount++;
    renderer.refresh();
    //redraw the window.
    napms(updateInterval);
  }
}
void Interface::initValues() {
  screenWidth = renderer.getWidth();
  screenHeight = renderer.getHeight();

  center = renderer.getCenter();

  if(screenHeight * xFactor < screenWidth)
  {
    clockRadius = screenHeight / 2 - 2;
  }
  else {
    clockRadius = int(float(screenWidth) / 2.0f /xFactor - 2.0f);
  }
}
void Interface::drawClock() {
  std::vector<std::string> symbols;
  std::vector<std::string> symbolsSecondary;
  float correction = 1.02f; // When using drawClockNumbers it works a bit differently than drawEllipse so the points arent on the ellipse scaling xFactor by 1.02 helps this.
  switch(style) {
    case Styles::Basic:
      symbols = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
      symbolsSecondary = {"/", "/", "-", "\\", "\\", "|", "/", "/", "-", "\\", "\\", "|"};
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      ellipseSymbol = L'█';
      drawClockBezel();
      drawClockNumbers(center, int(clockRadius * 0.99f), 48, ".", xFactor);
      drawClockNumbers(center, int(clockRadius * 0.99f), 12, symbolsSecondary, xFactor);
      drawClockNumbers(center, int(clockRadius * 0.9f), 12, symbols, xFactor);
      drawClockHands(clockRadius * 0.8f);
      break;
    case Styles::Word:
      symbols = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve"};
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      ellipseSymbol = L'█';
      drawClockBezel();
      drawClockNumbers(center, int(clockRadius * 0.9f), 12, symbols, xFactor);
      drawClockHands(clockRadius * 0.8f);
      break;
    case Styles::Floats:
      symbols = {"1.00", "1.25", "1.50", "1.75",
        "2.00", "2.25", "2.50", "2.75",
        "3.00", "3.25", "3.50", "3.75",
        "4.00", "4.25", "4.50", "4.75",
        "5.00", "5.25", "5.50", "5.75",
        "6.00", "6.25", "6.50", "6.75",
        "7.00", "7.25", "7.50", "7.75",
        "8.00", "8.25", "8.50", "8.75",
        "9.00", "9.25", "9.50", "9.75",
        "10.00", "10.25", "10.50", "10.75",
        "11.00", "11.25", "11.50", "11.75",
        "12.00", "12.25", "12.50", "12.75", };
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      ellipseSymbol = L'█';
      drawClockBezel();
      drawClockNumbers(center, int(clockRadius * 0.9f), 48, symbols, xFactor);
      drawClockHands(clockRadius * 0.8f);
      break;
    case Styles::Hybrid:
      symbols = {"1:00", "1:15", "1:30", "1:45",
        "2:00", "2:15", "2:30", "2:45",
        "3:00", "3:15", "3:30", "3:45",
        "4:00", "4:15", "4:30", "4:45",
        "5:00", "5:15", "5:30", "5:45",
        "6:00", "6:15", "6:30", "6:45",
        "7:00", "7:15", "7:30", "7:45",
        "8:00", "8:15", "8:30", "8:45",
        "9:00", "9:15", "9:30", "9:45",
        "10:00", "10:15", "10:30", "10:45",
        "11:00", "11:15", "11:30", "11:45",
        "12:00", "12:15", "12:30", "12:45", };
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      ellipseSymbol = L'█';
      drawClockBezel();
      drawClockNumbers(center, int(clockRadius * 0.9f), 48, symbols, xFactor);
      drawClockHands(clockRadius * 0.8f);
      break;
    case Styles::Minimal:
      symbols = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      drawClockNumbers(center, int(clockRadius), 12, symbols, xFactor);
      drawClockHands(clockRadius * 0.9f);
      break;
    case Styles::Minimaler:
      symbols = {"/", "/", "-", "\\", "\\", "|", "/", "/", "-", "\\", "\\", "|"};
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      drawClockNumbers(center, int(clockRadius), 12, symbols, xFactor);
      drawClockHands(clockRadius * 0.9f);
      break;
    case Styles::Minimalest:
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      centerSymbol = L'*';
      drawClockHands(clockRadius);
      break;
    case Styles::Skeleton:
      symbols = {"i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x", "xi", "xii"};
      minuteHandSymbol = L':';
      hourHandSymbol = L'#';
      ellipseSymbol = L'@';
      centerSymbol = L'*';
      drawBackground();
      drawClockBezel();
      drawClockNumbers(center, int(clockRadius * 0.9f), 12, symbols, xFactor);
      drawClockHands(clockRadius * 0.8f);
      drawClockNumbers(center, clockRadius, 12, "+", xFactor * correction);
      break;
    default:
      break;
  }
}
void Interface::drawQuitMessage() const {
  renderer.printStringAtBottomRight("Press q to quit.");
}
void Interface::drawStyleInfo() {
  //  Maybe I will switch it to a vector of theme objects with all the themes including the names
  std::string name;
  switch(style) {
    case Styles::Skeleton:
      name = "Skeleton";
      break;
    case Styles::Minimal:
      name = "Minimal";
      break;
    case Styles::Minimaler:
      name = "Minimaler";
      break;
    case Styles::Minimalest:
      name = "Minimalest";
      break;
    case Styles::Basic:
      name = "Basic";
      break;
    case Styles::Word:
      name = "Worded";
      break;
    case Styles::Floats:
      name = "Floats";
      break;
    case Styles::Hybrid:
      name = "Hybrid";
      break;
    default:
      name = "?";
      break;
  }
  styleInfoWindow.erase();
  styleInfoWindow.resize(getInfoRect(20, 5));
  renderer.putStringAt(&styleInfoWindow, name, renderer.getCenter(&styleInfoWindow), Shapes::Allignment::Center);
  box(styleInfoWindow.windowPointer, 0, 0);
  styleInfoWindow.refresh();
}
RectI Interface::getInfoRect(int width, int height) {
  Vec2 pos(screenWidth / 2, int(screenHeight * 0.85f));
  return RectI(RectI(pos - Vei2(width / 2, height / 2), pos + Vei2(width / 2, height / 2 + 1)));
}
void Interface::drawClockHands(int radius) {
  drawMinuteHand(radius);
  drawSecondHand(radius);
  drawHourHand(radius * 0.67f);
  renderer.putAt(centerSymbol, center);
}
void Interface::drawClockNumbers(Vei2 center, int radius, int segments, const std::vector<std::string>& symbols, float xFactor) const {
  float anglePerHour = 360.0f / segments;
  int nSymbols = symbols.size();
  for(int i = 0; i < segments; i++) {
    renderer.putStringAt(symbols[((i - 1 + segments) % segments) % nSymbols], Shapes::getLineAngleEndPosition(center, radius, anglePerHour * i - std::ceil(67.5f / anglePerHour) * anglePerHour, xFactor), Shapes::Allignment::Center);
  }
}
void Interface::drawClockNumbers(Vei2 center, int radius, int segments, const std::string& symbol, float xFactor) const {
  float anglePerHour = 360.0f / segments;
  for(int i = 0; i < segments; i++) {
    renderer.putStringAt(symbol, Shapes::getLineAngleEndPosition(center, radius, anglePerHour * i, xFactor), Shapes::Allignment::Center);
  }
}
void Interface::drawSecondHand(int radius) {
  renderer.drawLineSmoothAngle(center, radius, Shapes::getSecondHandAngle(clock.getSeconds()), xFactor);
}
void Interface::drawMinuteHand(int radius) {
  renderer.drawLineAngle(minuteHandSymbol, center, radius, Shapes::getMinuteHandAngle(clock.getMinutes(), clock.getSeconds()), xFactor);
}
void Interface::drawHourHand(int radius) {
  renderer.drawLineAngle(hourHandSymbol, center, radius, Shapes::getHourHandAngle(clock.getHours(), clock.getMinutes(), clock.getSeconds()), xFactor);
}
void Interface::drawClockBezel() const {
  renderer.drawEllipse(ellipseSymbol, center, clockRadius * xFactor, clockRadius);
}
void Interface::printTime() {
  std::ostringstream currentTime;

  currentTime << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds();

  renderer.putStringAt(currentTime.str(), center - Vei2(0, 5), Shapes::Allignment::Center); 
}
void Interface::drawBackground() {
  updateSurfaces();
  renderer.drawSurface(surfaces[0], Vei2(5, 5), RectI(Vei2(0, 0), Vei2(screenWidth - 1, screenHeight - 2)));
  renderer.drawSurface(surfaces[1], Vei2(35, 30), RectI(Vei2(0, 0), Vei2(screenWidth - 1, screenHeight - 2)));
  renderer.drawSurface(surfaces[2], Vei2(screenWidth - 10, screenHeight - 10), RectI(Vei2(0, 0), Vei2(screenWidth, screenHeight)));
}
void Interface::initSurfaces() {
  std::string filename;
  surfaces.clear();
  switch(style) {
    case Styles::Skeleton:
      filename = "gear.sch";

      surfaces.push_back(input.readSurface(filename));
      surfaces.push_back(input.readSurface(filename));

      surfaces.push_back(surfaces[1].getScaled(1.3f));
      break;
    default:
      break;
  }
}
void Interface::updateSurfaces() {
  surfaces[0].advance();
  if(loopCount % 2 == 0) {
    surfaces[1].advance();
  }
}
void Interface::drawArrows() {
  leftArrowSymbol = L'󰜱'; 
  rightArrowSymbol = L'󰜴';

  renderer.putAt(leftArrowSymbol, Vei2(2, renderer.getHeight() / 2));
  renderer.putAt(rightArrowSymbol, Vei2(renderer.getWidth() - 3, renderer.getHeight() / 2));
}
void Interface::cycleStyles(int n) {
  int options = static_cast<int>(Interface::Styles::Count);
  int styleNumber = static_cast<int>(style);

  styleNumber = (styleNumber + n + options) % options;
  while(styleNumber < 0) 
    styleNumber += options;
  style = static_cast<Interface::Styles>(styleNumber);
}
void Interface::processInputs() {
  switch(getch()) {
    case -1:  //  Nothing is pressed
      break;
    case 27:
    case 'q':
      loop = false;
      break;
    case 'h':
      showStyleInfoTimer.setTimer(2);
      cycleStyles(-1);
      initSurfaces();
      break;
    case 'l':
      showStyleInfoTimer.setTimer(2);
      cycleStyles(1);
      initSurfaces();
      break;
    case 'i':
      showStyleInfoTimer.setTimer(2);
      break;
    default:
      showQuitTimer.setTimer(2);
      break;
  }
}
void Interface::printTimezoneDescription(const Timezone& timezone, Vei2 pos) {
  renderer.putStringAt(timezone.abbreviation, pos, Shapes::Allignment::Left);
  renderer.putStringAt(timezone.fullname, pos + Vei2(timezone.abbreviation.size() + 2, 0), Shapes::Allignment::Left);
}
void Interface::setup() {
  float xFactor = 2.0f;
  bool loop = true;
  initValues();
  int radius;
  int selectedTimezone = 0;
  std::stringstream configFile;

  while(loop) {
    initValues();
    radius = clockRadius * 0.6f;
    renderer.clear();
    renderer.drawEllipse(L'#', center, radius * xFactor, radius);
    renderer.putStringAt("Calibrate until you see a perfect sphere.", center - Vei2(0, radius + 2), Shapes::Allignment::Center);
    renderer.putStringAt("(use j to increase and k to decrease)", center - Vei2(0, radius + 1), Shapes::Allignment::Center);
    renderer.printStringAtBottomRight("Press n to proceed.");
    renderer.refresh();
    switch(getch()) {
      case 'j':
        xFactor+=0.1f;
        break;
      case 'k':
        xFactor-=0.1f;
        break;
      case 'n':
        loop = false;
        break;
    }
  }
  xFactor = xFactor;
  configFile << "xFactor = " << xFactor << std::endl;
  renderer.clear();
  loop = true;
  std::vector<Timezone> timezones = Timezone::getTimezones();
  int nTimezones = timezones.size();
  Surface map = input.readSurface("map.sch");
  while(loop) {
    initValues();
    renderer.clear();
    if(screenWidth > 85 && screenHeight > 30) {
      radius = clockRadius * 0.6f;
      float ratio = (float(screenHeight - 10) - (float(screenHeight) / 2 - radius)) / float(map.getHeight());
      Surface resizedMap = map.getScaled(ratio);
      renderer.drawSurface(resizedMap, Vei2(screenWidth / 2, screenHeight / 2 - radius + resizedMap.getHeight() / 2), RectI(Vei2(0, 0), Vei2(screenWidth, screenHeight)));
      renderer.putStringAt("Choose your timezone.", center - Vei2(0, radius + 2), Shapes::Allignment::Center);
      renderer.putStringAt("(use j and k to list)", center - Vei2(0, radius + 1), Shapes::Allignment::Center);
      renderer.printStringAtBottomRight("Press n to proceed.");
      for(int index = -5; index <= 5; index++) {
        printTimezoneDescription(timezones[(selectedTimezone + index + nTimezones) % nTimezones], Vei2(3, screenHeight + index - 10));
        if(index == 0) {
          renderer.putAt(L'󰜴', Vei2(1, screenHeight - 10));
        }
      }
      switch(getch()) {
        case 'j':
          selectedTimezone++;
          if(selectedTimezone >= nTimezones) {
            selectedTimezone = 0;
          }
          renderer.clear();
          break;
        case 'k':
          selectedTimezone--;
          if(selectedTimezone < 0) {
            selectedTimezone = nTimezones - 1;
          }
          renderer.clear();
          break;
        case 'n':
          loop = false;
          break;
      }
    }
    else {
      renderer.printStringAtCenter("Window too small!");
    }
    renderer.refresh();
  }
  clock.setTimezone(timezones[selectedTimezone]);
  configFile << "timezone = " << selectedTimezone << std::endl;
  input.writeConfig(configFile.str());
}

