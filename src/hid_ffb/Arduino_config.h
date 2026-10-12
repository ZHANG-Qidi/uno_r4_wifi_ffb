#pragma once

// UNO R4 WiFi: three different GPT channels, leaving D10-D13 for SPI.
#define CONFIG_FOC_MOTOR_U 3
#define CONFIG_FOC_MOTOR_V 5
#define CONFIG_FOC_MOTOR_W 6
#define CONFIG_FOC_MOTOR_EN 8
#define CONFIG_ARDUINO_SPI_CS0 10
#define SPI_MASTER_CS_IO CONFIG_ARDUINO_SPI_CS0

// SPI: MOSI D11, MISO D12, SCK D13. I2C: SDA A4, SCL A5.
#define CONFIG_ARDUINO_I2C_FREQ_HZ 400000
#define CONFIG_PEDAL_0 A0
#define CONFIG_PEDAL_1 A1
#define CONFIG_PEDAL_2 A2

// D13/LED_BUILTIN is SPI SCK. Leave the status LED disabled with SPI;
// an optional external LED can use D7, or D13 when using an I2C encoder.
#define CONFIG_STATUS_LED_PIN -1
