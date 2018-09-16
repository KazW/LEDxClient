#pragma once
#include <ESP8266HTTPClient.h>

#include "globals.hpp"
#include "secrets.hpp"
#include "power.hpp"
#include "parser.hpp"
#include "serializer.hpp"

void setupRequests();
ledx_config fetchConfig(int retries = 0);
