
#include "SysTick.h"
#include "startup/hardware.h"


static void (*callback)(void);

bool SysTick_Init (void (*funcallback)(void))
{
	bool error = true;
	error &= SysTick_Config(12500000L);

	//NVIC_SetVector(SysTick_IRQn, (uint32_t)funcallback);
	callback = funcallback;

	return !error;
}

__ISR__ SysTick_Handler (void)
{
	callback();
}
