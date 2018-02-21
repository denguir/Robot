#include <xc.h>
#include "callibration.h"
#include "regulation.h"
#include "encoder.h"
#include "motor.h"

float speedR;
float speedL;

float sumSpeedR;
float sumSpeedL;

float avR;
float avL;

void callibrate() {
    velocityMotors(0.4, 0.4);
    int i;
    for (i=0; i<400; i++) {
        delay();
    }
    for (i=0; i<1000; i++) {
        getVelocity();
        speedR = getVelocityRight();
        speedL = getVelocityLeft();
        
        sumSpeedR += speedR;
        sumSpeedL += speedL;   
    }
    OC2RS = 0;
    OC3RS = 0;
    avR = sumSpeedR/1000;
    avL = sumSpeedL/1000;
}


