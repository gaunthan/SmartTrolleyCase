#include <msp430.h> 
#include "HAL_Board.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_AppUart.h"
#include <stdio.h>
#include "GPS.h"
#include "GPRS.h"
#include "HAL_Board.h"

/**
 * 配置开发板，使其处于正常工作模式
 */
void SystemInit(void);


/*
 * main.c
 */
int main(void)
{
	SystemInit();
	GPRS_Init();

	while(1) {
		if(OK == GPRS_InitTCPEnv())
			Board_ledToggle(LED1);
		else
			Board_ledToggle(LED2);
	}

	return 0;
}



/**
 * 配置开发板，使其处于正常工作模式
 */
void SystemInit(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    Board_init();				// 初始化开发板

    SetVCore(3);                // 设VCore为最大

    LFXT_Start(XT1DRIVE_0);     // Use 32.768kHz XTAL as reference

    Init_FLL_Settle(25000, 762);// Set system clock to max (25MHz)

    SFRIFG1 = 0;                                 //清中断标志
    SFRIE1 |= OFIE;                              //使能晶振失效中断

    // Globally enable interrupts
    __enable_interrupt();                        //使能全局中断
}

