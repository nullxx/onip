#pragma once

#include <json-c/json.h>

#include "curl_utils.h"
#include "environment.h"
#include "logger.h"
#include "utils.h"

struct notify_response_st {
    int code;
    const char *msg;
    int error;
};
struct notify_response_st notify(char ip[]);