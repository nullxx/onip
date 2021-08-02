#include "environment.h"

char *environment_arr[] = {"FULL_FILE_NAME",
                           "DIRECTORY",
                           "FILE_NAME",
                           "CLOUDFLARE_ZONE_ID",
                           "CLOUDFLARE_DNS_RECORD_ID",
                           "CLOUDFLARE_BEARER_TOKEN",
                           "CLOUDFLARE_RECORD_TYPE",
                           "CLOUDFLARE_RECORD_NAME",
                           "CLOUDFLARE_ZONE_NAME",
                           "CLOUDFLARE_RULE_PROXIABLE",
                           "SUPERALERT_BEARER_TOKEN"};
static struct environment_st environment;

struct environment_st get_environment() {
    if (environment.is_inited == false) {
        return load_environment();
    }

    return environment;
}

struct environment_st load_environment() {
    log_info("Loading environment variables");
    if (environment.is_inited == true) {
        log_warn("Environment was already loaded.");
    }

    const int arr_size = sizeof(environment_arr) / sizeof(environment_arr[0]);
    log_debug("Found %d environment variables", arr_size);

    size_t loaded_env_index = 0;
    for (size_t i = 0; i < arr_size; i++) {
        char *value = getenv(environment_arr[i]);
        if (value == NULL) {
            log_error("Environment variable not set: %s", environment_arr[i]);
            exit(1);
        }
        log_debug("Trying to load environment var %s", environment_arr[i]);
        if (strcmp(environment_arr[i], "FULL_FILE_NAME") == 0) {
            environment.FULL_FILE_NAME = malloc(1 + strlen(value));
            strcpy(environment.FULL_FILE_NAME, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "DIRECTORY") == 0) {
            environment.DIRECTORY = malloc(1 + strlen(value));
            strcpy(environment.DIRECTORY, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "FILE_NAME") == 0) {
            environment.FILE_NAME = malloc(1 + strlen(value));
            strcpy(environment.FILE_NAME, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_ZONE_ID") == 0) {
            environment.CLOUDFLARE_ZONE_ID = malloc(1 + strlen(value));
            strcpy(environment.CLOUDFLARE_ZONE_ID, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_DNS_RECORD_ID") == 0) {
            environment.CLOUDFLARE_DNS_RECORD_ID = malloc(1 + strlen(value));
            strcpy(environment.CLOUDFLARE_DNS_RECORD_ID, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_BEARER_TOKEN") == 0) {
            environment.CLOUDFLARE_BEARER_TOKEN = malloc(1 + strlen(value));
            strcpy(environment.CLOUDFLARE_BEARER_TOKEN, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "SUPERALERT_BEARER_TOKEN") == 0) {
            environment.SUPERALERT_BEARER_TOKEN = malloc(1 + strlen(value));
            strcpy(environment.SUPERALERT_BEARER_TOKEN, value);
            loaded_env_index++;

        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RECORD_TYPE") == 0) {
            environment.CLOUDFLARE_RECORD_TYPE = malloc(1 + strlen(value));
            strcpy(environment.CLOUDFLARE_RECORD_TYPE, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RECORD_NAME") == 0) {
            environment.CLOUDFLARE_RECORD_NAME = malloc(1 + strlen(value));
            strcpy(environment.CLOUDFLARE_RECORD_NAME, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_PROXIABLE") == 0) {
            environment.CLOUDFLARE_RULE_PROXIABLE = atoi(value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_PROXIED") == 0) {
            environment.CLOUDFLARE_RULE_PROXIED = atoi(value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_TTL") == 0) {
            environment.CLOUDFLARE_RULE_TTL = atoi(value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_LOCKED") == 0) {
            environment.CLOUDFLARE_RULE_LOCKED = atoi(value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_ZONE_NAME") == 0) {
            environment.CLOUDFLARE_ZONE_NAME = malloc(1 + strlen(value));
            strcpy(environment.CLOUDFLARE_ZONE_NAME, value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_AUTO_ADDED") == 0) {
            environment.CLOUDFLARE_RULE_AUTO_ADDED = atoi(value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_MANAGED_BY_APPS") == 0) {
            environment.CLOUDFLARE_RULE_MANAGED_BY_APPS = atoi(value);
            loaded_env_index++;
        } else if (strcmp(environment_arr[i], "CLOUDFLARE_RULE_MANAGED_BY_ARGO_TUNNEL") == 0) {
            environment.CLOUDFLARE_RULE_MANAGED_BY_ARGO_TUNNEL = atoi(value);
            loaded_env_index++;
        }
    }
    if (loaded_env_index > 0) {
        environment.is_inited = true;
    }

    log_debug("Loaded %d environment variables", loaded_env_index);
    return environment;
}
