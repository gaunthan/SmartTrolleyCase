/***************************************************************************************
*        File Name              :	GPS_H
*        CopyRight              :	gaunthan
*        ModuleName             :	GPS
*
*        CPU                    :   MSP430
*        RTOS                   :   None
*
*        Create Data            :	2016/5/7
*        Author/Corportation    :	gaunthan
*
*        Abstract Description   :	封装UBLOX-6M GPS模块，提供地理参数获取接口。
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/7	gaunthan        		 	Create this file
*		2		v1.1		2016/5/9	gaunthan		nmea		移植nmea库
*		3		v2.0		2016/5/10	gaunthan					移出nmea库，自己实现协议的解码
*		4		v2.1		2016/5/15	gaunthan		comment		为代码添加详细的注释
*
***************************************************************************************/

/**************************************************************
*        Multi-Include-Prevent Section
**************************************************************/
#ifndef GPS_H
#define GPS_H

/**************************************************************
*        Debug switch Section
**************************************************************/
/**
 * GPS模块调试开关宏。1代表开启调试信息，0代表不开启。
 */
#define GPS_DEBUG_ON 0


/**
 * GPS模块数据缓冲区大小定义
 */
#define GPS_BUFF_SIZE 512


/**
 * 正常情况下，GPGLL命令的长度为50
 */
#define NMEA_GPGLL_LENGTH 50

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
/**
 * NMEA协议解析后的字段，只包含一些本项目需要的字段。
 */
typedef struct {
	double longitude;	//经度，格式为：dddmm.mmmmm
	double latitude;	//纬度，格式为：ddmm.mmmmm
	unsigned long utc;	//UTC时间，格式为：hhmmss
	char status;		//定位状态，A=有效定位，V=无效定位
}NMEA_msg;

/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief	初始化GPS模块与相关引脚。
 * @param	None
 * @return	None
 */
void GPS_InitPort(void);


/**
 * 从GPS模块获得经度和纬度信息，其将保存在结构中。
 */
Status GPS_GetPosition(NMEA_msg *msg);


/**
 * @brief	供调试使用，打印msg各成员。
 * @param	msg 解码信息结构体指针
 * @return	None
 */
void GPS_ShowPosition(NMEA_msg *msg);


/**
 * @brief	获取经纬度并按格式XX,XX放置到输出缓冲区buf中
 * @param	buf 输出缓冲区
 * 			bufSize 缓冲区大小
 * @return	OK 操作成功
 * 			ERROR 操作失败
 */
Status GPS_PutLocation(char *buf, int bufSize);


/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
