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
*        Abstract Description   :	��װUBLOX-6M GPSģ�飬�ṩ���������ȡ�ӿڡ�
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/7	gaunthan        		 	Create this file
*		2		v1.1		2016/5/9	gaunthan		nmea		��ֲnmea��
*		3		v2.0		2016/5/10	gaunthan					�Ƴ�nmea�⣬�Լ�ʵ��Э��Ľ���
*		4		v2.1		2016/5/15	gaunthan		comment		Ϊ���������ϸ��ע��
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
 * GPSģ����Կ��غꡣ1������������Ϣ��0����������
 */
#define GPS_DEBUG_ON 0


/**
 * GPSģ�����ݻ�������С����
 */
#define GPS_BUFF_SIZE 512


/**
 * ��������£�GPGLL����ĳ���Ϊ50
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
 * NMEAЭ���������ֶΣ�ֻ����һЩ����Ŀ��Ҫ���ֶΡ�
 */
typedef struct {
	double longitude;	//���ȣ���ʽΪ��dddmm.mmmmm
	double latitude;	//γ�ȣ���ʽΪ��ddmm.mmmmm
	unsigned long utc;	//UTCʱ�䣬��ʽΪ��hhmmss
	char status;		//��λ״̬��A=��Ч��λ��V=��Ч��λ
}NMEA_msg;

/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief	��ʼ��GPSģ����������š�
 * @param	None
 * @return	None
 */
void GPS_InitPort(void);


/**
 * ��GPSģ���þ��Ⱥ�γ����Ϣ���佫�����ڽṹ�С�
 */
Status GPS_GetPosition(NMEA_msg *msg);


/**
 * @brief	������ʹ�ã���ӡmsg����Ա��
 * @param	msg ������Ϣ�ṹ��ָ��
 * @return	None
 */
void GPS_ShowPosition(NMEA_msg *msg);


/**
 * @brief	��ȡ��γ�Ȳ�����ʽXX,XX���õ����������buf��
 * @param	buf ���������
 * 			bufSize ��������С
 * @return	OK �����ɹ�
 * 			ERROR ����ʧ��
 */
Status GPS_PutLocation(char *buf, int bufSize);


/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
