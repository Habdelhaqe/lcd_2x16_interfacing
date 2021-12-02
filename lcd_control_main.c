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

    //u8 string[] = "IN The Name Of Allah";

    //set portD pins for o/p
    //setPortInOut(IOD,OUTPUT);
    
    configureLCDDataBusLines();
        
    initLEDS();

    initBTNS();
    
    turnLEDOnOff(LED0,ON);
    turnLEDOnOff(LED1,ON);
    turnLEDOnOff(LED2,ON);
    _delay_ms(500);
    turnLEDOnOff(LED0,OFF);
    turnLEDOnOff(LED1,OFF);
    turnLEDOnOff(LED2,OFF);
    
    while(KEEP_EXECUTING){

        if(BTN_PRESSED == isBTNPressed(BTN0).scanned_data){
            outControlSignalThroughPort(OUTD,0x38);
            turnLEDOnOff(LED0,isBTNPressed(BTN0).scanned_data);
            turnLEDOnOff(LED1,isBTNPressed(BTN0).scanned_data);
            _delay_ms(500);
        }

        if(BTN_PRESSED == isBTNPressed(BTN1).scanned_data){
            outControlSignalThroughPort(OUTD,0x01);
            turnLEDOnOff(LED0,isBTNPressed(BTN1).scanned_data);
            turnLEDOnOff(LED1,isBTNPressed(BTN1).scanned_data);
        }

        if(BTN_PRESSED == isBTNPressed(BTN2).scanned_data){
            outControlSignalThroughPort(OUTD,0x02);
        }
        
    }
}