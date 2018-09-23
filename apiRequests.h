#pragma once
#include <ESP8266HTTPClient.h>

#include "globals.h"
#include "secrets.h"
#include "power.h"
#include "parser.h"
#include "serializer.h"

void setupRequests();
ledx_config fetchConfig(int retries = 0);
