#include "display.h"

Display::Display(int16_t width, int16_t height, int8_t reset_pin, uint8_t address, int16_t SDA_pin, int16_t SCL_pin)
  : u8g2(U8G2_R0, reset_pin == -1 ? U8X8_PIN_NONE : reset_pin, SCL_pin, SDA_pin),
    SDA(SDA_pin), SCL(SCL_pin), screen_address(address), DISPLAY_WIDTH(width), DISPLAY_HEIGHT(height)
{
}

bool Display::startDisplay()
{
  delay(100);
  u8g2.begin();
  u8g2.setFont(u8g2_font_5x8_tf);
  
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, "Display Init...");
  u8g2.sendBuffer();
  
  delay(1000);
  return true;
}

void Display::setWhite()
{
  u8g2.clearBuffer();
  u8g2.drawBox(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  u8g2.sendBuffer();
}

void Display::setDisplayText(std::string text, int16_t x, int16_t y, float size)
{
  if (text.length() > 21) {
    text = text.substr(0, 21);
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawStr(x * 6, (y + 1) * 8, text.c_str());
  u8g2.sendBuffer();
}

void Display::setDisplayText(const char* text, int16_t x, int16_t y, float size)
{
  setDisplayText(std::string(text), x, y, size);
}

void Display::setDisplayText(int text, int16_t x, int16_t y, float size)
{
  setDisplayText(std::to_string(text), x, y, size);
}

void Display::setDisplayTextF(float text, int16_t x, int16_t y, float size)
{
  setDisplayText(std::to_string(text), x, y, size);
}

void Display::appendDisplayText(std::string text, int16_t x, int16_t y, float size)
{
  if (text.length() > 21) {
    text = text.substr(0, 21);
  }
  // Draws directly onto the back-buffer without wiping previous lines
  u8g2.drawStr(x * 6, (y + 1) * 8, text.c_str());
  u8g2.sendBuffer();
}

void Display::appendDisplayText(const char* text, int16_t x, int16_t y, float size)
{
  appendDisplayText(std::string(text), x, y, size);
}

void Display::appendDisplayText(int text, int16_t x, int16_t y, float size)
{
  appendDisplayText(std::to_string(text), x, y, size);
}

void Display::appendDisplayTextF(float text, int16_t x, int16_t y, float size)
{
  appendDisplayText(std::to_string(text), x, y, size);
}

void Display::clear()
{
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}
