#pragma once

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

struct curl_fetch_st {
    char *payload;
    size_t size;
};

enum curl_error { CURL_EXPAND_BUFFER_ERR = 1, CURL_NO_HANDLE_ERR = 2, CURL_FETCH_FAILED = 3, CURL_POPULATE_PAYLOAD_ERR = 4 };

size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp);
CURLcode curl_fetch_url(CURL *ch, const char *url, struct curl_fetch_st *fetch);
