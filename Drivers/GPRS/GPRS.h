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
*        Abstract Description   :	��װSIM900A_mini GPSģ�飬�ṩ�����ʼ����ܡ�
*
*--------------------------------Revision History--------------------------------------
*       No      version     Date        Revised By      Item        Description
*       1       v1.0        2016/5/15	gaunthan        		 	Create this file
*       2		v2.0		2016/5/16	gaunthan		email		����TCP��SMTPʵ�ַ����ʼ�����
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
 * GPRSģ����Կ��غꡣ1������������Ϣ��0����������
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
 * @brief	��ʼ��GPSģ����������š�
 * @param	None
 * @return	OK ��ʼ���ɹ�
			ERROR ��ʼ��ʧ��
 */
Status GPRS_Init(void);


/**
 * @brief	����GPRS TCP����
 * @param	None
 * @return	OK ��ʼ���ɹ�
 * 			ERROR ��ʼ��ʧ��
 */
Status GPRS_InitTCPEnv(void);


/**
 * @brief	��ʼ��SMTP������������163�������������֤
 * @param	None
 * @return	OK ��ʼ���ɹ�
 *			ERROR ��ʼ��ʧ��
 */
Status GPRS_InitSMTP(void);


/**
 * @brief	ͨ��SMTPЭ�鷢��һ������Ϊmsg���ʼ�
 * @param	msg ��Ҫ���͵���Ϣ
 * @return	OK ���ͳɹ�
 *			ERROR ����ʧ��
 */
Status GPRS_SendMail(char *msg);


/**
 * @brief	��ȡGPRSģ��Ĳ�Ʒ���к�
 * @param	buf �����������ڴ洢��ȡ�������к�
 * 			bufSize ��������С
 * @return	OK ��ȡ�ɹ�
 *			ERROR ��ȡʧ��
 */
Status GPRS_GetDevCode(char *buf, int bufSize);

/**
 * @brief	����GPRSģ��
 * @param	None
 * @return	OK �����ɹ�
 *			ERROR ����ʧ��
 */
Status GPRS_RebootDev(void);

/**************************************************************
*        End-Multi-Include-Prevent Section
**************************************************************/
#endif
