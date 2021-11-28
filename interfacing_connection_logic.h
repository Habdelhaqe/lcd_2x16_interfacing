/* 
 * File:   interfacing_connection_logic.h
 * Author: Engs
 *
 * Created on 28 November 2021, 18:54
 */

#ifndef INTERFACING_CONNECTION_LOGIC_H

#include "atmega32a.h"

    #define	INTERFACING_CONNECTION_LOGIC_H
    
    #define ON  1
    #define OFF 0
    
    #define BTTN0 PIN0 //portB pin:0 IN
    #define BTTN1 PIN6 //portD pin:6 IN
    #define BTTN2 PIN2 //portD pin:2 IN

    #define LED0 PIN2 //portC pin:2 OUT ON/OFF
    #define LED1 PIN7 //portC pin:7 OUT ON/OFF
    #define LED2 PIN3 //portD pin:2 OUT ON/OFF

    #define BUZZER PIN3 //portA pin:3 OUT
    #define RELLAY PIN2 //portA pin:2 OUT
    
    /*
     * LCD_RS : data register access O/P LOW signalling LCD To Treat coming 
     *      data as data to display (DATA Holder)    
     *        : command register access O/P HIGH signalling LCD To Treat coming 
     *      data as command to control LCD Microcontroller (COMMAND Holder)
     */
    #define LCD_RS PIN1 //portB pin:1 OUT 
    
    /*
     * LCD_RW : read from LCD O/P LOW signalling LCD To Send Data Back  
     *        : write  to LCD O/P HIGH signalling LCD To Receive Data available
     *          on DATA Lines  
     */
    #define LCD_RW PIN2 //portB pin:2 OUT

    /*
     * LCD_EN : o/p a pulse LOW__|-HIGH<delayed>-|__LOW 
     *      to signal to LCD to start accepting data/command
     *      placed on the DATA lines      
     */
    #define LCD_EN PIN3 //portB pin:3 OUT
    
    
    //that's what connected on the Kit (4-bit LCD Mode nibble)
    #define LCD_D4 PIN4 //PortA pin:4 OUT/IN
    #define LCD_D5 PIN5 //PortA pin:5 OUT/IN
    #define LCD_D6 PIN6 //PortA pin:6 OUT/IN
    #define LCD_D7 PIN7 //PortA pin:7 OUT/IN
    
    //only use those will testing the LCD (8-bit Mode)
    #define LCD_D0 PIN0 //PortA pin:0 OUT/IN
    #define LCD_D1 PIN1 //PortA pin:1 OUT/IN
    #define LCD_D2 PIN2 //PortA pin:2 OUT/IN
    #define LCD_D3 PIN3 //PortA pin:3 OUT/IN
    
    //initiate all interfacing port pins 
    FUN_RETURN_STATUS initLED(u8 /*which LED*/);
    FUN_RETURN_STATUS initBNT(u8 /*which BTN*/);
    FUN_RETURN_STATUS initBuzzer(void);
    FUN_RETURN_STATUS initRellay(void);
    
    //control logic signals
    FUN_RETURN_STATUS signalLEDOnOff(u8 /*which LED*/,u8 /*turn on off*/);
    scan_fun_return scanSignalFromBTN(u8 /*which button*/);
    
#endif	/* INTERFACING_CONNECTION_LOGIC_H */
