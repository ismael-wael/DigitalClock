/*Libraries*/
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>

/*Application*/
#include <Application/ControlModule_interface.h>
#include <Application/DisplayModule_interface.h>
#include <Application/StatusModule_interface.h>

/*HAL*/
#include <HAL/Led_interface.h>
#include <HAL/SSD_interface.h>

/*OS*/
#include <OS/OS_interface.h>
#include <OS/OS_config.h>

/********************************************************************************************/

/* variable used by user to select between display and edit options
 * EDIT : 	 0
 * DISPLAY : 1
 */
static ToggleState_t DisplayOrEdit = DISPLAY;

/*variable used by user to choose what to display : date or time*
 * DISPLAY_TIME 		: 2
 * DISPLAY_DATE 		: 1
 * DISPLAY_STOPWATCH	: 0
 */
static u8 DisplayState = DISPLAY_TIME;

/*variable used by user to choose Alarm State :
 * ALARM_ON 	: 1
 * ALARM_OFF    : 0
 */
static ToggleState_t AlarmState = ALARM_ON;

/*variable set by user to choose position of editing
 * in case of time  :
 * 			EDIT_SECONDS				1
			EDIT_MINUTES				2
			EDIT_HOURS					3
 * */
static u8 u8EditPosition;

/*variable set by user to choose state of editing , either :
 * in case of time or alarm :
 * 		DECREASE :      2
 * 		INCREASE : 		1
 * 		NONE     : 		0
 * */
static u8 u8EditState      ;

/*variable set by user to choose what to Edit , either :
 * 		EDIT_TIME 		:       3
 * 		EDIT_DATE 		: 		2
 * 		EDIT_ALARM_TIME : 		1
 * 		EDIT_ALARM_DATE :       0
 * */
static u8 u8WhatToEdit = EDIT_DATE;

/* StopWatch States :
 *
 * 	RESET_STOPWATCH	   :	2
	RESUME_STOPWATCH   :	1
	STOP_STOPWATCH	   :	0
 * */
static u8 u8StopWatchStates = RESET_STOPWATCH;

static Time_t	Time = {50,35,12};
static Date_t	Date = {17,Dec,21};
static Alarm_t  Alarm = {{17,Dec,21} , {00,36,12}};

static Time_t 	StopWatch = {0,0,0};
static Date_t	Dummy_Date; // used with StopWatch when passing it to time funcs , just to verify the func's prototype!

void ControlModule_voidInit(void)
{
	OS_VoidCreateTask(UPDATE_TASK, 1000, ControlModule_voidUpdate, 0);
	OS_VoidCreateTask(UPDATE_DISPLAY_TASK, 1000, ControlModule_voidUpdateDisplay, 0);
	OS_VoidCreateTask(UPDATE_EDIT_TASK, 40, ControlModule_voidUpdateEdit, 0);

	/*update Task is initially Active*/
	OS_VoidResumeTask(UPDATE_TASK);
	/*UpdateDisplay task is initially off*/
	OS_VoidSuspendTask(UPDATE_DISPLAY_TASK);
	/*UpdateEdit task is initally off*/
	OS_VoidSuspendTask(UPDATE_EDIT_TASK);
}

void ControlModule_voidUpdate(void)
{
	if(DisplayOrEdit == DISPLAY)
	{
		OS_VoidSuspendTask(UPDATE_EDIT_TASK);
		OS_VoidResumeTask(UPDATE_DISPLAY_TASK);
	}
	else
	{
		OS_VoidResumeTask(UPDATE_EDIT_TASK);

		u8WhatToEdit == EDIT_TIME ? OS_VoidSuspendTask(UPDATE_DISPLAY_TASK) : OS_VoidResumeTask(UPDATE_DISPLAY_TASK);
	}
}

