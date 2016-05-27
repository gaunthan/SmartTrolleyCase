#include "app.h"


/**
 * @brief	配置开发板，使其处于正常工作模式
 * @param	None
 * @return	None
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



/**
 * @brief	初始化系统子模块硬件环境
 * @param	None
 * @return	None
 */
void ModulesInit(void)
{
	LOCK_InitPort();
	AppUart_init();
	GM8125_InitPort();
	GPS_InitPort();
	GPRS_InitPort();
	BT_InitPort();
	HX711_GPIO_Init();
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

	GM8125_SelectChannel(GPRS_CHANNEL);

	/* 获取设备码并放入发送缓冲区 */
	GPRS_GetDevCode(devCode, sizeof(devCode));

	if(OK == GPRS_InitTCPEnv()) { /* 初始化TCP环境成功 */
		if(OK == GPRS_InitSMTP()) {
			/* 填充发送缓冲区 */
			do {

				/* 选择通道1并从通道1获取GPS信息 */
				GM8125_SelectChannel(GPR_CHANNEL);
				while(ERROR == GPS_PutLocation(tmpBuf, sizeof(tmpBuf))) {};

				/* 成功获取地理信息，包装信息 */
				sendBuf[0] = '\0';
				strcat(sendBuf, devCode);
				strcat(sendBuf, "\r\n");
				strcat(sendBuf, tmpBuf);
				strcat(sendBuf, "\r\n");

				/* 选择通道2以使MCU和GPRS模块通信 */
				GM8125_SelectChannel(GPRS_CHANNEL);
			}while(OK == GPRS_SendMail(sendBuf));	/* 持续发邮件直到发送失败 */

			GPRS_RebootDev();	/* 发送失败，重启设备 */
		}
	}
}



/**
 * @brief	从应用端接收一个请求
 * @param	None
 * @return	请求码
 */
Request GetRequest(void)
{
	return (Request)BT_Getchar();
}


/**
 * @brief	向应用端发送一个响应
 * @param	res 响应码
 * @return	None
 */
void SendResponse(Request res)
{
	BT_Putchar((Request)res);
}

