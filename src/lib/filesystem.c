#include "filesystem.h"

#include "logger.h"
#include "utils.h"

#ifdef _WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

char* get_saved_ip(char *file_name) {
    FILE *fp;
    fp = fopen(file_name, "r");

    char buffer[10];
    char *input = 0;
    size_t cur_len = 0;
    while (fgets(buffer, sizeof(buffer), fp) != 0) {
        size_t buf_len = strlen(buffer);
        char *extra = realloc(input, buf_len + cur_len + 1);
        if (extra == 0) break;
        input = extra;
        strcpy(input + cur_len, buffer);
        cur_len += buf_len;
    }
    fclose(fp);
    return input;
}
int save_ip(char *dir, char *file_name, char *contents) {
    const size_t dir_len = strlen(dir);
    const size_t file_name_len = strlen(file_name);
    const size_t path_sep = strlen(PATH_SEP);
    const size_t full_path_len = dir_len + file_name_len + path_sep;

    char *full_path = malloc(sizeof(char) * full_path_len);
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