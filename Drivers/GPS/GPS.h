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
#define GPS_DEBUG_ON 1


/**
 * GPSģ�����ݻ�������С����
 */
#define GPS_RBUFF_SIZE 512

/**************************************************************
*        Include File Section
**************************************************************/
#include "HAL_AppUart.h"
#include "nmea/nmea.h"
#include "general.h"
#include <stdlib.h>


/**************************************************************
*        Macro Define Section
**************************************************************/

/**
 * @brief	������Ϣ����궨��
 */
#if GPS_DEBUG_ON
	#include <stdio.h>
	#define GPS_DEBUG(str) printf(str)
#else
	#define GPS_DEBUG(str)
#endif

/**************************************************************
*        Struct Define Section
**************************************************************/
/**
 * ����λ�ýṹ���壬��Ա�о��Ⱥ�γ�ȡ�
 */
typedef struct geoPos {
	double lat;		/* ���� */
	double lon;		/* γ�� */
}GeoPos;

/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * ��ʼ��GPSģ����������š�
 */
void GPS_Init(void);


/**
 * ��GPSģ���þ��Ⱥ�γ����Ϣ���佫�����ڽṹGeoPos�С�
 */
Status GPS_GetPosition(GeoPos *pos);


/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
