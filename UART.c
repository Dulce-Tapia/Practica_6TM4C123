#include "lib/include.h"

extern void Configurar_UART3(void)
{
    SYSCTL->RCGCUART  = (1<<3);   //Paso 1 (RCGCUART) pag.344 UART/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<2);     //Paso 2 (RCGCGPIO) pag.340 Enable clock port A
    //(GPIOAFSEL) pag.671 Enable alternate function
    GPIOC->AFSEL = (1<<6) | (1<<7);
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOC->PCTL = (GPIOC->PCTL&0x11FFFFFF) | 0x11000000;// (1<<0) | (1<<4);//0x00000011
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOC->DEN = (1<<6) | (1<<7);//PA1 PA0
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART3->CTL = (0<<9) | (0<<8) | (0<<0);

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 33,000,000 / (16*19200) = 107.421875
    UARTFBRD[DIVFRAC] = integer(.421875 * 64 + 0.5) = 27.5 
    */
    UART3->IBRD = 107;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART3->FBRD = 27;
    //  UART Line Control (UARTLCRH) pag.916
    UART3->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART3->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART3->CTL = (1<<0) | (1<<8) | (1<<9);



}

extern void UART3_Transmitter(unsigned char Result,unsigned char Result1)  
{
    while((UART3->FR & (1<<5)) != 0 );
    UART3->DR =Result;
    UART3->DR =Result1;
}


extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART3->FR & (1<<4)) != 0 );
    v = UART3->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART3->FR & (1<<5)) != 0 );
    UART3->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern char * readString(char delimitador)
{
  char letra; 
  static char Nombre[30];
  int cont = 0; 
  letra = readChar();
  while( letra != delimitador) 
  {
    Nombre[cont] = letra;
    letra = readChar();
    cont++;
  }
  return &Nombre[0];
}