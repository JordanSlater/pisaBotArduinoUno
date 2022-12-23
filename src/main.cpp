#ifdef PROGRAM
#if PROGRAM == MAIN

#include "I2Cdev.h"
#include "MPU6050.h"
#include "calibration.hpp"
#include "quaternion.hpp"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t raw_ax, raw_ay, raw_az;
int16_t raw_gx, raw_gy, raw_gz;

long int last_read;

Quaternion rotation;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");

    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    last_read = millis();
}

void loop() {
    long int current_time = millis();
    long int time_in_ms_since_read = current_time - last_read;
    float dt = static_cast<float>(time_in_ms_since_read) / 1000.f;
    last_read = current_time;

    accelgyro.getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);

    // float ax = ((static_cast<float>(raw_ax) - Calibration::DefaultSet.Accel.Offset.X) / Calibration::DefaultSet.Accel.LsbPerUnit) * dt;
    // float ay = ((static_cast<float>(raw_ay) - Calibration::DefaultSet.Accel.Offset.Y) / Calibration::DefaultSet.Accel.LsbPerUnit) * dt;
    // float az = ((static_cast<float>(raw_az) - Calibration::DefaultSet.Accel.Offset.Z) / Calibration::DefaultSet.Accel.LsbPerUnit) * dt;
    float gx = ((static_cast<float>(raw_gx) - Calibration::DefaultSet.Gyro.Offset.X) / Calibration::DefaultSet.Gyro.LsbPerUnit) * dt;
    float gy = ((static_cast<float>(raw_gy) - Calibration::DefaultSet.Gyro.Offset.Y) / Calibration::DefaultSet.Gyro.LsbPerUnit) * dt;
    float gz = ((static_cast<float>(raw_gz) - Calibration::DefaultSet.Gyro.Offset.Z) / Calibration::DefaultSet.Gyro.LsbPerUnit) * dt;

    Quaternion incremental_rotation = Quaternion::from_euler_rotation(gx, gy, gz);

    rotation *= incremental_rotation;

    rotation.

    Serial.println(roll);
}

#endif
#endif
