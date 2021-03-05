#ifndef APPLICATION_DISPLAY_H_
#define APPLICATION_DISPLAY_H_

//give number to each SSD in the system starting from 0 (Time Display)
#define ADISPLAY_SECONDS_UNITS		0
#define ADISPLAY_SECONDS_TENS		1
#define ADISPLAY_MINUTES_UNITS		2
#define ADISPLAY_MINUTES_TENS		3
#define ADISPLAY_HOURS_UNITS		4
#define ADISPLAY_HOURS_TENS			5

//give number to each SSD in the system starting from 0 (Date Display)
#define ADISPLAY_DAYS_UNITS			0
#define ADISPLAY_DAYS_TENS			1
#define ADISPLAY_MONTHS_UNITS		2
#define ADISPLAY_MONTHS_TENS		3
#define ADISPLAY_YEARS_UNITS		4
#define ADISPLAY_YEARS_TENS			5

/*initializes Display Module,
 * All i need to display time*/
void DispalyModule_voidInit(void);

void DisplayModule_voidDisplaySeconds(void);
void DisplayModule_voidDisplayMinutes(void);
void DisplayModule_voidDisplayHours(void);

void DisplayModule_voidDisplayDays(void);
void DisplayModule_voidDisplayMonths(void);
void DisplayModule_voidDisplayYears(void);

/*setter : sets the new time*/
void DisplayModule_voidSetTime(Time_t localTime);

/*setter : sets the new date*/
void DisplayModule_voidSetDate(Date_t localDate);

#endif /* APPLICATION_DISPLAY_H_ */
