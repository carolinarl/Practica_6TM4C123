#include "lib/include.h"

uint16_t Result[2];
uint16_t duty[2];
void Hilo_1(void)
{
    /*
 //llamada a la conversion por procesador
    PWM0->_1_CMPB = duty[0];
    PWM0->_1_CMPA = duty[1];
    PWM0->_0_CMPA = 1500;    
    */
    GPIOB_AHB->DATA = (1<<0);
    ADC0_InSeq2(Result,duty);
    GPIOB_AHB->DATA = (0<<0);
    

}

int main(void)
{

    Configurar_PLL(_25MHZ);  //Velocidad de reloj
    Configurar_GPIO();
    Configurar_ADC0();
    Configurar_UART0();
    Configurar_PWM(50);// Configuración PWM
    Configurar_Timer0(&Hilo_1,10000);
    while(1)
    {
        
    }

}