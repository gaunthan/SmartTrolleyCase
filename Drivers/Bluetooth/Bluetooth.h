/***************************************************************************************
*        File Name              :	Bluetooth.h
*        CopyRight              :	gaunthan
*        ModuleName             :	Bluetooth
*
*        CPU                    :   MSP430
*        RTOS                   :   None
*
*        Create Data            :	2016/5/25
*        Author/Corportation    :	gaunthan
*
*        Abstract Description   :	封装Bluetooth数据收发功能
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/25	gaunthan        		 	Create this file
*
***************************************************************************************/

/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/**************************************************************
*        Debug switch Section
**************************************************************/
/**
 * 模块调试开关宏。1代表开启调试信息，0代表不开启。
 */
#define BT_DEBUG_ON 0


/**************************************************************
*        Include File Section
**************************************************************/
#include "HAL_AppUart.h"
#include "general.h"

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
 * @brief	初始化蓝牙模块与相关引脚。
 * @param	None
 * @return	None
 */
void BT_InitPort(void);


/**
 * @brief	向蓝牙模块发送一个字符
 * @param	ch 需要发送的字符
 * @return	None
 */
void BT_Putchar(char ch);


/**
 * @brief	从蓝牙模块读取一个字符
 * @param	None
 * @return	一个字符
 */
char BT_Getchar(void);


/**
 * @brief	向蓝牙模块发送一个字符串，末尾追发<CR><LF>
 * @param	str 需要发送的字符串
 * @return	None
 */
void BT_Println(const char *str);


/**
 * @brief	从蓝牙模块获取一个字符串，以<CR><LF>标志输入字符串的结束。若输入字符串过长将被截断。
 * @param	buf 输出缓冲区
 *			n 缓冲区大小
 * @return	None
 */
void BT_Gets(char *buf, int n);

/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
