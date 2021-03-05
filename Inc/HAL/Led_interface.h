#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_

#include <HAL/Led_config.h>
#include <MCAL/GPIO_interface.h>

#define HLED_ACTIVE_HIGH		1
#define HLED_ACTIVE_LOW			0

typedef struct{
	GPIO_t	HLED_GPIO_tPin;
	u8 HLED_u8ActiveLevel;
}LED_t;

extern LED_t  HLEDArrayOfLeds [ NUM_OF_LEDS ] ;

void Hled_voidInit(void);
void Hled_voidToggleLed(u8 Hled_u8Number);
void Hled_voidLedOn(u8 Hled_u8Number);
void Hled_voidLedOff(u8 Hled_u8Number);

#endif /* HAL_LED_INTERFACE_H_ */
