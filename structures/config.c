#include "config.h"
#include <libconfig.h>

Config* cfg_init(const char* filename) {
    config_t cfg;
    config_setting_t *setting;
    Config* config = (Config*)malloc(sizeof(Config));
    if (!config) {
        perror("Failed to allocate memory for config");
        return NULL;
    }

    config_init(&cfg);
    if (!config_read_file(&cfg, filename)) {
        fprintf(stderr, "Error: %s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return NULL;
    }

    setting = config_lookup(&cfg, "leds");
    if (setting != NULL) {
        int count = config_setting_length(setting);
        config->count = count;
        config->leds = malloc(sizeof(LED) * count);

        for (int i = 0; i < count; i++) {
            config_setting_t *led_entry = config_setting_get_elem(setting, i);
            config_setting_lookup_int(led_entry, "GPIO", &(config->leds[i].GPIO));
            config->leds[i].state = 0;  // Default state
        }
    } else {
        config->leds = NULL;
        config->count = 0;
    }

    config_destroy(&cfg);
    return config;
}

void cfg_free(Config* config) {
    free(config->leds);
    free(config);
}
