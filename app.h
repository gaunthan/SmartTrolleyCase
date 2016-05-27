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
 * ģ����Կ��غꡣ1������������Ϣ��0����������
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
 * @brief	����ģ�������Ӵ��ڣ�ͨ����
 */
#define GPR_CHANNEL GM8125_CHANNEL1
#define GPRS_CHANNEL GM8125_CHANNEL2
#define BLUETOOTH_CHANNEL GM8125_CHANNEL3


/**
 * @brief	ѡ�񴮿�ͨ��ͨ��
 */
#define SelectChannel(chan) GM8125_SelectChannel(chan)

/**************************************************************
*        Struct Define Section
**************************************************************/
/**
 * @brief	���� APP����ʹ�õ������ź�
 */
typedef enum {
	 SYS_START = 0x01,		/* ������ϵͳ���� */
	 KEEP_ALIVE = 0x02,		/* �������ӻ��� */
	 GET_WEIGHT = 0x04,		/* �����ȡϵͳ������Ϣ */
	 UNLOCK_DEVICE = 0x08,	/* ��������豸 */

}Request;


/**************************************************************
*        Prototype Declare Section
**************************************************************/

/**
 * @brief	���ÿ����壬ʹ�䴦����������ģʽ
 * @param	None
 * @return	None
 */
void SystemInit(void);


/**
 * @brief	��ʼ��ϵͳ��ģ��Ӳ������
 * @param	None
 * @return	None
 */
void ModulesInit(void);


/**
 * @brief	��Զ�̷������ϱ�����λ����Ϣ
 * @param	None
 * @return	None
 */
void ReportLocation(void);


/**
 * @brief	��Ӧ�ö˽���һ������
 * @param	None
 * @return	������
 */
Request GetRequest(void);


/**
 * @brief	��Ӧ�ö˷���һ����Ӧ
 * @param	res ��Ӧ��
 * @return	None
 */
void SendResponse(Request res);

/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
