/* 
 * File:   interfacing_connection_logic.h
 * Author: Engs
 *
 * Created on 28 November 2021, 18:54
 */

#ifndef INTERFACING_CONNECTION_LOGIC_H
    #define F_CPU 16000000UL // 16 Mhz clk

    #include "atmega32a.h"
    #include<util/delay.h>
    #include<stdlib.h>

    #define PULSE_DELAY 1 //10ms for 16 Mhz clk

    #define	INTERFACING_CONNECTION_LOGIC_H
    
    #define LOOP_ZER0_INITIALIZER 0
        
    #define DECIMAL_RADIX 10
    #define BUFFER_MAX_SIZE 11 //8 bytes: 10 digit number + 1 null char
    
    #define BIT0 0
    #define BIT1 1
    #define BIT2 2
    #define BIT3 3
    #define BIT4 4
    #define BIT5 5
    #define BIT6 6
    #define BIT7 7

    #define BTN_PRESSED   HIGH
    #define BTN_UNPRSSED  LOW

    #define BTN0 _PA_PIN7
    #define BTN1 _PB_PIN4
    #define BTN2 _PB_PIN5

    #define LED0 _PD_PIN2 
    #define LED1 _PD_PIN1
    #define LED2 _PD_PIN0

//    #define BUZZER PIN3 //portA pin:3 OUT
//    #define RELLAY PIN2 //portA pin:2 OUT

    #define BUZZER _PA_PIN3 //portA pin:3 OUT
    #define RELLAY _PA_PIN2 //portA pin:2 OUT

    /*
     * LCD 16*2 URLs:
     * https://www.elprocus.com/lcd-16x2-pin-configuration-and-its-working/
     * https://www.watelectronics.com/lcd-16x2/
     * https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram
     * http://www.firmcodes.com/microcontrollers/8051-3/interfacing-lcd-with-8051/lcd-commands-and-understanding-of-lcd/
     * https://circuitdigest.com/article/16x2-lcd-display-module-pinout-datasheet
     * https://mil.ufl.edu/3744/docs/lcdmanual/commands.html
     * https://www.electronicwings.com/8051/lcd16x2-interfacing-in-8-bit-with-8051
     * https://abcrob.com/lcd-interfacing-in-8-bit-mode/
     * https://www.vishay.com/docs/37484/lcd016n002bcfhet.pdf
     * http://web.alfredstate.edu/faculty/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
     * https://www.electronicwings.com/avr-atmega/interfacing-lcd-16x2-in-4-bit-mode-with-atmega-16-32-#:~:text=LCD%2016x2%20can%20be%20used,required%20data%20in%20data%20mode.
     * https://asset.conrad.com/media10/add/160267/c1/-/en/001070528ML02/manual-1070528-joy-it-rb-lcd-16x2-module-56-cm-222-inch-16-x-2-p-compatible-with-raspberry-pi.pdf
     * https://atmega32-avr.com/interface-lcd-4-bit-mode-avr-microcontroller/
     * https://exploreembedded.com/wiki/Interfacing_LCD_in_4-bit_mode_with_8051
     * https://www.bipom.com/documents/appnotes/LCD%20Interfacing%20using%20HD44780%20Hitachi%20chipset%20compatible%20LCD.pdf
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
    //#define LCD_RS PIN1 //portB pin:1 OUT 
    #define LCD_RS _PB_PIN2
    
    /*
     * LCD_RW : read from LCD O/P HIGH signaling LCD microcontroller to make 
     *          data available on data bus lines for reading
     *        : write to LCD O/P LOW signaling LCD microcontroller to receive 
     *          data available on data bus lines(weather it's data/command)
     */
    //#define LCD_RW PIN2 //portB pin:2 OUT
    #define LCD_RW _PB_PIN1

    /*
     * LCD_EN : o/p a pulse LOW__|-HIGH<delayed>-|__LOW 
     *      to signal to LCD to start accepting data/command
     *      placed on the DATA lines      
     */
    //#define LCD_EN PIN3 //portB pin:3 OUT
    #define LCD_EN _PB_PIN3
    
