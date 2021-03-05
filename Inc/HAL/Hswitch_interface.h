#ifndef HAL_HSWITCH_INTERFACE_H_
#define HAL_HSWITCH_INTERFACE_H_

#include <HAL/Hswitch_config.h>
#include <MCAL/GPIO_interface.h>

typedef struct{
    GPIO_t GPIO_tSwitch;

    u8 u8SwitchMode;        // INPUT_ANALOG
}Hswitch_t;                 // INPUT_FLOATING
                            // INPUT_PULL_UP_OR_DOWN

extern const Hswitch_t ArrOfSwitches[NO_OF_SWITCHES];

void Hswitch_voidInit(void);

ToggleState_t Hswitch_voidGetCenterSwitch(void);
ToggleState_t Hswitch_voidGetRightSwitch(void);
ToggleState_t Hswitch_voidGetLeftSwitch(void);
ToggleState_t Hswitch_voidGetUpSwitch(void);
ToggleState_t Hswitch_voidGetDownSwitch(void);

#endif
