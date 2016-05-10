#include "GPS.h"

nmeaINFO info;          //GPS�����õ�����Ϣ
nmeaPARSER parser;      //����ʱʹ�õ����ݽṹ

u8 GPS_Buf[GPS_RBUFF_SIZE];


/**
 * ��GPSģ���ȡһ���ֽ�
 */
static u8 GPS_GetByte(void)
{
	return AppUart_getChar();
}


/**
 * ��GPSģ�鷢��һ���ֽ�
 */
static void GPS_SendByte(u8 b)
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
 * @param 	None
 * @return	��������ַ
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
 * ��GPSģ���þ��Ⱥ�γ����Ϣ���佫�����ڽṹGeoPos�С�
 */
Status GPS_GetPosition(GeoPos *pos)
{
	if(NULL == pos) {
		GPS_DEBUG("GPS: Invalid argument.\r\n");
		return ERROR;
	}

	//��ȡGPSԭʼ����
	if(ERROR == GPS_GetData(GPS_Buf, GPS_RBUFF_SIZE)) {
		GPS_DEBUG("GPS: Error in GPS_GetData().\r\n");
		return ERROR;
	}else
		GPS_DEBUG("GPS: Data received.\r\n");

	//���������Ϣ
    if(nmea_parse(&parser, GPS_Buf, GPS_RBUFF_SIZE, &info) <= 0) {
		GPS_DEBUG("GPS: no data be parsed.\r\n");
		return ERROR;
    }else
    	GPS_DEBUG("Pared data...\r\n");

	if(0 == info.sig) {    /* ��λ��Ч */
		GPS_DEBUG("GPS: Location not get.\r\n");
		return ERROR;
	}else {
		pos->lat = info.lat;
		pos->lon = info.lon;
		return OK;
	}
}