//    //that's what connected on the Kit (4-bit LCD Mode nibble)
//    #define LCD_D4 PIN4 //PortA pin:4 OUT/IN
//    #define LCD_D5 PIN5 //PortA pin:5 OUT/IN
//    #define LCD_D6 PIN6 //PortA pin:6 OUT/IN
//    #define LCD_D7 PIN7 //PortA pin:7 OUT/IN
//    
//    //only use those will testing the LCD (8-bit Mode)
//    #define LCD_D0 PIN0 //PortA pin:0 OUT/IN
//    #define LCD_D1 PIN1 //PortA pin:1 OUT/IN
//    #define LCD_D2 PIN2 //PortA pin:2 OUT/IN
//    #define LCD_D3 PIN3 //PortA pin:3 OUT/IN

    #define LCD_D4 _PD_PIN4 
    #define LCD_D5 _PD_PIN5
    #define LCD_D6 _PD_PIN6 
    #define LCD_D7 _PD_PIN7 
    #define LCD_D0 _PD_PIN0 
    #define LCD_D1 _PD_PIN1 
    #define LCD_D2 _PD_PIN2 
    #define LCD_D3 _PD_PIN3 
    #define LCD_PORT OUTD
    
    //states for LCD_RS : configure REG accessing for passing a data/a command  
    #define CMD   LOW
    #define DATA  HIGH

    //states for LCD_RW : configure flow of data to(Write)/from(READ) LCD module
    #define WRITE LOW
    #define READ  HIGH
    
    //count starts from zero rows:0->1 , columns:0->15
    #define LCD_ROW_COUNT 1
    #define LCD_COLUMN_COUNT 16
    #define LCD_LAST_COLUMN_OFFSET 0xF
    #define LCD_START_POS   0

    //CMD for LCD control in Hex
    #define CLEAR_DISPLAY 0x01
    #define CUSROR_HOME 0x02 //make use when talking 4bit mode
