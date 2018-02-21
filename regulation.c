#include <xc.h>
#include "regulation.h"
#include "encoder.h"
#include "motor.h"
#include <math.h>
#include "UART.h"

float sumErrorSpeedR = 0;
float sumErrorSpeedL = 0;

float commandR;
float commandL;


void resetErrors() {
    sumErrorSpeedR = 0;
    sumErrorSpeedL = 0;
    
    commandR = 0;
    commandL = 0;
}

void go(int order, float param) {
    float dist;
    
    resetPos();
    resetErrors();
    if (order == 0) {
        regulatePosition(param, param); // go forward
    }
    else if (order == 1) {
        dist = param*(3.1415/180)*Radius; // angle to length
        regulatePosition(dist, -dist); // turn right
    }
    else if (order == 2) {
        dist = param*(3.1415/180)*Radius; // angle to length
        regulatePosition(-dist, dist); // turn left
    }
}

void delay() {
    TMR1 = 0;
    T1CONbits.TON = 1;
    while(!IFS0bits.T1IF) {}
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 0;
}

void regulateSpeed(float speedR, float speedL) {
    getVelocity(); // 10 ms delay
    float measuredSpeedR = getVelocityRight();
//    sendTx(measuredSpeedR);
    float measuredSpeedL = getVelocityLeft();
    
    float errorSpeedR = speedR - measuredSpeedR;
    float errorSpeedL = speedL - measuredSpeedL;
    
    sumErrorSpeedR += errorSpeedR;
    sumErrorSpeedL += errorSpeedL;

    commandR = VKp*errorSpeedR + VKi*sumErrorSpeedR;
    commandL = VKp*errorSpeedL + VKi*sumErrorSpeedL;
    
    velocityMotors(commandR, commandL);   
}

void polar(float speedR, float speedL, float posR, float posL) {
    float pR = 10;
    float pL = 10;
    
    if (posL < 0) {
        pL = -pL;
    }
    if (posR < 0) {
        pR = -pR;
    }
    float averagePos = (fabs(posR) + fabs(posL))/2;
    float errorR = averagePos - fabs(posR);
    float errorL = averagePos - fabs(posL);
    velocityMotors(speedR + pR*errorR, speedL + pL*errorL);
}

void regulatePosition(float inputPosR, float inputPosL) {
    
    int COUNTER = 0;
    
    float speedR;
    float speedL;
    
    float oldSpeedR = 0;
    float oldSpeedL = 0;
    
    float currentPosR = 0;
    float currentPosL = 0;
    
    float errorPosR = inputPosR - currentPosR;
    float errorPosL = inputPosL - currentPosL;
    
    float errorPosRelR = errorPosR/inputPosR;
    float errorPosRelL = errorPosL/inputPosL;
    
    while (1) {
        
        speedR = Kp*errorPosR;
        speedL = Kp*errorPosL;

        // speed saturation Right
        if(speedR > Vmax) {
            speedR = Vmax;
        } else if (speedR < -Vmax) {
            speedR = -Vmax;
        }
        // speed saturation Left
        if(speedL > Vmax) {
            speedL = Vmax;
        } else if (speedL < -Vmax) {
            speedL = -Vmax;
        }
        
        // acceleration saturation Right
        if (speedR - oldSpeedR > Amax*deltaT) {
            speedR = oldSpeedR + Amax*deltaT;
        } 
        else if (speedR - oldSpeedR < -Amax*deltaT) {
            speedR = oldSpeedR - Amax*deltaT;
        }
        // acceleration saturation Left
        if (speedL - oldSpeedL > Amax*deltaT) {
            speedL = oldSpeedL + Amax*deltaT;
        } 
        else if (speedL - oldSpeedL < -Amax*deltaT) {
            speedL = oldSpeedL - Amax*deltaT;
        }
        
        oldSpeedR = speedR;
        oldSpeedL = speedL;
        
        currentPosR = getPosRight();
        currentPosL = getPosLeft();
        
        regulateSpeed(speedR, speedL);
        polar(speedR, speedL, currentPosR, currentPosL);
        
        errorPosR = inputPosR - currentPosR;
        errorPosL = inputPosL - currentPosL;
        
        errorPosRelR = errorPosR/inputPosR;
        errorPosRelL = errorPosL/inputPosL;
        
        if (sqrt(pow(errorPosRelR,2) + pow(errorPosRelL,2)) < 0.03) {
            COUNTER += 1;
            if (COUNTER >= 30) {
                velocityMotors(0,0);
                break;
            }
        }
    }    
}

