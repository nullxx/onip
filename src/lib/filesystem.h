#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct saved_ip_st {
    const char *ip;
    int error;
};
int get_saved_ip(char *file_name, char *ip, size_t string_length);
int save_ip(char *dir, char *file_name, char *contents);