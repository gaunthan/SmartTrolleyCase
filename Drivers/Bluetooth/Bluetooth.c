#include "Bluetooth.h"

/**
 * @brief	������Ϣ����궨��
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define BT_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define BT_DEBUG(fmt, args...)
#endif



/**
 * @brief	��ʼ������ģ����������š�
 * @param	None
 * @return	None
 */
void BT_InitPort(void)
{
	AppUart_init();		/* ��ʼ��Ӳ��ͨ�Žӿ� */
}


/**
 * @brief	������ģ�鷢��һ���ַ�
 * @param	ch ��Ҫ���͵��ַ�
 * @return	None
 */
void BT_Putchar(char ch)
{
	AppUart_putChar(ch);
	BT_DEBUG("%c", ch);
}


/**
 * @brief	������ģ���ȡһ���ַ�
 * @param	None
 * @return	һ���ַ�
 */
char BT_Getchar(void)
{
	char ch = AppUart_getChar();
	BT_DEBUG("%c", ch);

	return ch;
}



/**
 * @brief	������ģ�鷢��һ���ַ�����ĩβ׷��<CR><LF>
 * @param	str ��Ҫ���͵��ַ���
 * @return	None
 */
void BT_Println(const char *str)
{
	if(NULL == str)
		return;
	while(*str) {
		BT_Putchar(*str);
		str++;
	}
	BT_Putchar('\r');
	BT_Putchar('\n');
}


/**
 * @brief	������ģ���ȡһ���ַ�������<CR><LF>��־�����ַ����Ľ������������ַ������������ضϡ�
 * @param	buf ���������
 *			n ��������С
 * @return	None
 */
void BT_Gets(char *buf, int n)
{
	char ch;

	while((ch = BT_Getchar()) == '\r' || ch == '\n' || ch == '\0' || ch == ' ')	/* �Թ���ͷ�Ļس����пո� */
		;

	*buf++ = ch;
	n--;
	while(n > 1) {
		if((ch = BT_Getchar()) != '\r') {
			*buf++ = ch;
			n--;
		}else if((ch = BT_Getchar()) != '\n') {
			*buf++ = ch;
			n--;
		}else	/* �����ַ�����<CR><LF>��ǽ��� */
			break;
	}
	*buf = '\0';
}
