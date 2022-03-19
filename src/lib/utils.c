#include "utils.h"

char* get_ip() { return fetch(FETCH_IP_URL, "GET", NULL, NULL); }

void split(char* str, char* sep, char* arr[]) {
    char* string;

    string = strdup(str);
    if (string != NULL) {
        size_t i = 0;
        char* token;
        char* tofree;
        tofree = string;

        while ((token = strsep(&string, sep)) != NULL) {
            arr[i] = malloc(sizeof(token));
            strcpy(arr[i++], token);
        }

        free(tofree);
    }
}
