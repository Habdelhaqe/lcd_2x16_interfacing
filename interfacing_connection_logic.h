/* 
 * File:   interfacing_connection_logic.h
 * Author: Engs
 *
 * Created on 28 November 2021, 18:54
 */

#ifndef INTERFACING_CONNECTION_LOGIC_H

    #define	INTERFACING_CONNECTION_LOGIC_H
    
    #define ON  1
    #define OFF 0
    
    #define BTN0 PIN0 //portB pin:0 IN
    #define BTN1 PIN6 //portD pin:6 IN
    #define BTN2 PIN2 //portD pin:2 IN

    #define LED0 PIN2 //portC pin:2 OUT ON/OFF
    #define LED1 PIN7 //portC pin:7 OUT ON/OFF
    #define LED2 PIN3 //portD pin:2 OUT ON/OFF

    #define BUZZER PIN3 //portA pin:3 OUT
    #define RELLAY PIN2 //portA pin:2 OUT

    /*
     * LCD 16*2 URLs:
     * https://www.elprocus.com/lcd-16x2-pin-configuration-and-its-working/
     * https://www.watelectronics.com/lcd-16x2/
     * https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram
     * 
     */

    /* configure/control which type of data 
     * (weather a data to display : o/p HIGH on that pin OR 
     *          a command to signal the internal microcontroller of LCD to do 
     *          some work: o/p LOW on that pin) 
     * is available on Data lines of LCD
     * LCD_RS : -data register access O/P HIGH signaling LCD To Treat coming 
     *           data as data to display (DATA Holder)    
     *          -command register access O/P LOW signaling LCD To Treat coming 
     *           data as command to control LCD Microcontroller (COMMAND Holder)
     */
    #define LCD_RS PIN1 //portB pin:1 OUT 
    
    /*
     * LCD_RW : read from LCD O/P HIGH signaling LCD microcontroller to make 
     *          data available on data lines for reading
     *        : write to LCD O/P LOW signaling LCD microcontroller to receive 
     *          data available on data lines(weather it's data/command)
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
    /*
     * initialize/configure/program the LED Connected Port pin to be o/p
     * for write/output control signal
     * fun argument : u8 which_led to do work for
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    FUN_RETURN_STATUS initLED(u8 /*which LED*/);
 
    /*
     * initialize/configure/program the BTN Connected Port pin to be i/p
     * for read/scan control signal
     * fun argument : u8 which_BTN to do work for
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    FUN_RETURN_STATUS initBTN(u8 /*which BTN*/);

    /*
     * initialize/configure/program the BUZZER Connected Port pin to be o/p
     * for write/output control signal
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    FUN_RETURN_STATUS initBuzzer(void);
    
    /*
     * initialize/configure/program the Relay Connected Port pin to be o/p
     * for write/output control signal
     * fun return : FUN_RETURN_STATUS to check for function return status
     */    
    FUN_RETURN_STATUS initRelay(void);

    /*
     * initialize/configure/program the All LEDs Connected Port pin to be o/p
     * for write/output control signal for all LEDs
     * fun return : FUN_RETURN_STATUS to check for function return status
     */        
    FUN_RETURN_STATUS initLEDS(void);

    /*
     * initialize/configure/program the All BTNs Connected Port pin to be i/p
     * for read/scan control signal from all BTNs
     * fun return : FUN_RETURN_STATUS to check for function return status
     */    
    FUN_RETURN_STATUS initBTNS(void);
    
    //business logic signals
    
    /*
     * signal LED to be turned ON/OFF via o/p a control signal on the 
     * connected port pin HIGH : TURN ON / lOW : TURN OFF
     * fun argument : which LED select LED to control
     *                control signal to TURN LED ON(HIGH)/OFF(LOW)
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    FUN_RETURN_STATUS signalLEDOnOff(u8 /*which LED*/,u8 /*turn on off*/);
    
    /*
     * scan signal From BTN to be turned HIGH/LOW via i/p on control signal 
     * on the connected port pin HIGH : BTN Pushed / lOW : BTN Not Pushed
     * fun argument : which BTN select BTN to scan control signal from
     * fun return : scan_fun_return to check for function return status along
     *              with scanned control signal
     */
    scan_fun_return scanSignalFromBTN(u8 /*which button*/);
    
    /*
     * check weather LED is turned ON/OFF via Checking the o/p control signal
     * on the LED connected port pin weather it's HIGH/LOW
     * fun return : scan_fun_return to check for function return status along
     *              with scanned control signal status
     */
    scan_fun_return chekLEDOnOFF(u8 /*which LED*/);
    
#endif	/* INTERFACING_CONNECTION_LOGIC_H */
