/* Library includes */
#include <Libraries/LIB_BMNP.h>
#include <Libraries/LIB_STDTypes.h>
#include <MCAL/AFIO_interface.h>
#include <MCAL/AFIO_private.h>
#include <MCAL/GPIO_interface.h>

/* Module includes */


void AFIO_voidSetEXTIConfiguration(u8 Copy_u8EXTI_Line ,u8 Copy_u8PortMap)
{
	
	u8 LOC_u8RegIndex = Copy_u8EXTI_Line / 4;

	Copy_u8EXTI_Line = Copy_u8EXTI_Line % 4;
	/* Clear the four bits first */
	AFIO_Ptr -> EXTICRx[LOC_u8RegIndex] &= ~(( 0b1111) << (Copy_u8EXTI_Line * 4));
	/* Write into the four bits */
	AFIO_Ptr -> EXTICRx[LOC_u8RegIndex] |= (Copy_u8PortMap) << (Copy_u8EXTI_Line * 4);
}
