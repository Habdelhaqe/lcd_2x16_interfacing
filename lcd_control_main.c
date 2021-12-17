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

void mainInterfaceADCWithLM35TempDisplayOnLCD(void);
void mainInterfaceADCWithLM35TempDisplayOnLCDPollingTechique(void);
void mainInterfacingWithKeyPad(void);
void mainVisitAllLCDCursorPositions(void);
void mainIdonotKnowWhatThisCodeFor(void);

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
//"in the name of allah the most gracious the most merciful"
u8 start_msg[] = "in the name of allah most G & M";

int main(void) {
    
    initLCD();
    
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
    
    displayStringOnLCD(start_msg);
    
    _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
        
    //detect if initInterruptService is not a success
//    turnLEDOnOff(LED0 , 
//            ERR == initInterruptService(INT0,INTERRUPT_RISING_EDGE_MODE));
    
    //SERG set I bit : ENABLE global interrupt concept for the MIcroController
    sei(); 
        
    
//    mainInterfaceADCWithLM35TempDisplayOnLCD();
//    mainInterfaceADCWithLM35TempDisplayOnLCDPollingTechique();
//    mainVisitAllLCDCursorPositions();
    mainInterfacingWithKeyPad();
    
}

//my own polling way trying not to stall/wait for ADC
void mainInterfaceADCWithLM35TempDisplayOnLCD(void){
    
    u8 msg[] = "NOT COMPLETED!!!!!!!" ,
       temp_conv_string [] = "TEMP " ,
       degree_in_string [] = " C"    ;     

    initLEDS();

    initBTNS();
            
    //initLCD();

    onInitADC(ADC_CHANNEL0 , VOLTAGE_AVCC , RIGHT_ADJUST , PRESCALER_CLK_BY_128);
        
    DISABLE_CONVERSION_COMPLETE_INTERRUPT;
 
    /*
     * you must see the concept of adding the delay to stall any access 
     * of the IOs/interfacing_units till internal initialize of HW is completed
     * so this code must be directly above the code that uses/utilizes the HW
     * how to calculate the delay!!!!
     */
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
  
    //as it is the first conversion it takes 25 ADC CLK to complete
    onStartConversion(SINGLE_CONVERSION_MODE);
    
    //holder for conversion result    
    s32 conversion_result;
    
    //my own solution to not stall microcontroller
    while(KEEP_EXECUTING){
        
        //condition the LED2 be ON incase of a conversion OFF if non
        turnLEDOnOff(LED2,IS_CONVERSION_STARTED);
        
        turnLEDOnOff(LED0,IS_CONVERSION_COMPLETED);
        
        conversion_result = onConversionCompleteUsingPollingSpeedy();
        
        commandLCD(CLEAR_DISPLAY);
        
        displayStringOnLCD(msg);      
        
        turnLEDOnOff(LED1 , conversion_result==CONVERSION_PROCESS_NOT_COMPLETE );
        
        if( conversion_result!= 
                CONVERSION_PROCESS_NOT_COMPLETED_ADJUSTMENT_LEFT_RIGHT ){
            
            commandLCD(CLEAR_DISPLAY);
            
            displayStringOnLCD(temp_conv_string);
            
            //O/P THE DEGREE IN C
            displayINTOnLCD( conversion_result * DIGITAL_REPRESENTATION_LM35V_FOR_1_C);
            
            displayStringOnLCD(degree_in_string);
            
            _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
            
            onStartConversion(SINGLE_CONVERSION_MODE);
        
        }
        
    }

}

