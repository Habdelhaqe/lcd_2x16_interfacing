/*
 * File:   lcd_control_main.c
 * Author: DELL
 *
 * Created on November 28, 2021, 10:41 AM
 */

#include"atmega32a.h"
#include"interfacing_connection_logic.h"
#include"phone_keypad.h"
#include"interrupt_configuration.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define KEEP_EXECUTING 1

#define INTERRUPT_RISING_EDGE_MODE            3 //0x03 : 0b 0000 0011
#define INTERRUPT_FALLING_EDGE_MODE           2 //0x02 : 0b 0000 0010
#define INTERRUPT_ANY_LOGICSL_CHANGE_MODE     1 //0x01 : 0b 0000 0001
#define INTERRUPT_LOW_LEVEL_MODE              0 //0x00 : 0b 0000 0000

/*
 * external interrupt initiated on INT0
 */
ISR(INT0_vect){
        
        //blinking light
        turnLEDOnOff(LED0,ON);
        turnLEDOnOff(LED1,ON);
        turnLEDOnOff(LED2,ON);

        for(u8 i = 0 ; i<11 ; i++){
            _delay_ms(100);
            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
        }
    
}

ISR(INT1_vect){
    
}

ISR(INT2_vect){
    
}

int main(void) {

    //u8 string[] = "In The Name Of ALLAH";
    //u8 string[] = {NULL_CHAR,NULL_CHAR,NULL_CHAR,NULL_CHAR,NULL_CHAR};

    //int my_id=9742;
    
    configureLCDDataBusLines();
    
    configureLCDControlPins();
        
    initLCD();
        
    initLEDS();

    initBTNS();
    
    //detect if initInterruptService is not a success
    if(ERR == initInterruptService(INT0,INTERRUPT_RISING_EDGE_MODE)){
        turnLEDOnOff(LED1,ON);
    }
    sei(); //SERG access
    
    
    //\c moveCursorToLocation(u8,u8) does not work with 4_bit Mode!!!!!!!
//    if(ERR == moveCursorToLocation(LCD_ROW_COUNT,4)){
//        turnLEDOnOff(LED0,ON);
//    }
    
    //displayStringOnLCD(string);
    
//    moveCursorToLocation(2,0);
//    
//    displayINTOnLCD(my_id);
    
    initKeypad();
    
    u8 key;
        
    while(KEEP_EXECUTING){

        if(BTN_PRESSED == isBTNPressed(BTN0).scanned_data){
            outControlSignalThroughPort(OUTD,0x38);
            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
        }        
        
        if(BTN_PRESSED == isBTNPressed(BTN1).scanned_data){
            outControlSignalThroughPort(OUTD,0x01);
            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
        }
                
        if(BTN_PRESSED == isBTNPressed(BTN2).scanned_data){
            outControlSignalThroughPort(OUTD,0x02);
            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
        }
        
        key = getPressedKey();
        
        switch(key){
            case KEYPAD_BTN0: displayCharacterOnLCD('0'); break;
            case KEYPAD_BTN1: displayCharacterOnLCD('1'); break;
            case KEYPAD_BTN2: displayCharacterOnLCD('2'); break;
            case KEYPAD_BTN3: displayCharacterOnLCD('3'); break;
            case KEYPAD_BTN4: displayCharacterOnLCD('4'); break;
            case KEYPAD_BTN5: displayCharacterOnLCD('5'); break;
            case KEYPAD_BTN6: displayCharacterOnLCD('6'); break;
            case KEYPAD_BTN7: displayCharacterOnLCD('7'); break;
            case KEYPAD_BTN8: displayCharacterOnLCD('8'); break;
            case KEYPAD_BTN9: displayCharacterOnLCD('9'); break;            
            case KEYPAD_BTN_STAR: displayCharacterOnLCD('*'); break;
            case KEYPAD_BTN_POUND: displayCharacterOnLCD('#'); break;
            default:
                //nothing is pressed
                break;
        }
       _delay_ms(100);
    }
}