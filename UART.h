/* 
 * File:   UART.h
 * Author: Quy Phan
 *
 * Created on 20 f�vrier 2017, 20:02
 */

#ifndef UART_H
#define	UART_H

#define BAUDRATE 115200
#define FCY 40000000 // fr�quence machine

/**
 * Configure le TIMER3 utilis� pour l'ADC
 */
void UARTInit();

/**
 * Renvoie l'octet re�u
 */
void echo(void);

int readRx(void);

void sendTx(float);

#endif	/* UART_H */

