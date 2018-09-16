#include "networking.hpp"

char ledxIp[24];
int ledxPort;
bool mdns = false;

void setupNetworking()
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Trying to connect to WiFi: ");
  Serial.println(WIFI_SSID);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }

  Serial.println(" Connected!");
  Serial.print("Device IP address: ");
  Serial.println(WiFi.localIP());

  if (mDNS())
  {
    Serial.println("Network ready.");
  }
  else
  {
    Serial.print("Connected to WiFi, ");
    Serial.print("but unable to start mDNS, ");
    Serial.println("going to sleep.");
    forceNapIf(true);
  }
}

void findServer()
{
  if (!mDNS())
    return;

  Serial.println("Locating LEDx Server via mDNS...");
  int n = MDNS.queryService("ledx", "tcp");

  if (n == 0)
  {
    Serial.println("No LEDx server found, sleeping.");
    forceNapIf(true);
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(MDNS.hostname(i));
      Serial.print(" (");
      Serial.print(MDNS.IP(i));
      Serial.print(":");
      Serial.print(MDNS.port(i));
      Serial.println(")");

      if (MDNS.hostname(i) == LEDX_HOST)
      {
        IPAddress ipAddr = MDNS.IP(i);
        sprintf(ledxIp, "%d.%d.%d.%d", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
        ledxPort = MDNS.port(i);
      }
    }

    if (ledxPort != 0)
    {
      Serial.print("Found LEDx server IP: ");
      Serial.println(ledxIp);
    }
    else
    {
      Serial.print("LEDx server(s) found, ");
      Serial.print("but did not match configuration, ");
      Serial.println("going to sleep.");
      forceNapIf(true);
    }
  }
}

bool mDNS()
{
  if (!mdns)
  {
    mdns = MDNS.begin(HOSTNAME);
    if (!mdns)
      Serial.println("mDNS responder error!");
  }
  return mdns;
}
