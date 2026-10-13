#include "usb_setup.h"

#include <Arduino.h>
#include <tusb.h>
#include <usb/USB.h>

#include "hidReportDesc.h"

// Arduino Renesas core owns device/configuration/string descriptors and USB IRQs.
// Supply the FFB report descriptor through its HID hook.
uint8_t *__USBGetHIDReport(size_t *length) {
    *length = sizeof(desc_hid_report);
    return const_cast<uint8_t *>(desc_hid_report);
}

void usb_setup(void) { __USBStart(); }
