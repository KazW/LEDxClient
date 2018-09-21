#pragma once

typedef struct LEDxPin ledx_pin;
struct LEDxPin
{
  char name[32];
  int pin;
  int ledCount;
  Adafruit_NeoPixel *leds;
};

typedef struct LEDxConfig ledx_config;
struct LEDxConfig
{
  bool configured;
  char name[32];
  bool poweredOn;
  int pinCount;
  unsigned long long lastUpdate;
  ledx_pin pins[10];
};

typedef struct LEDxPinFrame ledx_pin_frame;
struct LEDxPinFrame
{
  char pinName[32];
  int red;
  int green;
  int blue;
};

typedef struct LEDxFrame ledx_frame;
struct LEDxFrame
{
  char name[32];
  int durationMillis;
  ledx_pin_frame pinFrames[256];
};

typedef struct LEDxAnimation ledx_animation;
struct LEDxAnimation
{
  char name[32];
  int frameCount;
  unsigned long long lastUpdate;
  ledx_frame frames[100];
};
