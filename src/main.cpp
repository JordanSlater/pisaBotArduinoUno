#include "I2Cdev.h"
#include "MPU6050.h"
#include "calibration.hpp"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

float roll = 0, pitch = 0, yaw = 0;

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
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax -= Calibration::DefaultSet.Accel.Offset.X;
    ay -= Calibration::DefaultSet.Accel.Offset.Y;
    az -= Calibration::DefaultSet.Accel.Offset.Z;
    gx -= Calibration::DefaultSet.Gyro.Offset.X;
    gy -= Calibration::DefaultSet.Gyro.Offset.Y;
    gz -= Calibration::DefaultSet.Gyro.Offset.Z;

    roll += (float)gx;
    pitch += (float)gy;
    yaw += (float)gz;

    Serial.println(roll);
}