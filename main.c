#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "init.h"
#include "motor.h"
#include "encoder.h"
#include "UART.h"
#include "bluetooth.h"
#include "regulation.h"
#include "callibration.h"

int main() {
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    LATBbits.LATB4 = 1;
    LATBbits.LATB5 = 0;
    
    oscillatorInit();
    timerInit();
    motorInit();
    encoderInit();
    UARTInit();
    bluetoothInit();
    
    go(0,1);
    
    while(1) { 
    }

}