//    #define CUSROR_HOME 0x03 //Same Function as 0x01
    #define _8BIT_1L_MODE 0x30
    #define _8BIT_2L_MODE 0x38
    #define _4BIT_1L_MODE 0x20
    #define _4BIT_2L_MODE 0x28
    #define _4BIT_MODE_INIT 0x2C
    #define DISPLAY_ON_CUSROR_ON 0x0F
    #define DISPLAY_ON_CUSROR_OFF 0x0C
    #define PLACE_CUR_AT_BEGINE_OF_FIRST_LINE 0x80
    #define PLACE_CUR_AT_LAST_OF_FIRST_LINE 0x8F
    #define PLACE_CUR_AT_BEGINE_OF_SECOND_LINE 0xC0
    #define PLACE_CUR_AT_LAST_OF_SECOND_LINE 0xCF
    #define SECOND_ROW_START_OFFSET 0x40
    #define INC_DISPLAY_SHIFT_TO_RIGHT 0x06
    #define FUNCTION_SET 0b00111100
    #define UNKNOWN_SHIT_CMD 0x33
    #define UNKNOWN_SHIT_CMD2 0x83
    
    #define LCD_OPERATION_MODE _4BIT_2L_MODE

    #define CLEAR_LCD commandLCD(CLEAR_DISPLAY)

    /*
     * initialize/configure/program the LED Connected Port pin to be o/p
     * for write/output control signal
     * fun argument : -\c which_led determine the pin attached to that led
     *                and port selected led/pin is attached to    
     * 
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    //FUN_RETURN_STATUS initLED(u8 /*which LED*/,u8 /*on which port*/);
    FUN_RETURN_STATUS initLED(u8 /*which LED*/);
 
    /*
     * initialize/configure/program the BTN Connected Port pin to be i/p
     * for read/scan control signal
     * fun argument : -which_BTN determine the pin attached to that BTN
     *                and port selected BTN/pin is attached to    
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    //FUN_RETURN_STATUS initBTN(u8 /*which BTN*/,u8 /*on which port*/);
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
     * the fun return not needed so the fun signature changed to 
     * /c     void initLEDS(void);
     */        
    //FUN_RETURN_STATUS initLEDS(void);
    void initLEDS(void);

    /*
     * initialize/configure/program the All BTNs Connected Port pin to be i/p
     * for read/scan control signal from all BTNs
     * fun return : FUN_RETURN_STATUS to check for function return status
     * the fun return not needed so the fun signature changed to 
     * /c     void initBTNS(void);
     */    
    //FUN_RETURN_STATUS initBTNS(void);
    void initBTNS(void);
    
    //business logic signals
    
    /*
     * signal LED to be turned ON/OFF via o/p a control signal on the 
     * connected port pin HIGH : TURN ON / lOW : TURN OFF
     * fun argument : which LED select LED to control
     *                control signal to TURN LED ON(HIGH)/OFF(LOW)
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    FUN_RETURN_STATUS turnLEDOnOff(u8 /*which LED*/,u8 /*turn on off*/);
    
    /*
     * scan signal From BTN to be turned HIGH/LOW via i/p on control signal 
     * on the connected port pin HIGH : BTN Pushed / lOW : BTN Not Pushed
     * fun argument : which BTN select BTN to scan control signal from
     * fun return : scan_fun_return to check for function return status along
     *              with scanned control signal
     */
    //scan_fun_return scanSignalFromBTN(u8 /*which button*/);
    scan_fun_return isBTNPressed(u8 /*which button*/);
    
    /*
     * check weather LED is turned ON/OFF via Checking the o/p control signal
     * on the LED connected port pin weather it's HIGH/LOW
     * fun return : scan_fun_return to check for function return status along
     *              with scanned control signal status
     */
    scan_fun_return isLEDOnOrOFF(u8 /*which LED*/);
    
    /*
     * LCD Configuration RS RW EN all are o/p pins from 
     * atmega32a microcontroller
     * fun return : FUN_RETURN_STATUS to check for function return status
     * the fun return not needed so the fun signature changed to 
     * \c     void configureLCDControlPins(void);
     */    
    //FUN_RETURN_STATUS configureLCDControlPins(void);
    void configureLCDControlPins(void);
    
    /*
     * configuration/programming LCD data bus lines on microcontroller
     * D7 through D0
     * fun return : FUN_RETURN_STATUS to check for function return status
     * the fun return not needed so the fun signature changed to 
     * \c     void configureLCDDataBusLines(void);
     */
    //FUN_RETURN_STATUS configureLCDDataBusLines(void);
    void configureLCDDataBusLines(void);
    
    /*
     * 0x30 : function set:8-bit ,1 Line,5x7 Dots
     * 0x38 : function set:8-bit ,2 Line,5x7 Dots
     * 0x20 : function set:4-bit ,1 Line,5x7 Dots
     * 0x28 : function set:4-bit ,2 Line,5x7 Dots
     * 
     * 
     * LCD Commands :-
     * ---------------
     *      CMD         RS  RW D7|6|6|4|3|2|1|0           Description
     * Clear display :  0   0   0|0|0|0|0|0|0|1     Clears display and returns 
     *                                              cursor to the home position 
     *                                              (address 0).
     *                                              Execution time:	1.64mS
     * 
     * Cursor home	 :  0	0	0|0|0|0|0|0|1|*     Returns cursor to home 
     *                                              position (address 0). 
     *                                              Also returns display being 
     *                                              shifted to the original 
     *                                              position. DDRAM contents 
     *                                              remains unchanged.	
     *                                              Execution time:	1.64mS
     * 
     * Display On	 : 0	0	0|0|0|0|1|D|C|B     Sets On/Off of all display (D)
     * /Off control                                 , cursor On/Off (C) 
     *                                              and blink of cursor 
     *                                              position character (B).
     *                                              Execution time:	40uS
     * 
     * Entry mode set: 0	0	0|0|0|0|0|1|I|S     Sets cursor move direction 
     *                                      D       (I/D), specifies to shift 
     *                                              the display (S). 
     *                                              These operations are 
     *                                              performed during data 
     *                                              read/write.
     *                                              Execution time:	40uS
     * 
     * Cursor/display: 0	0	0|0|0|1|S|R|*|*     Sets cursor-move 
     * shift                            C|L         or display-shift (S/C), 
     *                                              shift direction (R/L). 
     *                                              DDRAM contents remains 
     *                                              unchanged.
     *                                              Execution time:	40uS
     *
     * Function set  :0     0	0|0|1|DL|N|F|*|*	Sets interface data length 
     *                                              (DL), number of display 
     *                                              line (N) and character 
     *                                              font(F).
     *                                              Execution time:	40uS
     * 
     * 
     */
    
    /*
     * generate a pulse to trigger LCD MicroController to start communicating/
     * interfacing with it through data bus lines 
     */
    void generateLCDEnableControlPuls(void);
   
    /*
     * Clears display and returns cursor to the home position (address 0).
     * put 0x01 on data bus lines
     * put LOW to RS:command
     * put LOW to RW:write
     * fun return : FUN_RETURN_STATUS to check for function re-turn status
     */
//    FUN_RETURN_STATUS clearLCD(void);
    
    /*
     * Returns cursor to home position (address 0).
     * Also returns display being shifted to the original position
     * put 0x02/03 on data bus lines
     * put LOW to RS:command
     * put LOW to RW:write
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
//    FUN_RETURN_STATUS returnLCDCursorHome(void);
    
    /*
     * configure LCD to be in:
     * CMD  0x30 set 8-bit ,1 Line,5x7 Dots
     * CMD  0x38 set 8-bit ,2 Line,5x7 Dots
     * CMD  0x20 set 4-bit ,1 Line,5x7 Dots
     * CMD  0x28 set 4-bit ,2 Line,5x7 Dots
     */
