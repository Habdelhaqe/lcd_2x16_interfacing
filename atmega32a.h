/* 
 * File:   atmega32a.h
 * Author: ENG AHMED
 *
 * Created on November 28, 2021, 10:20 AM
 */
#include<avr/io.h>
#include"common_types_defs.h"

#ifndef ATMEGA32A_H
    #define	ATMEGA32A_H

    //8PINS MAPING
    #define PIN0 0
    #define PIN1 1
    #define PIN2 2
    #define PIN3 3
    #define PIN4 4
    #define PIN5 5
    #define PIN6 6
    #define PIN7 7
    

    //Renaming the DDRx Registers
    /*
     * gives compilation error :case label 
     * does not reduce to an integer constant
     */
//    #define IOA DDRA
//    #define IOB DDRB 
//    #define IOC DDRC
//    #define IOD DDRC

    #define IOA 0
    #define IOB 1
    #define IOC 2
    #define IOD 3

    //renaming the PORTx registers
    #define OUTA 0
    #define OUTB 1
    #define OUTC 2
    #define OUTD 3

    //renaming the PINx registers
    #define INA 0
    #define INB 1
    #define INC 2
    #define IND 3
    
    //port pins layout
    //PORTA
    #define _PA_PIN0 0
    #define _PA_PIN1 1
    #define _PA_PIN2 2
    #define _PA_PIN3 3
    #define _PA_PIN4 4
    #define _PA_PIN5 5
    #define _PA_PIN6 6
    #define _PA_PIN7 7
    //PORTB
    #define _PB_PIN0 8
    #define _PB_PIN1 9
    #define _PB_PIN2 10
    #define _PB_PIN3 11
    #define _PB_PIN4 12
    #define _PB_PIN5 13
    #define _PB_PIN6 14
    #define _PB_PIN7 15
    //PORTC
    #define _PC_PIN0 16
    #define _PC_PIN1 17
    #define _PC_PIN2 18
    #define _PC_PIN3 19
    #define _PC_PIN4 20
    #define _PC_PIN5 21
    #define _PC_PIN6 22
    #define _PC_PIN7 23
    //PORTD
    #define _PD_PIN0 24
    #define _PD_PIN1 25
    #define _PD_PIN2 26
    #define _PD_PIN3 27
    #define _PD_PIN4 28
    #define _PD_PIN5 29
    #define _PD_PIN6 30
    #define _PD_PIN7 31
    
    #define UN_IDENTIFIED 0xFF

    #define ALL_PINS_CONFIG_OUT 0xFF
    #define ALL_PINS_CONFIG_IN  0x00
    
    #define OUT_ALL_PINS_HIGH  0xFF
    #define OUT_ALL_PINS_LOW   0x00

    #define OUT_HIGH_ON_PIN(PORT , PIN)     SET_BIT(PORT , PIN)
    #define OUT_LOW_ON_PIN(PORT , PIN)      CLEAR_BIT(PORT , PIN)
    #define SCAN_SIGANL_ON_PIN(PORT , PIN)  GET_BIT(PORT , PIN)

    typedef enum FUN_RETURN_STATUS{
        NO_ERRORS,
        ERR_WRONG_PORT_NUMBER,
        ERR_WRONG_PIN_NUMBER,
        ERR        
    }FUN_RETURN_STATUS;
        
    
    typedef struct scan_fun_return{
        FUN_RETURN_STATUS fun_return;
        u8 scanned_data;
    }scan_fun_return;
    

    /*
     * program/configure the port to be used
     * as Input:Reader control signal_in : LOW
     * as Output:Writer control signal_out : HIGH 
     * fun arguments : -port number to select which port to program/configure
     *                 -port control signal to program/configure selected port
     *                  to be : o/p passing HIGH
     *                          i/p passing LOW
     * caller of fun should check for the return
     *  success = > NO_ERRORS is returned
     *  error   = > ERR_WRONG_PORT_NUMBER is returned
     */
    FUN_RETURN_STATUS setPortInOut(u8 /*port number*/ , 
                                   u8 /*port configuration in LOW or out HIG*/);
   
    /*
     * program/configure the port pin to be used
     * as Input:Reader control signal_in : LOW
     * as Output:Writer control signal_out : HIGH 
     * fun arguments : -port number to select which port to program/configure
     *                 -pin number to select which pin on the selected port 
     *                  to program/configure
     *                 -port control signal to program/configure selected port
     *                  pin to be : o/p passing HIGH
     *                              i/p passing LOW
     * caller of fun should check for the return
     *  success = > NO_ERRORS is returned
     *  error   = > ERR_WRONG_PORT_NUMBER 
     *              ERR_WRONG_PIN_NUMBER
     *              is returned
     */
    FUN_RETURN_STATUS setPortPinInOut(u8 /*port number*/ , 
                         u8 /*pin number*/ ,
                         u8 /*port configuration in LOW or out HIG*/);

    /*
     * program/configure the port pin to be used
     * as Input:Reader control signal_in : LOW
     * as Output:Writer control signal_out : HIGH 
     * fun arguments : -port & pin number to select which pin on the selected 
     *                  port to program/configure
     *                 -port control signal to program/configure selected port
     *                  pin to be : o/p passing HIGH
     *                              i/p passing LOW
     * caller of fun should check for the return
     *  success = > NO_ERRORS is returned
     *  error   = > ERR_WRONG_PORT_NUMBER 
     *              ERR_WRONG_PIN_NUMBER
     *              is returned
     */
    FUN_RETURN_STATUS programPortPinInOut(u8 /*port_pin_number*/ ,
                         u8 /*port configuration in LOW or out HIG*/);    
    
    /*
     * output selected control signal status on selected port
     * fun arguments : -port number to select which port to output control
     *                  signal through
     *                 -port control signal status to be weather HIGH/LOW
     * caller of fun should check for the return
     *  success = > NO_ERRORS is returned
     *  error   = > ERR_WRONG_PORT_NUMBER is returned
     */
    FUN_RETURN_STATUS outControlSignalThroughPort(u8 /*port number*/ , 
                         u8 /*control signal status*/);
    
    /*
     * output selected control signal status on selected port pin
     * fun arguments : -port number to select which port to output control
     *                  signal through
     *                 -pin number to select which pin on the selected port to
     *                  output control signal through 
     *                 -port control signal status to be weather HIGH/LOW
     * caller of fun should check for the return
     *  success = > NO_ERRORS is returned
     *  error   = > ERR_WRONG_PORT_NUMBER is returned
     */
    FUN_RETURN_STATUS outControlSignalThroughPortPin(u8 /*port number*/ , 
                                        u8 /*pin number*/ , 
                                        u8 /*control signal status*/);

    /*
     * output selected control signal status on selected port pin
     * fun arguments : -port & pin number to select which pin on the selected 
     *                  port to output control signal through 
     *                 -port control signal status to be weather HIGH/LOW
     * caller of fun should check for the return
     *  success = > NO_ERRORS is returned
     *  error   = > ERR_WRONG_PORT_NUMBER is returned
     */
    FUN_RETURN_STATUS writeControlSignalOnPortPin(u8 /*port_pin_number*/ , 
                                        u8 /*control signal status*/);
    
    /*
     * input/scan/read selected control signal status on selected port
     * fun arguments : -port number to select which port the passed control 
     *                  signal will be available on
     * fun return is the scanned control signal status passing through
     * the selected port
     * caller of fun should check for the return structure "scan_fun_return"
     * member : fun_return to decide if to discard the data scanned or to
     * use it 
     *  success = > NO_ERRORS is returned go a head with scanned data
     *  error   = > ERR_WRONG_PORT_NUMBER is returned user should discard
     *              scanned data
     */
    scan_fun_return scanControlSignalThroughPort(u8 /*port number*/ );
    
    /*
     * input/scan/read selected control signal status on selected port pin
     * fun arguments : -port number to select which port the passed control 
     *                  signal will be available on
     *                 -pin number to select which port pin the passed control 
     *                  signal will be available on
     * fun return is the scanned control signal status passing through
     * the selected port
     * caller of fun should check for the return structure "scan_fun_return"
     * member : fun_return to decide if to discard the data scanned or to
     * use it 
     *  success = > NO_ERRORS is returned go a head with scanned data
     *  error   = > ERR_WRONG_PORT_NUMBER is returned user should discard
     *              scanned data
     */
    scan_fun_return scanControlSignalThroughPortPin(u8 /*port number*/ , u8 /*pin number*/);

    /*
     * input/scan/read selected control signal status on selected port pin
     * fun arguments : -PORT & pin number to select which port pin the passed control 
     *                  signal will be available on
     * fun return is the scanned control signal status passing through
     * the selected port
     * caller of fun should check for the return structure "scan_fun_return"
     * member : fun_return to decide if to discard the data scanned or to
     * use it 
     *  success = > NO_ERRORS is returned go a head with scanned data
     *  error   = > ERR_WRONG_PORT_NUMBER is returned user should discard
     *              scanned data
     */
    scan_fun_return scanControlPassingThroughPortPin(u8 /*port_pin_number*/);
    
#endif	/* ATMEGA32A_H */
