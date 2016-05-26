#include "GPS.h"

/**
 * @brief	������Ϣ����궨��
 */
#if GPS_DEBUG_ON
	#include <stdio.h>
	#define GPS_DEBUG(str) printf(str)
#else
	#define GPS_DEBUG(str)
#endif



/**
 * @brief	���ݻ����������ڻ����GPSģ����յ������ݡ�
 */
static char GPS_Buf[GPS_BUFF_SIZE + 1] = {0};


/**
 * @brief	��GPSģ���ȡһ���ַ�
 * @param	None
 * @return	һ���ַ�
 */
static inline char GPS_Getchar(void)
{
	return AppUart_getChar();
}


/**
 * @brief	��ʼ��GPSģ����������š�
 * @param	None
 * @return	None
 */
void GPS_InitPort(void)
{
	AppUart_init();
}




/**
 * @brief	��GPSģ����size�ֽڵĵ���λ��ԭʼ��Ϣ������洢��buf�С�
 * @param	buf ��������ַ
 * 			size ��������С
 * @return	OK �ɹ���ȡ����
 * 			ERROR ��ȡʧ��
 */
static Status GPS_GetData(char *buf, int size)
{
	int i;

	if(NULL == buf || size < 0) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	for(i = 0; i < size; ++i) {
		buf[i] = GPS_Getchar();
	}
	return OK;
}



/**
 * @brief	��ȡ��buf����ʼ��cx�����ŵ�λ�á�
 */
static char *NMEA_GetCommaPos(char *buf, int cx)
{
	char *p = buf;

	if(NULL == buf || cx < 0)
		return NULL;

	while(cx) {
		if(*p == '*' || *p < ' ' ||  *p > 'z')	/* �������ַ�  */
			return NULL;
		if(*p == ',')
			cx--;
		p++;
	}

	return p;
}


/**
 * @brief	����ָ���������е�GPGLL������������msg�С�
 * @param	buf ��Ҫ����Ļ�������ַ
 * 			size ��������С
 * 			msg �ṹ��ָ�룬ָ�򽫴�Ž�������Ϣ�Ľṹ��
 * @return	OK ����ɹ�
 * 			ERROR ����ʧ��
 */
static Status NMEA_DecodeGPGLL(const char *buf, int size, NMEA_msg *msg)
{
	char *cmd;
	char *arg;
	double dtmp;
	long ltmp;

	cmd = strstr(buf, "$GPGLL");	/* ����GPGLL������ʼλ�� */
	if(NULL == cmd)	/* ���������޴�������Ϣ */
		return ERROR;
	else if(cmd + NMEA_GPGLL_LENGTH > buf + size)	/* GPGLL����ĳ���ΪNMEA_GPGLL_LENGTH�ֽ� */
		return ERROR;
	else if(*(cmd + 7) == ',' && *(cmd + 8) == ',')	/* �����б��������������ţ�����δ�����ȷ���� */
		return ERROR;
	else {	/* ������Ч */
		arg = NMEA_GetCommaPos(cmd, 1);	/* ��õ�һ������λ�ã�γ�ȣ�*/
		if(NULL != arg) {
			dtmp = atof(arg);	/* γ�ȸ�ʽ��ddmm.mmmmm */
			ltmp = (long)dtmp;
			msg->latitude = ((dtmp - ltmp) + ltmp % 100) / 60 + ltmp / 100;
		}

		arg = NMEA_GetCommaPos(arg, 2); /* ��õ���������λ�� �����ȣ�*/
		if(NULL != arg) {
			dtmp = atof(arg);	/* ���ȸ�ʽ��dddmm.mmmmm */
			ltmp = (long)dtmp;
			msg->longitude = ((dtmp - ltmp) + ltmp % 100) / 60 + ltmp / 100;
		}

		arg = NMEA_GetCommaPos(arg, 2); /* ��õ��������λ�� ��UTC��*/
		if(NULL != arg)
			msg->utc = atoi(arg);

		arg = NMEA_GetCommaPos(arg, 1); /* ��õ���������λ�� ����λ״̬��*/
		if(NULL != arg)
			msg->status = *arg == 'A' ? 1 : 0;

		return OK;
	}
}


/**
 * ��GPSģ���þ��Ⱥ�γ����Ϣ���佫�����ڽṹ�С�
 */
Status GPS_GetPosition(NMEA_msg *msg)
{
	if(NULL == msg) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	//��ȡGPSԭʼ����
	if(ERROR == GPS_GetData(GPS_Buf, GPS_BUFF_SIZE)) {
		GPS_DEBUG("GPS: Error in GPS_GetData().\r\n");
		return ERROR;
	}

	//���������Ϣ
	return NMEA_DecodeGPGLL(GPS_Buf, GPS_BUFF_SIZE, msg);
}



/**
 * @brief	��ȡ��γ�Ȳ�����ʽXX,XX���õ����������buf��
 * @param	buf ���������
 * 			bufSize ��������С
 * @return	OK �����ɹ�
 * 			ERROR ����ʧ��
 */
Status GPS_PutLocation(char *buf, int bufSize)
{
	NMEA_msg msg;
	char tmpBuf[16];

	if(NULL == buf || bufSize < 32)
		return ERROR;

	if(OK == GPS_GetPosition(&msg)) {
		/* ����γ�ȵ���������� */
		ftoa(buf, msg.latitude, 6);

		/* ���þ��ȵ���������� */
		strcat(buf, ",");
		ftoa(tmpBuf, msg.longitude, 6);
		strcat(buf, tmpBuf);

		return OK;
	}
	else {
		GPS_DEBUG("GPS ERROR: Get position failed.\n");
		return ERROR;
	}
}




/**
 * @brief	������ʹ�ã���ӡmsg����Ա��
 * @param	msg ������Ϣ�ṹ��ָ��
 * @return	None
 */
void GPS_ShowPosition(NMEA_msg *msg)
{
	char buf[32];

	GPS_DEBUG("\r\nLocation: ");
	ftoa(buf, msg->longitude, 6);
	GPS_DEBUG(buf);

	GPS_DEBUG(",");

	ftoa(buf, msg->latitude, 6);
	GPS_DEBUG(buf);

	GPS_DEBUG("\r\nUTC��");
	GPS_DEBUG(numToStr(buf, msg->utc));

	GPS_DEBUG("\r\nStatus��");
	GPS_DEBUG(numToStr(buf, msg->status));
}
