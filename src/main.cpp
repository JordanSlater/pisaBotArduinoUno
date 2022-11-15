// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

constexpr size_t SAMPLES = 10000;
size_t sample = 0;

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

float sum_ax, sum_ay, sum_az;
float sum_gx, sum_gy, sum_gz;

/*
Full-Scale Range
AFS_SEL=0 ±2 g
AFS_SEL=1 ±4 g
AFS_SEL=2 ±8 g
AFS_SEL=3 ±16 g
Sensitivity Scale Factor
AFS_SEL=0 16,384 LSB/g
AFS_SEL=1 8,192 LSB/g
AFS_SEL=2 4,096 LSB/g
AFS_SEL=3 2,048 LSB/g
*/

constexpr float OFFSET_A_X = 24306.08;
constexpr float OFFSET_A_Y = -3813.78;
constexpr float OFFSET_A_Z = -30673.64 + 16384.0;
constexpr float OFFSET_G_X = 115.81;
constexpr float OFFSET_G_Y = 189.59;
constexpr float OFFSET_G_Z = -243.07;

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
    // accelgyro.setFullScaleGyroRange();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    sum_ax += ax;
    sum_ay += ay;
    sum_az += az;
    sum_gx += gx;
    sum_gy += gy;
    sum_gz += gz;

    if (sample == SAMPLES) {
        Serial.print("a,g:\t");
        Serial.print(sum_ax / SAMPLES); Serial.print("\t");
        Serial.print(sum_ay / SAMPLES); Serial.print("\t");
        Serial.print(sum_az / SAMPLES); Serial.print("\t");
        Serial.print(sum_gx / SAMPLES); Serial.print("\t");
        Serial.print(sum_gy / SAMPLES); Serial.print("\t");
        Serial.print(sum_gz / SAMPLES); Serial.print("\t");
        Serial.print("a,g scale:\t");
        Serial.print(accelgyro.getFullScaleAccelRange()); Serial.print("\t");
        Serial.print(accelgyro.getFullScaleGyroRange()); Serial.print("\t");
        Serial.println();

        sum_ax = 0;
        sum_ay = 0;
        sum_az = 0;
        sum_gx = 0;
        sum_gy = 0;
        sum_gz = 0;

        sample = 0;
    }
    sample++;
}