#include "app.h"
#include "lock.h"


/**
 * @brief	标志定时器是否计时结束
 */
int TimeoutFlag = FALSE;

/*
 * @brief	主程序
 */
int main(void)
{
	Request req;

  	SystemInit();
	ModulesInit();

	SelectChannel(BLUETOOTH_CHANNEL);
	while(GetRequest() != SYS_START){}	/* 等待接收SYS_START信号以开始工作 */
	SendResponse(SYNC);


	while(1) {
		req = GetRequest();	/* 获取应用请求，并调用相应功能API */
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
					LOCK_Unlock();	/* 解锁电子锁 */
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



