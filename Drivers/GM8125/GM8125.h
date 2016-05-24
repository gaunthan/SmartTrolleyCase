/***************************************************************************************
*        File Name              :	GM8125.h
*        CopyRight              :	gaunthan
*        ModuleName             :	UART MUX
*
*        CPU                    :   MSP430
*        RTOS                   :   None
*
*        Create Data            :	2016/5/19
*        Author/Corportation    :	gaunthan
*
*        Abstract Description   :	封装GM8125模块单通道模式下的控制操作，提供选择串口子通道函数。
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/19	gaunthan        		 	Create this file
*
***************************************************************************************/

/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef GM8125_H
#define GM8125_H

/**************************************************************
*        Debug switch Section
**************************************************************/
/**
 * 模块调试开关宏。1代表开启调试信息，0代表不开启。
 */
#define GM8125_DEBUG_ON 1


/**************************************************************
*        Include File Section
**************************************************************/
#include "HAL_AppUart.h"
#include "general.h"
#include "msp430f5529.h"

/**************************************************************
*        Macro Define Section
**************************************************************/

/* 定义输入通道地址引脚 */
#define STADD2 0
#define STADD1 BIT1
#define STADD0 BIT0

/* 定义输出通道地址引脚 */
#define SRADD2 0
#define SRADD1 BIT4
#define SRADD0 BIT3



/**************************************************************
*        Struct Define Section
**************************************************************/


/**
 * @brief	定义子通道标识符。
 */
typedef enum {
	GM_CHANNEL1,
	GM_CHANNEL2,
	GM_CHANNEL3,
	GM_CHANNEL4,
	GM_CHANNEL5,
}GM_Channel;


/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief	初始化GM8125模块硬件连接
 * @param	None
 * @return	None
 */
void GM_InitPort(void);


/**
 * @brief	选择与母通道通信的子通道
 * @param	channel 通道值，可选为1~5
 * @return	None
 */
void GM_SelectChannel(GM_Channel channel);



/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
