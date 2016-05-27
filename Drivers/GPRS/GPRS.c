#include "GPRS.h"

/**
 * @brief	������Ϣ����궨��
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GPRS_DEBUG(fmt, args...) printf (fmt ,##args)
#else
	#define GPRS_DEBUG(fmt, args...)
#endif



/**
 * @brief	��ʼ��GPSģ����������š�
 * @param	None
 * @return	None
 */
void GPRS_InitPort(void)
{
	AppUart_init();		/* ��ʼ��Ӳ��ͨ�Žӿ� */
}


/**
 * @brief	��GPRSģ���ȡһ���ַ�
 * @param	None
 * @return	һ���ַ�
 */
static char GPRS_GetChar(void)
{
	char ch = AppUart_getChar();
	GPRS_DEBUG("%c", ch);

	return ch;
}


/**
 * @brief	��GPRSģ�鷢��һ���ַ�
 * @param	ch ��Ҫ���͵��ַ�
 * @return	None
 */
static void GPRS_PutChar(char ch)
{
	AppUart_putChar(ch);
	GPRS_DEBUG("%c", ch);
}



/**
 * @brief	��GPRSģ�鷢��һ���ַ�����ĩβ׷��<CR><LF>
 * @param	str ��Ҫ���͵��ַ���
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
 * @brief	��GPRSģ���ȡһ���ַ�������<CR><LF>��־�����ַ����Ľ������������ַ������������ضϡ�
 * @param	buf ���������
 *			n ��������С
 * @return	None
 */
static void GPRS_Gets(char *buf, int n)
{
	char ch;

	while((ch = GPRS_GetChar()) == '\r' || ch == '\n' || ch == '\0' || ch == ' ')	/* �Թ���ͷ�Ļس����пո� */
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
		}else	/* �����ַ�����<CR><LF>��ǽ��� */
			break;
	}
	*buf = '\0';
}


/**
 * @brief	��GPRSģ�鷢��һ��AT����
 * @param	cmd AT����
 * @return	None
 */
static void GPRS_SendATCmd(char *cmd)
{
	GPRS_Println(cmd);
}



/**
 * @brief	��GPRSģ�����һ����Ӧ�������ݸ���Ӧ�ж���ִ�������Ƿ�ɹ�
 * @param	reply һ����Ӧ����Ϊ�Ƚϻ�׼
 * @return	OK ִ�гɹ�
 * 			ERROR ִ��ʧ��
 */
static Status GPRS_GetAndVerifyATReply(void)
{
	char buf[32];

	do {
		GPRS_Gets(buf, 32);
		if(NULL != strstr(buf, "OK"))	/* ������Ӧ���Ƿ���"OK"���������򷵻�OK */
			return OK;
		else if(NULL != strstr(buf, "ALREAY"))
			return OK;
		else if(NULL != strstr(buf, "ERROR"))	/* ������Ӧ���Ƿ���"ERROR"���������򷵻�ERROR */
			return ERROR;
		else if(NULL != strstr(buf, "FAIL"))
			return ERROR;
	}while(1);
}



/**
 * @brief	�ȴ�����ע��
 * @param	None
 * @return	OK ����ע��ɹ�
 * 			ERROR ����ע��ʧ��
 */
static Status GPRS_WaitCREG(void)
{
	char buf[32];

	do {
		GPRS_SendATCmd("AT+CREG?");					/* ��ѯ����ע����Ϣ */
		GPRS_Gets(buf, 32);							/* ������Ӧ */
	}while(NULL == strstr(buf, ",1"));				/* ������Ӧ���Ƿ���",1"������û�������ѯ�� */

	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CREG?\r\n");
		return ERROR;
	}

	GPRS_DEBUG("Succeed in registing network.\r\n");

	return OK;
}


/**
 * @brief	�ȴ�GPRSģ��ע������
 * @param	None
 * @return	OK ע��ɹ�
 *			ERROR ע��ʧ��
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
 * @brief	����GPRS TCP����
 * @param	None
 * @return	OK ��ʼ���ɹ�
 * 			ERROR ��ʼ��ʧ��
 */
Status GPRS_InitTCPEnv(void)
{
	GPRS_SendATCmd("AT+CIPSHUT");						/* �ر��ƶ����� */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CIPSHUT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGCLASS=\"B\"");					/* �����źŵȼ�Ϊ��B��������MT�ն�֧�ְ������͵�·����ģʽ */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CGCLASS\r\n");
		return ERROR;
	}


	GPRS_SendATCmd("AT+CGDCONT=1,\"IP\",\"CMNET\"");	/* ʹ���ն��豸����һ�������ģ�����CID1������PDP����ΪIP����������ƺ�IP��ַδ���� */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CGDCONT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGATT=1");						/* ��MT����GPRSҵ�� */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CGATT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CIPCSGP=1,\"CMNET\"");			/* ����ΪGPRS����ģʽ�������ΪCMNET */
	if(ERROR == GPRS_GetAndVerifyATReply()) {
		GPRS_DEBUG("ERROR: +CIPCSGP\r\n");
		return ERROR;
	}
	return OK;
}


/**
 * @brief	ͨ��GPRS��ʹ��ATָ�������
 * @param	data ��Ҫ���͵����ݣ���NIL��β
 * @return	OK ���ͳɹ�
 *			ERROR ����ʧ��
 */
