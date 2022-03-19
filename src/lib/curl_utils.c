#include "curl_utils.h"

#include "logger.h"

size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct curl_fetch_st *p = (struct curl_fetch_st *)userp;

    char *temp = realloc(p->payload, p->size + realsize + 1);

    if (temp == NULL) {
        log_error("Failed to expand buffer in curl_callback");
        /* free buffer */
        free(p->payload);
        /* return */
        return CURL_EXPAND_BUFFER_ERR;
    }

    p->payload = temp;

    memcpy(&(p->payload[p->size]), contents, realsize);

    p->size += realsize;
    p->payload[p->size] = 0;
    return realsize;
}

CURLcode curl_fetch_url(CURL *ch, const char *url, struct curl_fetch_st *fetch) {
    CURLcode rcode;

    /* init payload */
    fetch->payload = (char *)calloc(1, sizeof(*fetch->payload));

    if (fetch->payload == NULL) {
        /* log error */
        log_error("Failed to allocate payload in curl_fetch_url");
        /* return error */
        return CURLE_FAILED_INIT;
    }

    fetch->size = 0;

    curl_easy_setopt(ch, CURLOPT_URL, url);
    curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(ch, CURLOPT_WRITEDATA, (void *)fetch);
    curl_easy_setopt(ch, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(ch, CURLOPT_TIMEOUT, 15);
    curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);
    rcode = curl_easy_perform(ch);

    return rcode;
}
