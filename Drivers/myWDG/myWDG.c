/*
 * myWDG.c
 *
 *  Created on: 2016年5月25日
 *      Author: Administrator
 */
#include "myWDG.h"
#include "timer_a.h"

unsigned char WDGOverTime = 0;
unsigned char  WDGCounter = 0;

//Init the Timer
void myWDGInit(unsigned char time)
{
	//Start timer in continuous mode sourced by ACLK
	    Timer_A_clearTimerInterrupt(TIMER_A1_BASE);

	    Timer_A_initContinuousModeParam param = {0};
	    param.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
	    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
	    param.timerClear = TIMER_A_DO_CLEAR;
	    param.startTimer = true;
	    Timer_A_initContinuousMode(TIMER_A1_BASE, &param);

	    WDGOverTime = time;  		//Actual OverTime = 2*WDGOverTime  (seconds)
}

//清楚看门狗计数器的值
void ResetWDGCounter(void)
{
	WDGCounter = 0;
}
