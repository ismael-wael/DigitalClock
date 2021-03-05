#include <HAL/Led_config.h>
#include <HAL/Led_interface.h>
#include <MCAL/GPIO_interface.h>

LED_t  HLEDArrayOfLeds [ NUM_OF_LEDS ] =
{

				[HLED_Red_Alarm] = {
											.HLED_GPIO_tPin = {PIN0 ,GPIOB_Port},
											.HLED_u8ActiveLevel = HLED_ACTIVE_HIGH
									},

				[HLED_Green_Time] = {
											.HLED_GPIO_tPin = {PIN1 ,GPIOB_Port},
											.HLED_u8ActiveLevel = HLED_ACTIVE_HIGH
									},

				[HLED_Yellow_Date] = {
											.HLED_GPIO_tPin = {PIN10 ,GPIOB_Port},
											.HLED_u8ActiveLevel = HLED_ACTIVE_HIGH
									 },

				[HBUZZER] = 		 {
											.HLED_GPIO_tPin = {PIN11 ,GPIOB_Port},
											.HLED_u8ActiveLevel = HLED_ACTIVE_HIGH
									 }

};


