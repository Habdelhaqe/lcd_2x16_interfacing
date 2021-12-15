/* 
 * File:   interrupt_configuration.h
 * Author: Engs
 *
 * Created on 06 December 2021, 11:37
 */

#ifndef INTERRUPT_CONFIGURATION_H

#include "atmega32a.h"

    #define	INTERRUPT_CONFIGURATION_H
    
    #define INTERRUPT_RISING_EDGE_MODE            3 //0x03 : 0b 0000 0011
    #define INTERRUPT_FALLING_EDGE_MODE           2 //0x02 : 0b 0000 0010
    #define INTERRUPT_ANY_LOGICAL_CHANGE_MODE     1 //0x01 : 0b 0000 0001
    #define INTERRUPT_LOW_LEVEL_MODE              0 //0x00 : 0b 0000 0000

    #define INTERRUPT_INT1_SHIFT    2  //configuring ISC11(BIT3) ISC10(BIT2) 

/*
 * configuring the interrupt pin to enable/disable the pin
 * which program/configure the interrupt controller circuitry
 * that acts as a monitor or watch dog for interrupt signal coming through the
 * designated pin INT0 , INT1 , INT2 that will force the MicroController to
 * respond to the signal(which it's architecture or designed to do so) 
 * switching context to another routine(fun) which it's address in code
 * segment will be passed to the INTx_VECTOR address acting as a pointer for
 * that routine(fun). 
 * also the mode of interrupt signal also is passed to 
 * trigger the responds on:
 *  -rising edge  : INTERRUPT_RISING_EDGE_MODE
 *  -falling edge : INTERRUPT_FALLING_EDGE_MODE
 *  -any change   : INTERRUPT_ANY_LOGICSL_CHANGE_MODE 
 *  -low level    : INTERRUPT_LOW_LEVEL_MODE  
 * FUN_RETURN_STATUS returned holding the execution result reporting error if
 * encountered
 * 
 * ACTIONS TAKING
 * init Interrupt Service configuration through
 * accessing register MCUCR For handling INT0 & INT1 CONFIGURATIONS ON BITS
 * 
 * X : DON'T CARE
 * 
 * INT0 : BIT 1 -> ISC01 , BIT 0 -> ISC00
 *      INTERRUPT_RISING_EDGE_MODE : 0b XXXX XX11
 *      INTERRUPT_FALLING_EDGE_MODE : 0b XXXX XX10
 *      INTERRUPT_ANY_LOGICSL_CHANGE_MODE: 0b XXXX XXX1
 *      INTERRUPT_LOW_LEVEL_MODE : 0b XXXX XX00
 * 
 * INT1 : BIT 3 -> ISC11 , BIT 2 -> ISC10 (same as 
 *      INTO but values are shifted right by 2)
 *      INTERRUPT_RISING_EDGE_MODE : 0b XXXX 11XX
 *      INTERRUPT_FALLING_EDGE_MODE : 0b XXXX 10XX
 *      INTERRUPT_ANY_LOGICSL_CHANGE_MODE: 0b XXXX 01XX
 *      INTERRUPT_LOW_LEVEL_MODE : 0b XXXX 00XX
 * 
 * accessing register MCUCSR For handling INT2
 * INT2 : BIT 6 -> ISC2
 *      INTERRUPT_RISING_EDGE_MODE : 0b X1XX XXXX
 *      INTERRUPT_FALLING_EDGE_MODE : 0b X0XX XXXX
 *
 * ENABLE/DISBALE the interrupt service controller/monitor through register 
 * GICR -> HIGH : ENABLE , LOW : DISABLE
 *  
 * GICR :  BIT 7 -> INT1 , BIT 6(ISC2==6) -> INT0 , BIT 5 -> INT2
 *
 * ENABLE/DISABLE THE GLOBAL interrupt service controller/monitor through
 * SREG ON BIT 7 -> I FLAG/BIT done via abstraction macros 
 *          <avr.interrupt.h>SEI:sei() for ENABLE  INTERRUPT : I = HIGH
 *          <avr.interrupt.h>SEI:sei() for DISABLE INTERRUPT : I = LOW 
 *                  
 * FUN ARGUMENT : -select external interrupt number 
 *                -select which mode of interrupt
 *                        INTERRUPT_RISING_EDGE_MODE 
 *                        INTERRUPT_FALLING_EDGE_MODE 
 *                        INTERRUPT_ANY_LOGICSL_CHANGE_MODE
 *                        INTERRUPT_LOW_LEVEL_MODE
 * fun return : FUN_RETURN_STATUS to check for function return status
 */         
FUN_RETURN_STATUS initInterruptService(u8 /*which external interrupt pin*/ ,
                                        u8 /*mode of interrupt signal*/ );

#endif	/* INTERRUPT_CONFIGURATION_H */