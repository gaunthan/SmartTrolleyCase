#include "app.h"
#include "lock.h"
#include "Scale.h"
#include "myWDG.h"
#include "GPRS.h"

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
	char weightBUf[32];
	char devCode[32];

  	SystemInit();
	ModulesInit();

	SelectChannel(GPRS_CHANNEL);
	GPRS_GetDevCode(devCode, sizeof(devCode));

	SelectChannel(BLUETOOTH_CHANNEL);
	while(GetRequest() != SYS_START){}	/* �ȴ�����SYS_START�ź��Կ�ʼ���� */
	SendResponse(SYS_START);

	BT_Println(devCode);

	while(1) {
		myWDGInit(30);	/* ���ö�ʱ����ֵΪ30*2=60s=1min����ʱ�ᵼ��ϵͳ��Ϊ�����ѶϿ����Ӷ�����alarmģʽ�� */

		req = GetRequest();	/* ��ȡӦ�����󣬲�������Ӧ����API */
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
					LOCK_Unlock();	/* ���������� */
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


