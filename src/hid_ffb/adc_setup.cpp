#include "adc_setup.h"

#include "Arduino.h"
#include "Arduino_config.h"

void adc_setup(void) {
    analogReference(AR_DEFAULT);
    analogReadResolution(12);
    pinMode(CONFIG_PEDAL_0, INPUT);
    pinMode(CONFIG_PEDAL_1, INPUT);
    pinMode(CONFIG_PEDAL_2, INPUT);
}
