#include "filesystem.h"

#include "logger.h"
#include "utils.h"

#ifdef _WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

int get_saved_ip(char *file_name, char *ip, size_t string_length) {
    FILE *fp;
    fp = fopen(file_name, "r");

    if (fp == NULL) {
        return -1;
    }

    fgets(ip, string_length, fp);
    fclose(fp);
    return 0;
}
int save_ip(char *dir, char *file_name, char *contents) {
    char *full_path = malloc(100);
    sprintf(full_path, "%s%s%s", dir, PATH_SEP, file_name);

    struct saved_ip_st saved_ip;

    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        int r = mkdir(dir, 0700);
        log_debug("Created directory result code %d", r);
    }

    FILE *fp;
    fp = fopen(full_path, "w");
    if (fp == NULL) {
        return -1;
    }

    fputs(contents, fp);
    fclose(fp);
    free(full_path);
    return 0;
}