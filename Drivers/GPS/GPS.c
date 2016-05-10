#include "GPS.h"

/**
 * 数据缓冲区，用于缓存从GPS模块接收到的数据。
 */
char GPS_Buf[GPS_RBUFF_SIZE + 1] = {0};


/**
 * 从GPS模块读取一个字节
 */
static inline unsigned char GPS_GetByte(void)
{
	return AppUart_getChar();
}


/**
 * 向GPS模块发送一个字节
 */
static inline void GPS_SendByte(unsigned char b)
{
	AppUart_putChar(b);
}


/**
 * 初始化GPS模块与相关引脚。
 */
void GPS_Init(void)
{
	AppUart_init();
}


/**
 * 从GPS模块获得size字节的地理位置原始信息，将其存储在buf中。
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
 * 获取自buf处开始第cx个逗号的位置。
 */
static char *NMEA_GetCommaPos(char *buf, int cx)
{
	char *p = buf;

	if(NULL == buf || cx < 0)
		return NULL;

	while(cx) {
		if(*p == '*' || *p < ' ' ||  *p > 'z')	/* 非命令字符  */
			return NULL;
		if(*p == ',')
			cx--;
		p++;
	}

	return p;
}


/**
 * 解码指定缓冲区中的GPGLL命令，结果将存在msg中。
 */
static Status NMEA_DecodeGPGLL(const char *buf, int size, NMEA_msg *msg)
{
	char *cmd;
	char *arg;
	double dtmp;
	long ltmp;

	cmd = strstr(buf, "$GPGLL");	/* 解析GPGLL命令起始位置 */
	if(NULL == cmd)	/* 缓冲区中无此命令信息 */
		return ERROR;
	else if(cmd + NMEA_GPGLL_LENGTH > buf + size)	/* GPGLL命令的长度为NMEA_GPGLL_LENGTH字节 */
		return ERROR;
	else if(*(cmd + 7) == ',' && *(cmd + 8) == ',')	/* 参数列表连续有两个逗号，表明未获得正确数据 */
		return ERROR;
	else {	/* 数据有效 */
		arg = NMEA_GetCommaPos(cmd, 1);	/* 获得第一个参数位置（纬度）*/
		if(NULL != arg) {
			dtmp = atof(arg);	/* 纬度格式：ddmm.mmmmm */
			ltmp = (long)dtmp;
			msg->latitude = ((dtmp - ltmp) + ltmp % 100) / 60 + ltmp / 100;
		}

		arg = NMEA_GetCommaPos(arg, 2); /* 获得第三个参数位置 （经度）*/
		if(NULL != arg) {
			dtmp = atof(arg);	/* 经度格式：dddmm.mmmmm */
			ltmp = (long)dtmp;
			msg->longitude = ((dtmp - ltmp) + ltmp % 100) / 60 + ltmp / 100;
		}

		arg = NMEA_GetCommaPos(arg, 2); /* 获得第五个参数位置 （UTC）*/
		if(NULL != arg)
			msg->utc = atoi(arg);

		arg = NMEA_GetCommaPos(arg, 1); /* 获得第六个参数位置 （定位状态）*/
		if(NULL != arg)
			msg->status = *arg == 'A' ? 1 : 0;

		return OK;
	}
}


/**
 * 从GPS模块获得经度和纬度信息，其将保存在结构中。
 */
Status GPS_GetPosition(NMEA_msg *msg)
{
	if(NULL == msg) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	//获取GPS原始数据
	if(ERROR == GPS_GetData(GPS_Buf, GPS_RBUFF_SIZE)) {
		GPS_DEBUG("GPS: Error in GPS_GetData().\r\n");
		return ERROR;
	}

	//解码地理信息
	return NMEA_DecodeGPGLL(GPS_Buf, GPS_RBUFF_SIZE, msg);
}




/**
 * 将整型n转换为字符串，结果存储在buf中。函数返回buf。
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

   /* 将num各位转换为char */
   while(n > 0) {
	   buf[i++] = n % 10 + '0';
	   n /= 10;
   }

   /* 填补字符串结束符 */
   buf[i--] = '\0';

   /* 将字符串逆序 */
   for(; j < i; ++j, --i) {
	   tmp = buf[j];
	   buf[j] = buf[i];
	   buf[i] = tmp;
   }

   return buf;
}



int ftoa(char *str, float num, int n)        //n是转换的精度，即是字符串'.'后有几位小数
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
 * 供调试使用，打印msg各成员。
 */
void GPS_ShowPosition(NMEA_msg *msg)
{
	char buf[32];

	GPS_DEBUG("\r\n经纬度：");
	ftoa(buf, msg->longitude, 6);
	GPS_DEBUG(buf);

	GPS_DEBUG(",");

	ftoa(buf, msg->latitude, 6);
	GPS_DEBUG(buf);

	GPS_DEBUG("\r\nUTC：");
	GPS_DEBUG(numToStr(buf, msg->utc));

	GPS_DEBUG("\r\nStatus：");
	GPS_DEBUG(numToStr(buf, msg->status));
}
