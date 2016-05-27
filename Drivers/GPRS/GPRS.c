#include "GPRS.h"

/**
 * @brief	调试信息输出宏定义
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GPRS_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define GPRS_DEBUG(fmt, args...)
#endif



/**
 * @brief	初始化GPS模块与相关引脚。
 * @param	None
 * @return	None
 */
void GPRS_InitPort(void)
{
	AppUart_init();		/* 初始化硬件通信接口 */
}


/**
 * @brief	从GPRS模块读取一个字符
 * @param	None
 * @return	一个字符
 */
static char GPRS_GetChar(void)
{
	char ch = AppUart_getChar();
	GPRS_DEBUG("%c", ch);

	return ch;
}


/**
 * @brief	向GPRS模块发送一个字符
 * @param	ch 需要发送的字符
 * @return	None
 */
static void GPRS_PutChar(char ch)
{
	AppUart_putChar(ch);
	GPRS_DEBUG("%c", ch);
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

	while((ch = GPRS_GetChar()) == '\r' || ch == '\n' || ch == '\0' || ch == ' ')	/* 略过开头的回车换行空格 */
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
static void GPRS_SendATCmd(char *cmd)
{
	GPRS_Println(cmd);
}



/**
 * @brief	从GPRS模块接收一个响应，并根据该响应判断所执行命令是否成功
 * @param	reply 一个响应，作为比较基准
 * @return	OK 执行成功
 * 			ERROR 执行失败
 */
static Status GPRS_GetAndVerifyATReply(void)
{
	char buf[32];

	do {
		GPRS_Gets(buf, 32);
		if(NULL != strstr(buf, "OK"))	/* 查找响应中是否有"OK"字样，有则返回OK */
			return OK;
		else if(NULL != strstr(buf, "ALREAY"))
			return OK;
		else if(NULL != strstr(buf, "ERROR"))	/* 查找响应中是否有"ERROR"字样，有则返回ERROR */
			return ERROR;
		else if(NULL != strstr(buf, "FAIL"))
			return ERROR;
	}while(1);
}



/**
 * @brief	等待网络注册
 * @param	None
 * @return	OK 网络注册成功
 * 			ERROR 网络注册失败
 */
static Status GPRS_WaitCREG(void)
{
	char buf[32];

	do {
		GPRS_SendATCmd("AT+CREG?");					/* 查询网络注册信息 */
		GPRS_Gets(buf, 32);							/* 接收响应 */
	}while(NULL == strstr(buf, ",1"));				/* 查找响应中是否有",1"字样，没有则继续询问 */

	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CREG?\r\n");
		return ERROR;
	}

	GPRS_DEBUG("Succeed in registing network.\r\n");

	return OK;
}


/**
 * @brief	等待GPRS模块注册网络
 * @param	None
 * @return	OK 注册成功
 *			ERROR 注册失败
 */
Status GPRS_WaitRegister(void)
{
	if(ERROR == GPRS_WaitCREG()) {
		GPRS_DEBUG("ERROR: +WaitCREG\r\n");
		return ERROR;
	}

	return OK;
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
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CIPSHUT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGCLASS=\"B\"");					/* 设置信号等级为“B”，代表MT终端支持包交换和电路交换模式 */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CGCLASS\r\n");
		return ERROR;
	}


	GPRS_SendATCmd("AT+CGDCONT=1,\"IP\",\"CMNET\"");	/* 使用终端设备建立一个上下文：定义CID1并设置PDP类型为IP；接入点名称和IP地址未设置 */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CGDCONT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGATT=1");						/* 将MT附着GPRS业务 */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CGATT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CIPCSGP=1,\"CMNET\"");			/* 设置为GPRS连接模式，接入点为CMNET */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CIPCSGP\r\n");
		return ERROR;
	}
	return OK;
}


/**
 * @brief	通过GPRS，使用AT指令发送数据
 * @param	data 需要发送的数据，以NIL结尾
 * @return	OK 发送成功
 *			ERROR 发送失败
 */
static Status GPRS_SendATData(char *data)
{
	GPRS_SendATCmd("AT+CIPSEND");		/* 使用AT发送数据 */
	while(GPRS_GetChar() != '>')	/* '>'标志数据输入的开始 */
		;
	GPRS_Println(data);	/* 发送数据 */
	GPRS_PutChar(0x1A);	/* ^Z标志数据输入的结束 */

	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* 接收命令响应 */
		GPRS_DEBUG("ERROR: +CIPSEND\r\n");
		return ERROR;
	}

	return OK;
}


