#include "foc_setup.h"

#include "SimpleFOC.h"

// magnetic sensor
#if defined(CONFIG_FFB_MagneticSensorSPI)
/** Typical configuration for the 14bit AMS AS5147 magnetic sensor over SPI interface */
MagneticSensorSPIConfig_s MT6701_SPI = {
    .spi_mode = SPI_MODE1,
    .clock_speed = 1000000,
    .bit_resolution = 14,
    .angle_register = 0x3FFF,
    .data_start_bit = 15,
    .command_rw_bit = 0,
    .command_parity_bit = 1,
};
// magnetic sensor instance - SPI
MagneticSensorSPI sensor = MagneticSensorSPI(MT6701_SPI, SPI_MASTER_CS_IO);
#endif
// #define CONFIG_FFB_MagneticSensorIIC
#if defined(CONFIG_FFB_MagneticSensorIIC)
// magnetic sensor instance - I2C
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
#endif
// BLDC motor & driver instance
BLDCMotor motor = BLDCMotor(BLDC_MOTOR_PP);
static BLDCDriver3PWM driver = BLDCDriver3PWM(MOTOR_U, MOTOR_V, MOTOR_W, MOTOR_EN);
void foc_setup(void) {
    // initialise magnetic sensor hardware
    sensor.init();
    // link the motor to the sensor
    motor.linkSensor(&sensor);
    // power supply voltage
    driver.voltage_power_supply = VOLTAGE_POWER;
    driver.voltage_limit = VOLTAGE_LIMIT;
    driver.init();
    motor.linkDriver(&driver);
    // aligning voltage
    motor.voltage_sensor_align = VOLTAGE_SENSOR_ALIGN;
    // choose FOC modulation (optional)
    motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
    // set motion control loop to be used
    motor.controller = MotionControlType::torque;
    // set torque control loop to be used
    motor.torque_controller = TorqueControlType::voltage;
    // use monitoring with serial
    SerialUSB.begin(COMMANDER_BAUD_RATE);
    // comment out if not needed
    motor.useMonitoring(SerialUSB);
    // initialize motor
    motor.init();
    // align sensor and start FOC
    motor.initFOC();
    SerialUSB.println(F("Motor ready."));
    delay(1000);
}
