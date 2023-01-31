#include "lib/include.h"

uint16_t Result[2];
uint16_t duty[2];
void Hilo_1(void)
{
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
    
    // Main loop
    while(1)
    {

        while ((ADC0->RIS & 0x1) == 0)
        {
        }

        // Read the ADC result for channel 0
        uint32_t adcResult0 = ADC0->SSFIFO0 & 0xFFF;

        // Clear the ADC interrupt flag for channel 0
        ADC0->ISC = 0x1;

        // Start the ADC conversion for channel 1
        ADC0->PSSI |= 0x2;

        while ((ADC0->RIS & 0x2) == 0)
        {
        }

        // Read the ADC result for channel 1
        uint32_t adcResult1 = ADC0->SSFIFO1 & 0xFFF;
        // Clear the ADC interrupt flag for channel 1
        ADC0->ISC = 0x2;

        // Process the ADC results for both channels here


    }
}