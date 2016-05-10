#include "GPS.h"

/**
 * ���ݻ����������ڻ����GPSģ����յ������ݡ�
 */
char GPS_Buf[GPS_RBUFF_SIZE + 1] = {0};


/**
 * ��GPSģ���ȡһ���ֽ�
 */
static inline unsigned char GPS_GetByte(void)
{
	return AppUart_getChar();
}


/**
 * ��GPSģ�鷢��һ���ֽ�
 */
static inline void GPS_SendByte(unsigned char b)
{
	AppUart_putChar(b);
}


/**
 * ��ʼ��GPSģ����������š�
 */
void GPS_Init(void)
{
	AppUart_init();
}


/**
 * ��GPSģ����size�ֽڵĵ���λ��ԭʼ��Ϣ������洢��buf�С�
 */
static Status GPS_GetData(char *buf, int size)
{
	int i;

	if(NULL == buf || size < 0) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	for(i = 0; i < size; ++i) {
		buf[i] = GPS_GetByte();
	}
	return OK;
}



/**
 * ��ȡ��buf����ʼ��cx�����ŵ�λ�á�
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
 * ����ָ���������е�GPGLL������������msg�С�
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
	if(ERROR == GPS_GetData(GPS_Buf, GPS_RBUFF_SIZE)) {
		GPS_DEBUG("GPS: Error in GPS_GetData().\r\n");
		return ERROR;
	}

	//���������Ϣ
	return NMEA_DecodeGPGLL(GPS_Buf, GPS_RBUFF_SIZE, msg);
}




/**
 * ������nת��Ϊ�ַ���������洢��buf�С���������buf��
 */
static char *numToStr(char *buf, int n)
{
   int i = 0, j = 0, tmp;

   if(NULL == buf) {
	   return NULL;
   }else if(n < 0) {
	   buf[i++] = '-';
	   j = 1;
	   n = -n;
   }

   /* ��num��λת��Ϊchar */
   while(n > 0) {
	   buf[i++] = n % 10 + '0';
	   n /= 10;
   }

   /* ��ַ��������� */
   buf[i--] = '\0';

   /* ���ַ������� */
   for(; j < i; ++j, --i) {
	   tmp = buf[j];
	   buf[j] = buf[i];
	   buf[i] = tmp;
   }

   return buf;
}



int ftoa(char *str, float num, int n)        //n��ת���ľ��ȣ������ַ���'.'���м�λС��
{
    int     sumI;
    float   sumF;
    int     sign = 0;
    int     temp;
    int     count = 0;

    char *p;
    char *pp;

    if(str == NULL) return -1;
    p = str;

    /*Is less than 0*/
    if(num < 0)
    {
        sign = 1;
        num = 0 - num;
    }

    sumI = (int)num;    //sumI is the part of int
    sumF = num - sumI;  //sumF is the part of float

    /*Int ===> String*/
    do
    {
        temp = sumI % 10;
        *(str++) = temp + '0';
    }while((sumI = sumI /10) != 0);


    /*******End*******/

    if(sign == 1)
    {
        *(str++) = '-';
    }

    pp = str;

    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }

    *(str++) = '.';     //point

    /*Float ===> String*/
    do
    {
        temp = (int)(sumF*10);
        *(str++) = temp + '0';

        if((++count) == n)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));

    *str = '/0';

    return 0;

}


/**
 * ������ʹ�ã���ӡmsg����Ա��
 */
void GPS_ShowPosition(NMEA_msg *msg)
{
	char buf[32];

	GPS_DEBUG("\r\n��γ�ȣ�");
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
