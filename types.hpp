#pragma once

typedef struct LEDxPin ledx_pin;
struct LEDxPin
{
  const char *name;
  int pin;
  int ledCount;
};

typedef struct LEDxConfig ledx_config;
struct LEDxConfig
{
  bool configured;
  const char *name;
  bool poweredOn;
  int pinCount;
  ledx_pin pins[10];
};
