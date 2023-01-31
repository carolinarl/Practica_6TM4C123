#include "lib/include.h"

extern void Configurar_UART0(void)
{
    SYSCTL->RCGCUART  = (1<<5);   // Habilitación UART (RCGCUART)
    SYSCTL->RCGCGPIO |= (1<<4);     // Habilitación Puerto A
    //(GPIOAFSEL) pag.671 Enable alternate function
    
    GPIOE->AFSEL |= (1<<5) | (1<<4);
    GPIOE->DIR |= (1<<5) | (0<<4);
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOE->PCTL |= (GPIOE->PCTL&0xFF00FFFF) | 0x00110000;  // (1<<0) | (1<<4);//0x00000011
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOE->DEN |= (1<<5) | (1<<4);//PA1 PA0
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART0->CTL |= (0<<9) | (0<<8) | (0<<0);


    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 25,000,000/ (16 * 28800) =  54.25347222
    UARTFBRD[DIVFRAC] = integer(0.25347222 * 64 + 0.5) = 16.72222
    */
    UART0->IBRD = 54;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART0->FBRD = 16;
    //  UART Line Control (UARTLCRH) pag.916
    UART0->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART0->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART0->CTL = (1<<0) | (1<<8) | (1<<9);



}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART0 ->FR & (1<<4)) != 0 );
    v = UART0 ->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART0->FR & (1<<5)) != 0 );
    UART0->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern void readString(char UART0_String[], char delimitador)
{

   int i=0;
   char string [20]; //= (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       (UART0_String[i]) = c;
       i++;

       c = readChar();
   }

     UART0_String[i]= '\0';

}
