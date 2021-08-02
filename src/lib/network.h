#pragma once

#include <json-c/json.h>
#include <unistd.h>

#include "curl_utils.h"
#include "logger.h"

int fetch(char *url, char *method, char *auth_header, char *plain_result, json_object *body);