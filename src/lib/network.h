#pragma once

#include <json-c/json.h>
#include <unistd.h>

#include "curl_utils.h"
#include "logger.h"

char* fetch(char *url, char *method, char *auth_header, json_object *body);