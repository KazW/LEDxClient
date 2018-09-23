#include "leds.h"

void setupLEDpins()
{
  int &pinCount = deviceConfig.pinCount;
  if (pinCount == 0 || pinCount > 10)
  {
    Serial.println("Configured pin count is 0 or greater than 10, going to sleep.");
    forceNapIf(true);
  }

  for (int i = 0; i < deviceConfig.pinCount; i++)
  {
    ledx_pin &pin = deviceConfig.pins[i];
    pin.leds = new Adafruit_NeoPixel(pin.ledCount, pin.pin, NEO_GBR);
    pin.leds->begin();
  }
}
