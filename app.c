#include "app.h"






/**
 * @brief	��ʼ��ϵͳ��ģ��Ӳ������
 * @param	None
 * @return	None
 */
void ModulesInit(void)
{
	AppUart_init();
	GM8125_InitPort();
	GPS_InitPort();
	GPRS_InitPort();
	BT_InitPort();
}


/**
 * @brief	��Զ�̷������ϱ�����λ����Ϣ
 * @param	None
 * @return	None
 */
void ReportLocation(void)
{
	char sendBuf[128];
	char tmpBuf[64];
	char devCode[32];

	GM8125_SelectChannel(GPRS_CHANNEL);

	/* ��ȡ�豸�벢���뷢�ͻ����� */
	GPRS_GetDevCode(devCode, sizeof(devCode));

	if(OK == GPRS_InitTCPEnv()) { /* ��ʼ��TCP�����ɹ� */
		if(OK == GPRS_InitSMTP()) {
			/* ��䷢�ͻ����� */
			do {

				/* ѡ��ͨ��1����ͨ��1��ȡGPS��Ϣ */
				GM8125_SelectChannel(GPR_CHANNEL);
				while(ERROR == GPS_PutLocation(tmpBuf, sizeof(tmpBuf))) {};

				/* �ɹ���ȡ������Ϣ����װ��Ϣ */
				sendBuf[0] = '\0';
				strcat(sendBuf, devCode);
				strcat(sendBuf, "\r\n");
				strcat(sendBuf, tmpBuf);
				strcat(sendBuf, "\r\n");

				/* ѡ��ͨ��2��ʹMCU��GPRSģ��ͨ�� */
				GM8125_SelectChannel(GPRS_CHANNEL);
			}while(OK == GPRS_SendMail(sendBuf));	/* �������ʼ�ֱ������ʧ�� */

			GPRS_RebootDev();	/* ����ʧ�ܣ������豸 */
		}
	}
}



/**
 * @brief	��Ӧ�ö˽���һ������
 * @param	None
 * @return	������
 */
Request GetRequest(void)
{
	return (Request)BT_Getchar();
}


/**
 * @brief	��Ӧ�ö˷���һ����Ӧ
 * @param	res ��Ӧ��
 * @return	None
 */
void SendResponse(Response res)
{
	BT_Putchar((Response)res);
}

