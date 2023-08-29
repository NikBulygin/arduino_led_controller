#ifndef GTK_WIDGET_LED_H
#define GTK_WIDGET_LED_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int state;
    int GPIO;
} LED;

// Declaration of the initialization function
LED* led_init(int initialState, int gpioPin);

// Declaration of the cleanup function
void led_free(LED* led);

#endif // GTK_WIDGET_LED_H
