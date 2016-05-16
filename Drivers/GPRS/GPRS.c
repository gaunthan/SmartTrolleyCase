#include <GPRS.h>


/**
 * @brief	调试信息输出宏定义
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GPRS_DEBUG(str) printf(str)
#else
	#define GPRS_DEBUG(str)
#endif


/**
 * @brief	从GPRS模块读取一个字符
 * @param	None
 * @return	一个字符
 */
static inline char GPRS_GetChar(void)
{
	return AppUart_getChar();
}


/**
 * @brief	向GPRS模块发送一个字符
 * @param	ch 需要发送的字符
 * @return	None
 */
static inline void GPRS_PutChar(char ch)
{
	AppUart_putChar(ch);
}



/**
 * @brief	向GPRS模块发送一个字符串，末尾追发<CR><LF>
 * @param	str 需要发送的字符串
 * @return	None
 */
static void GPRS_Println(const char *str)
{
	if(NULL == str)
		return;
	while(*str) {
		GPRS_PutChar(*str);
		str++;
	}
	GPRS_PutChar('\r');
	GPRS_PutChar('\n');
}


/**
 * @brief	从GPRS模块获取一个字符串，以<CR><LF>标志输入字符串的结束。若输入字符串过长将被截断。
 * @param	buf 输出缓冲区
 *			n 缓冲区大小
 * @return	None
 */
static void GPRS_Gets(char *buf, int n)
{
	char ch;

	while((ch = GPRS_GetChar()) == '\r' || ch == '\n')	/* 略过开头的回车换行 */
		;

	*buf++ = ch;
	n--;
	while(n > 1) {
		if((ch = GPRS_GetChar()) != '\r') {
			*buf++ = ch;
			n--;
		}else if((ch = GPRS_GetChar()) != '\n') {
			*buf++ = ch;
			n--;
		}else	/* 输入字符串以<CR><LF>标记结束 */
			break;
	}
	*buf = '\0';
}


/**
 * @brief	向GPRS模块发送一个AT命令
 * @param	cmd AT命令
 * @return	None
 */
static inline void GPRS_SendATCmd(char *cmd)
{
	GPRS_Println(cmd);
}



/**
 * @brief	从GPRS模块接收一个响应，并根据该响应判断所执行命令是否成功
 * @param	reply 一个响应，作为比较基准
 * @return	OK 执行成功
 * 			ERROR 执行失败
 */
static Status GPRS_GetAndVerifyReply(void)
{
	char buf[32];

	GPRS_Gets(buf, 32);
	GPRS_Println(strcat(buf, "###"));
	if(NULL != strstr(buf, "OK"))	/* 查找响应中是否有"OK"字样 */
		return OK;
	else
		return ERROR;
}


/**
 * @brief	初始化GPS模块与相关引脚。
 * @param	None
 * @return	None
 */
void GPRS_Init(void)
{
	AppUart_init();

	GPRS_SendATCmd("ATE0");						/* 关闭回显 */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +ATE0\r\n");
		return ERROR;
	}
}


/**
 * @brief	建立GPRS TCP环境
 * @param	None
 * @return	OK 初始化成功
 * 			ERROR 初始化失败
 */
Status GPRS_InitTCPEnv(void)
{
	GPRS_SendATCmd("AT+CIPSHUT");						/* 关闭移动场景 */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CIPSHUT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGCLASS=\"B\"");					/* 设置信号等级为“B”，代表MT终端支持包交换和电路交换模式 */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CGCLASS\r\n");
		return ERROR;
	}
	GPRS_SendATCmd("AT+CGDCONT=1,\"IP\",\"CMNET\"");	/* 使用终端设备建立一个上下文：定义CID1并设置PDP类型为IP；接入点名称和IP地址未设置 */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CGDCONT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGATT=1");						/* 将MT附着GPRS业务 */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CGATT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CIPCSGP=1,\"CMNET\"");			/* 设置为GPRS连接模式，接入点为CMNET */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CIPCSGP\r\n");
		return ERROR;
	}
	return OK;
}
