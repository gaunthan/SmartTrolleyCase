#ifndef HX711_H_
#define HX711_H_

#include <msp430.h>

void HX711_GPIO_Init(void);
unsigned long HX711_GetAD(void);

#endif /* HX711_H_ */
