/*
 * File:   lcd_control_main.c
 * Author: DELL
 *
 * Created on November 28, 2021, 10:41 AM
 */

#include"atmega32a.h"
#include"interfacing_connection_logic.h"
#include <avr/io.h>
#define KEEP_EXECUTING 1

int main(void) {

    u8 string[] = "In The Name Of ALLAH";

    //int my_id=9742;
    
    configureLCDDataBusLines();
    
    configureLCDControlPins();
    
    initLCD();
        
    initLEDS();

    initBTNS();
    
    //displayCharacterOnLCD('a');
    
    //\c moveCursorToLocation(u8,u8) does not work with 4_bit Mode!!!!!!!
//    if(ERR == moveCursorToLocation(LCD_ROW_COUNT,4)){
//        turnLEDOnOff(LED0,ON);
//    }
    
    displayStringOnLCD(string);
    
//    moveCursorToLocation(2,0);
//    
//    displayINTOnLCD(my_id);
//    
    //blinking light
    turnLEDOnOff(LED0,ON);
    turnLEDOnOff(LED1,ON);
    turnLEDOnOff(LED2,ON);
    for(u8 i = 0 ; i<11 ; i++){
        _delay_ms(200);
        turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
        turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
        turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
    }
    
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
       _delay_ms(500);
    }
    
}