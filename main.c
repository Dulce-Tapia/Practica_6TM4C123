#include "lib/include.h"

    uint16_t Result[2];
    uint16_t Result1[2];
    uint16_t bin[1024];
    uint16_t m;
    int i; 

void Hilo_1(void)
{
    GPIOB_AHB->DATA = (1<<0);
    ADC0_In(Result);
    GPIOB_AHB->DATA = (0<<0);

    GPIOB_AHB->DATA = (1<<0);
    ADC1_In(Result1);
    GPIOB_AHB->DATA = (0<<0);
} 


int main(void)
{

    Configurar_PLL(_20MHZ); //Experimento 1
    Configurar_UART3();
    Configurar_GPIO();
    Configura_Reg_PWM0(10000); //Configuro a 10kHz el pwm Experimento 1
    Configurar_Timer0A(&Hilo_1,1000);

    while(1)
    { 
      /*FALTA CONVERTIR A VALOR BINARIO*/ 
    }
}
