#include "state.hpp"

ledx_config deviceConfig;

const int RefreshPeriod = 10 * 1000;
unsigned long lastConfigMillis = 0;
unsigned long lastAnimationMillis = 0;

unsigned long millisSinceConfig()
{
  return millis() - lastConfigMillis;
}

unsigned long millisSinceAnimation()
{
  return millis() - lastAnimationMillis;
}

void refreshAnimation(bool force = false)
{
  if (!force && millisSinceAnimation() < RefreshPeriod)
    return;
  Serial.println("Refreshing animation...");
  lastAnimationMillis = millis();
}

void refreshConfig()
{
  if (deviceConfig.configured && millisSinceConfig() < RefreshPeriod)
    return;

  Serial.println("Refreshing state...");
  ledx_config newDeviceConfig = fetchConfig();

  if (newDeviceConfig.pinCount == 0)
  {
    Serial.println("No pins configured, going to sleep.");
    forceNapIf(true);
  }
  else if (!newDeviceConfig.poweredOn)
  {
    Serial.println("Configured to be off, going to sleep.");
    forceNapIf(true);
  }

  if (newDeviceConfig.lastUpdate > deviceConfig.lastUpdate)
  {
    deviceConfig = newDeviceConfig;
    deviceConfig.configured = true;
    setupLEDpins();
    refreshAnimation(true);
  }

  lastConfigMillis = millis();
}

void refreshState()
{
  refreshConfig();
  refreshAnimation();
}