//    FUN_RETURN_STATUS configureLCD8_4bitMode1_2Line(u8 /*8_bit_mode_4_bit_mode*/,
//                                            u8 /*2_lines_mode_1_line_mode*/);
    
    /*
     * Passing LCD command signals to LCD microcontroller for
     * controlling actions
     * configuration pin:
     *      -put LOW to RS:command
     *      -put LOW to RW:write
     * place CMD passed on data bus lines
     * call enable pulse generator to deliver pulse to signal the LCD 
     *  microcontroller to get CMD control signals
     * fun argument :- command to control LCD microcontroller
     * fun return : FUN_RETURN_STATUS to check for function return status
     * no need for function return 
     */
    //FUN_RETURN_STATUS commandLCD(u8 /*command to control LCD microcontroller*/);
    void commandLCD(u8 /*command to control LCD microcontroller*/);

    /*
     * Passing data(characters) to LCD microcontroller for displaying
     * configuration pin:
     *      -put HIGH to RS:data
     *      -put LOW  to RW:write
     * place data passed on data bus lines
     * call enable pulse generator to deliver pulse to signal the LCD 
     *  microcontroller to get CMD control signals
     * fun argument :- command to control LCD microcontroller
     * fun return : FUN_RETURN_STATUS to check for function return status
     * no need for function return 
     */
    //FUN_RETURN_STATUS displayCharacterOnLCD(u8 /*character data*/);
    void displayCharacterOnLCD(u8 /*character data*/);

    /*
     * there is no need for this function now as the problem was in the
     * PIN4 @ ALL PORTs in cases for checking selection of :
     *  _PA_PIN4 , _PB_PIN4 , _PC_PIN4 , _PD_PIN4 
     * \c FUN_RETURN_STATUS writeControlSignalOnPortPin(u8,u8)
     * wrapper function to test for case of shifting the character sent
     *  to be displayed adding 1 (0b : 0001)  to the upper nibble and aslo
     * to the lower nibble as i know that function : \c void commandLCD(u8)
     * is working correctly and i'm sure that both functions : 
     * \c void commandLCD(u8)
     * \c void displayCharacterOnLCD(u8)
     * had same Logic
     */
    FUN_RETURN_STATUS displayCharOrCommandLCD(u8 /*Data : char or command*/,
                                 u8/*treat Data passed as char or command*/);
    
    /*
     * same as : FUN_RETURN_STATUS displayCharacterOnLCD(u8 character)
     * it's called inside the code for display character
     * Passing data(string) to LCD microcontroller for displaying
     * configuration pin:
     *      -put HIGH to RS:data
     *      -put LOW  to RW:write
     * place data char by char passed on data bus lines
     * call enable pulse generator to deliver pulse to signal the LCD 
     *  microcontroller to get CMD control signals
     * fun argument :- command to control LCD microcontroller
     * fun return : FUN_RETURN_STATUS to check for function return status
     * no need for function return 
     */
    //FUN_RETURN_STATUS displayStringOnLCD(u8 */*pointer to string of chars*/);    
    void displayStringOnLCD(u8 */*pointer to string of chars*/);    
    
    /*
     * integer value is converted to char[n] via \c stdlib.iota() function
     * then passed to \c  FUN_RETURN_STATUS displayStringOnLCD(u8 *)
     * Passing data(integer) to LCD microcontroller for displaying
     * configuration pin:
     *      -put HIGH to RS:data
     *      -put LOW  to RW:write
     * place data char by char passed on data bus lines
     * call enable pulse generator to deliver pulse to signal the LCD 
     *  microcontroller to get CMD control signals
     * fun argument :- command to control LCD microcontroller
     * fun return : FUN_RETURN_STATUS to check for function return status
     * no need for function return 
     */
    //FUN_RETURN_STATUS displayINTOnLCD(int /*integer value to display*/);
    void displayINTOnLCD(int /*integer value to display*/);
    
    /*
     * initialize LCD
     * fun argument :- command to control LCD microcontroller mode:
     * CMD  0x30 set 8-bit ,1 Line,5x7 Dots
     * CMD  0x38 set 8-bit ,2 Line,5x7 Dots
     * CMD  0x20 set 4-bit ,1 Line,5x7 Dots
     * CMD  0x28 set 4-bit ,2 Line,5x7 Dots
     * not needed also using \c macro LCD_operation_mode which will hold
     * the mode value 
     * fun return : FUN_RETURN_STATUS to check for function return status
     * the fun return not needed so the fun signature changed to 
     * \c     void configureLCDDataBusLines(void);
     */
    //FUN_RETURN_STATUS initLCD(u8 /*LCD operation mode*/);
    void initLCD(void);
    
    /*
     * move the LCD cursor to the selected location
     * start cursor position address is 0x80
     * row (2): line1 = 0x80 
     *        : line2 = 0x80+0x40
     * col (16): offset to get to the right column(0->16 : per each row)
     * fun return : FUN_RETURN_STATUS to check for function return status
     */
    FUN_RETURN_STATUS moveCursorToLocation(u8 /*row*/,u8 /*col*/);
    
#endif	/* INTERFACING_CONNECTION_LOGIC_H */
