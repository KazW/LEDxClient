#include "parser.h"

const size_t configBufferSize = JSON_ARRAY_SIZE(10) + JSON_OBJECT_SIZE(1) + 11 * JSON_OBJECT_SIZE(4) + 1770;

// Example payload
/*
  {
    "data": {
      "name": "Device 249",
      "hardware_id": 249,
      "powered_on": false,
      "pins": [
        {
          "pin": 1,
          "name": "B1",
          "led_count": 7,
          "id": "58599f09-4545-4877-b252-3e54075c0b25"
        },
        {
          "pin": 2,
          "name": "B2",
          "led_count": 7,
          "id": "f5dfba2a-bf54-4e8b-927c-7cd6fe2f62c8"
        },
        {
          "pin": 3,
          "name": "Q",
          "led_count": 6,
          "id": "4e525616-1f78-42b8-9fd7-8844146af9fe"
        }
      ]
    }
  }
*/
ledx_config parseConfig(char *configJson)
{
  ledx_config config;
  DynamicJsonBuffer jsonConfigBuffer(configBufferSize);
  JsonObject &data = jsonConfigBuffer.parseObject(configJson)["data"];
  JsonArray &pins = data["pins"];

  // Device config
  data["name"].printTo(config.name);
  config.poweredOn = data["powered_on"];
  config.lastUpdate = (long long)data["last_update"].as<long>();

  // Pin configuration
  config.pinCount = pins.size();
  for (int i = 0; i < pins.size(); ++i)
  {
    if (i == 10)
      break;
    ledx_pin pin;

    pins[i]["name"].printTo(pin.name);
    pin.pin = pins[i]["pin"];
    pin.ledCount = pins[i]["led_count"];

    config.pins[i] = pin;
  }

  return config;
}
