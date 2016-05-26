#include "GPS.h"

/**
 * @brief	调试信息输出宏定义
 */
#if GPS_DEBUG_ON
	#include <stdio.h>
	#define GPS_DEBUG(str) printf(str)
#else
	#define GPS_DEBUG(str)
#endif



/**
 * @brief	数据缓冲区，用于缓存从GPS模块接收到的数据。
 */
static char GPS_Buf[GPS_BUFF_SIZE + 1] = {0};


/**
 * @brief	从GPS模块读取一个字符
 * @param	None
 * @return	一个字符
 */
static inline char GPS_Getchar(void)
{
	return AppUart_getChar();
}


/**
 * @brief	初始化GPS模块与相关引脚。
 * @param	None
 * @return	None
 */
void GPS_InitPort(void)
{
	AppUart_init();
}




/**
 * @brief	从GPS模块获得size字节的地理位置原始信息，将其存储在buf中。
 * @param	buf 缓冲区地址
 * 			size 缓冲区大小
 * @return	OK 成功获取数据
 * 			ERROR 获取失败
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
 * @brief	获取自buf处开始第cx个逗号的位置。
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
 * @brief	解码指定缓冲区中的GPGLL命令，结果将存在msg中。
 * @param	buf 需要解码的缓冲区地址
 * 			size 缓冲区大小
 * 			msg 结构体指针，指向将存放解码后的信息的结构体
 * @return	OK 解码成功
 * 			ERROR 解码失败
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
	if(ERROR == GPS_GetData(GPS_Buf, GPS_BUFF_SIZE)) {
		GPS_DEBUG("GPS: Error in GPS_GetData().\r\n");
		return ERROR;
	}

	//解码地理信息
	return NMEA_DecodeGPGLL(GPS_Buf, GPS_BUFF_SIZE, msg);
}



/**
 * @brief	获取经纬度并按格式XX,XX放置到输出缓冲区buf中
 * @param	buf 输出缓冲区
 * 			bufSize 缓冲区大小
 * @return	OK 操作成功
 * 			ERROR 操作失败
 */
Status GPS_PutLocation(char *buf, int bufSize)
{
	NMEA_msg msg;
	char tmpBuf[16];

	if(NULL == buf || bufSize < 32)
		return ERROR;

	if(OK == GPS_GetPosition(&msg)) {
		/* 放置纬度到输出缓冲区 */
		ftoa(buf, msg.latitude, 6);

		/* 放置经度到输出缓冲区 */
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
 * @brief	供调试使用，打印msg各成员。
 * @param	msg 解码信息结构体指针
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

	GPS_DEBUG("\r\nUTC：");
	GPS_DEBUG(numToStr(buf, msg->utc));

	GPS_DEBUG("\r\nStatus：");
	GPS_DEBUG(numToStr(buf, msg->status));
}
