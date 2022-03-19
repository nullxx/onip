#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct saved_ip_st {
    const char *ip;
    int error;
};
char* get_saved_ip(char *file_name);
int save_ip(char *dir, char *file_name, char *contents);