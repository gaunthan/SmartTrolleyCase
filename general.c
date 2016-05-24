#include "general.h"

/**
 * 将整型n转换为字符串，结果存储在buf中。函数返回buf。
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

/**
 * @brief	将一个浮点数转换为字符串。
 * @param	str 输出缓冲区
 * 			num 需要被转换的数
 * 			n 转换精度
 * @return	0 转换成功
 * 			-1 转换失败
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
