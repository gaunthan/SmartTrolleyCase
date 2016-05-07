#include "printf.h"


/**
 * 重定向输出
 */
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到UART */
	AppUart_putChar((uint8_t)ch);

    return ch;
}


/**
 * 重定向输入
 */
int fgetc(FILE *f)
{
    /* 从UART获得一个字节数据，并返回它 */
    return AppUart_getChar();

}
