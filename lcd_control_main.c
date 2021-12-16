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
#include "adc_interfacing.h"
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
//ISR(INT0_vect){
//        
//        //blinking light
//        turnLEDOnOff(LED0,ON);
//        turnLEDOnOff(LED1,ON);
//        turnLEDOnOff(LED2,ON);
//
//        for(u8 i = 0 ; i<11 ; i++){
//            _delay_ms(100);
//            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
//        }
//    
//}

ISR(ADC_vect){
    
    commandLCD(CLEAR_DISPLAY);
    
    //write result on display
    displayINTOnLCD(onConversionComplete());
    
    _delay_ms(1000);

    //condition the LED1 be ON conversion completed
    turnLEDOnOff(LED1 , IS_CONVERSION_COMPLETED);
     
    //condition the LED2 be OFF if conversion not started
    turnLEDOnOff(LED2,IS_CONVERSION_STARTED);
    
    _delay_ms(1000);
    
    //start another conversion 
    onStartConversion(SINGLE_CONVERSION_MODE);
    
    //condition the LED2 be ON incase of a conversion started
    turnLEDOnOff(LED2,IS_CONVERSION_STARTED);

    //condition the LED1 be conversion not completed
    turnLEDOnOff(LED1 , IS_CONVERSION_COMPLETED);

}

