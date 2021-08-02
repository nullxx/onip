#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"

#define FETCH_IP_URL "http://ident.me"

int get_ip(char* ip);
void split(char* str, char* sep, char* arr[]);