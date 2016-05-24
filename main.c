#include <msp430.h> 
#include "HAL_Board.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_AppUart.h"
#include <stdio.h>
#include "GPS.h"
#include "GPRS.h"
#include "HAL_Board.h"
#include "GM8125.h"


/**
 * @brief	���ÿ����壬ʹ�䴦����������ģʽ
 * @param	None
 * @return	None
 */
void SystemInit(void);


/**
 * @brief	��Զ�̷������ϱ�����λ����Ϣ
 * @param	None
 * @return	None
 */
void ReportLocation(void);


/*
 * @brief	������
 */
int main(void)
{
	SystemInit();
	AppUart_init();
	GM_InitPort();
	GPS_InitPort();
	GPRS_InitPort();

	while(1) {
		ReportLocation();
	}

	return 0;
}


/**
 * @brief	��Զ�̷������ϱ�����λ����Ϣ
 * @param	None
 * @return	None
 */
void ReportLocation(void)
{
	char sendBuf[128];
	char tmpBuf[64];
	char devCode[32];

	GM_SelectChannel(GM_CHANNEL2);

	/* ��ȡ�豸�벢���뷢�ͻ����� */
	GPRS_GetDevCode(devCode, sizeof(devCode));

	if(OK == GPRS_InitTCPEnv()) { /* ��ʼ��TCP�����ɹ� */
		if(OK == GPRS_InitSMTP()) {
			/* ��䷢�ͻ����� */
			do {

				/* ѡ��ͨ��1����ͨ��1��ȡGPS��Ϣ */
				GM_SelectChannel(GM_CHANNEL1);
				while(ERROR == GPS_PutLocation(tmpBuf, sizeof(tmpBuf))) {};

				/* �ɹ���ȡ������Ϣ����װ��Ϣ */
				sendBuf[0] = '\0';
				strcat(sendBuf, devCode);
				strcat(sendBuf, "\r\n");
				strcat(sendBuf, tmpBuf);
				strcat(sendBuf, "\r\n");

				/* ѡ��ͨ��2��ʹMCU��GPRSģ��ͨ�� */
				GM_SelectChannel(GM_CHANNEL2);
			}while(OK == GPRS_SendMail(sendBuf));	/* �������ʼ�ֱ������ʧ�� */

			GPRS_RebootDev();	/* ����ʧ�ܣ������豸 */
		}
	}
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

