#include "interface.h"
#include <string>

void Interface::draw() {
  while(values.loop) {
    //clear the window before rendering.
    renderer.clear();
    drawClock();
    drawArrows();
    renderer.refresh();
    //redraw the window.
    napms(200);
  }
}
void Interface::initValues() {
  values.width = renderer.getWidth();
  values.height = renderer.getHeight();

  if(values.height * values.xFactor < values.width)
  {
    values.clockRadius = values.height / 2 - 2;
  }
  else {
    values.clockRadius = int(float(values.width) / 2.0f /values.xFactor - 2.0f);
  }

  //update values.center in case of screen resizing.
  values.center = Vei2(values.width / 2,values.height / 2);
}
void Interface::drawClock() {
  //get inputs from user.
  processInputs();
  
  initValues();

  //when a key that is not recognized pressed display the press q to quit message for 2 seconds
  if(values.showQuitTimer < values.clock.getTimestamp() - values.showQuitFor) {
    values.showQuit = false;
  }
  
  std::vector<std::string> symbols;
  switch(values.style) {
    case Styles::Basic:
      symbols = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
      values.minuteHandSymbol = L':';
      values.hourHandSymbol = L'#';
      values.ellipseSymbol = L'█';
      drawClockBezel();
      drawClockNumbers(values.center, int(values.clockRadius * 0.9f), symbols, values.xFactor);
      drawClockHands(values.clockRadius * 0.8f);
      break;
    case Styles::Word:
      symbols = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve"};
      values.minuteHandSymbol = L':';
      values.hourHandSymbol = L'#';
      values.ellipseSymbol = L'█';
      drawClockBezel();
      drawClockNumbers(values.center, int(values.clockRadius * 0.9f), symbols, values.xFactor);
      drawClockHands(values.clockRadius * 0.8f);
      break;
    case Styles::Minimal:
      symbols = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
      values.minuteHandSymbol = L':';
      values.hourHandSymbol = L'#';
      drawClockNumbers(values.center, int(values.clockRadius), symbols, values.xFactor);
      drawClockHands(values.clockRadius * 0.9f);
      break;
    case Styles::Minimalest:
      values.minuteHandSymbol = L':';
      values.hourHandSymbol = L'#';
      drawClockHands(values.clockRadius);
      break;
    case Styles::Skeleton:
      symbols = {"i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x", "xi", "xii"};
      values.minuteHandSymbol = L':';
      values.hourHandSymbol = L'#';
      values.ellipseSymbol = L'@';
      drawBackground();
      drawClockBezel();
      drawClockNumbers(values.center, int(values.clockRadius * 0.9f), symbols, values.xFactor);
      drawClockHands(values.clockRadius * 0.8f);
      break;
  }
  if(values.showQuit) renderer.printStringAtBottomRight("Press q to quit.");

  values.loopCount++;
}
void Interface::drawClockHands(int radius) {
  drawSecondHand(radius);
  drawMinuteHand(radius);
  drawHourHand(radius * 0.67f);
}
void Interface::drawClockNumbers(Vei2 center, int radius, std::vector<std::string> numberSymbols, float xFactor) const {
  float anglePerHour = 30.0f;
  for(int i = 0; i < 12; i++) {
    int hour = i + 3;
    if(hour > 12) hour -= 12;
    renderer.putStringAt(numberSymbols[hour - 1], Shapes::getLineAngleEndPosition(center, radius, anglePerHour * i, xFactor), Shapes::Allignment::Center);
  }
}
void Interface::drawSecondHand(int radius) {
  renderer.drawLineSmoothAngle(values.center, radius, Shapes::getSecondHandAngle(values.clock.getSeconds()), values.xFactor);
}
void Interface::drawMinuteHand(int radius) {
  renderer.drawLineAngle(values.minuteHandSymbol, values.center, radius, Shapes::getMinuteHandAngle(values.clock.getMinutes(), values.clock.getSeconds()), values.xFactor);
}
void Interface::drawHourHand(int radius) {
  renderer.drawLineAngle(values.hourHandSymbol, values.center, radius, Shapes::getHourHandAngle(values.clock.getHours(), values.clock.getMinutes(), values.clock.getSeconds()), values.xFactor);
}
void Interface::drawClockBezel() {
  renderer.drawEllipse(values.ellipseSymbol, values.center, values.clockRadius * values.xFactor, values.clockRadius);
}
void Interface::printTime() {
  std::ostringstream currentTime;

  currentTime << values.clock.getHours() << ":" << values.clock.getMinutes() << ":" << values.clock.getSeconds();

  renderer.putStringAt(currentTime.str(), values.center - Vei2(0, 5), Shapes::Allignment::Center); 
}
void Interface::drawBackground() {
  updateSurfaces();
  renderer.drawSurface(surfaces[0], Vei2(5, 5), RectI(Vei2(0, 0), Vei2(values.width - 1, values.height - 2)));
  renderer.drawSurface(surfaces[1], Vei2(35, 30), RectI(Vei2(0, 0), Vei2(values.width - 1, values.height - 2)));
  renderer.drawSurface(surfaces[2], Vei2(values.width - 10, values.height - 10), RectI(Vei2(0, 0), Vei2(values.width, values.height)));
}
void Interface::initSurfaces() {
  std::string filename;
  surfaces.clear();
  switch(values.style) {
    case Styles::Skeleton:
      filename = "art/gear.sch";

      surfaces.push_back(values.input.readSurface(filename));
      surfaces.push_back(values.input.readSurface(filename));

      surfaces.push_back(surfaces[1].getScaled(1.3f));
      break;
    case Styles::Minimal:
    case Styles::Minimalest:
    case Styles::Basic:
    case Styles::Word:
      break;
  }
}
void Interface::updateSurfaces() {
  surfaces[0].advance();
  if(values.loopCount % 2 == 0) {
    surfaces[1].advance();
  }
}
void Interface::drawArrows() {
  values.leftArrowSymbol = L'󰜱'; 
  values.rightArrowSymbol = L'󰜴';

  renderer.putAt(values.leftArrowSymbol, Vei2(2, renderer.getHeight() / 2));
  renderer.putAt(values.rightArrowSymbol, Vei2(renderer.getWidth() - 3, renderer.getHeight() / 2));
}
void Interface::cycleStyles() {
  switch(values.style) {
    case Styles::Basic:
      values.style = Styles::Word;
      break;
    case Styles::Word:
      values.style = Styles::Minimal;
      break;
    case Styles::Minimal:
      values.style = Styles::Minimalest;
      break;
    case Styles::Minimalest:
      values.style = Styles::Skeleton;
      break;
    case Styles::Skeleton:
      values.style = Styles::Basic;
      break;
  }
}
void Interface::processInputs() {
  switch(getch()) {
    case 'q':
      values.loop = false;
      break;
    case 'n':
      cycleStyles();
      initSurfaces();
    case -1:
      break;
    default:
      values.showQuitTimer = values.clock.getTimestamp();
      values.showQuit = true;
      break;
  }
}
void Interface::printTimezoneDescription(Timezone timezone, Vei2 pos) {
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
    radius = values.clockRadius * 0.6f;
    renderer.clear();
    renderer.drawEllipse(L'#', values.center, radius * xFactor, radius);
    renderer.putStringAt("Calibrate until you see a perfect sphere.", values.center - Vei2(0, radius + 2), Shapes::Allignment::Center);
    renderer.putStringAt("(use j to increase and k to decrease)", values.center - Vei2(0, radius + 1), Shapes::Allignment::Center);
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
  values.xFactor = xFactor;
  configFile << "xFactor = " << xFactor << std::endl;
  renderer.clear();
  loop = true;
  std::vector<Timezone> timezones = Timezone::getTimezones();
  int nTimezones = timezones.size();
  Surface map = values.input.readSurface("art/map.sch");
  while(loop) {
    initValues();
    renderer.clear();
    if(values.width > 85 && values.height > 30) {
    radius = values.clockRadius * 0.6f;
    float ratio = (float(values.height - 10) - (float(values.height) / 2 - radius)) / float(map.getHeight());

    Surface resizedMap = map.getScaled(ratio);
    renderer.drawSurface(resizedMap, Vei2(values.width / 2, values.height / 2 - radius + resizedMap.getHeight() / 2), RectI(Vei2(0, 0), Vei2(values.width, values.height)));
    renderer.putStringAt("Choose your timezone.", values.center - Vei2(0, radius + 2), Shapes::Allignment::Center);
    renderer.putStringAt("(use j and k to list)", values.center - Vei2(0, radius + 1), Shapes::Allignment::Center);
    renderer.printStringAtBottomRight("Press n to proceed.");
    for(int index = -5; index <= 5; index++) {
      printTimezoneDescription(timezones[(selectedTimezone + index + nTimezones) % nTimezones], Vei2(3, values.height + index - 10));
      if(index == 0) {
        renderer.putAt(L'󰜴', Vei2(1, values.height - 10));
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
  values.clock.setTimezone(timezones[selectedTimezone]);
  configFile << "timezone = " << selectedTimezone << std::endl;
  values.input.writeFile(configFile.str(), "config");
}

