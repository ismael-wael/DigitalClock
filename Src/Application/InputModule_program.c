/*Libraries*/
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>

/*MCAL*/
#include <MCAL/AFIO_interface.h>
#include <MCAL/EXTI_interface.h>
#include <MCAL/GPIO_interface.h>
#include <MCAL/GPIO_private.h>
#include <MCAL/NVIC_interface.h>

/*HAL*/
#include <HAL/Hswitch_interface.h>
#include <HAL/Led_interface.h>

/*Application*/
#include <Application/InputModule_interface.h>
#include <Application/ControlModule_interface.h>

/*OS*/
#include <OS/OS_interface.h>
#include <OS/OS_config.h>

/******************************************************************************/

static SwitchesState Switches;

static u8 InputModule_u8EditPosition= EDIT_HOURS;

static u8 InputModule_u8WhatToEdit = EDIT_TIME;

static u8 InputModule_u8DisplayStates = DISPLAY_TIME;

void InputModule_voidInit(void)
{
	Switches.DownSwitchState = SWITCH_RELEASED;
	Switches.UpSwitchState = SWITCH_RELEASED;
	Switches.LeftSwitchState = SWITCH_RELEASED;
	Switches.RightSwitchState = SWITCH_RELEASED;
	Switches.CenterSwitchState = CENTERSWITCH_DISPLAY;

	Hswitch_voidInit();

	/*Enable Interrupt for Switches*/
	MEXTI_voidEnableEXTI(LINE9);
	MEXTI_voidEnableEXTI(LINE8);
	MEXTI_voidEnableEXTI(LINE7);
	MEXTI_voidEnableEXTI(LINE6);
	MEXTI_voidEnableEXTI(LINE5);

	MNVIC_voidEnableInterrupt(EXTI5);
	MNVIC_voidEnableInterrupt(EXTI6);
	MNVIC_voidEnableInterrupt(EXTI7);
	MNVIC_voidEnableInterrupt(EXTI8);
	MNVIC_voidEnableInterrupt(EXTI9);

	AFIO_voidSetEXTIConfiguration(AFIO_EXTI5 ,GPIOB_Port);
	AFIO_voidSetEXTIConfiguration(AFIO_EXTI6 ,GPIOB_Port);
	AFIO_voidSetEXTIConfiguration(AFIO_EXTI7 ,GPIOB_Port);
	AFIO_voidSetEXTIConfiguration(AFIO_EXTI8 ,GPIOB_Port);
	AFIO_voidSetEXTIConfiguration(AFIO_EXTI9 ,GPIOB_Port);

	MEXTI_voidSetCallBack(InputModule_voidActivateProcessInputsTask , LINE5);

	MEXTI_voidInit(LINE9, FALLING_EDGE);
	MEXTI_voidInit(LINE8, FALLING_EDGE);
	MEXTI_voidInit(LINE7, FALLING_EDGE);
	MEXTI_voidInit(LINE6, FALLING_EDGE);
	MEXTI_voidInit(LINE5, FALLING_EDGE);

	/*periodicity = 40, for 5 buttons : 200, and tick time : 1ms
	 * then 200 * 1 ms = 200 ms;
	 * 200 ms is smallest time between 2 ticks*/
	OS_VoidCreateTask(PROCESS_INPUTS_TASK, 40, InputModule_voidProcessInputs, 0);

	/*Process Input is Off till any switch is pressed, then the ISR will Activate it*/
	OS_VoidSuspendTask(PROCESS_INPUTS_TASK);
}

void InputModule_voidProcessInputs(void)
{
	static u8 u8Counter = 5;

	/*arrange according to priority*/
	switch(u8Counter)
	{
		case 5 :
			InputModule_voidProcessCenterSwitch();
			u8Counter--;
			break;
		case 4 :
			InputModule_voidProcessRightSwitch();
			u8Counter--;
			break;
		case 3 :
			InputModule_voidProcessLeftSwitch();
			u8Counter--;
			break;
		case 2 :
			InputModule_voidProcessUpSwitch();
			u8Counter--;
			break;
		case 1 :
			InputModule_voidProcessDownSwitch();
			u8Counter--;
			break;
		case 0 :
			/*reload it to 5 for next Switch Press (ISR)*/
			u8Counter = 5;
			/*Suspend this task*/
			OS_VoidSuspendTask(PROCESS_INPUTS_TASK);
		default :
			break;
	}
}


static void InputModule_voidProcessCenterSwitch(void)
{
	ToggleState_t CenterSwitchState = Hswitch_voidGetCenterSwitch();

	if(CenterSwitchState == SWITCH_PRESSED)
	{
		Switches.CenterSwitchState = ! Switches.CenterSwitchState;
		if(Switches.CenterSwitchState == CENTERSWITCH_DISPLAY)
		{
			ControlModule_voidSetDisplayOrEdit(DISPLAY);
		}
		else
		{
			ControlModule_voidSetDisplayOrEdit(EDIT);
			ControlModule_voidSetWhatToEdit(InputModule_u8WhatToEdit);
			InputModule_u8WhatToEdit == 0 ? (EDIT_TIME) : (InputModule_u8WhatToEdit--) ;
		}
	}
}

