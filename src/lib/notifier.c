#include "notifier.h"

#define SUPERALERT_BASE_URL "https://alerter.nullx.me/notification"

static struct environment_st environment;

static void initialize() { environment = get_environment(); }

struct notify_response_st notify(char ip[]) {
    log_debug("Notifying...");

    if (environment.is_inited == false) {
        initialize();
    }

    struct notify_response_st notify_response = {-1, "", 1};

    json_object *body_json = json_object_new_object();
    char body[100];
    sprintf(body, "New IP **%s**", ip);

    /* build post data START */
    json_object_object_add(body_json, "title", json_object_new_string("Cluster IP updated"));
    json_object_object_add(body_json, "body", json_object_new_string(body));
    json_object_object_add(body_json, "category", json_object_new_string("cluster-ip"));
    json_object_object_add(body_json, "risk", json_object_new_string("success"));
    /* build post data END */

    char authorization_header[300];
    sprintf(authorization_header, "Authorization: Bearer %s", environment.SUPERALERT_BEARER_TOKEN);

    char plain_result[10];
    int ret_call = fetch(SUPERALERT_BASE_URL, "POST", authorization_header, plain_result, body_json);

    if (ret_call != 0) {
        log_error("Something wrong in fetch call to cloudflare");
        notify_response.error = ret_call;
        return notify_response;
    }

    enum json_tokener_error jerr = json_tokener_success;
    json_object *response = json_tokener_parse_verbose(plain_result, &jerr);

    int code = (int)json_object_get_int(json_object_object_get(response, "code"));
    const char *msg = json_object_get_string(json_object_object_get(response, "msg"));

    notify_response.code = code;
    notify_response.msg = msg;

    json_object_put(body_json);
    json_object_put(response);

    return notify_response;
}
