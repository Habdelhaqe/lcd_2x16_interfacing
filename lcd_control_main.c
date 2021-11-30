/*
 * File:   lcd_control_main.c
 * Author: DELL
 *
 * Created on November 28, 2021, 10:41 AM
 */

#include"atmega32a.h"
#define F_CPU 16000000UL
#include"interfacing_connection_logic.h"
#include <avr/io.h>
#define KEEP_EXECUTING 1

int main(void) {
    /* Replace with your application code */
    if(NO_ERRORS == initBTNS()){
        if(NO_ERRORS == initLEDS()){
            
            //all initialization is done correctly proceed to business logic
            while (KEEP_EXECUTING) {
                
                if(chekLEDOnOFF(LED0).scanned_data == OFF){
                    signalLEDOnOff(LED0,ON);
                }
                
                signalLEDOnOff(LED1,isBTNPressed(BTN1).scanned_data);
                signalLEDOnOff(LED2,isBTNPressed(BTN2).scanned_data);
            }
                
        }else{
               //ERR Should Be handled here @ higher logic to decide what to do
        }
    }else{
        //ERR Should Be handled here @ higher logic to decide what to do
    }
}