#ifndef APPLICATION_STATUSMODULE_INTERFACE_H_
#define APPLICATION_STATUSMODULE_INTERFACE_H_

void StatusModule_voidInit(void);
void StatusModule_voidActivateAlarm(void);
void StatusModule_voidDeactivateAlarm(void);

void StatusModule_voidTimeStatus(void);
void StatusModule_voidDateStatus(void);
void StatusModule_voidStopWatchStatus(void);

void StatusModule_voidAlarmOn(void);
void StatusModule_voidAlarmOff(void);

#endif /* APPLICATION_STATUSMODULE_INTERFACE_H_ */