void ControlModule_voidUpdateEdit(void)
{
	switch(u8WhatToEdit)
	{
		case EDIT_TIME :
			ControlModule_voidEditTime(&Time);
			break;
		case EDIT_DATE :
			ControlModule_voidEditDate(&Date);
			break;
		case EDIT_ALARM_TIME :
			ControlModule_voidEditTime(&(Alarm.AlarmTime));
			break;
		case EDIT_ALARM_DATE :
			ControlModule_voidEditDate(&(Alarm.AlarmDate));
			break;
		default :
			break;
	}
}

/*sums the updates and send them to display,
 * also checks alarm and calls alarmOccured if it happended*/
void ControlModule_voidUpdateDisplay(void)
{
	/*Process Time : update or edit*/
	ControlModule_u8UpdateTime(&Time , &Date);
	Bool_t Activate_Alarm = ControlModule_BoolCheckAlarm(&Alarm , &Time , &Date);

	if(AlarmState && Activate_Alarm)
	{
		OS_VoidResumeTask(ACTIVATE_ALARM_TASK);
	}

	if(DisplayState == DISPLAY_STOPWATCH)
	{
		switch(u8StopWatchStates)
		{
			case RESET_STOPWATCH :
				StopWatch.u8Hour = 0;
				StopWatch.u8Minute = 0;
				StopWatch.u8Second = 0;
				break;
			case STOP_STOPWATCH :
				break;
			case RESUME_STOPWATCH :
				ControlModule_u8UpdateTime(&StopWatch , &Dummy_Date);
				break;
			default :
				break;
		}
	}

	/*Display : update*/
	DisplayState == DISPLAY_STOPWATCH ? ControlModule_voidDisplayOptions(StopWatch , Dummy_Date) : ControlModule_voidDisplayOptions(Time , Date);
}

static void ControlModule_voidDisplayOptions(Time_t DisplayTime , Date_t DisplayDate)
{
	if(DisplayState == DISPLAY_TIME || DisplayState == DISPLAY_STOPWATCH)
	{
		DisplayModule_voidSetTime(DisplayTime);

		/*Suspend Date Tasks*/
		OS_VoidSuspendTask(DISPLAY_YEARS_TASK);
		OS_VoidSuspendTask(DISPLAY_MONTHS_TASK);
		OS_VoidSuspendTask(DISPLAY_DAYS_TASK);

		/*Resume Time Tasks*/
		OS_VoidResumeTask(DISPLAY_HOURS_TASK);
		OS_VoidResumeTask(DISPLAY_MINUTES_TASK);
		OS_VoidResumeTask(DISPLAY_SECONDS_TASK);

	}
	else
	{
		DisplayModule_voidSetDate(DisplayDate);

		/*Suspend Time Tasks*/
		OS_VoidSuspendTask(DISPLAY_HOURS_TASK);
		OS_VoidSuspendTask(DISPLAY_MINUTES_TASK);
		OS_VoidSuspendTask(DISPLAY_SECONDS_TASK);

		/*Resume Date Tasks*/
		OS_VoidResumeTask(DISPLAY_YEARS_TASK);
		OS_VoidResumeTask(DISPLAY_MONTHS_TASK);
		OS_VoidResumeTask(DISPLAY_DAYS_TASK);
	}
}

static void ControlModule_voidEditDate(Date_t* EditDate )
{
	/*Suspend Time Tasks : Not to appear on SSD */
	OS_VoidSuspendTask(DISPLAY_HOURS_TASK);
	OS_VoidSuspendTask(DISPLAY_MINUTES_TASK);
	OS_VoidSuspendTask(DISPLAY_SECONDS_TASK);

	static u8 u8Tog = 20;

	switch(u8EditPosition)
	{
		case EDIT_DAYS :
			ControlModule_voidEditDays(EditDate);

			OS_VoidResumeTask(DISPLAY_YEARS_TASK);
			OS_VoidResumeTask(DISPLAY_MONTHS_TASK);

			u8Tog >= 10 ? OS_VoidResumeTask(DISPLAY_DAYS_TASK) : OS_VoidSuspendTask(DISPLAY_DAYS_TASK) ;

			break;
		case EDIT_MONTHS :
			ControlModule_voidEditMonths(&(EditDate->u8Month));

			OS_VoidResumeTask(DISPLAY_YEARS_TASK);
			OS_VoidResumeTask(DISPLAY_DAYS_TASK);

			u8Tog >= 10 ? OS_VoidResumeTask(DISPLAY_MONTHS_TASK) : OS_VoidSuspendTask(DISPLAY_MONTHS_TASK) ;

			break;
		case EDIT_YEARS :
			ControlModule_voidEditYears(&(EditDate->u8Year));

			OS_VoidResumeTask(DISPLAY_MONTHS_TASK);
			OS_VoidResumeTask(DISPLAY_DAYS_TASK);

			u8Tog >= 10 ? OS_VoidResumeTask(DISPLAY_YEARS_TASK) : OS_VoidSuspendTask(DISPLAY_YEARS_TASK) ;

			break;
		default :
			break;
	}

	u8Tog--;

	if(u8Tog == 0)
		u8Tog = 20;


	DisplayModule_voidSetDate(*EditDate);
}

