#include <GPRS.h>


/**
 * @brief	������Ϣ����궨��
 */
#if GPRS_DEBUG_ON
	#include <stdio.h>
	#define GPRS_DEBUG(str) printf(str)
#else
	#define GPRS_DEBUG(str)
#endif


/**
 * @brief	��GPRSģ���ȡһ���ַ�
 * @param	None
 * @return	һ���ַ�
 */
static inline char GPRS_GetChar(void)
{
	return AppUart_getChar();
}


/**
 * @brief	��GPRSģ�鷢��һ���ַ�
 * @param	ch ��Ҫ���͵��ַ�
 * @return	None
 */
static inline void GPRS_PutChar(char ch)
{
	AppUart_putChar(ch);
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

	while((ch = GPRS_GetChar()) == '\r' || ch == '\n')	/* �Թ���ͷ�Ļس����� */
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
static inline void GPRS_SendATCmd(char *cmd)
{
	GPRS_Println(cmd);
}



/**
 * @brief	��GPRSģ�����һ����Ӧ�������ݸ���Ӧ�ж���ִ�������Ƿ�ɹ�
 * @param	reply һ����Ӧ����Ϊ�Ƚϻ�׼
 * @return	OK ִ�гɹ�
 * 			ERROR ִ��ʧ��
 */
static Status GPRS_GetAndVerifyReply(void)
{
	char buf[32];

	GPRS_Gets(buf, 32);
	GPRS_Println(strcat(buf, "###"));
	if(NULL != strstr(buf, "OK"))	/* ������Ӧ���Ƿ���"OK"���� */
		return OK;
	else
		return ERROR;
}


/**
 * @brief	��ʼ��GPSģ����������š�
 * @param	None
 * @return	None
 */
void GPRS_Init(void)
{
	AppUart_init();

	GPRS_SendATCmd("ATE0");						/* �رջ��� */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +ATE0\r\n");
		return ERROR;
	}
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
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CIPSHUT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGCLASS=\"B\"");					/* �����źŵȼ�Ϊ��B��������MT�ն�֧�ְ������͵�·����ģʽ */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CGCLASS\r\n");
		return ERROR;
	}
	GPRS_SendATCmd("AT+CGDCONT=1,\"IP\",\"CMNET\"");	/* ʹ���ն��豸����һ�������ģ�����CID1������PDP����ΪIP����������ƺ�IP��ַδ���� */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CGDCONT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CGATT=1");						/* ��MT����GPRSҵ�� */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CGATT\r\n");
		return ERROR;
	}

	GPRS_SendATCmd("AT+CIPCSGP=1,\"CMNET\"");			/* ����ΪGPRS����ģʽ�������ΪCMNET */
	if(ERROR == GPRS_GetAndVerifyReply()) {
		GPRS_DEBUG("ERROR: +CIPCSGP\r\n");
		return ERROR;
	}
	return OK;
}
