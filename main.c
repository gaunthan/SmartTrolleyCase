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
 * ���ÿ����壬ʹ�䴦����������ģʽ
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

