#include "lock.h"


/**
 * @brief	��ʼ��������Ӳ������
 * @param	None
 * @return	None
 */
void LOCK_InitPort(void)
{
	P4DIR |= LOCK_PIN;	/* set pin as output mode */
	P4DS |= LOCK_PIN;	/* full drive strength */
	LOCK_PIN_LOW();
}




/**
 * @brief	����������
 * @param	None
 * @return	None
 */
void LOCK_Unlock(void)
{
	unsigned int i = (unsigned int)-1, j = i;

	LOCK_PIN_HIGH();			/* unlock device */
	while(i--) {	/* delay a moment */
		while(j--);
	}
	LOCK_PIN_LOW();
}
