// clogger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#define LOG_LEVEL -1
#define PRINT_VAR
#include "clogger.h"


int main(int argc, const char * argv[]) {

    _(LOG_DEBUG("Maybe i can touch this button...");)

    LOG_INFO("Pressure is dropping...");

    LOG_ERROR("Houston we have a problem!");

    int going_down = 1;
    LOG_IF_ERROR(going_down, "i'm going down... if only i had used macro-logger...");

    return 0;
}