// Project includes
#include "globals.hpp"
#include "state.hpp"
#include "power.hpp"
#include "networking.hpp"
#include "apiRequests.hpp"
#include "leds.hpp"

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("");
  Serial.println("Booted.");

  setupPower();
  setupNetworking();
  findServer();
  setupRequests();
  refreshState();
  setupLEDpins();
}

void loop()
{
  // animate
  refreshState();
}
