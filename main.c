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
 * @brief	配置开发板，使其处于正常工作模式
 * @param	None
 * @return	None
 */
void SystemInit(void);


/**
 * @brief	向远程服务器上报地理位置信息
 * @param	None
 * @return	None
 */
void ReportLocation(void);


/*
 * @brief	主程序
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
 * @brief	向远程服务器上报地理位置信息
 * @param	None
 * @return	None
 */
void ReportLocation(void)
{
	char sendBuf[128];
	char tmpBuf[64];
	char devCode[32];

	GM_SelectChannel(GM_CHANNEL2);

	/* 获取设备码并放入发送缓冲区 */
	GPRS_GetDevCode(devCode, sizeof(devCode));

	if(OK == GPRS_InitTCPEnv()) { /* 初始化TCP环境成功 */
		if(OK == GPRS_InitSMTP()) {
			/* 填充发送缓冲区 */
			do {

				/* 选择通道1并从通道1获取GPS信息 */
				GM_SelectChannel(GM_CHANNEL1);
				while(ERROR == GPS_PutLocation(tmpBuf, sizeof(tmpBuf))) {};

				/* 成功获取地理信息，包装信息 */
				sendBuf[0] = '\0';
				strcat(sendBuf, devCode);
				strcat(sendBuf, "\r\n");
				strcat(sendBuf, tmpBuf);
				strcat(sendBuf, "\r\n");

				/* 选择通道2以使MCU和GPRS模块通信 */
				GM_SelectChannel(GM_CHANNEL2);
			}while(OK == GPRS_SendMail(sendBuf));	/* 持续发邮件直到发送失败 */

			GPRS_RebootDev();	/* 发送失败，重启设备 */
		}
	}
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

