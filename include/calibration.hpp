#pragma once

namespace Calibration {
    /*
    -Full-Scale Range
    -AFS_SEL=0 ±2 g
    -AFS_SEL=1 ±4 g
    -AFS_SEL=2 ±8 g
    -AFS_SEL=3 ±16 g
    -Sensitivity Scale Factor
    -AFS_SEL=0 16,384 LSB/g
    -AFS_SEL=1 8,192 LSB/g
    -AFS_SEL=2 4,096 LSB/g
    -AFS_SEL=3 2,048 LSB/g
    */
    struct Offsets {
        float X, Y, Z;
    };

    struct InertialData {
        Offsets Offset;
        uint8_t ConfigurationFlag;
        float LsbPerUnit;
        float MaxUnitMeasured;
    };

    struct Set {
        InertialData Accel;
        InertialData Gyro;
    };

    static const Set DefaultSet ={
        { // ACCEL
            {
                24306.08,
                -3813.78,
                -30673.64 + 16384.0
            },
            0,
            16384.0,
            2
        },
        { // GYRO
            {
                115.81,
                189.59,
                -243.07
            },
            0,
            131,
            250
        }
    };
};
