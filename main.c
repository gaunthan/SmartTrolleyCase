#include "app.h"
#include "lock.h"


/**
 * @brief	��־��ʱ���Ƿ��ʱ����
 */
int TimeoutFlag = FALSE;

/*
 * @brief	������
 */
int main(void)
{
	Request req;

  	SystemInit();
	ModulesInit();

	SelectChannel(BLUETOOTH_CHANNEL);
	while(GetRequest() != SYS_START){}	/* �ȴ�����SYS_START�ź��Կ�ʼ���� */
	SendResponse(SYNC);


	while(1) {
		req = GetRequest();	/* ��ȡӦ�����󣬲�������Ӧ����API */
		if(FALSE == TimeoutFlag) {
			switch(req) {
				case KEEP_ALIVE:
					SendResponse(ACK);
					break;

				case GET_WEIGHT:
					SendResponse(ACK);
					BT_Println("Get weight.");
					break;

				case UNLOCK_DEVICE:
					SendResponse(ACK);
					LOCK_Unlock();	/* ���������� */
					break;

				default:
					BT_Println("Request invalid.");
			}
		}else {
			while(1) { ReportLocation(); }
		}

	}

	return 0;
}



