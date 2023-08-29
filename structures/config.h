// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include "led.h"
#include <libconfig.h>

typedef struct {
    LED* leds;
    int count;  // Number of LEDs in the array
} Config;

Config* cfg_init(const char* filename);
void cfg_free(Config* config);

#endif // CONFIG_H
