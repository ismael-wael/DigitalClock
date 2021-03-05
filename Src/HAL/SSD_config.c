#include <HAL/SSD_config.h>
#include <HAL/SSD_interface.h>
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>
#include <MCAL/GPIO_interface.h>

 SSD_t HSSDArrayOfSSD [ NUM_OF_SSD ] = {

		{//Seconds Units
				.Type = COM_ANODE,
				.GPIO_tPin_A = {PIN0 , GPIOA_Port },
				.GPIO_tPin_B = {PIN1 , GPIOA_Port },
				.GPIO_tPin_C = {PIN2 , GPIOA_Port },
				.GPIO_tPin_D = {PIN3 , GPIOA_Port },
				.GPIO_tPin_E = {PIN4 , GPIOA_Port },
				.GPIO_tPin_F = {PIN5 , GPIOA_Port },
				.GPIO_tPin_G = {PIN6 , GPIOA_Port },
				.GPIO_tEnablePin = {PIN8 , GPIOA_Port}
		},

		{//Seconds Tens
				.Type = COM_ANODE,
				.GPIO_tPin_A = {PIN0 , GPIOA_Port },
				.GPIO_tPin_B = {PIN1 , GPIOA_Port },
				.GPIO_tPin_C = {PIN2 , GPIOA_Port },
				.GPIO_tPin_D = {PIN3 , GPIOA_Port },
				.GPIO_tPin_E = {PIN4 , GPIOA_Port },
				.GPIO_tPin_F = {PIN5 , GPIOA_Port },
				.GPIO_tPin_G = {PIN6 , GPIOA_Port },
				.GPIO_tEnablePin = {PIN9 , GPIOA_Port}
		},

		{//Minutes Units
				.Type = COM_CATHODE,
				.GPIO_tPin_A = {PIN0 , GPIOA_Port },
				.GPIO_tPin_B = {PIN1 , GPIOA_Port },
				.GPIO_tPin_C = {PIN2 , GPIOA_Port },
				.GPIO_tPin_D = {PIN3 , GPIOA_Port },
				.GPIO_tPin_E = {PIN4 , GPIOA_Port },
				.GPIO_tPin_F = {PIN5 , GPIOA_Port },
				.GPIO_tPin_G = {PIN6 , GPIOA_Port },
				.GPIO_tEnablePin = {PIN10 , GPIOA_Port}
		},

		{//Minutes Tens
				.Type = COM_CATHODE,
				.GPIO_tPin_A = {PIN0 , GPIOA_Port },
				.GPIO_tPin_B = {PIN1 , GPIOA_Port },
				.GPIO_tPin_C = {PIN2 , GPIOA_Port },
				.GPIO_tPin_D = {PIN3 , GPIOA_Port },
				.GPIO_tPin_E = {PIN4 , GPIOA_Port },
				.GPIO_tPin_F = {PIN5 , GPIOA_Port },
				.GPIO_tPin_G = {PIN6 , GPIOA_Port },
				.GPIO_tEnablePin = {PIN11 , GPIOA_Port}
		},

		{//Hours Units
				.Type = COM_ANODE,
				.GPIO_tPin_A = {PIN0 , GPIOA_Port },
				.GPIO_tPin_B = {PIN1 , GPIOA_Port },
				.GPIO_tPin_C = {PIN2 , GPIOA_Port },
				.GPIO_tPin_D = {PIN3 , GPIOA_Port },
				.GPIO_tPin_E = {PIN4 , GPIOA_Port },
				.GPIO_tPin_F = {PIN5 , GPIOA_Port },
				.GPIO_tPin_G = {PIN6 , GPIOA_Port },
				.GPIO_tEnablePin = {PIN12 , GPIOA_Port}
		},

		{//Hours Tens
				.Type = COM_ANODE,
				.GPIO_tPin_A = {PIN0 , GPIOA_Port },
				.GPIO_tPin_B = {PIN1 , GPIOA_Port },
				.GPIO_tPin_C = {PIN2 , GPIOA_Port },
				.GPIO_tPin_D = {PIN3 , GPIOA_Port },
				.GPIO_tPin_E = {PIN4 , GPIOA_Port },
				.GPIO_tPin_F = {PIN5 , GPIOA_Port },
				.GPIO_tPin_G = {PIN6 , GPIOA_Port },
				.GPIO_tEnablePin = {PIN7 , GPIOA_Port}
		}

};

