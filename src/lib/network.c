#include "network.h"

int fetch(char *url, char *method, char *auth_header, char *plain_result, json_object *body) {
    CURL *ch;
    CURLcode rcode;

    struct curl_fetch_st curl_fetch;
    struct curl_fetch_st *cf = &curl_fetch;
    struct curl_slist *headers = NULL;

    if ((ch = curl_easy_init()) == NULL) {
        log_error("Failed to create curl handle in fetch_session");
        return CURL_NO_HANDLE_ERR;
    }

    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "User-Agent: curl/7.16.3");

    if (auth_header != NULL && strlen(auth_header) > 0) {
        headers = curl_slist_append(headers, auth_header);
    }

    curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, method);
    curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch, CURLOPT_POSTFIELDS, json_object_to_json_string(body));

    rcode = curl_fetch_url(ch, url, cf);

    curl_easy_cleanup(ch);

    curl_slist_free_all(headers);

    if (rcode != CURLE_OK || cf->size < 1) {
        log_error("Failed to fetch url (%s) - curl said: %s", url, curl_easy_strerror(rcode));
        return CURL_FETCH_FAILED;
    }

    if (cf->payload != NULL) {
        strcpy(plain_result, cf->payload);
        free(cf->payload);
        return 0;
    } else {
        log_error("Failed to populate payload");
        free(cf->payload);
        return CURL_POPULATE_PAYLOAD_ERR;
    }
}
