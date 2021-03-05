/*Libraries*/
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>

/*Application*/
#include <Application/StatusModule_interface.h>

/*HAL*/
#include <HAL/Led_interface.h>

/*OS*/
#include <OS/OS_interface.h>
#include <OS/OS_config.h>

void StatusModule_voidInit(void)
{
	OS_VoidCreateTask(ACTIVATE_ALARM_TASK, 1000, StatusModule_voidActivateAlarm, 0);

	/*Alarm is initially Off*/
	OS_VoidSuspendTask(ACTIVATE_ALARM_TASK);
}

void StatusModule_voidTimeStatus(void)
{
	Hled_voidLedOn(HLED_Green_Time);
	Hled_voidLedOff(HLED_Yellow_Date);
}

void StatusModule_voidDateStatus(void)
{
	Hled_voidLedOff(HLED_Green_Time);
	Hled_voidLedOn(HLED_Yellow_Date);
}

void StatusModule_voidStopWatchStatus(void)
{
	Hled_voidLedOff(HLED_Green_Time);
	Hled_voidLedOff(HLED_Yellow_Date);
}

void StatusModule_voidAlarmOn(void)
{
	Hled_voidLedOn(HLED_Red_Alarm);
}

void StatusModule_voidAlarmOff(void)
{
	Hled_voidLedOff(HLED_Red_Alarm);
}

void StatusModule_voidActivateAlarm(void)
{
	static u8 u8Counter = 10; // 10 seconds ; alarm active for 10 seconds
							 // as this function is called every 1 seconds
	static ToggleState_t state = On;


	Hled_voidLedOn(HBUZZER);

	if(state)
	{
		Hled_voidLedOn(HLED_Green_Time);
		Hled_voidLedOn(HLED_Red_Alarm);
		Hled_voidLedOn(HLED_Yellow_Date);
		state = Off;
	}
	else
	{
		Hled_voidLedOff(HLED_Green_Time);
		Hled_voidLedOff(HLED_Red_Alarm);
		Hled_voidLedOff(HLED_Yellow_Date);
		state = On;
	}

	u8Counter--;

	if(u8Counter == 0)
	{
		/*Suspend Alarm Task*/
		OS_VoidSuspendTask(4);
		StatusModule_voidDeactivateAlarm();
		u8Counter = 10;
	}
}

void StatusModule_voidDeactivateAlarm(void)
{
	Hled_voidLedOff(HLED_Green_Time);
	Hled_voidLedOff(HLED_Red_Alarm);
	Hled_voidLedOff(HLED_Yellow_Date);
	Hled_voidLedOff(HBUZZER);
}

