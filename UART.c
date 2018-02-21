#include <xc.h>
#include "UART.h"

void UARTInit() {
	U1MODEbits.UARTEN = 1;              // Activation de la réception
	U1STAbits.UTXEN = 1;                // Activation de la transmission
    U1MODEbits.PDSEL = 00;              // 8-bit data, no parity
    U1BRG = (FCY/(16*BAUDRATE)) - 1;    // Configuaration du baud rate
    
    RPINR18bits.U1RXR = 6; // RX PIN
    RPOR3bits.RP7R = 3;    // TX PIN 
}

void echo(){
    if(U1STAbits.URXDA){
        U1TXREG = U1RXREG;
    }
}

int readRx(){
    return U1RXREG;
}

void sendTx(float data) {
    data *= 100;
    U1TXREG = (signed int) data;
}
