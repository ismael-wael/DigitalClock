#include <HAL/Hswitch_config.h>
#include <HAL/Hswitch_interface.h>
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>
#include <MCAL/GPIO_interface.h>



void Hswitch_voidInit(void)
{
	u8 u8Iterator;

	for(u8Iterator = 0 ; u8Iterator < NO_OF_SWITCHES ; u8Iterator++)
	{
		MGPIO_voidSetPinDirection(ArrOfSwitches[u8Iterator].GPIO_tSwitch, ArrOfSwitches[u8Iterator].u8SwitchMode);
	}
}

ToggleState_t Hswitch_voidGetCenterSwitch(void)
{
	ToggleState_t CenterSwitchValue = MGPIO_u8GetPinValue(ArrOfSwitches[SWITCH_CENTER].GPIO_tSwitch);

	return CenterSwitchValue;
}

ToggleState_t Hswitch_voidGetRightSwitch(void)
{
	ToggleState_t RightSwitchValue = MGPIO_u8GetPinValue(ArrOfSwitches[SWITCH_RIGHT].GPIO_tSwitch);

	return RightSwitchValue;
}

ToggleState_t Hswitch_voidGetLeftSwitch(void)
{
	ToggleState_t LeftSwitchValue = MGPIO_u8GetPinValue(ArrOfSwitches[SWITCH_LEFT].GPIO_tSwitch);

	return LeftSwitchValue;
}

ToggleState_t Hswitch_voidGetUpSwitch(void)
{
	ToggleState_t UpSwitchValue = MGPIO_u8GetPinValue(ArrOfSwitches[SWITCH_UP].GPIO_tSwitch);

	return UpSwitchValue;
}

ToggleState_t Hswitch_voidGetDownSwitch(void)
{
	ToggleState_t DownSwitchValue = MGPIO_u8GetPinValue(ArrOfSwitches[SWITCH_DOWN].GPIO_tSwitch);

	return DownSwitchValue;
}


