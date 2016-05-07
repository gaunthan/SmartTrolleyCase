#include <msp430.h> 
#include "HAL_Board.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_AppUart.h"
#include "printf.h"

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


/*
 * main.c
 */
int main(void)
{
	SystemInit();
	AppUart_init();

	while(1) {
		uint8_t data = AppUart_getChar();
		AppUart_putChar(data);
		unsigned char i = 10;
		while(i--);
		printf("Hello, World!\r\n");
	}

	return 0;
}
