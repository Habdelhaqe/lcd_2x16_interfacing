/*
 * File:   lcd_control_main.c
 * Author: DELL
 *
 * Created on November 28, 2021, 10:41 AM
 */

#include"atmega32a.h"
#include"interfacing_connection_logic.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define KEEP_EXECUTING 1

#define INTERRUPT_RISING_EDGE_MODE            3 //0x03 : 0b 0000 0011
#define INTERRUPT_FALLING_EDGE_MODE           2 //0x02 : 0b 0000 0010
#define INTERRUPT_ANY_LOGICSL_CHANGE_MODE     1 //0x01 : 0b 0000 0001
#define INTERRUPT_LOW_LEVEL_MODE              0 //0x00 : 0b 0000 0000

/*
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
FUN_RETURN_STATUS initInterruptService(char , u8);

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

int main(void) {

    u8 string[] = "In The Name Of ALLAH";
    //u8 string[] = {NULL_CHAR,NULL_CHAR,NULL_CHAR,NULL_CHAR,NULL_CHAR};

    //int my_id=9742;
    
    configureLCDDataBusLines();
    
    configureLCDControlPins();
        
    initLCD();
        
    initLEDS();

    initBTNS();
    
    //detect if initInterruptService is not a success
//    if(ERR == initInterruptService(INT0,INTERRUPT_RISING_EDGE_MODE)){
//        turnLEDOnOff(LED1,ON);
//    }
//    sei(); //SERG access
    
    
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
//    turnLEDOnOff(LED0,ON);
//    turnLEDOnOff(LED1,ON);
//    turnLEDOnOff(LED2,ON);
//    for(u8 i = 0 ; i<11 ; i++){
//        _delay_ms(200);
//        turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
//        turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
//        turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
//    }
    
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

FUN_RETURN_STATUS initInterruptService(char interrupt_number 
                                        , u8 interrupt_mode){
    
    FUN_RETURN_STATUS err_check_value = NO_ERRORS;
    
    if(interrupt_mode > INTERRUPT_RISING_EDGE_MODE || 
            (interrupt_number != INT0 && 
                interrupt_number != INT1 &&
                    interrupt_number != INT2) ){
    
        err_check_value = ERR;
    
    }else{
       
        switch(interrupt_number){
            
            case INT0 :
                MCUCR |= interrupt_mode;
                break;
            
            case INT1 :    
                MCUCR |= interrupt_mode<<2;
                break;
           
            case INT2 :
                MCUCSR |= interrupt_mode == INTERRUPT_RISING_EDGE_MODE 
                        ? HIGH : LOW<< ISC2;
                break;
                
            default:
                    err_check_value = ERR;
        }
        
        GICR |= HIGH<<interrupt_number;  
    }
    
    return err_check_value;
}