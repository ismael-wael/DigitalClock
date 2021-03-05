#ifndef APPLICATION_CONTROL_H_
#define APPLICATION_CONTROL_H_

#define RESET_STOPWATCH		2
#define RESUME_STOPWATCH	1
#define STOP_STOPWATCH		0

						/***************Edit Time positions****************/
#define EDIT_SECONDS			1
#define EDIT_MINUTES			2
#define EDIT_HOURS				3

						/***************Edit Date positions****************/
#define EDIT_DAYS				1
#define EDIT_MONTHS				2
#define EDIT_YEARS				3

						/***************Choose What To Edit***************/
#define EDIT_TIME 		        3
#define EDIT_DATE 		 		2
#define EDIT_ALARM_TIME  		1
#define EDIT_ALARM_DATE         0

						/************************************************/
#define NONE					0
#define	INCREASE				1
#define DECREASE				2
						/*******************EDIT or DISPLAY ***************/
#define DISPLAY					1
#define EDIT					0

										/*Display States*/
#define DISPLAY_TIME			2
#define DISPLAY_DATE			1
#define DISPLAY_STOPWATCH		0

										/*Alarm States*/
#define ALARM_ON				1
#define ALARM_OFF				0

typedef enum{
	Jan = 1 , Feb , Mar , Apr , May , June , July , Aug , Sep , Oct , Nov , Dec
}Month;

void ControlModule_voidInit(void);
/*summs the updates and send them to display,
 * also checks alarm and calls alarmOccured if it happended*/
void ControlModule_voidUpdate(void);
void ControlModule_voidUpdateEdit(void);
/*sums the updates and send them to display,
 * also checks alarm and calls alarmOccured if it happended*/
void ControlModule_voidUpdateDisplay(void);

static void ControlModule_u8UpdateTime(Time_t* Time_Ptr , Date_t* Date_Ptr);
static void ControlModule_u8UpdateDate(Date_t* Date_Ptr);
static Bool_t ControlModule_BoolIsLeapYear(Date_t* Date_Ptr);

static Bool_t ControlModule_BoolCheckAlarm(Alarm_t* Alarm_Ptr , Time_t* Time_Ptr , Date_t* Date_Ptr);

static void ControlModule_voidDisplayOptions(Time_t DisplayTime , Date_t DisplayDate);

static void ControlModule_voidEditDate(Date_t* EditDate );
void ControlModule_voidEditYears(u8* Object);
void ControlModule_voidEditMonths(u8* Object);
void ControlModule_voidEditDays(Date_t* Object);
static void ControlModule_u8UpdateDaysIncrease(Date_t* Date_Ptr);
static void ControlModule_u8UpdateDaysDecrease(Date_t* Date_Ptr);

static void ControlModule_voidEditTime(Time_t* EditTime );
void ControlModule_voidEditSecondsMinutes(u8* Object);
void ControlModule_voidEditHours(u8* Object);

void ControlModule_voidSetAlarmState(ToggleState_t localAlarmState);
void ControlModule_voidSetDisplayState(u8 u8localDisplayState);
void ControlModule_voidSetDisplayOrEdit(ToggleState_t localDisplayOrEdit);
void ControlModule_voidSetEditState  (u8 localEditState);
void ControlModule_voidSetEditPosition  (u8 u8localEditPosition);
void ControlModule_voidSetWhatToEdit  (u8 u8localWhatToEdit);
void ControlModule_voidSetStopWatchState  (u8 u8localStopWatchState);

#endif /* APPLICATION_CONTROL_H_ */
