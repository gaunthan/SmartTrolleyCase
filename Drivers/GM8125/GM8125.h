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
*        Abstract Description   :	��װGM8125ģ�鵥ͨ��ģʽ�µĿ��Ʋ������ṩѡ�񴮿���ͨ��������
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
 * ģ����Կ��غꡣ1������������Ϣ��0����������
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

/* ��������ͨ����ַ���� */
#define STADD2 0
#define STADD1 BIT1
#define STADD0 BIT0

/* �������ͨ����ַ���� */
#define SRADD2 0
#define SRADD1 BIT4
#define SRADD0 BIT3



/**************************************************************
*        Struct Define Section
**************************************************************/


/**
 * @brief	������ͨ����ʶ����
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
 * @brief	��ʼ��GM8125ģ��Ӳ������
 * @param	None
 * @return	None
 */
void GM_InitPort(void);


/**
 * @brief	ѡ����ĸͨ��ͨ�ŵ���ͨ��
 * @param	channel ͨ��ֵ����ѡΪ1~5
 * @return	None
 */
void GM_SelectChannel(GM_Channel channel);



/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
