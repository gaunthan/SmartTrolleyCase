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
*        Abstract Description   :	��װBluetooth�����շ�����
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
 * ģ����Կ��غꡣ1������������Ϣ��0����������
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
 * @brief	��ʼ������ģ����������š�
 * @param	None
 * @return	None
 */
void BT_InitPort(void);


/**
 * @brief	������ģ�鷢��һ���ַ�
 * @param	ch ��Ҫ���͵��ַ�
 * @return	None
 */
void BT_Putchar(char ch);


/**
 * @brief	������ģ���ȡһ���ַ�
 * @param	None
 * @return	һ���ַ�
 */
char BT_Getchar(void);


/**
 * @brief	������ģ�鷢��һ���ַ�����ĩβ׷��<CR><LF>
 * @param	str ��Ҫ���͵��ַ���
 * @return	None
 */
void BT_Println(const char *str);


/**
 * @brief	������ģ���ȡһ���ַ�������<CR><LF>��־�����ַ����Ľ������������ַ������������ضϡ�
 * @param	buf ���������
 *			n ��������С
 * @return	None
 */
void BT_Gets(char *buf, int n);

/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
