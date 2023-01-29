#include "lib/include.h"

extern void Configura_Reg_PWM0(uint16_t freq)
{ 
    //Habilitar el reloj de modulo PWM0 pag 354
    SYSCTL->RCGCPWM |= (1<<0);
    //Habilitar el reloj de GPIO Puerto B pag 340 
    SYSCTL->RCGCGPIO |= (1<<1);
    //Habilitar el divisor del reloj PWM pag 254 Nota *No es necesario                                                                  
    SYSCTL->RCC &= ~(1<<20); 
    //Habilitar función alternativa  Control de registros ya sea por GPIO o Otros Pag 672
    GPIOB->AFSEL |= (1<<4);
    // Salida de PWM 
    GPIOB->DIR = (1<<4); 
    //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    // 4 indica que es PWM 
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00040000; 
    // para decirle si es digital o no Pag 682
    GPIOB->DEN |= (1<<4); 
    //Bloqueo y desbloqueo pag 1266, pag 1233 generadores de PWM 
    PWM0->_1_CTL = (0<<0); 
    //Pag 1248  PWM3 trabaja con comparador A 
    PWM0->_1_GENA = 0x0000008C; 
    //cuentas=fclk/fpwm  para 1khz cuentas = (50,000,000/10000)
    PWM0->_1_LOAD = 5000;  
    PWM0->_1_CMPA = 1500; //Ciclo de trabajo Nota *Regla de 3
    // Se activa el generador 1
    PWM0->_1_CTL = (1<<0);
    //Se habilita el PWM2 pag. 1247 y 1233
    PWM0->ENABLE = (1<<2); 
}
