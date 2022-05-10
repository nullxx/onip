#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

struct environment_st {
    bool is_inited;
    char *FULL_FILE_NAME;
    char *DIRECTORY;
    char *FILE_NAME;

    char *CLOUDFLARE_ZONE_ID;
    char *CLOUDFLARE_DNS_RECORD_ID;
    char *CLOUDFLARE_BEARER_TOKEN;
    char *CLOUDFLARE_RECORD_TYPE;
    char *CLOUDFLARE_RECORD_NAME;
    int CLOUDFLARE_RULE_PROXIABLE;
    int CLOUDFLARE_RULE_PROXIED;
    int CLOUDFLARE_RULE_TTL;
    int CLOUDFLARE_RULE_LOCKED;
    char *CLOUDFLARE_ZONE_NAME;
    int CLOUDFLARE_RULE_AUTO_ADDED;
    int CLOUDFLARE_RULE_MANAGED_BY_APPS;
    int CLOUDFLARE_RULE_MANAGED_BY_ARGO_TUNNEL;
    char *SUPERALERT_BEARER_TOKEN;
    char *SUPERALERT_KEY;
    
};

struct environment_st load_environment();
struct environment_st get_environment();