#include "GM8125.h"

/**
 * @brief	调试信息输出宏定义
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GM8125_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define GM8125_DEBUG(fmt, args...)
#endif



/**
 * @brief	设置引脚输出值
 */
#define GM8125_SetPin(pin, value)					\
	do {										\
		if(value)								\
			P2OUT |= pin;						\
		else									\
			P2OUT &= ~pin;						\
	}while(0)




/**
 * @brief	初始化GM8125模块硬件连接
 * @param	None
 * @return	None
 */
void GM8125_InitPort(void)
{
	P2DIR |= STADD0 | STADD1 | STADD2 | SRADD0 | SRADD1 | SRADD2;
}



/**
 * @brief	选择与母通道通信的子通道
 * @param	channel 通道值，可选为1~5
 * @return	None
 */
void GM8125_SelectChannel(GM8125_Channel channel)
{
	switch(channel) {
		case GM8125_CHANNEL1:	/* 通道2的地址值为001 */
			GM8125_SetPin(STADD0, 1);
			GM8125_SetPin(STADD1, 0);
			GM8125_SetPin(STADD2, 0);

			GM8125_SetPin(SRADD0, 1);
			GM8125_SetPin(SRADD1, 0);
			GM8125_SetPin(SRADD2, 0);
			break;

		case GM8125_CHANNEL2:	/* 通道2的地址值为010 */

			GM8125_SetPin(STADD0, 0);
			GM8125_SetPin(STADD1, 1);
			GM8125_SetPin(STADD2, 0);

			GM8125_SetPin(SRADD0, 0);
			GM8125_SetPin(SRADD1, 1);
			GM8125_SetPin(SRADD2, 0);
			break;

		case GM8125_CHANNEL3:	/* 通道3的地址值为011 */

			GM8125_SetPin(STADD0, 1);
			GM8125_SetPin(STADD1, 1);
			GM8125_SetPin(STADD2, 0);

			GM8125_SetPin(SRADD0, 1);
			GM8125_SetPin(SRADD1, 1);
			GM8125_SetPin(SRADD2, 0);
			break;

		case GM8125_CHANNEL4:	/* 通道4的地址值为100 */

			GM8125_SetPin(STADD0, 0);
			GM8125_SetPin(STADD1, 0);
			GM8125_SetPin(STADD2, 1);

			GM8125_SetPin(SRADD0, 0);
			GM8125_SetPin(SRADD1, 0);
			GM8125_SetPin(SRADD2, 1);
			break;

		case GM8125_CHANNEL5:	/* 通道1的地址值为101 */

			GM8125_SetPin(STADD0, 1);
			GM8125_SetPin(STADD1, 0);
			GM8125_SetPin(STADD2, 1);

			GM8125_SetPin(SRADD0, 1);
			GM8125_SetPin(SRADD1, 0);
			GM8125_SetPin(SRADD2, 1);
			break;

		default:
			GM8125_DEBUG("ERROR: Channel not support!\r\n");
	}

}
