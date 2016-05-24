#include "GM8125.h"

/**
 * @brief	������Ϣ����궨��
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GM_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define GM_DEBUG(fmt, args...)
#endif



/**
 * @brief	�����������ֵ
 */
#define GM_SetPin(pin, value)					\
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
void GM_InitPort(void)
{
	P2DIR |= STADD0 | STADD1 | STADD2 | SRADD0 | SRADD1 | SRADD2;
}



/**
 * @brief	ѡ����ĸͨ��ͨ�ŵ���ͨ��
 * @param	channel ͨ��ֵ����ѡΪ1~5
 * @return	None
 */
void GM_SelectChannel(GM_Channel channel)
{
	switch(channel) {
		case GM_CHANNEL1:	/* ͨ��2�ĵ�ֵַΪ001 */
			GM_SetPin(STADD0, 1);
			GM_SetPin(STADD1, 0);
			GM_SetPin(STADD2, 0);

			GM_SetPin(SRADD0, 1);
			GM_SetPin(SRADD1, 0);
			GM_SetPin(SRADD2, 0);
			break;

		case GM_CHANNEL2:	/* ͨ��2�ĵ�ֵַΪ010 */

			GM_SetPin(STADD0, 0);
			GM_SetPin(STADD1, 1);
			GM_SetPin(STADD2, 0);

			GM_SetPin(SRADD0, 0);
			GM_SetPin(SRADD1, 1);
			GM_SetPin(SRADD2, 0);
			break;

		case GM_CHANNEL3:	/* ͨ��3�ĵ�ֵַΪ011 */

			GM_SetPin(STADD0, 1);
			GM_SetPin(STADD1, 1);
			GM_SetPin(STADD2, 0);

			GM_SetPin(SRADD0, 1);
			GM_SetPin(SRADD1, 1);
			GM_SetPin(SRADD2, 0);
			break;

		case GM_CHANNEL4:	/* ͨ��4�ĵ�ֵַΪ100 */

			GM_SetPin(STADD0, 0);
			GM_SetPin(STADD1, 0);
			GM_SetPin(STADD2, 1);

			GM_SetPin(SRADD0, 0);
			GM_SetPin(SRADD1, 0);
			GM_SetPin(SRADD2, 1);
			break;

		case GM_CHANNEL5:	/* ͨ��1�ĵ�ֵַΪ101 */

			GM_SetPin(STADD0, 1);
			GM_SetPin(STADD1, 0);
			GM_SetPin(STADD2, 1);

			GM_SetPin(SRADD0, 1);
			GM_SetPin(SRADD1, 0);
			GM_SetPin(SRADD2, 1);
			break;

		default:
			GM_DEBUG("ERROR: Channel not support!\r\n");
	}

}