static void InputModule_voidProcessRightSwitch(void)
{
	ToggleState_t RightSwitchState = Hswitch_voidGetRightSwitch();

	if(RightSwitchState == SWITCH_PRESSED)
	{
		if(Switches.CenterSwitchState == CENTERSWITCH_DISPLAY)
		{
			switch(InputModule_u8DisplayStates)
			{
			case RIGHTSWITCH_TIME :
				ControlModule_voidSetDisplayState(DISPLAY_TIME);
				break;

			case RIGHTSWITCH_DATE :
				ControlModule_voidSetDisplayState(DISPLAY_DATE);
				break;

			case RIGHTSWITCH_STOPWATCH :
				ControlModule_voidSetDisplayState(DISPLAY_STOPWATCH);
				break;
			}
			InputModule_u8DisplayStates = InputModule_u8DisplayStates == RIGHTSWITCH_STOPWATCH ? RIGHTSWITCH_TIME : (InputModule_u8DisplayStates-1);
		}
		else if(Switches.CenterSwitchState == CENTERSWITCH_EDIT_TIME)
		{
			InputModule_u8EditPosition--;
			InputModule_u8EditPosition = (InputModule_u8EditPosition < EDIT_SECONDS) || (InputModule_u8EditPosition > EDIT_HOURS) ? EDIT_HOURS : InputModule_u8EditPosition;
			ControlModule_voidSetEditPosition(InputModule_u8EditPosition);
		}
	}
}

static void InputModule_voidProcessLeftSwitch(void)
{
	ToggleState_t LeftSwitchState = Hswitch_voidGetLeftSwitch();

	if(LeftSwitchState == SWITCH_PRESSED)
	{
		if(Switches.CenterSwitchState == CENTERSWITCH_DISPLAY)
		{
			Switches.LeftSwitchState = ! Switches.LeftSwitchState;

			if(Switches.LeftSwitchState == LEFTSWITCH_ALARM_OFF)
			{
				ControlModule_voidSetAlarmState(ALARM_OFF);
			}
			else
			{
				ControlModule_voidSetAlarmState(ALARM_ON);
			}
		}
		else if(Switches.CenterSwitchState == CENTERSWITCH_EDIT_TIME)
		{
			InputModule_u8EditPosition++;
			InputModule_u8EditPosition = (InputModule_u8EditPosition > EDIT_HOURS) || (InputModule_u8EditPosition < EDIT_SECONDS) ? EDIT_SECONDS : InputModule_u8EditPosition;
			ControlModule_voidSetEditPosition(InputModule_u8EditPosition);
		}
	}
}

static void InputModule_voidProcessUpSwitch(void)
{
	ToggleState_t UpSwitchState = Hswitch_voidGetUpSwitch();

	if(UpSwitchState == SWITCH_PRESSED)
	{
		if(Switches.CenterSwitchState == CENTERSWITCH_DISPLAY)
		{
			Switches.UpSwitchState = ! Switches.UpSwitchState;
			if(Switches.UpSwitchState)
			{

				ControlModule_voidSetStopWatchState(RESUME_STOPWATCH);
			}
			else
			{
				ControlModule_voidSetStopWatchState(STOP_STOPWATCH);
			}
		}
		else if(Switches.CenterSwitchState == CENTERSWITCH_EDIT_TIME)
		{
			ControlModule_voidSetEditState(INCREASE);
		}
	}
	else
	{
		ControlModule_voidSetEditState(NONE);
	}
}

static void InputModule_voidProcessDownSwitch(void)
{
	ToggleState_t DownSwitchState = Hswitch_voidGetDownSwitch();

	if(DownSwitchState == SWITCH_PRESSED)
	{
		if(Switches.CenterSwitchState == CENTERSWITCH_DISPLAY)
		{
			ControlModule_voidSetStopWatchState(RESET_STOPWATCH);
		}
		else if(Switches.CenterSwitchState == CENTERSWITCH_EDIT_TIME)
		{
			ControlModule_voidSetEditState(DECREASE);
		}
	}
	else
	{
		ControlModule_voidSetEditState(NONE);
	}
}

/*if any pushButton is pressed, an interrupt to EXTI9_5_IRQHandler will occur,
 * that function will be called when the interrupt occur
 * the function Activate : "InputModule_voidProcessInputs" Task*/
void InputModule_voidActivateProcessInputsTask(void)
{
	OS_VoidResumeTask(PROCESS_INPUTS_TASK);
}

