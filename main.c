#include <msp430.h> 
#include "HAL_Board.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_AppUart.h"
#include <stdio.h>
#include "GPS.h"
#include "HAL_Board.h"

/**
 * ���ÿ����壬ʹ�䴦����������ģʽ
 */
void SystemInit(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    Board_init();				// ��ʼ��������

    SetVCore(3);                // ��VCoreΪ���

    LFXT_Start(XT1DRIVE_0);     // Use 32.768kHz XTAL as reference

    Init_FLL_Settle(25000, 762);// Set system clock to max (25MHz)

    SFRIFG1 = 0;                                 //���жϱ�־
    SFRIE1 |= OFIE;                              //ʹ�ܾ���ʧЧ�ж�

    // Globally enable interrupts
    __enable_interrupt();                        //ʹ��ȫ���ж�
}

/*
 * main.c
 */
int main(void)
{
	GeoPos pos;


	SystemInit();
	GPS_Init();
	Board_ledOff(LED1);
	Board_ledOff(LED2);

	while(1) {
		if(OK == GPS_GetPosition(&pos)) {
			Board_ledToggle(LED1);
		}

		Board_ledToggle(LED2);
	}

	return 0;
}
