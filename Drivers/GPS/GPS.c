#include "GPS.h"

nmeaINFO info;          //GPS解码后得到的信息
nmeaPARSER parser;      //解码时使用的数据结构

u8 GPS_Buf[GPS_RBUFF_SIZE];


/**
 * 从GPS模块读取一个字节
 */
static u8 GPS_GetByte(void)
{
	return AppUart_getChar();
}


/**
 * 向GPS模块发送一个字节
 */
static void GPS_SendByte(u8 b)
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
 * @param 	None
 * @return	缓冲区地址
 */
static Status GPS_GetData(u8 *buf, int size)
{
	int i;

	if(NULL == buf || size < 0) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	for(i = 0; i < size; ++i) {
		buf[i] = GPS_GetByte();
		GPS_SendByte(buf[i]);
	}
	return OK;
}


/**
 * 从GPS模块获得经度和纬度信息，其将保存在结构GeoPos中。
 */
Status GPS_GetPosition(GeoPos *pos)
{
	if(NULL == pos) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	//获取GPS原始数据
	if(ERROR == GPS_GetData(GPS_Buf, GPS_RBUFF_SIZE)) {
		GPS_DEBUG("GPS: Error in GPS_GetData().\r\n");
		return ERROR;
	}else
		GPS_DEBUG("GPS: Data received.\r\n");

	//解码地理信息
    if(nmea_parse(&parser, GPS_Buf, GPS_RBUFF_SIZE, &info) <= 0) {
		GPS_DEBUG("GPS: no data be parsed.\r\n");
		return ERROR;
    }else
    	GPS_DEBUG("Pared data...\r\n");

	if(0 == info.sig) {    /* 定位无效 */
		GPS_DEBUG("GPS: Location not get.\r\n");
		return ERROR;
	}else {
		pos->lat = info.lat;
		pos->lon = info.lon;
		return OK;
	}
}