void ControlModule_voidEditYears(u8* Object)
{
	switch(u8EditState)
	{
		case INCREASE :
			*Object = *Object + 1 ;
			break;
		case DECREASE :
			*Object = *Object == 0 ? 99 : (*Object - 1);
			break;
		case NONE :
			break;
		default :
			break;
	}
	u8EditState = NONE;
}

void ControlModule_voidEditMonths(u8* Object)
{
	switch(u8EditState)
	{
		case INCREASE :
			*Object = *Object == 12 ? 1 : *Object + 1 ;
			break;
		case DECREASE :
			*Object = *Object == 1 ? 12 : (*Object - 1);
			break;
		case NONE :
			break;
		default :
			break;
	}
	u8EditState = NONE;
}

void ControlModule_voidEditDays(Date_t* Object)
{
	switch(u8EditState)
	{
		case INCREASE :
			ControlModule_u8UpdateDaysIncrease(Object);
			break;
		case DECREASE :
			ControlModule_u8UpdateDaysDecrease(Object);
			break;
		case NONE :
			break;
		default :
			break;
	}
	u8EditState = NONE;
}

static void ControlModule_u8UpdateDaysIncrease(Date_t* Date_Ptr)
{
	switch(Date_Ptr->u8Month)
	{
		case	Jan :
		case 	Mar :
		case 	May :
		case 	July :
		case 	Aug :
		case 	Oct :
		case 	Dec :
			if(Date_Ptr->u8Day == 31)
			{
				Date_Ptr->u8Day = 1;
			}
			else
			{
				Date_Ptr->u8Day++;
			}
			break;

		case Feb :
			if(ControlModule_BoolIsLeapYear(Date_Ptr))
			{
				if(Date_Ptr->u8Day == 29)
				{
					Date_Ptr->u8Day = 1;
				}
				else
				{
					Date_Ptr->u8Day++;
				}
			}
			else
			{
				if(Date_Ptr->u8Day == 28)
				{
					Date_Ptr->u8Day = 1;
				}
				else
				{
					Date_Ptr->u8Day++;
				}
			}
			break;
		case Apr :
		case June :
		case Sep :
		case Nov :
			if(Date_Ptr->u8Day == 30)
			{
				Date_Ptr->u8Day = 1;
			}
			else
			{
				Date_Ptr->u8Day++;
			}
			break;
	}
}

static void ControlModule_u8UpdateDaysDecrease(Date_t* Date_Ptr)
{
	switch(Date_Ptr->u8Month)
	{
		case	Jan :
		case 	Mar :
		case 	May :
		case 	July :
		case 	Aug :
		case 	Oct :
		case 	Dec :
			if(Date_Ptr->u8Day == 1)
			{
				Date_Ptr->u8Day = 31;
			}
			else
			{
				Date_Ptr->u8Day--;
			}
			break;

		case Feb :
			if(ControlModule_BoolIsLeapYear(Date_Ptr))
			{
				if(Date_Ptr->u8Day == 1)
				{
					Date_Ptr->u8Day = 29;
				}
				else
				{
					Date_Ptr->u8Day--;
				}
			}
			else
			{
				if(Date_Ptr->u8Day == 1)
				{
					Date_Ptr->u8Day = 28;
				}
				else
				{
					Date_Ptr->u8Day--;
				}
			}
			break;
		case Apr :
		case June :
		case Sep :
		case Nov :
			if(Date_Ptr->u8Day == 1)
			{
				Date_Ptr->u8Day = 30;
			}
			else
			{
				Date_Ptr->u8Day--;
			}
			break;
	}
}

