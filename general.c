#include "general.h"

/**
 * ������nת��Ϊ�ַ���������洢��buf�С���������buf��
 */
char *numToStr(char *buf, int n)
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

/**
 * @brief	��һ��������ת��Ϊ�ַ�����
 * @param	str ���������
 * 			num ��Ҫ��ת������
 * 			n ת������
 * @return	0 ת���ɹ�
 * 			-1 ת��ʧ��
 */
int ftoa(char *str, float num, int n)
{
    int     sumI;
    float   sumF;
    int     sign = 0;
    int     temp;
    int     count = 0;

    char *p;
    char *pp;

    if(str == NULL)
    	return -1;
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

    *str = '\0';

    return 0;
}