//polling microcontroller
void mainInterfaceADCWithLM35TempDisplayOnLCDPollingTechique(void){

    u8 temp_conv_string [] = "TEMP " ,
       degree_in_string [] = " C"    ;     

    initLEDS();

    initBTNS();
            
    //initLCD();

    onInitADC(ADC_CHANNEL0 , VOLTAGE_AVCC , RIGHT_ADJUST , PRESCALER_CLK_BY_128);
       
    DISABLE_CONVERSION_COMPLETE_INTERRUPT;

    /*
     * you must see the concept of adding the delay to stall any access 
     * of the IOs/interfacing_units till internal initialize of HW is completed
     * so this code must be directly above the code that uses/utilizes the HW
     * how to calculate the delay!!!!
     */
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
  
    //as it is the first conversion it takes 25 ADC CLK to complete
    onStartConversion(SINGLE_CONVERSION_MODE);
    
    //holder for conversion result    
    s32 conversion_result;
    
    //stalling microcontroller way
    while(KEEP_EXECUTING){
                
        conversion_result = onConversionCompleteUsingPolling();
                
        turnLEDOnOff(LED1 , !IS_CONVERSION_COMPLETED );

        turnLEDOnOff(LED0 , IS_CONVERSION_COMPLETED );
        
        commandLCD(CLEAR_DISPLAY);

        displayStringOnLCD(temp_conv_string);
            
        //O/P THE DEGREE IN C
        displayINTOnLCD( conversion_result * DIGITAL_REPRESENTATION_LM35V_FOR_1_C);
            
        displayStringOnLCD(degree_in_string);

        _delay_ms(LCD_DISPLAY_DELAY_IN_MS);

        onStartConversion(SINGLE_CONVERSION_MODE);

    }
}

void mainInterfacingWithKeyPad(void){

    initKeypad();
    
    initLEDS();
    
    //initLCD();
    
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
    
    u8 key;
    
    commandLCD(CLEAR_DISPLAY);
    
    while(KEEP_EXECUTING){
        
        key = getPressedKey();
        
        switch(key){
            case KEYPAD_BTN0: key = ASCI_0; break;
            case KEYPAD_BTN1: 
            case KEYPAD_BTN2: 
            case KEYPAD_BTN3: 
            case KEYPAD_BTN4: 
            case KEYPAD_BTN5: 
            case KEYPAD_BTN6: 
            case KEYPAD_BTN7: 
            case KEYPAD_BTN8: 
            case KEYPAD_BTN9: key = ASCI_0 + key; break;            
            case KEYPAD_BTN_STAR: key = ASCI_STAR; break;
            case KEYPAD_BTN_POUND: key = ASCI_POUND;
        }
        
        displayCharacterOnLCD(key);
       //_delay_ms(LCD_DISPLAY_DELAY_IN_MS);
    }
}

void mainIdonotKnowWhatThisCodeFor(void){
    
    initBTNS();
    
    initLEDS();
    
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
    
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

    }
    
}

void mainVisitAllLCDCursorPositions(void){
    
    initLED(LED0);
    
//    initLCD();
    
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
    
    u8 move_cursor_command , shift , line ;
    
    while(KEEP_EXECUTING){

        for( move_cursor_command =  PLACE_CUR_AT_BEGINE_OF_FIRST_LINE ; 
                move_cursor_command <= PLACE_CUR_AT_LAST_OF_SECOND_LINE ;
                    move_cursor_command++ ){
            
            turnLEDOnOff(LED0,!isLEDOnOrOFF(LED0).scanned_data);
            
            commandLCD(move_cursor_command);
            
            _delay_ms(VISIT_ALL_LCD_IN_MS);
            
            if(move_cursor_command == PLACE_CUR_AT_LAST_OF_FIRST_LINE ){
                move_cursor_command = PLACE_CUR_AT_BEGINE_OF_SECOND_LINE;
            }
        }
        
        for(shift = LOOP_ZER0_INITIALIZER , line = LOOP_ZER0_INITIALIZER ; 
                shift<=LCD_LAST_COLUMN_OFFSET && line<=LCD_ROW_COUNT ; 
                    shift++){
            
            turnLEDOnOff(LED0,!isLEDOnOrOFF(LED0).scanned_data);
            
            moveCursorToLocation(line , shift);
            
            if( shift==LCD_LAST_COLUMN_OFFSET && !line){
                line++;
                shift = LOOP_ZER0_INITIALIZER;
            }
            _delay_ms(VISIT_ALL_LCD_IN_MS);
        }
    
    }
}