static void ControlModule_voidEditTime(Time_t* EditTime )
{
	/*Suspend Date Tasks*/
	OS_VoidSuspendTask(DISPLAY_YEARS_TASK);
	OS_VoidSuspendTask(DISPLAY_MONTHS_TASK);
	OS_VoidSuspendTask(DISPLAY_DAYS_TASK);

	static u8 u8Tog = 20;

	switch(u8EditPosition)
	{
		case EDIT_SECONDS :
			ControlModule_voidEditSecondsMinutes(&(EditTime->u8Second));

			OS_VoidResumeTask(DISPLAY_HOURS_TASK);
			OS_VoidResumeTask(DISPLAY_MINUTES_TASK);

			u8Tog >= 10 ? OS_VoidResumeTask(DISPLAY_SECONDS_TASK) : OS_VoidSuspendTask(DISPLAY_SECONDS_TASK) ;

			break;
		case EDIT_MINUTES :
			ControlModule_voidEditSecondsMinutes(&(EditTime->u8Minute));

			OS_VoidResumeTask(DISPLAY_HOURS_TASK);
			OS_VoidResumeTask(DISPLAY_SECONDS_TASK);

			u8Tog >= 10 ? OS_VoidResumeTask(DISPLAY_MINUTES_TASK) : OS_VoidSuspendTask(DISPLAY_MINUTES_TASK) ;

			break;
		case EDIT_HOURS :
			ControlModule_voidEditHours(&(EditTime->u8Hour));

			OS_VoidResumeTask(DISPLAY_SECONDS_TASK);
			OS_VoidResumeTask(DISPLAY_MINUTES_TASK);

			u8Tog >= 10 ? OS_VoidResumeTask(DISPLAY_HOURS_TASK) : OS_VoidSuspendTask(DISPLAY_HOURS_TASK) ;

			break;
		default :
			break;
	}

	u8Tog--;

	if(u8Tog == 0)
		u8Tog = 20;

	DisplayModule_voidSetTime(*EditTime);
}

void ControlModule_voidEditSecondsMinutes(u8* Object)
{
	switch(u8EditState)
	{
		case INCREASE :
			*Object = *Object == 59 ? 0 : (*Object + 1);
			break;
		case DECREASE :
			*Object = *Object == 0 ? 59 : (*Object - 1);
			break;
		case NONE :
			break;
		default :
			break;
	}
	u8EditState = NONE;
}

void ControlModule_voidEditHours(u8* Object)
{
	switch(u8EditState)
	{
		case INCREASE :
			*Object = *Object == 12 ? 1 : (*Object + 1);
			break;
		case DECREASE :
			*Object = *Object == 1 ? 12 : (*Object - 1);
			break;
		case NONE :
			break;
		default :
			break;
	}
	u8EditState = NONE;
}

static void ControlModule_u8UpdateTime(Time_t* Time_Ptr , Date_t* Date_Ptr)
{
	if(Time_Ptr->u8Second == 59)
	{
		Time_Ptr->u8Second = 0;
		if(Time_Ptr->u8Minute == 59)
		{
			Time_Ptr->u8Minute = 0;
			if(Time_Ptr->u8Hour == 11)
			{
				Time_Ptr->u8Hour = 12;
				ControlModule_u8UpdateDate(Date_Ptr);
			}
			else if(Time_Ptr->u8Hour == 12)
			{
				Time_Ptr->u8Hour = 1;
			}
			else
			{
				Time_Ptr->u8Hour++;
			}
		}
		else
		{
			Time_Ptr->u8Minute++;
		}
	}
	else
	{
		Time_Ptr->u8Second++;
	}
}

