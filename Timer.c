#include "lib/include.h"

void (*PeriodicTask)(void);

extern void Configurar_Timer0(void(*task)(void), unsigned long int periodo)
{
    SYSCTL->RCGCTIMER |= (1<<0); // Periférico Timer0
    PeriodicTask = task; // DIRECCIÓN DE MEMORIA DE LA TAREA
    TIMER0->CTL = (0<<0);  // Deshabilitación del periférico
    TIMER0->CFG = 0x00000000; // Modo de operación de 32 bits
    TIMER0->TAMR = (0x2<<0); // Modo periódico
    TIMER0->TAILR = periodo - 1;
    TIMER0->ICR = 1<<0;
    TIMER0->IMR = 1<<0;
    NVIC->IP[4] = (NVIC->IP[4]&0x00FFFFFF) | 0x20000000;
    NVIC->ISER[0] = (1UL << 19); //pag 147
    // numero de interrupcion TIMER0A = 19 
    // n=19 ----> [4n+3] [4n+2] [4n+1] [4n] ---> [4n+3]
    TIMER0->CTL = (1<<0);

}

extern void Timer0(void)
{
  TIMER0->ICR = 1<<0;// acknowledge TIMER0A timeout
  (*PeriodicTask)();           
}