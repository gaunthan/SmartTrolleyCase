#include "HX711.h"


void delay_us(unsigned long i)
{
	while(i--);
}
/**************************************************************

.
.
unsigned long data;
data=ReadAD();
.
.
-------------------------------------------------------------*/

void HX711_GPIO_Init(void)
{
	P7SEL &= ~BIT2 + ~BIT3;

	P7DIR |= BIT2;          //7.2 SCK(OUTPUT)

	//INPUT WITH PULL-DOWN RESISTORS
	P7DIR &= ~BIT3;		    //7.3  DOUT(INPUT with pulldown resistors)
	P7REN |= BIT3;			//置高/ 置低使能
	P7OUT &= ~BIT3;			//置高（类似于下拉）
}

unsigned long HX711_GetAD(void)  //读HX711芯片输出的数据。
{
	unsigned long val = 0;
	unsigned char i = 0;


	P7OUT &= ~BIT3;         //7.3->high LEVEL
	P7OUT &= ~BIT2;  		//SCK=0

	while(P7IN & BIT3);  				//AD转换未结束则等待，否则开始读取

	for(i=0; i<24; i++)
	{
		P7OUT |= BIT2;  	    //SCK=1
		val=val<<1;
		delay_us(4);
		P7OUT &= ~BIT2;		//SCK=0

		if (P7IN & BIT3)   	//DOUT=1
			val++;

		while(P7IN & BIT3);  				//AD转换未结束则等待，否则开始读取
	}

	delay_us(2);
	P7OUT |= BIT3;         //7.3->HIGH LEVEL

	P7OUT |= BIT2;  		//SCK=1
	val = val^0x800000;     //processed the conversion
	delay_us(4);
	P7OUT &= ~BIT2;			//SCK=0

	return val;
}


