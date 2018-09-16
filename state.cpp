#include "state.hpp"

ledx_config deviceConfig;

const unsigned long configRefreshPeriod = 10 * 1000;
unsigned long lastRefreshMillis = 0;

unsigned long millisSinceRefresh()
{
  return millis() - lastRefreshMillis;
}

void refreshAnimation()
{
  Serial.println("Refreshing Animation...");
}

void refreshState()
{
  if (deviceConfig.configured && millisSinceRefresh() < configRefreshPeriod)
    return;

  Serial.println("Refreshing state...");
  deviceConfig = fetchConfig();
  deviceConfig.configured = true;
  lastRefreshMillis = millis();

  if (deviceConfig.pinCount == 0)
  {
    Serial.println("No pins configured, forcing sleep.");
    forceNapIf(true);
  }
  else if (!deviceConfig.poweredOn)
  {
    Serial.println("Configured to be off, forcing sleep.");
    forceNapIf(true);
  }

  refreshAnimation();
}
