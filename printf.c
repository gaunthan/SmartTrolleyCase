#include "printf.h"


/**
 * �ض������
 */
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ�UART */
	AppUart_putChar((uint8_t)ch);

    return ch;
}


/**
 * �ض�������
 */
int fgetc(FILE *f)
{
    /* ��UART���һ���ֽ����ݣ��������� */
    return AppUart_getChar();

}
