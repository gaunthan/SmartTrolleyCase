/***************************************************************************************
*        File Name              :	GPRS_H
*        CopyRight              :	gaunthan
*        ModuleName             :	GPRS
*
*        CPU                    :   MSP430
*        RTOS                   :   None
*
*        Create Data            :	2016/5/15
*        Author/Corportation    :	gaunthan
*
*        Abstract Description   :	封装SIM900A_mini GPS模块，提供发送邮件功能。
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/15	gaunthan        		 	Create this file
*       2		v2.0		2016/5/16	gaunthan		email		利用TCP和SMTP实现发送邮件功能
*
***************************************************************************************/

/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef GPRS_H
#define GPRS_H

/**************************************************************
*        Debug switch Section
**************************************************************/
/**
 * GPRS模块调试开关宏。1代表开启调试信息，0代表不开启。
 */
#define GPRS_DEBUG_ON 1


/**************************************************************
*        Include File Section
**************************************************************/
#include "HAL_AppUart.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>

/**************************************************************
*        Macro Define Section
**************************************************************/


/**************************************************************
*        Struct Define Section
**************************************************************/




/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief	初始化GPS模块与相关引脚。
 * @param	None
 * @return	OK 初始化成功
			ERROR 初始化失败
 */
Status GPRS_Init(void);


/**
 * @brief	建立GPRS TCP环境
 * @param	None
 * @return	OK 初始化成功
 * 			ERROR 初始化失败
 */
Status GPRS_InitTCPEnv(void);


/**
 * @brief	初始化SMTP环境，连接至163服务器且完成认证
 * @param	None
 * @return	OK 初始化成功
 *			ERROR 初始化失败
 */
Status GPRS_InitSMTP(void);


/**
 * @brief	通过SMTP协议发送一封内容为msg的邮件
 * @param	msg 需要发送的信息
 * @return	OK 发送成功
 *			ERROR 发送失败
 */
Status GPRS_SendMail(char *msg);


/**
 * @brief	获取GPRS模块的产品序列号
 * @param	buf 缓冲区，用于存储获取到的序列号
 * 			bufSize 缓冲区大小
 * @return	OK 获取成功
 *			ERROR 获取失败
 */
Status GPRS_GetDevCode(char *buf, int bufSize);

/**
 * @brief	重启GPRS模块
 * @param	None
 * @return	OK 重启成功
 *			ERROR 重启失败
 */
Status GPRS_RebootDev(void);

/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
