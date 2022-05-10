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

    const char *body_tmp = "New IP **%s**";
    const size_t body_tmp_len = strlen(body_tmp);
    size_t ip_len = strlen(ip);

    char body[body_tmp_len + ip_len + 1 - 2];

    sprintf(body, body_tmp, ip);

    /* build post data START */
    json_object_object_add(body_json, "title", json_object_new_string("Cluster IP updated"));
    json_object_object_add(body_json, "body", json_object_new_string(body));
    json_object_object_add(body_json, "category", json_object_new_string("cluster-ip"));
    json_object_object_add(body_json, "risk", json_object_new_string("success"));
    /* build post data END */

    char *authorization_header_tmp = "Authorization: Bearer %s";
    size_t authorization_header_tmp_len = strlen(authorization_header_tmp);
    size_t bearer_len = strlen(environment.SUPERALERT_BEARER_TOKEN);

    size_t authorization_header_len = authorization_header_tmp_len + bearer_len + 1 - 2;
    char authorization_header[authorization_header_len];
    sprintf(authorization_header, authorization_header_tmp, environment.SUPERALERT_BEARER_TOKEN);

    size_t key_len = strlen(environment.SUPERALERT_KEY);
    size_t url_len = strlen(SUPERALERT_BASE_URL) + strlen("?key=") + key_len + 1;
    char url[url_len];
    sprintf(url, SUPERALERT_BASE_URL "?key=%s", environment.SUPERALERT_KEY);

    char *plain_result = fetch(url, "POST", authorization_header, body_json);

    if (plain_result == NULL) {
        log_error("Something wrong in fetch call to superalert");
        notify_response.error = 1;
        return notify_response;
    }

    enum json_tokener_error jerr = json_tokener_success;
    json_object *response = json_tokener_parse_verbose(plain_result, &jerr);

    int code = (int)json_object_get_int(json_object_object_get(response, "code"));
    const char *msg = json_object_get_string(json_object_object_get(response, "msg"));

    notify_response.code = code;
    notify_response.msg = msg;
    notify_response.error = 0;

    json_object_put(body_json);
    json_object_put(response);

    free(plain_result);
    return notify_response;
}
