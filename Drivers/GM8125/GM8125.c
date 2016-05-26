#include "GM8125.h"

/**
 * @brief	������Ϣ����궨��
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GM8125_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define GM8125_DEBUG(fmt, args...)
#endif



/**
 * @brief	�����������ֵ
 */
#define GM8125_SetPin(pin, value)					\
	do {										\
		if(value)								\
			P2OUT |= pin;						\
		else									\
			P2OUT &= ~pin;						\
	}while(0)




/**
 * @brief	��ʼ��GM8125ģ��Ӳ������
 * @param	None
 * @return	None
 */
void GM8125_InitPort(void)
{
	P2DIR |= STADD0 | STADD1 | STADD2 | SRADD0 | SRADD1 | SRADD2;
}



/**
 * @brief	ѡ����ĸͨ��ͨ�ŵ���ͨ��
 * @param	channel ͨ��ֵ����ѡΪ1~5
 * @return	None
 */
void GM8125_SelectChannel(GM8125_Channel channel)
{
	switch(channel) {
		case GM8125_CHANNEL1:	/* ͨ��2�ĵ�ֵַΪ001 */
			GM8125_SetPin(STADD0, 1);
			GM8125_SetPin(STADD1, 0);
			GM8125_SetPin(STADD2, 0);

			GM8125_SetPin(SRADD0, 1);
			GM8125_SetPin(SRADD1, 0);
			GM8125_SetPin(SRADD2, 0);
			break;

		case GM8125_CHANNEL2:	/* ͨ��2�ĵ�ֵַΪ010 */

			GM8125_SetPin(STADD0, 0);
			GM8125_SetPin(STADD1, 1);
			GM8125_SetPin(STADD2, 0);

			GM8125_SetPin(SRADD0, 0);
			GM8125_SetPin(SRADD1, 1);
			GM8125_SetPin(SRADD2, 0);
			break;

		case GM8125_CHANNEL3:	/* ͨ��3�ĵ�ֵַΪ011 */

			GM8125_SetPin(STADD0, 1);
			GM8125_SetPin(STADD1, 1);
			GM8125_SetPin(STADD2, 0);

			GM8125_SetPin(SRADD0, 1);
			GM8125_SetPin(SRADD1, 1);
			GM8125_SetPin(SRADD2, 0);
			break;

		case GM8125_CHANNEL4:	/* ͨ��4�ĵ�ֵַΪ100 */

			GM8125_SetPin(STADD0, 0);
			GM8125_SetPin(STADD1, 0);
			GM8125_SetPin(STADD2, 1);

			GM8125_SetPin(SRADD0, 0);
			GM8125_SetPin(SRADD1, 0);
			GM8125_SetPin(SRADD2, 1);
			break;

		case GM8125_CHANNEL5:	/* ͨ��1�ĵ�ֵַΪ101 */

			GM8125_SetPin(STADD0, 1);
			GM8125_SetPin(STADD1, 0);
			GM8125_SetPin(STADD2, 1);

			GM8125_SetPin(SRADD0, 1);
			GM8125_SetPin(SRADD1, 0);
			GM8125_SetPin(SRADD2, 1);
			break;

		default:
			GM8125_DEBUG("ERROR: Channel not support!\r\n");
	}

}
