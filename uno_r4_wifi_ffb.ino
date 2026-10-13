#include <Arduino.h>

#include "src/hid_ffb/Arduino_config.h"
#include "src/hid_ffb/adc_loop.h"
#include "src/hid_ffb/adc_setup.h"
#include "src/hid_ffb/foc_loop.h"
#include "src/hid_ffb/foc_setup.h"
#include "src/hid_ffb/usb_loop.h"
#include "src/hid_ffb/usb_setup.h"

static uint32_t lastFocUs;
static uint32_t lastUsbMs;
static uint32_t lastAdcMs;
static uint32_t lastLedMs;
static bool ledOn;

void setup() {
#if CONFIG_STATUS_LED_PIN >= 0
    pinMode(CONFIG_STATUS_LED_PIN, OUTPUT);
    digitalWrite(CONFIG_STATUS_LED_PIN, LOW);
#endif
    adc_setup();
    usb_setup();
    foc_setup();
    lastFocUs = micros();
    lastUsbMs = lastAdcMs = lastLedMs = millis();
}

void loop() {
    const uint32_t nowUs = micros();
    if (uint32_t(nowUs - lastFocUs) >= uint32_t(FOC_LOOP_PERIOD)) {
        lastFocUs = nowUs;
        foc_loop();
    }
    const uint32_t nowMs = millis();
    if (uint32_t(nowMs - lastAdcMs) >= ADC_READ_INTERVAL) {
        lastAdcMs = nowMs;
        adc_loop();
    }
    if (uint32_t(nowMs - lastUsbMs) >= USB_POLLING_INTERVAL) {
        lastUsbMs = nowMs;
        usb_loop();
    }
#if CONFIG_STATUS_LED_PIN >= 0
    if (uint32_t(nowMs - lastLedMs) >= blink_interval_ms_usb_status) {
        lastLedMs = nowMs;
        ledOn = !ledOn;
        digitalWrite(CONFIG_STATUS_LED_PIN, ledOn ? HIGH : LOW);
    }
#endif
}