static void ControlModule_u8UpdateDate(Date_t* Date_Ptr)
{
	switch(Date_Ptr->u8Month)
	{
		case	Jan :
		case 	Mar :
		case 	May :
		case 	July :
		case 	Aug :
		case 	Oct :
		case 	Dec :
			if(Date_Ptr->u8Day == 31)
			{
				if(Date_Ptr->u8Month == Dec)
				{
					Date_Ptr->u8Month = Jan;
					Date_Ptr->u8Year++;
				}
				else
				{
					Date_Ptr->u8Month++;
				}
				Date_Ptr->u8Day = 1;
			}
			else
			{
				Date_Ptr->u8Day++;
			}
			break;

		case Feb :
			if(ControlModule_BoolIsLeapYear(Date_Ptr))
			{
				if(Date_Ptr->u8Day == 29)
				{
					Date_Ptr->u8Month = Mar;
					Date_Ptr->u8Day = 1;
				}
				else
				{
					Date_Ptr->u8Day++;
				}
			}
			else
			{
				if(Date_Ptr->u8Day == 28)
				{
					Date_Ptr->u8Month = Mar;
					Date_Ptr->u8Day = 1;
				}
				else
				{
					Date_Ptr->u8Day++;
				}
			}
			break;

		case Apr :
		case June :
		case Sep :
		case Nov :
			if(Date_Ptr->u8Day == 30)
			{
				Date_Ptr->u8Month++;
				Date_Ptr->u8Day = 1;
			}
			else
			{
				Date_Ptr->u8Day++;
			}
			break;
	}

}

static Bool_t ControlModule_BoolIsLeapYear(Date_t* Date_Ptr)
{
	if(Date_Ptr->u8Year % 400 == 0 || Date_Ptr->u8Year % 4 == 0)
	{
		return True;
	}
	else
	{
		return False;
	}
}

static Bool_t ControlModule_BoolCheckAlarm(Alarm_t* Alarm_Ptr , Time_t* Time_Ptr , Date_t* Date_Ptr)
{
	if(((Alarm_Ptr->AlarmDate.u8Day    == Date_Ptr->u8Day   ) &&
	    (Alarm_Ptr->AlarmDate.u8Month  == Date_Ptr->u8Month ) &&
	    (Alarm_Ptr->AlarmDate.u8Year   == Date_Ptr->u8Year  ))&&
	    ((Alarm_Ptr->AlarmTime.u8Hour  == Time_Ptr->u8Hour  ) &&
	    (Alarm_Ptr->AlarmTime.u8Minute == Time_Ptr->u8Minute) &&
	    (Alarm_Ptr->AlarmTime.u8Second == Time_Ptr->u8Second)))
	{
		return True;
	}
	else
	{
		return False;
	}
}

void ControlModule_voidSetAlarmState(ToggleState_t localAlarmState)
{
	AlarmState = localAlarmState;

	if(AlarmState == ALARM_ON)
	{
		StatusModule_voidAlarmOn();
	}
	else
	{
		StatusModule_voidAlarmOff();
	}
}

void ControlModule_voidSetDisplayState(u8 u8localDisplayState)
{
	DisplayState = u8localDisplayState;
}

void ControlModule_voidSetDisplayOrEdit(ToggleState_t localDisplayOrEdit)
{
	DisplayOrEdit = localDisplayOrEdit;
}

void ControlModule_voidSetEditState  (u8 u8localEditState)
{
	u8EditState = u8localEditState;
}

void ControlModule_voidSetEditPosition  (u8 u8localEditPosition)
{
	u8EditPosition = u8localEditPosition;
}

void ControlModule_voidSetWhatToEdit  (u8 u8localWhatToEdit)
{
	u8WhatToEdit = u8localWhatToEdit;
}

void ControlModule_voidSetStopWatchState  (u8 u8localStopWatchState)
{
	u8StopWatchStates = u8localStopWatchState;
}