int main(void) {

    u8 string[] = "In The Name Of ALLAH";
    //u8 string[] = {NULL_CHAR,NULL_CHAR,NULL_CHAR,NULL_CHAR,NULL_CHAR};
    //int my_id=9742;
    
    initLEDS();

    initBTNS();
    
    configureLCDDataBusLines();
    
    configureLCDControlPins();
        
    initLCD();

    //initADCInternalCircuitry(ADC_CHANNEL0 , VOLTAGE_AVCC , RIGHT_ADJUST , PRESCALER_CLK_BY_128);
    onInitADC(ADC_CHANNEL0 , VOLTAGE_AVCC , RIGHT_ADJUST , PRESCALER_CLK_BY_128);
        
        
    //detect if initInterruptService is not a success
//    if(ERR == initInterruptService(INT0,INTERRUPT_RISING_EDGE_MODE)){
//        turnLEDOnOff(LED1,ON);
//    }
//    //SERG set I bit : ENABLE global interrupt concept for the MIcroController
    sei(); 
  
     /*
     * you must see the concept of adding the delay to stall any access 
     * of the IOs/interfacing_units till internal initialize of HW is completed
     * so this code must be directly above the code that uses/utilizes the HW
     * how to calculate the delay!!!!
     */
    _delay_ms(10);
    //\c moveCursorToLocation(u8,u8) does not work with 4_bit Mode!!!!!!!
//    if(ERR == moveCursorToLocation(LCD_ROW_COUNT,0)){
//        turnLEDOnOff(LED0,ON);
//        _delay_ms(2000);
//    }
    
    //displayStringOnLCD(string);
    
    //_delay_ms(200);
           
    //    moveCursorToLocation(2,0);
//    
//    displayINTOnLCD(my_id);
    
//    initKeypad();
    
//    u8 key;
//        
//    while(KEEP_EXECUTING){
//
//        if(BTN_PRESSED == isBTNPressed(BTN0).scanned_data){
//            outControlSignalThroughPort(OUTD,0x38);
//            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
//        }        
//        
//        if(BTN_PRESSED == isBTNPressed(BTN1).scanned_data){
//            outControlSignalThroughPort(OUTD,0x01);
//            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
//        }
//                
//        if(BTN_PRESSED == isBTNPressed(BTN2).scanned_data){
//            outControlSignalThroughPort(OUTD,0x02);
//            turnLEDOnOff(LED0,ON==isLEDOnOrOFF(LED0).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED1,ON==isLEDOnOrOFF(LED1).scanned_data ? OFF:ON );
//            turnLEDOnOff(LED2,ON==isLEDOnOrOFF(LED2).scanned_data ? OFF:ON );
//        }
//        
//        key = getPressedKey();
//        
//        switch(key){
//            case KEYPAD_BTN0: displayCharacterOnLCD('0'); break;
//            case KEYPAD_BTN1: displayCharacterOnLCD('1'); break;
//            case KEYPAD_BTN2: displayCharacterOnLCD('2'); break;
//            case KEYPAD_BTN3: displayCharacterOnLCD('3'); break;
//            case KEYPAD_BTN4: displayCharacterOnLCD('4'); break;
//            case KEYPAD_BTN5: displayCharacterOnLCD('5'); break;
//            case KEYPAD_BTN6: displayCharacterOnLCD('6'); break;
//            case KEYPAD_BTN7: displayCharacterOnLCD('7'); break;
//            case KEYPAD_BTN8: displayCharacterOnLCD('8'); break;
//            case KEYPAD_BTN9: displayCharacterOnLCD('9'); break;            
//            case KEYPAD_BTN_STAR: displayCharacterOnLCD('*'); break;
//            case KEYPAD_BTN_POUND: displayCharacterOnLCD('#'); break;
//            default:
//                //nothing is pressed
//                break;
//        }
//       _delay_ms(100);
//    }

//  commandLCD(CLEAR_DISPLAY);
    
    u8 msg[] = "NOT COMPLETED!!!!!!!";
    
    displayStringOnLCD(string);
    
    _delay_ms(500);
    
    commandLCD(CLEAR_DISPLAY);
    
    DISABLE_CONVERSION_COMPLETE_INTERRUPT;
    
    //onStartConversion(SINGLE_CONVERSION_MODE);
    //as it is the first conversion it takes 25 ADC CLK to complete
    
    //holder for conversion result    
    s16 conversion_result;
    
    //my own solution to not stall microcontroller
//    while(KEEP_EXECUTING){
//        
//        //condition the LED2 be ON incase of a conversion OFF if non
//        turnLEDOnOff(LED2,IS_CONVERSION_STARTED);
//        
//        turnLEDOnOff(LED0,IS_CONVERSION_COMPLETED);
//        
//        conversion_result = onConversionCompleteUsingPollingSpeedy();
//        
//        commandLCD(CLEAR_DISPLAY);
//        displayStringOnLCD(msg);      
//        
//        turnLEDOnOff(LED1 , conversion_result==CONVERSION_PROCESS_NOT_COMPLETE );
//        
//        if( conversion_result!= 
//                CONVERSION_PROCESS_NOT_COMPLETED_ADJUSTMENT_LEFT_RIGHT ){
//            
//            commandLCD(CLEAR_DISPLAY);
//            displayINTOnLCD(conversion_result);
//            _delay_ms(1000);
//            onStartConversion(SINGLE_CONVERSION_MODE);
//        
//        }
//        
//    }
       
    //stalling microcontroller way
    while(KEEP_EXECUTING){
        
       //condition the LED2 be ON incase of a conversion OFF if non
        turnLEDOnOff(LED2,IS_CONVERSION_STARTED);
        
        turnLEDOnOff(LED0,IS_CONVERSION_COMPLETED);

        commandLCD(CLEAR_DISPLAY);
        displayStringOnLCD(msg);      
        
        conversion_result = onConversionCompleteUsingPolling();
                
        turnLEDOnOff(LED1 , conversion_result==CONVERSION_PROCESS_NOT_COMPLETE );
        
        commandLCD(CLEAR_DISPLAY);
        displayINTOnLCD(conversion_result);
        _delay_ms(1000);
        onStartConversion(SINGLE_CONVERSION_MODE);

    }
    
    //visiting all LCD places
//    while(KEEP_EXECUTING){
//        for(u8 move_cursor_command =  PLACE_CUR_AT_BEGINE_OF_FIRST_LINE ; 
//                move_cursor_command <= 0xCF ; move_cursor_command++ ){
//            turnLEDOnOff(LED0,!isLEDOnOrOFF(LED0).scanned_data);
//            commandLCD(move_cursor_command);
//            _delay_ms(100);
//            if(move_cursor_command==0x8F ){
//                move_cursor_command = PLACE_CUR_AT_BEGINE_OF_SECOND_LINE;
//            }
//        }
//        
//        for(u8 shift = LOOP_ZER0_INITIALIZER , line = LOOP_ZER0_INITIALIZER ; shift<=LCD_LAST_COLUMN_OFFSET & line<=LCD_ROW_COUNT ; shift++){
//            turnLEDOnOff(LED0,!isLEDOnOrOFF(LED0).scanned_data);
//            moveCursorToLocation(line , shift);
//            if( shift==LCD_LAST_COLUMN_OFFSET && !line){
//                line++;
//                shift = LOOP_ZER0_INITIALIZER;
//            }
//            _delay_ms(100);
//        }
//    }
    
}