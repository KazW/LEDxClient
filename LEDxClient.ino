// Project includes
#include "globals.h"
#include "state.h"
#include "power.h"
#include "networking.h"
#include "apiRequests.h"

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
