#include "lock.h"


/**
 * @brief	初始化电子锁硬件连接
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
 * @brief	解锁电子锁
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
