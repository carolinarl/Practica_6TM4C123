#include "lib/include.h"

extern void Configurar_PWM(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1 << 0);

    // Enable the clock to Port B
    SYSCTL->RCGCGPIO |= (1 << 1);

    // Set the PWM pin as a PWM pin
    GPIOB->AFSEL |= (1 << 6) | (1 << 7);
    GPIOB->PCTL &= ~((0xF << 24) | (0xF << 28));
    GPIOB->PCTL |= (0x4 << 24) | (0x4 << 28);

    // Disable the PWM generator before configuring it
    PWM0->_0_CTL &= ~(1 << 0);

    // Set the PWM generator to count up down mode
    PWM0->_0_GENA = (0x000000C0 | 0x00000008);
    PWM0->_0_GENB = (0x00000C00 | 0x00000008);

    // Set the period of the PWM signal
    PWM0->_0_LOAD = (SystemCoreClock / 2000) - 1;

    // Set the initial duty cycle to 0
    PWM0->_0_CMPA = 0;
    PWM0->_0_CMPB = 0;

    // Enable the PWM output on the appropriate pins
    PWM0->ENABLE = (0x00000002 | 0x00000004);

    // Enable the PWM generator
    PWM0->_0_CTL |= (1 << 0);
}