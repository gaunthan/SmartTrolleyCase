/*
 * myWDG.h
 *
 *  Created on: 2016Äê5ÔÂ25ÈÕ
 *      Author: Administrator
 */



#ifndef MYWDG_H_
#define MYWDG_H_

#include <msp430.h>

/**************************************************************
*	Macro Define Section
**************************************************************/
#define OVERTIME 10

void myWDGInit(unsigned char time);
void ResetWDGCounter(void);




#endif /* MYWDG_H_ */
