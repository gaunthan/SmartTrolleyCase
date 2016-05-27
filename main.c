#include "app.h"
#include "lock.h"
#include "Scale.h"
#include "myWDG.h"
#include "GPRS.h"

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
	char weightBUf[32];
	char devCode[32];

  	SystemInit();
	ModulesInit();

	SelectChannel(GPRS_CHANNEL);
	GPRS_GetDevCode(devCode, sizeof(devCode));

	SelectChannel(BLUETOOTH_CHANNEL);
	while(GetRequest() != SYS_START){}	/* 等待接收SYS_START信号以开始工作 */
	SendResponse(SYS_START);

	BT_Println(devCode);

	while(1) {
		myWDGInit(30);	/* 设置定时器，值为30*2=60s=1min。超时会导致系统认为蓝牙已断开，从而进入alarm模式。 */

		req = GetRequest();	/* 获取应用请求，并调用相应功能API */
		if(FALSE == TimeoutFlag) {
			switch(req) {
				case KEEP_ALIVE:
					SendResponse(KEEP_ALIVE);
					ResetWDGCounter();
					break;

				case GET_WEIGHT:
					SendResponse(GET_WEIGHT);
					GetWeight(weightBUf);
					BT_Println(weightBUf);
					ResetWDGCounter();
					break;

				case UNLOCK_DEVICE:
					SendResponse(UNLOCK_DEVICE);
					LOCK_Unlock();	/* 解锁电子锁 */
					ResetWDGCounter();
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






//******************************************************************************
//
//This is the TIMER1_A3 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A1_VECTOR)))
#endif
void TIMER1_A1_ISR(void)
{
	extern unsigned char WDGOverTime;
	extern unsigned char  WDGCounter;

    //Any access, read or write, of the TAIV register automatically resets the
    //highest "pending" interrupt flag
    switch(__even_in_range(TA1IV,14))
    {
		case  0: break;                              //No interrupt
		case  2: break;                              //CCR1 not used
		case  4: break;                              //CCR2 not used
		case  6: break;                              //CCR3 not used
		case  8: break;                              //CCR4 not used
		case 10: break;                              //CCR5 not used
		case 12: break;                              //CCR6 not used
		case 14:
			WDGCounter++;

			if (WDGCounter >= WDGOverTime)
			{
				UCA1IFG |= UCRXIFG;   //when in the Timer_interrupt, Set the UCRXIF
				TimeoutFlag = TRUE;
				ResetWDGCounter(); 	//reset the WDGCounter
			}
			break;
		default: break;
    }
}


