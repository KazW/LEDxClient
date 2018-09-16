#pragma once
// Network libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "secrets.hpp" // Needs to be manually created
#include "globals.hpp"
#include "power.hpp"

void setupNetworking();
void findServer();
bool mDNS();
