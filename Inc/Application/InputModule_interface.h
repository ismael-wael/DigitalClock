#ifndef APPLICATION_INPUTMODULE_INTERFACE_H_
#define APPLICATION_INPUTMODULE_INTERFACE_H_

#define SWITCH_PRESSED			0
#define SWITCH_RELEASED			1

#define CENTERSWITCH_DISPLAY		1 //(default)
#define CENTERSWITCH_EDIT_TIME		0

		/*****************Switches States in case : Display Mode*********************/


#define RIGHTSWITCH_TIME		2 //(default)
#define RIGHTSWITCH_DATE		1
#define RIGHTSWITCH_STOPWATCH	0

#define LEFTSWITCH_ALARM_OFF	1 //(default)
#define LEFTSWITCH_ALARM_ON		0

		/*****************Switches States in case : Edit_Time Mode*********************/

#define RIGHTSWITCH_IDLE			0 //(default)
#define RIGHTSWITCH_MOVE_RIGHT		1

#define LEFTSWITCH_MOVE_LEFT		1
#define LEFTSWITCH_IDLE				0 //(default)

/*****************************************************************************************************/


typedef struct{
	ToggleState_t UpSwitchState;
	ToggleState_t DownSwitchState;
	ToggleState_t LeftSwitchState;
	ToggleState_t RightSwitchState;
	ToggleState_t CenterSwitchState;
}SwitchesState;

void InputModule_voidInit(void);

void InputModule_voidProcessInputs(void);

static void InputModule_voidProcessCenterSwitch(void);
static void InputModule_voidProcessRightSwitch(void);
static void InputModule_voidProcessLeftSwitch(void);
static void InputModule_voidProcessUpSwitch(void);
static void InputModule_voidProcessDownSwitch(void);

/*if any pushButton is pressed, an interrupt to EXTI9_5_IRQHandler will occur,
 * that function will be called when the interrupt occur
 * the function Activate : "InputModule_voidProcessInputs" Task*/
void InputModule_voidActivateProcessInputsTask(void);

#endif /* APPLICATION_INPUTMODULE_INTERFACE_H_ */
