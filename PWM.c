#include "lib/include.h"

extern void Configura_Reg_PWM0(uint16_t freq)
{
    /*Experimento 1 
    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo PWM0 pag 354
    SYSCTL->RCGCGPIO |= (1<<5); //Enable reloj de GPIO Puerto F pag 340 pin 5
    SYSCTL -> RCC &= ~(1<<20); // Enable PWM Clock Divisor pag 254 
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); // Control de registros ya sea por GPIO o Otros Pag 672
    GPIOF_AHB->AFSEL |= 0x0E;
    GPIOF_AHB->PCTL |= (GPIOF_AHB->PCTL&0xFFFF000F) | 0x00006660; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOF_AHB->DEN |= (1<<3)|(1<<2)|(1<<1);  para decirle si es digital o no Pag 682
    PWM0->_1_CTL = (0<<0); //Bloqueo y desbloqueo pagina 1266     
    PWM0->_1_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282
    PWM0->_1_LOAD = (int)(50000000/freq); /cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)
    PWM0->_1_CMPB = 15000;
    PWM0->_1_CMPA = 15000;
    PWM0->_1_CTL = (1<<0);// Se activa el generador 1
    PWM0->ENABLE = (1<<3) | (1<<2) ; // habilitar el bloque pa que pase Pag 1247
    */

   /*Experimento 2
    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo PWM0 pag 354
    SYSCTL->RCGCGPIO |= (1<<5); //Enable reloj de GPIO Puerto F pag 340 pin 5
    SYSCTL -> RCC &= ~(1<<20); // Enable PWM Clock Divisor pag 254 
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); // Control de registros ya sea por GPIO o Otros Pag 672
    GPIOF_AHB->AFSEL |= 0x0E;
    GPIOF_AHB->PCTL |= (GPIOF_AHB->PCTL&0xFFFF000F) | 0x00006660; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOF_AHB->DEN |= (1<<3)|(1<<2)|(1<<1);  para decirle si es digital o no Pag 682
    PWM0->_0_CTL = (0<<0); //Bloqueo y desbloqueo pagina 1266
    PWM0->_1_CTL = (0<<0);
    PWM0->_2_CTL = (0<<0);
    PWM0->_0_GENB = 0x0000080C;
    PWM0->_0_GENA = 0x0000008C;
    PWM0->_1_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282
    PWM0->_2_GENB = 0x0000080C; 
    PWM0->_2_GENA = 0x0000008C;
    PWM0->_0_LOAD = (int)(20000000/freq); /cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)
    PWM0->_1_LOAD = (int)(20000000/freq);
    PWM0->_2_LOAD = (int)(20000000/freq);
    PWM0->_0_CMPB = 15000;   //BUSCAR QUE ES NO ME ACUERDO 
    PWM0->_0_CMPA = 15000;
    PWM0->_1_CMPB = 15000; 
    PWM0->_1_CMPA = 15000; 
    PWM0->_2_CMPB = 15000; 
    PWM0->_2_CMPA = 15000; 
    PWM0->_0_CTL = (1<<0);// Se activa el generador 0
    PWM0->_1_CTL = (1<<0);// Se activa el generador 1
    PWM0->_2_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0); // habilitar el bloque pa que pase Pag 1247
   */

    /*EXPERIMENTO 3 
    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo PWM0 pag 354
    SYSCTL->RCGCGPIO |= (1<<5); //Enable reloj de GPIO Puerto F pag 340 pin 5
    SYSCTL -> RCC &= ~(1<<20); // Enable PWM Clock Divisor pag 254 
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); // Control de registros ya sea por GPIO o Otros Pag 672
    GPIOF_AHB->AFSEL |= 0x0E;
    GPIOF_AHB->PCTL |= (GPIOF_AHB->PCTL&0xFFFF000F) | 0x00006660; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOF_AHB->DEN |= (1<<3)|(1<<2)|(1<<1);  para decirle si es digital o no Pag 682
    PWM0->_0_CTL = (0<<0); //Bloqueo y desbloqueo pagina 1266
    PWM0->_1_CTL = (0<<0);
    PWM0->_2_CTL = (0<<0);
    PWM0->_0_GENB = 0x0000080C;
    PWM0->_0_GENA = 0x0000008C;
    PWM0->_1_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282
    PWM0->_2_GENB = 0x0000080C; 
    PWM0->_2_GENA = 0x0000008C;
    PWM0->_0_LOAD = (int)(20000000/freq); /cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)
    PWM0->_1_LOAD = (int)(20000000/freq);
    PWM0->_2_LOAD = (int)(20000000/freq);
    PWM0->_0_CMPB = 15000;   //BUSCAR QUE ES NO ME ACUERDO 
    PWM0->_0_CMPA = 15000;
    PWM0->_1_CMPB = 15000; 
    PWM0->_1_CMPA = 15000; 
    PWM0->_2_CMPB = 15000; 
    PWM0->_2_CMPA = 15000; 
    PWM0->_0_CTL = (1<<0);// Se activa el generador 0
    PWM0->_1_CTL = (1<<0);// Se activa el generador 1
    PWM0->_2_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0); // habilitar el bloque pa que pase Pag 1247
    */


}
