#include <xc.h>
#include "UART.h"

void bluetoothInit(void){
    TRISBbits.TRISB2 = 0;
    LATBbits.LATB2 = 1; 
            
	U2MODEbits.UARTEN = 1;              // Activation de la réception
	U2STAbits.UTXEN = 1;                // Activation de la transmission
    U2MODEbits.PDSEL = 00;              // 8-bit data, no parity
    U2BRG = (FCY/(16*BAUDRATE)) - 1;    // Configuaration du baud rate
    
    RPINR19bits.U2RXR = 14; // RX BT PIN
    RPOR7bits.RP15R = 5;    // TX BT PIN 
    
    RPINR19bits.U2CTSR = 3; // CTS BT PIN
    RPOR8bits.RP16R = 6;    // RTS BT PIN
    
    LATBbits.LATB2 = 0; 
}