#include "utils.h"

int get_ip(char* ip) { return fetch(FETCH_IP_URL, "GET", NULL, ip, NULL); }

void split(char* str, char* sep, char* arr[]) {
    char* token;
    char* string;
    char* tofree;

    string = strdup(str);
    size_t i = 0;
    if (string != NULL) {
        tofree = string;

        while ((token = strsep(&string, sep)) != NULL) {
            arr[i] = malloc(sizeof(token));
            strcpy(arr[i++], token);
        }

        free(tofree);
    }
}
