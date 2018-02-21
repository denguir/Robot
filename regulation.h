/* 
 * File:   regulation.h
 * Author: vador
 *
 * Created on 21 mars 2017, 14:43
 */

#ifndef REGULATION_H
#define	REGULATION_H

#define Vmax 0.4
#define Amax 0.5 // m/s²
#define deltaT 0.01 // s, periode echantillonnage

#define Kp 8.49 // m?¹
#define VKp 4.527//0.5317
#define VKi 26.47//0.0477

#define Radius 0.1075 // m, distance_between_wheels/2

void go(int, float);
void resetErrors(void);
void regulatePosition(float, float);
void regulateSpeed(float, float);
void delay(void);
void polar(float, float, float, float);

#endif	/* REGULATION_H */

