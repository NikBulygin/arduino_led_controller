#include "led.h"

// Definition of the initialization function
LED* led_init(int initialState, int gpioPin) {
    LED* newLED = (LED*)malloc(sizeof(LED));
    if (newLED == NULL) {
        perror("Failed to allocate memory for LED");
        return NULL;
    }
    newLED->state = initialState;
    newLED->GPIO = gpioPin;
    return newLED;
}

// Definition of the cleanup function
void led_free(LED* led) {
    free(led);
}
