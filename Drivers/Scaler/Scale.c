/*
 * Scale.c
 *
 *  Created on: 2016��5��22��
 *      Author: Administrator
 */

/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/
#include "Scale.h"
#include <stdio.h>
#include "general.h"
#include <string.h>

/**************************************************************
*	Macro Define Section
**************************************************************/

/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**************************************************************
*	Global Variable Declare Section
**************************************************************/
static float  weight = 0, z_weight = 77.58;
int weight_old = 0;

extern char weightBuffer[5];    //Buffer for storing the weight value
/**************************************************************
*	File Static Variable Define Section
**************************************************************/


/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name			void GetWeight();
 *	@description 	ʵ�ֵ��ӳӹ��ܵĺ���
 *	@param			weightBuff ���������Ϣ�Ļ�����
 *	@return			��
 *  @notice			��Ҫ�õ�LCD1602�����Ա����ȳ�ʼ�����ڴ˺����ڻ����ε�������ģ��ĺ���ʵ�ֹ���
 */
void GetWeight(char* weightBuff)
{
	unsigned int tryCnt = 10;
	ulong dig;

	do {
		dig = HX711_GetAD();
		weight = Caculate_weight(dig)-z_weight - 0.6977;
		if (weight < 0)
			weight = 0;
	}while(tryCnt-- > 0 && weight == 0);

	//Storing the data, n: precision
	ftoa(weightBuff, weight, 4);
	strcat(weightBuff, "kg");

	//Reserved Area
	/*
	printf("weight = ");
	AppUart_putChar((uint8_t)('0' + tmp/1000%10));
	printf(".");
	AppUart_putChar((uint8_t)('0' + tmp/100%10));
	AppUart_putChar((uint8_t)('0' + tmp/10%10));
	AppUart_putChar((uint8_t)('0' + tmp%10));
	printf(" kg");
	printf("\n");
	*/

	return;
}
