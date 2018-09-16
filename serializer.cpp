#include "serializer.hpp"

const size_t bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 124;

void createDeviceJson(char *outStr)
{
  char name[24];
  int hardwareId = ESP.getChipId();
  sprintf(name, "%s %d", HOSTNAME, hardwareId);

  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject &root = jsonBuffer.createObject();
  JsonObject &device = root.createNestedObject("device");
  device["name"] = name;
  device["hardware_id"] = hardwareId;

  root.printTo(outStr, 300);
}
