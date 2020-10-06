/*
 * Grupo 2
 * gpio by hand
 * Created: September 2020
 */

#include "gpio.h"
#include "MK64F12.h"
#include "core_cm4.h"
#include "startup/hardware.h"

#define PORT2_SIM_SCGC5_MASK(p) (SIM_SCGC5_PORTA_MASK << (((p)>>5) & 0x07) )

void interruptHandler(uint8_t port);

static PORT_Type * ports[] = PORT_BASE_PTRS;
static GPIO_Type * gpioPorts[] = GPIO_BASE_PTRS;


/**
 * @brief Configures the specified pin to behave either as an input or an output
 * @param pin the pin whose mode you wish to set (according PORTNUM2PIN)
 * @param mode INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN.
 */
void gpioMode (pin_t pin, uint8_t mode)
{

	SIM->SCGC5 |= PORT2_SIM_SCGC5_MASK(pin);

	uint8_t port = PIN2PORT(pin);
	uint8_t num = PIN2NUM(pin);


	ports[port]->PCR[num] = 0x0;
	ports[port]->PCR[num] |= PORT_PCR_MUX(1); //Set MUX to GPIO

	if(mode == OUTPUT) // Output
	{
		ports[port]->PCR[num] &= ~PORT_PCR_PE(0);
		gpioPorts[port]->PDDR |= (1<<num);
	}
	else // Input
	{
		if (mode == INPUT)
		{
			ports[port]->PCR[num] &= ~PORT_PCR_PE(0);
		}
		else
		{
			ports[port]->PCR[num] |= PORT_PCR_PE(1);
			if(mode == INPUT_PULLUP)
			{
				ports[port]->PCR[num] |= PORT_PCR_PS(1);
			}
			else
			{
				ports[port]->PCR[num] &= ~PORT_PCR_PS(0);
			}
		}
		gpioPorts[port]->PDDR &= ~(1<<num);
	}
}


/**
 * @brief Toggle the value of a digital pin (HIGH<->LOW)
 * @param pin the pin to toggle (according PORTNUM2PIN)
 */
void gpioToggle (pin_t pin)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t num = PIN2NUM(pin);
	gpioPorts[port]->PTOR |= (1<<num);

}

/**
 * @brief Reads the value from a specified digital pin, either HIGH or LOW.
 * @param pin the pin to read (according PORTNUM2PIN)
 * @return HIGH or LOW
 */
bool gpioRead (pin_t pin)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t num = PIN2NUM(pin);
	bool ret = (bool)(gpioPorts[port]->PDIR & (1<<num));
	return ret;
}

/**
 * @brief Write a HIGH or a LOW value to a digital pin
 * @param pin the pin to write (according PORTNUM2PIN)
 * @param val Desired value (HIGH or LOW)
 */
void gpioWrite (pin_t pin, bool value)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t num = PIN2NUM(pin);
	gpioPorts[port]->PDOR = (gpioPorts[port]->PDOR & ~(1<<num)) | (value << num);
}

/**
 * @brief Configures how the pin reacts when an IRQ event ocurrs
 * @param pin the pin whose IRQ mode you wish to set (according PORTNUM2PIN)
 * @param irqMode disable, risingEdge, fallingEdge or bothEdges
 * @param irqFun function to call on pin event
 * @return Registration succeed
 */
static void (*callbacks[5][32])(void);

bool gpioIRQ (pin_t pin, uint8_t irqMode, pinIrqFun_t irqFun)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t num = PIN2NUM(pin);
	ports[port]->PCR[num] |= PORT_PCR_IRQC_MASK;
	ports[port]->PCR[num] |= PORT_PCR_IRQC(irqMode);
	NVIC_EnableIRQ(PORTA_IRQn + port);
	callbacks[port][num] = irqFun;

	return NVIC_GetActive(PORTA_IRQn + port); // not implemented yet
}

/**
 * @brief Clear IRQ flag.
 * @param pin the pin to read (according PORTNUM2PIN)
 */
bool PORT_ClearInterruptFlag (pin_t pin)
{
	uint8_t port = PIN2PORT(pin);
	uint8_t num = PIN2NUM(pin);
	ports[port]->PCR[num] |= PORT_PCR_ISF_MASK;
	return true;
}

__ISR__ PORTA_IRQHandler (void)
{
	interruptHandler(0);
}

__ISR__ PORTB_IRQHandler (void)
{
	interruptHandler(1);
}

__ISR__ PORTC_IRQHandler (void)
{
	interruptHandler(2);
}

__ISR__ PORTD_IRQHandler (void)
{
	interruptHandler(3);
}

__ISR__ PORTE_IRQHandler (void)
{
	interruptHandler(4);
}

void interruptHandler(uint8_t port)
{
	int i;
	uint32_t isfr = ports[port]->ISFR;
	for (i = 0; i<32;i++)
	{
		if ( callbacks[port][i] && (isfr & 0x1) )
		{
			ports[port]->PCR[i] |= PORT_PCR_ISF_MASK;
			callbacks[port][i]();
		}
		isfr >>= 1;
	}
}
