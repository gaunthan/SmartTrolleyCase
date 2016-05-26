#include "Bluetooth.h"

/**
 * @brief	调试信息输出宏定义
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define BT_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define BT_DEBUG(fmt, args...)
#endif



/**
 * @brief	初始化蓝牙模块与相关引脚。
 * @param	None
 * @return	None
 */
void BT_InitPort(void)
{
	AppUart_init();		/* 初始化硬件通信接口 */
}


/**
 * @brief	向蓝牙模块发送一个字符
 * @param	ch 需要发送的字符
 * @return	None
 */
void BT_Putchar(char ch)
{
	AppUart_putChar(ch);
	BT_DEBUG("%c", ch);
}


/**
 * @brief	从蓝牙模块读取一个字符
 * @param	None
 * @return	一个字符
 */
char BT_Getchar(void)
{
	char ch = AppUart_getChar();
	BT_DEBUG("%c", ch);

	return ch;
}



/**
 * @brief	向蓝牙模块发送一个字符串，末尾追发<CR><LF>
 * @param	str 需要发送的字符串
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
 * @brief	从蓝牙模块获取一个字符串，以<CR><LF>标志输入字符串的结束。若输入字符串过长将被截断。
 * @param	buf 输出缓冲区
 *			n 缓冲区大小
 * @return	None
 */
void BT_Gets(char *buf, int n)
{
	char ch;

	while((ch = BT_Getchar()) == '\r' || ch == '\n' || ch == '\0' || ch == ' ')	/* 略过开头的回车换行空格 */
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
		}else	/* 输入字符串以<CR><LF>标记结束 */
			break;
	}
	*buf = '\0';
}
