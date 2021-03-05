#ifndef INCLUDE_H_
#define INCLUDE_H_

/*Library*/
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>

/*Application*/
#include <Application/ControlModule_interface.h>
#include <Application/DisplayModule_interface.h>
#include <Application/InputModule_interface.h>
#include <Application/StatusModule_interface.h>

/*OS*/
#include <OS/OS_interface.h>

/*HAL*/
#include <HAL/Hswitch_interface.h>
#include <HAL/Led_config.h>
#include <HAL/Led_interface.h>

/*MCAL*/
#include <MCAL/AFIO_interface.h>
#include <MCAL/EXTI_interface.h>
#include <MCAL/GPIO_interface.h>
#include <MCAL/NVIC_interface.h>
#include <MCAL/RCC_interface.h>
#include <MCAL/SysTick_interface.h>
#include <MCAL/Timer_interface.h>

#endif /* INCLUDE_H_ */
