#include "cloudflare.h"

#include "environment.h"
#include "logger.h"
#include "network.h"

#define CLOUDFLARE_BASE_URL "https://api.cloudflare.com/client/v4/zones"

static struct environment_st environment;

static void initialize() { environment = get_environment(); }

int update_at_cloudflare(char ip[]) {
    log_debug("Updating ip at cloudflare...");
    if (environment.is_inited == false) {
        initialize();
    }

    json_object *json_body;
    enum json_tokener_error jerr = json_tokener_success;

    char url[200];
    sprintf(url, "%s/%s/dns_records/%s", CLOUDFLARE_BASE_URL, environment.CLOUDFLARE_ZONE_ID, environment.CLOUDFLARE_DNS_RECORD_ID);

    char authorization_header[200];
    sprintf(authorization_header, "Authorization: Bearer %s", environment.CLOUDFLARE_BEARER_TOKEN);

    /* Building POST DATA START */
    json_body = json_object_new_object();

    json_object *meta_json = json_object_new_object();
    json_object_object_add(meta_json, "auto_added", json_object_new_boolean(environment.CLOUDFLARE_RULE_AUTO_ADDED));
    json_object_object_add(meta_json, "managed_by_apps", json_object_new_boolean(environment.CLOUDFLARE_RULE_MANAGED_BY_APPS));
    json_object_object_add(meta_json, "managed_by_argo_tunnel", json_object_new_boolean(environment.CLOUDFLARE_RULE_MANAGED_BY_ARGO_TUNNEL));
    json_object_object_add(json_body, "meta", meta_json);

    json_object_object_add(json_body, "id", json_object_new_string(environment.CLOUDFLARE_DNS_RECORD_ID));
    json_object_object_add(json_body, "type", json_object_new_string(environment.CLOUDFLARE_RECORD_TYPE));
    json_object_object_add(json_body, "name", json_object_new_string(environment.CLOUDFLARE_RECORD_NAME));
    json_object_object_add(json_body, "content", json_object_new_string(ip));
    json_object_object_add(json_body, "proxiable", json_object_new_boolean(environment.CLOUDFLARE_RULE_PROXIABLE));
    json_object_object_add(json_body, "proxied", json_object_new_boolean(environment.CLOUDFLARE_RULE_PROXIED));
    json_object_object_add(json_body, "ttl", json_object_new_int(environment.CLOUDFLARE_RULE_TTL));
    json_object_object_add(json_body, "locked", json_object_new_boolean(environment.CLOUDFLARE_RULE_LOCKED));
    json_object_object_add(json_body, "zone_id", json_object_new_string(environment.CLOUDFLARE_ZONE_ID));
    json_object_object_add(json_body, "zone_name", json_object_new_string(environment.CLOUDFLARE_ZONE_NAME));
    /* Building POST DATA END */

    char plain_result[100];
    int ret_call = fetch(url, "PUT", authorization_header, plain_result, json_body);

    if (ret_call != 0) {
        log_error("Something wrong in fetch call to cloudflare");
        return ret_call;
    }

    json_object *result = json_tokener_parse_verbose(plain_result, &jerr);

    json_bool success = json_object_get_boolean(json_object_object_get(result, "success"));

    if (success == true) {
        return 0;
    } else {
        return 1;
    }

    json_object_put(json_body);
    json_object_put(result);

    return success;
}
