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

//    if(NO_ERRORS == initBTNS()){
//        if(NO_ERRORS == initLEDS()){
//            
//            //all initialization is done correctly proceed to business logic
//            while (KEEP_EXECUTING) {
//                
//                if(chekLEDOnOFF(LED0).scanned_data == OFF){
//                    signalLEDOnOff(LED0,ON);
//                }
//                
//                if (ON == chekLEDOnOFF(signalLEDOnOff(LED1,isBTNPressed(BTN1)
//                        .scanned_data))
//                        .scanned_data){
//                    /*
//                     * Prove that all configuration functionality 
//                     * and control signals passing and scanning 
//                     * are in correct form that LED Went on
//                     */
//                }else{
//                    /*
//                     * something went wrong and further checking is needed
//                     */
//                }
//                
//                signalLEDOnOff(LED1,isBTNPressed(BTN1).scanned_data);
//                signalLEDOnOff(LED2,isBTNPressed(BTN2).scanned_data);
//            }
//                
//        }else{
//               //ERR Should Be handled here @ higher logic to decide what to do
//        }
//    }else{
//        //ERR Should Be handled here @ higher logic to decide what to do
//    }
    
 
    //--------------------------------test LCD on PORTD

//    //u8 string[] = "IN The Name Of Allah";
//    if(NO_ERRORS == configureLCDControlPins()){
//        if(NO_ERRORS == configureLCDDataBusLines()){  
//            if(NO_ERRORS == initLCD(_8BIT_2L_MODE)){
//                
//                //displayStringOnLCD(string);
//                
//                displayCharacterOnLCD('A');
//                
//                while(KEEP_EXECUTING){
//                }
//            }else{
//            
//            }
//        }else{
//            
//        }
//    }else{
//                    
//    }
    
    //set portD pins for o/p
    setPortInOut(IOD,OUTPUT);
    
    initBTN(IOB,BTN0);
    initBTN(IOB,BTN1);
    initBTN(IOB,BTN2);
    
//    setPortPinInOut(IOB,BTN0,INPUT);
//    setPortPinInOut(IOB,BTN1,INPUT);
//    setPortPinInOut(IOB,BTN2,INPUT);
    
    initLED(IOC,LED0);
    initLED(IOC,LED1);
    
//    setPortPinInOut(IOC,LED0,OUTPUT);
//    setPortPinInOut(IOC,LED1,OUTPUT);
    
    while(KEEP_EXECUTING){
        if(BTN_PRESSED == isBTNPressed(BTN0).scanned_data){
            outControlSignalThroughPort(OUTD,0x00);
            signalLEDOnOff(LED0,isBTNPressed(BTN0).scanned_data);
            signalLEDOnOff(LED1,isBTNPressed(BTN0).scanned_data);
        }
        if(BTN_PRESSED == isBTNPressed(BTN1).scanned_data){
            outControlSignalThroughPort(OUTD,0x01);
            signalLEDOnOff(LED0,isBTNPressed(BTN1).scanned_data);
            signalLEDOnOff(LED1,isBTNPressed(BTN1).scanned_data);
        }
        if(BTN_PRESSED == isBTNPressed(BTN2).scanned_data){
            outControlSignalThroughPort(OUTD,0x02);
        }
        
    }
}