static Status GPRS_SendATData(char *data)
{
	GPRS_SendATCmd("AT+CIPSEND");		/* ʹ��AT�������� */
	while(GPRS_GetChar() != '>')	/* '>'��־��������Ŀ�ʼ */
		;
	GPRS_Println(data);	/* �������� */
	GPRS_PutChar(0x1A);	/* ^Z��־��������Ľ��� */

	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* ����������Ӧ */
		GPRS_DEBUG("ERROR: +CIPSEND\r\n");
		return ERROR;
	}

	return OK;
}


/**
 * @brief	��ʼ��SMTP������������163�������������֤
 * @param	None
 * @return	OK ��ʼ���ɹ�
 *			ERROR ��ʼ��ʧ��
 */
Status GPRS_InitSMTP(void)
{
	char buf[128];
	char username[32] = "";
	char userpasswd[32] = "";

	/* ����TCP���ӣ�������Ϊsmtp.163.com���˿�Ϊ25 */
	GPRS_SendATCmd("AT+CIPSTART=\"TCP\",\"smtp.163.com\",\"25\"");
	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* ��������Ƿ�ִ�гɹ� */
		GPRS_DEBUG("ERROR: +CIPSTART\r\n");
		return ERROR;
	}

	/* ���շ�������Ӧ��������Ӧ���Ƿ���"CONNECT OK"����"ERROR"���� */
	do {
		GPRS_Gets(buf, 128);
	}while(NULL == strstr(buf, "OK") && NULL == strstr(buf, "ERROR") && NULL == strstr(buf, "FAIL"));
	if(NULL != strstr(buf, "ERROR"))
		return ERROR;

	GPRS_Gets(buf, 128);
	if(NULL == strstr(buf, "220"))	/* ������Ӧ���Ƿ���"220"���� */
		return ERROR;

	/* ��֤���� */
	if(ERROR == GPRS_SendATData("HELO ZOISITE")) {
		GPRS_DEBUG("ERROR: GPRS_SendATData\r\n");
		return ERROR;
	}
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "250 OK"))	/* ������Ӧ���Ƿ���"250 OK"���� */
		return ERROR;

	/* �û���֤ */
	GPRS_SendATData("AUTH LOGIN");
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "334"))		/* ������Ӧ���Ƿ���"334"���� */
		return ERROR;

	/* �����û��� */
	GPRS_SendATData(username);
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "334"))		/* ������Ӧ���Ƿ���"334"���� */
		return ERROR;

	/* �����û����� */
	GPRS_SendATData(userpasswd);
	GPRS_Gets(buf, 32);
	if(NULL == strstr(buf, "235"))		/* ������Ӧ���Ƿ���"235"���������������֤�ɹ� */
		return ERROR;

	return OK;
}


/**
 * @brief	ͨ��SMTPЭ�鷢��һ������Ϊmsg���ʼ�
 * @param	msg ��Ҫ���͵���Ϣ
 * @return	OK ���ͳɹ�
 *			ERROR ����ʧ��
 */
Status GPRS_SendMail(char *msg)
{
	char buf[64];
	char subject[32] = "Subject: smtp-test\r\n\r\n\r\n";
	char endFlag[16] = "\r\n.\r\n";

	/* ָ���ʼ������� */
	GPRS_SendATData("MAIL FROM: <SmartTrollyCase@163.com>");
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "250 Mail OK"))		/* ������Ӧ���Ƿ���"250 Mail OK"���� */
		return ERROR;

	/* ָ���ʼ������� */
	GPRS_SendATData("RCPT TO: <SmartTrollyCase@163.com>");
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "250 Mail OK"))		/* ������Ӧ���Ƿ���"250 Mail OK"���� */
		return ERROR;

	/* ��ʼ�ʼ����ݴ��� */
	GPRS_SendATData("DATA");
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "354"))		/* ������Ӧ���Ƿ���"354"���� */
		return ERROR;

	/* �����ʼ����� */
	strcpy(buf, subject);
	strcat(buf, msg);
	strcat(buf, endFlag);
	GPRS_SendATData(buf);
	GPRS_Gets(buf, 64);
	if(NULL == strstr(buf, "250 Mail OK"))		/* ������Ӧ���Ƿ���"250 Mail OK"���� */
		return ERROR;

	return OK;
}


/**
 * @brief	��ȡGPRSģ��Ĳ�Ʒ���к�
 * @param	buf �����������ڴ洢��ȡ�������к�
 * 			bufSize ��������С
 * @return	OK ��ȡ�ɹ�
 *			ERROR ��ȡʧ��
 */
Status GPRS_GetDevCode(char *buf, int bufSize)
{
	GPRS_SendATCmd("AT+CGSN");	/* ���Ͳ�ѯ��Ʒ���к����� */
	GPRS_Gets(buf, bufSize);	/* ��ȡ��Ʒ���к� */

	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* ��������Ƿ�ִ�гɹ� */
		GPRS_DEBUG("ERROR: +CGSN\r\n");
		return ERROR;
	}
	return OK;
}


/**
 * @brief	����GPRSģ��
 * @param	None
 * @return	OK �����ɹ�
 *			ERROR ����ʧ��
 */
Status GPRS_RebootDev(void)
{
	GPRS_SendATCmd("AT+CFUN=1,1");		/* AT+CFUN=1,1��������������ģ�� */
	if(ERROR == GPRS_GetAndVerifyATReply()) {	/* ��������Ƿ�ִ�гɹ� */
		GPRS_DEBUG("ERROR: +CGSN\r\n");
		return ERROR;
	}

	return OK;
}
