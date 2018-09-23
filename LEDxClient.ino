// Project includes
#include "globals.hpp"
#include "state.hpp"
#include "power.hpp"
#include "networking.hpp"
#include "apiRequests.hpp"

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
}

void loop()
{
  // animate
  refreshState();
}
