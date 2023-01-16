/* Configuración del módulo ADC */
#include "lib/include.h"

extern void Conguracion_ADC0(void)
{
   // 1. Inicializar el módulo 0 del reloj del ADC RCGCADC 
    SYSCTL-> RCGCADC =(1<<0);
    // 2. Habilitando el puerto E y D en base del reloj 
    SYSCTL -> RCGCGPIO |= (0<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(0<<0);
    // 3. Habilitar los pines como I/O 
    GPIOE_AHB-> DIR = (0<<1); // PE1 - Canal 2  
    GPIOD_AHB-> DIR = (0<<3)|(0<<1); //PD3 - Canal 4, PD1 - Canal 6
    // 4. Habilitar la función alternativa 
    GPIOE_AHB -> AFSEL = (1<<1);
    GPIOD_AHB -> AFSEL = (1<<3)|(1<<1);
    // 5. Deshabilitación del modo digital 
    GPIOE_AHB -> DEN =  (1<<1);
    GPIOD_AHB -> DEN = (1<<3)|(1<<1);
    // 6. GPIOCTL registro combinado con el GPIOAFSEL 
    GPIOE_AHB -> PCTL = GPIOE_AHB -> PCTL & (0xFF00FFFF);
    GPIOD_AHB -> PCTL = GPIOD_AHB -> PCTL & (0xFF00FFFF);
    // 7. Habilitar lo analogico 
    GPIOE_AHB -> AMSEL =  (1<<1);
    GPIOD_AHB -> AMSEL = (1<<3)|(1<<1);
    // 8. Velocidad de conversión 1 millon de muestras por segundo pág. 891 
    ADC0->PC = (1<<6)|(0<<5)|(1<<4)|(0<<3)|(1<<2)|(0<<1)|(1<<0); //1 Msps
    // 9. Prioridad de los secuenciadores CHECHAR SI ESTA BIEN 
                    // 3 2 1 0
    ADC0->SSPRI = 0x0231;
    // 10. Control de la activacion de los secuenciadores sec 3, sec 0, sec 2
    ADC0 ->ACTSS = (0<<1)|(0<<2)|(0<<0)|(0<<3);
    // 11. Selección del evento que activa la conversión trigger 
    ADC0->EMUX = (0x4); //GPIO Externo BOTONES en el puerto D
    /*AGREGAR (GPIOADCCTL) Como colocar esa cosa*/ 
    // 12. Define las entradas analógicas con el canal y secuenciador seleccionado 
    ADC0 ->SSMUX2 = 0x0089; // BUSCAR COLOQUE EL MISMO 
    // 13. Configurar el bit de control de muestreo y la interrupción 
    ADC0 -> SSCTL2 = (1<<6) | (1<<5); //BUSCAR COLOQUE LOS MISMOS
    // 14. ADC Interrupciones 
    ADC0 -> IM |= (1<<3); 
    ADC0 -> IM |= (1<<0); 
    ADC0 -> IM |= (1<<2); 
    // 10. Control de la activacion de los secuenciadores sec 3, sec 0, sec 2
    ADC0 ->ACTSS = (0<<1)|(1<<2)|(1<<0)|(1<<3);
    ADC0 ->PSSI =  (1<<2)|(1<<0)|(1<<3);
}

extern void Configuracion_ADC1(void)
{
    // 1. Inicializar el módulo 0 del reloj del ADC RCGCADC 
    SYSCTL-> RCGCADC =(1<<1);
    // 2. Habilitando el puerto E,D y B en base del reloj 
    SYSCTL -> RCGCGPIO |= (0<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(0<<0);
    // 3. Habilitar los pines como I/O 
    GPIOD_AHB-> DIR = (0<<0); //PD0 - Canal 7
    // 4. Habilitar la función alternativa 
    GPIOD_AHB -> AFSEL = (1<<0);
    // 5. Deshabilitación del modo digital 
    GPIOD_AHB -> DEN = (1<<0);
    // 6. GPIOCTL registro combinado con el GPIOAFSEL 
    GPIOD_AHB -> PCTL = GPIOE_AHB -> PCTL & (0xFF00FFFF);
    // 7. Habilitar lo analogico 
    GPIOD_AHB -> AMSEL = (1<<0);
    // 8. Velocidad de conversión 1 millon de muestras por segundo pág. 891 
    ADC1->PC = (1<<6)|(0<<5)|(1<<4)|(0<<3)|(1<<2)|(0<<1)|(1<<0); //1 Msps
    // 9. Prioridad de los secuenciadores CHECHAR SI ESTA BIEN 
                    // 3 2 1 0
    ADC1->SSPRI = 0x0231;
    // 10. Control de la activacion de los secuenciadores sec 3, sec 0, sec 2
    ADC1 ->ACTSS = (0<<1)|(0<<2)|(0<<0)|(0<<3);
    // 11. Selección del evento que activa la conversión trigger pág. 834
    ADC1->EMUX = (0x0); 
    // 12. Define las entradas analógicas con el canal y secuenciador seleccionado 
    ADC1 ->SSMUX2 = 0x0089; // BUSCAR COLOQUE EL MISMO 
    // 13. Configurar el bit de control de muestreo y la interrupción 
    ADC1 -> SSCTL2 = (1<<6) | (1<<5); //BUSCAR COLOQUE LOS MISMOS
    // 14. ADC Interrupciones 
    ADC1 -> IM |= (1<<3); 
    ADC1 -> IM |= (1<<0); 
    ADC1 -> IM |= (1<<2); 
    // 10. Control de la activacion de los secuenciadores sec 3, sec 0, sec 2
    ADC1 ->ACTSS = (0<<1)|(1<<2)|(1<<0)|(1<<3);
    ADC1 ->PSSI =  (1<<2)|(1<<0)|(1<<3);
}

extern void ADC0_In(uint16_t *Result)
{
    ADC0 -> PSSI = 0x00000004; 
    while ((ADC0->RIS&0x04)==0){}; //espera al convertidor 
    Result[1]= ADC0 ->SSFIFO2&0xFFF; 
    Result[0]= ADC0 ->SSFIFO2&0xFFF; 
    ADC0 ->ISC = 0x0004;
}

extern void ADC1_In(uint16_t *Result1)
{
    ADC1 -> PSSI = 0x00000004; 
    while ((ADC1->RIS&0x04)==0){}; //espera al convertidor 
    Result1[1]= ADC1 ->SSFIFO2&0xFFF; 
    Result1[0]= ADC1 ->SSFIFO2&0xFFF; 
    ADC1 ->ISC = 0x0004;
}