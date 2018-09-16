#include "apiRequests.hpp"

HTTPClient http;
const int maxRetries = 5;
const int retryDelay = 1000;

void setupRequests()
{
  http.setReuse(true);
}

void configURL(char *url)
{
  sprintf(url, "http://%s:%d/api/devices", ledxIp, ledxPort);
}

void addHeaders()
{
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");
}

ledx_config parseConfigPayload(String payloadStr)
{
  int payloadLnth = payloadStr.length() + 1;
  char *payload = new char[payloadLnth];
  payloadStr.toCharArray(payload, payloadLnth);
  return parseConfig(payload);
}

void sleepAfterRetries(int retry)
{
  forceNapIf(retry > maxRetries);
}

ledx_config createConfig(int retry = 0)
{
  sleepAfterRetries(retry);
  ledx_config config;
  char url[100];
  char body[200];
  configURL(url);
  createDeviceJson(body);

  http.begin(url);
  addHeaders();
  Serial.print("Attempting to create config at: ");
  Serial.println(url);
  Serial.print("Sending JSON: ");
  Serial.println(body);
  int httpCode = http.POST(body);

  if (httpCode == 201)
  {
    config = parseConfigPayload(http.getString());
  }
  else
  {
    Serial.print("HTTP status from config creation request: ");
    Serial.println(httpCode);
    http.end();
    delay(retry * retryDelay);
    Serial.println("Retrying...");
    config = createConfig(retry + 1);
  }

  http.end();
  return config;
}

ledx_config fetchConfig(int retry)
{
  sleepAfterRetries(retry);
  ledx_config config;
  char url[100];
  configURL(url);
  sprintf(url, "%s/%d", url, ESP.getChipId());
  Serial.print("Fetching config from: ");
  Serial.println(url);

  http.begin(url);
  addHeaders();
  int httpCode = http.GET();

  if (httpCode == 200)
  {
    config = parseConfigPayload(http.getString());
  }
  else if (httpCode == 404)
  {
    Serial.println("Missing config, attempting to create one.");
    http.end();
    return createConfig();
  }
  else
  {
    Serial.print("HTTP status from config request: ");
    Serial.println(httpCode);
    delay(retry * retryDelay);
    Serial.println("Retrying...");
    fetchConfig(retry + 1);
  }

  http.end();
  return config;
}