/**
 * @brief	初始化SMTP环境，连接至163服务器且完成认证
 * @param	None
 * @return	OK 初始化成功
 *			ERROR 初始化失败
 */
Status GPRS_InitSMTP(void)
{
	char buf[128];
	char username[32] = "";
	char userpasswd[32] = "";

	/* 建立TCP连接，服务器为smtp.163.com，端口为25 */
	GPRS_SendATCmd("AT+CIPSTART=\"TCP\",\"smtp.163.com\",\"25\"");
	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* 检查命令是否执行成功 */
		GPRS_DEBUG("ERROR: +CIPSTART\r\n");
		return ERROR;
	}

	/* 接收服务器响应。查找响应中是否有"CONNECT OK"或者"ERROR"字样 */
	do {
		GPRS_Gets(buf, 128);
	}while(NULL == strstr(buf, "OK") && NULL == strstr(buf, "ERROR") && NULL == strstr(buf, "FAIL"));
	if(NULL != strstr(buf, "ERROR"))
		return ERROR;

	GPRS_Gets(buf, 128);
	if(NULL == strstr(buf, "220"))	/* 查找响应中是否有"220"字样 */
		return ERROR;

	/* 验证主机 */
	if(ERROR == GPRS_SendATData("HELO ZOISITE")) {
		GPRS_DEBUG("ERROR: GPRS_SendATData\r\n");
		return ERROR;
	}
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "250 OK"))	/* 查找响应中是否有"250 OK"字样 */
		return ERROR;

	/* 用户认证 */
	GPRS_SendATData("AUTH LOGIN");
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "334"))		/* 查找响应中是否有"334"字样 */
		return ERROR;

	/* 发送用户名 */
	GPRS_SendATData(username);
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "334"))		/* 查找响应中是否有"334"字样 */
		return ERROR;

	/* 发送用户密码 */
	GPRS_SendATData(userpasswd);
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "235"))		/* 查找响应中是否有"235"字样。有则代表验证成功 */
		return ERROR;

	return OK;
}


/**
 * @brief	通过SMTP协议发送一封内容为msg的邮件
 * @param	msg 需要发送的信息
 * @return	OK 发送成功
 *			ERROR 发送失败
 */
Status GPRS_SendMail(char *msg)
{
	char buf[64];
	char subject[32] = "Subject: smtp-test\r\n\r\n\r\n";
	char endFlag[16] = "\r\n.\r\n";

	/* 指定邮件发件人 */
	GPRS_SendATData("MAIL FROM: <SmartTrollyCase@163.com>");
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "250 Mail OK"))		/* 查找响应中是否有"250 Mail OK"字样 */
		return ERROR;

	/* 指定邮件接收人 */
	GPRS_SendATData("RCPT TO: <SmartTrollyCase@163.com>");
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "250 Mail OK"))		/* 查找响应中是否有"250 Mail OK"字样 */
		return ERROR;

	/* 开始邮件内容传输 */
	GPRS_SendATData("DATA");
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "354"))		/* 查找响应中是否有"354"字样 */
		return ERROR;

	/* 发送邮件内容 */
	strcpy(buf, subject);
	strcat(buf, msg);
	strcat(buf, endFlag);
	GPRS_SendATData(buf);
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "250 Mail OK"))		/* 查找响应中是否有"250 Mail OK"字样 */
		return ERROR;

	return OK;
}


/**
 * @brief	获取GPRS模块的产品序列号
 * @param	buf 缓冲区，用于存储获取到的序列号
 * 			bufSize 缓冲区大小
 * @return	OK 获取成功
 *			ERROR 获取失败
 */
Status GPRS_GetDevCode(char *buf, int bufSize)
{
	GPRS_SendATCmd("AT+CGSN");	/* 发送查询产品序列号命令 */
	GPRS_Gets(buf, bufSize);	/* 获取产品序列号 */

	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* 检查命令是否执行成功 */
		GPRS_DEBUG("ERROR: +CGSN\r\n");
		return ERROR;
	}
	return OK;
}


/**
 * @brief	重启GPRS模块
 * @param	None
 * @return	OK 重启成功
 *			ERROR 重启失败
 */
Status GPRS_RebootDev(void)
{
	GPRS_SendATCmd("AT+CFUN=1,1");		/* AT+CFUN=1,1被用来主动重启模块 */
	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* 检查命令是否执行成功 */
		GPRS_DEBUG("ERROR: +CGSN\r\n");
		return ERROR;
	}

	return OK;
}
