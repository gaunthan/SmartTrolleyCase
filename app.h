/***************************************************************************************
*        File Name              :	app.h
*        CopyRight              :	gaunthan
*        ModuleName             :	applications
*
*        CPU                    :   MSP430
*        RTOS                   :   None
*
*        Create Data            :	2016/5/25
*        Author/Corportation    :	gaunthan
*
*        Abstract Description   :	high level applications
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/25	gaunthan        		 	Create this file
*
***************************************************************************************/

/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef APP_H
#define APP_H

/**************************************************************
*        Debug switch Section
**************************************************************/
/**
 * 模块调试开关宏。1代表开启调试信息，0代表不开启。
 */
#define APP_DEBUG_ON 0


/**************************************************************
*        Include File Section
**************************************************************/
#include <msp430.h>
#include "HAL_Board.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_AppUart.h"
#include "HAL_Board.h"
#include "general.h"
#include "GPS.h"
#include "GPRS.h"
#include "GM8125.h"
#include "Bluetooth.h"
#include "lock.h"
#include <stdio.h>
#include "Scale.h"


/**************************************************************
*        Macro Define Section
**************************************************************/
/**
 * @brief	设置模块所属子串口（通道）
 */
#define GPR_CHANNEL GM8125_CHANNEL1
#define GPRS_CHANNEL GM8125_CHANNEL2
#define BLUETOOTH_CHANNEL GM8125_CHANNEL3


/**
 * @brief	选择串口通信通道
 */
#define SelectChannel(chan) GM8125_SelectChannel(chan)

/**************************************************************
*        Struct Define Section
**************************************************************/
/**
 * @brief	定义 APP可以使用的请求信号
 */
typedef enum {
	 SYS_START = 0x01,		/* 启动本系统工作 */
	 KEEP_ALIVE = 0x02,		/* 保持连接活性 */
	 GET_WEIGHT = 0x04,		/* 请求获取系统重量信息 */
	 UNLOCK_DEVICE = 0x08,	/* 请求解锁设备 */

}Request;


/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief	配置开发板，使其处于正常工作模式
 * @param	None
 * @return	None
 */
void SystemInit(void);


/**
 * @brief	初始化系统子模块硬件环境
 * @param	None
 * @return	None
 */
void ModulesInit(void);


/**
 * @brief	向远程服务器上报地理位置信息
 * @param	None
 * @return	None
 */
void ReportLocation(void);


/**
 * @brief	从应用端接收一个请求
 * @param	None
 * @return	请求码
 */
Request GetRequest(void);


/**
 * @brief	向应用端发送一个响应
 * @param	res 响应码
 * @return	None
 */
void SendResponse(Request res);

/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
