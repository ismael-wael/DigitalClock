/*Libraries*/
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>

/*HAL*/
#include <HAL/SSD_interface.h>

/*MCAL*/
#include <MCAL/Timer_interface.h>

/*Application*/
#include <Application/DisplayModule_interface.h>>

/*OS*/
#include <OS/OS_config.h>
#include <OS/OS_interface.h>

/*initializes Display Module,
 * All i need to display time*/

static Time_t TimeDisplay;
static Date_t DateDisplay;

void DispalyModule_voidInit(void)
{
	TimeDisplay.u8Hour = 0;
	TimeDisplay.u8Minute = 0;
	TimeDisplay.u8Second = 0;

	SSD_Init();

	OS_VoidCreateTask(DISPLAY_HOURS_TASK, 9, DisplayModule_voidDisplayHours, 0);
	OS_VoidCreateTask(DISPLAY_MINUTES_TASK, 9, DisplayModule_voidDisplayMinutes, 2);
	OS_VoidCreateTask(DISPLAY_SECONDS_TASK, 9, DisplayModule_voidDisplaySeconds, 4);

	OS_VoidCreateTask(DISPLAY_YEARS_TASK, 9, DisplayModule_voidDisplayYears, 0);
	OS_VoidCreateTask(DISPLAY_MONTHS_TASK, 9, DisplayModule_voidDisplayMonths, 5);
	OS_VoidCreateTask(DISPLAY_DAYS_TASK, 9,DisplayModule_voidDisplayDays, 2);

	/*Display Time is initially off*/
	OS_VoidSuspendTask(DISPLAY_HOURS_TASK);
	OS_VoidSuspendTask(DISPLAY_MINUTES_TASK);
	OS_VoidSuspendTask(DISPLAY_SECONDS_TASK);

	/*Display Date is initially off*/
	OS_VoidSuspendTask(DISPLAY_YEARS_TASK);
	OS_VoidSuspendTask(DISPLAY_MONTHS_TASK);
	OS_VoidSuspendTask(DISPLAY_DAYS_TASK);
}

void DisplayModule_voidDisplaySeconds(void)
{
	u8 u8DisplaySeconds = TimeDisplay.u8Second;
	static ToggleState_t Tog = On;

	if(Tog)
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_SECONDS_UNITS);
		SSD_voidSendNumber( ADISPLAY_SECONDS_UNITS  , u8DisplaySeconds%10 );
	}
	else
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_SECONDS_TENS);
		SSD_voidSendNumber( ADISPLAY_SECONDS_TENS  , u8DisplaySeconds/10 );
	}

	Tog = ! Tog ;
}

void DisplayModule_voidDisplayMinutes(void)
{
	u8 u8DisplayMinutes = TimeDisplay.u8Minute;
	static ToggleState_t Tog = On;

	if(Tog)
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_MINUTES_UNITS);
		SSD_voidSendNumber( ADISPLAY_MINUTES_UNITS  , u8DisplayMinutes%10 );
	}
	else
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_MINUTES_TENS);
		SSD_voidSendNumber( ADISPLAY_MINUTES_TENS  , u8DisplayMinutes/10 );
	}

	Tog = ! Tog ;
}

void DisplayModule_voidDisplayHours(void)
{
	u8 u8DisplayHours = TimeDisplay.u8Hour;
	static ToggleState_t Tog = On;

	if(Tog)
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_HOURS_UNITS);
		SSD_voidSendNumber( ADISPLAY_HOURS_UNITS  , u8DisplayHours%10 );
	}
	else
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_HOURS_TENS);
		SSD_voidSendNumber( ADISPLAY_HOURS_TENS  , u8DisplayHours/10 );
	}

	Tog = ! Tog ;
}

void DisplayModule_voidDisplayDays(void)
{
	u8 u8DisplayDays = DateDisplay.u8Day;
	static ToggleState_t Tog = On;

	if(Tog)
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_DAYS_UNITS);
		SSD_voidSendNumber( ADISPLAY_DAYS_UNITS  , u8DisplayDays%10 );
	}
	else
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_DAYS_TENS);
		SSD_voidSendNumber( ADISPLAY_DAYS_TENS  , u8DisplayDays/10 );
	}

	Tog = ! Tog ;
}

void DisplayModule_voidDisplayMonths(void)
{
	u8 u8DisplayMonths = DateDisplay.u8Month;
	static ToggleState_t Tog = On;

	if(Tog)
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_MONTHS_UNITS);
		SSD_voidSendNumber( ADISPLAY_MONTHS_UNITS  , u8DisplayMonths%10 );
	}
	else
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_MONTHS_TENS);
		SSD_voidSendNumber( ADISPLAY_MONTHS_TENS  , u8DisplayMonths/10 );
	}

	Tog = ! Tog ;
}

void DisplayModule_voidDisplayYears(void)
{
	u8 u8DisplayYears = DateDisplay.u8Year;
	static ToggleState_t Tog = On;

	if(Tog)
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_YEARS_UNITS);
		SSD_voidSendNumber( ADISPLAY_YEARS_UNITS  , u8DisplayYears%10 );
	}
	else
	{
		SSD_voidEnableOneDisableRest(ADISPLAY_YEARS_TENS);
		SSD_voidSendNumber( ADISPLAY_YEARS_TENS  , u8DisplayYears/10 );
	}

	Tog = ! Tog ;
}

void DisplayModule_voidSetTime(Time_t localTime)
{
	TimeDisplay = localTime;
}

void DisplayModule_voidSetDate(Date_t localDate)
{
	DateDisplay = localDate;
}



