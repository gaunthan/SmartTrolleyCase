#include <msp430.h>
#include "HAL_Board.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_AppUart.h"
#include "HAL_Board.h"
#include "general.h"
/**
 * @brief	��־��ʱ���Ƿ��ʱ����
 */
int TimeoutFlag = FALSE;

/**
 * @brief	���ÿ����壬ʹ�䴦����������ģʽ
 * @param	None
 * @return	None
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
 * @brief	������
 */
int main(void)
{
	SystemInit();
	AppUart_init();

	while(1) {
		printf("hello,world!\n");
	}

	return 0;
}



