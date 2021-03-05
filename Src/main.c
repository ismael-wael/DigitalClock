#include "include.h"

int main(void)
{
	/********************************************Clock initialization****************************************/
 	MRCC_enuInitSysClock();
	MRCC_enuEnableClock (APB2_BUS , GPIOA_RCC);
	MRCC_enuEnableClock (APB2_BUS , GPIOB_RCC);
	MRCC_enuEnableClock (APB1_BUS , TIM4_RCC);
	MRCC_enuEnableClock (APB1_BUS , TIM3_RCC);
	MRCC_enuEnableClock (APB2_BUS, AFIO_RCC);

	/*********************************************Application initialization*********************************/
	DispalyModule_voidInit();
	InputModule_voidInit();
	ControlModule_voidInit();
	StatusModule_voidInit();

	/**************************************************Start Scheduler***************************************/
	OS_VoidStart();
	return 0;
}




