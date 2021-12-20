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
#include "timer0_interfacing.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define KEEP_EXECUTING 1
#define DELAY_MAIN_RETRUN_IN_MS_FOR_TIMER0_SETUP_NOT_WORKING 0.1
#define DELAY_MAIN_RETRUN_IN_MS_FOR_TIMER0_SETUP_WORKING 0.2

#define INTERRUPT_RISING_EDGE_MODE            3 //0x03 : 0b 0000 0011
#define INTERRUPT_FALLING_EDGE_MODE           2 //0x02 : 0b 0000 0010
#define INTERRUPT_ANY_LOGICSL_CHANGE_MODE     1 //0x01 : 0b 0000 0001
#define INTERRUPT_LOW_LEVEL_MODE              0 //0x00 : 0b 0000 0000

void mainInterfaceADCWithLM35TempDisplayOnLCD(void);
void mainInterfaceADCWithLM35TempDisplayOnLCDPollingTechique(void);
void mainInterfacingWithKeyPad(void);
void mainVisitAllLCDCursorPositions(void);
void mainIdonotKnowWhatThisCodeFor(void);
void main8LM35On8ChannelsDispalyTemp(void);
void mainTest2LinesLCDToggling(void);
void mainTimer0(void);
void instrcutionsExecutedEverySec(void);
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

//internal interrupts
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

ISR(TIMER0_OVF_vect){
    //this code could be executed only if a delay is encountered @ least 0.2 mS     
//    static u8 counter = 0;
//    counter++;
//    turnLEDOnOff(LED0,!isLEDOnOrOFF(LED0).scanned_data);
//    displayINTOnLCD(counter);
//    _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
    instrcutionsExecutedEverySec();
}

//"in the name of allah the most gracious the most merciful"
u8 start_msg[] = "in the name of allah most G & M";

u8 lcd_string[32];

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
    
//    mainTest2LinesLCDToggling();
    
//    mainInterfaceADCWithLM35TempDisplayOnLCD();
//    mainInterfaceADCWithLM35TempDisplayOnLCDPollingTechique();
//    mainVisitAllLCDCursorPositions();
//    mainInterfacingWithKeyPad();
//  main8LM35On8ChannelsDispalyTemp();
    
    mainTimer0();
        
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

/*
 * when calling:
 *      @onIntADC(u8,u8,u8,u8);
 *      DISABLE_CONVERSION_COMPLETE_INTERRUPT;
 *      to initiate ADC 2 times the o/p of ADC is ~= Doubled 
 *      ADCH and ADCL doesn't just updates(as if they are anded with the the 
 *      new value) no they are added to new ADCH and ADCL values(as if they are 
 *      Or)
 * that's one of the reasons for creating :
 * @CHANGE_ADC_CHANNEL_KEPP_OTHER_ADMUX_ADCSRA_SETTINGS(NEW_CHANNEL);
 * to keep the frequency and mode as selected along with the voltage ref 
 * and just change the channel to convert the analog signal passing through it
 */
void main8LM35On8ChannelsDispalyTemp(void){
    
    //initLCD();
    
    u8 conv_msg[] ="New Conversion Set...";
    
    CLEAR_LCD;
    
    s32 conversion_result ;
    
    u8 channel_iterator ;
        
    onInitADC(ADC_CHANNEL0,VOLTAGE_AVCC,RIGHT_ADJUST,PRESCALER_CLK_BY_128);
    DISABLE_CONVERSION_COMPLETE_INTERRUPT;
    //_delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
    while(KEEP_EXECUTING){
        
        for(channel_iterator = ADC_CHANNEL0 ; channel_iterator <= ADC_CHANNEL7 ; channel_iterator++ ){
        
            CHANGE_ADC_CHANNEL_KEPP_OTHER_ADMUX_ADCSRA_SETTINGS(channel_iterator);
            _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);        
        
            onStartConversion(SINGLE_CONVERSION_MODE);
            conversion_result = onConversionCompleteUsingPolling() * DIGITAL_REPRESENTATION_LM35V_FOR_1_C ;
        
            displayINTOnLCD(conversion_result);
            displayCharacterOnLCD(' ');
            
            //move cursor to second line for the reaming 4 Temp sensors
            if(channel_iterator == ADC_CHANNEL3){
                moveCursorToLocation(LCD_ROW_COUNT,LOOP_ZER0_INITIALIZER);
            }
        
        }
        _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
        CLEAR_LCD;
        
        displayStringOnLCD(conv_msg);
        _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
        CLEAR_LCD;
    }

    //double the first reading value code    
//    onStartConversion(SINGLE_CONVERSION_MODE);    
//    conversion_result = onConversionCompleteUsingPolling() * DIGITAL_REPRESENTATION_LM35V_FOR_1_C ;
//    
//    displayINTOnLCD(conversion_result);
//    _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
//    
//    CHANGE_ADC_CHANNEL_KEPP_OTHER_ADMUX_ADCSRA_SETTINGS(ADC_CHANNEL0+1);
//    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
// 
//    onStartConversion(SINGLE_CONVERSION_MODE);    
//    conversion_result_ = onConversionCompleteUsingPolling() * DIGITAL_REPRESENTATION_LM35V_FOR_1_C ;
    
    //moveCursorToLocation(LOOP_ZER0_INITIALIZER , LOOP_ZER0_INITIALIZER);
        
//    displayINTOnLCD(conversion_result);
//    displayINTOnLCD(conversion_result_);
//    _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
    
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

void mainTest2LinesLCDToggling(void){
    
    u8 line = LOOP_ZER0_INITIALIZER;
    
    CLEAR_LCD;
    
    while(KEEP_EXECUTING){
        
        line = !line;
        
        moveCursorToLocation(line , 0);
        
        displayINTOnLCD(9742);
        
        line = !line;
        
        moveCursorToLocation(line , 0);
    
        displayINTOnLCD(2020);
    
        _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
        
        CLEAR_LCD; 
        
        line = !line;
    } 
   
}

void mainTimer0(void){
    
    initLED(LED0);
    
    //initLCD();
    
    CLEAR_LCD;
    
    _delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
    
    onInitTimer(TIMER0_PRESCALER_CLK_BY_1024 ,
                NORMAL_MODE ,
                NON_PWD_NORMAL_PORT_OPERATION_MODE ,
                TRUE ,
                FALSE );
    /*
     * case study : 
     *          i forgot to add the infinite loop statement that keeps
     * the @main fun statements/instructions running all time keeping 
     * the microcontroller CPU looping for ever or till REST interrupt or 
     * powered off ,
     * timer0 TOIE0 is set so @ISR(TIMER0_OVF_vect) is activated: when @TCNT0 
     * reaches @MAX(0xFF) the @TOVF0 is set interrupting the CPU internally 
     * CPU examines the VECTOR TABLE finds :
     *  $016 TIMER0 OVF "Timer/Counter0 Overflow" VECTOR_ENTRY and executes the 
     *  instruction:  @jmp TIM0_OVF -> causing the execution of the 
     *  @ISR(TIMER0_OVF_vect) routine; and then rest(idle)/continue any other 
     *  routines or respond to other service/routines/interrupts 
     * so if my analogy is correct then if i return from the @main fun 
     * (does not keep CPU lingering/stall/stuck in a loop)
     * the timer0 should be working and CPU should continue to respond 
     * (give it be HW/Circuitry_no_SW involved or SW/instructions CPU carries 
     * to do the respond mechanism ) to @TOVF0 flag calling @ISR(TIMER0_OVF_vect).
     * @PROBLEM :- 
     *      if i did return from @main fun after TIMER0 setup code is done the 
     * @ISR(TIMER0_OVF_vect) is NEVER called .
     *      if i delayed the return form @main fun by calling @_delay_ms(0.1);
     * THE @ISR(TIMER0_OVF_vect) is NEVER called .
     *      if i delayed the return form @main fun by calling @_delay_ms(0.2);
     * THE @ISR(TIMER0_OVF_vect) is called .
     *      if the @ISR(TIMER0_OVF_vect) routine contains a call to a fun
     * that holds statements to execute what ever the delay is it is NEVER called
     * also tested if the code/statements was placed in the routine directly
     * also doesn't work!!! note(code is longer than before) 
     */
    
    //_delay_ms(DELAY_MAIN_RETRUN_IN_MS_FOR_TIMER0_SETUP_NOT_WORKING);   
    //_delay_ms(DELAY_MAIN_RETRUN_IN_MS_FOR_TIMER0_SETUP_WORKING);
    //_delay_ms(HW_INITIALIZATION_DELAY_IN_MS);
   //_delay_ms(LCD_DISPLAY_DELAY_IN_MS);
 
    while(KEEP_EXECUTING);
}

void instrcutionsExecutedEverySec(void){
    #define NUMBER_OF_COMPLETE_COUNTS_TO_MAX_IN_1_SEC (u8)(1000000/16384)
    //#define NUMBER_OF_COMPLETE_COUNTS_TO_MAX_IN_1_SEC 61
    /*
     * remember each statement you add causes a delay in the count
     * as statement is converted to instructions added by compiler to deliver 
     * the logic so the delay depends on how many cycles per each instruction
     * multiplied by number of instructions / statements so for higher pression
     * keep it to minimum and place the entire code inside the ISR routine
     */
    static u8 complete_count_to_max_counter ,
              seconds_counter ,
              halting_time  ,
              frequency_change_req  ;
    
    //check if ~= 1 sec passed
    if(complete_count_to_max_counter == 
            NUMBER_OF_COMPLETE_COUNTS_TO_MAX_IN_1_SEC){
        //toggle LED0 ON / OFF
        turnLEDOnOff(LED0,!isLEDOnOrOFF(LED0).scanned_data);
        //display on LCD number of Seconds passed 
        CLEAR_LCD;
        displayINTOnLCD(++seconds_counter);
        //rest the complete_count_to_max_counter for the upcoming count for 1 sec
        complete_count_to_max_counter = 0;
    }else{
        complete_count_to_max_counter ++;
    }
    if(seconds_counter == 5 && halting_time==0){
        haltTimer();
        halting_time++;
        frequency_change_req = LOOP_ZER0_INITIALIZER;
        *(lcd_string + frequency_change_req++) = ' ';
        *(lcd_string + frequency_change_req++) =('c');
        *(lcd_string + frequency_change_req++) =('o');
        *(lcd_string + frequency_change_req++) =('n');
        *(lcd_string + frequency_change_req++) =('f');
        *(lcd_string + frequency_change_req++) =('i');
        *(lcd_string + frequency_change_req++) =('g');
        *(lcd_string + frequency_change_req++) =('u');
        *(lcd_string + frequency_change_req++) =('r');
        *(lcd_string + frequency_change_req++) =('a');        
        *(lcd_string + frequency_change_req++) =('t');
        *(lcd_string + frequency_change_req++) =('i');
        *(lcd_string + frequency_change_req++) =('o');
        *(lcd_string + frequency_change_req++) =('n');
        *(lcd_string + frequency_change_req++) =(':');
        displayStringOnLCD(lcd_string);
//        displayCharacterOnLCD(' ');
//        displayCharacterOnLCD('c');
//        displayCharacterOnLCD('o');
//        displayCharacterOnLCD('f');
//        displayCharacterOnLCD('i');
//        displayCharacterOnLCD('g');
//        displayCharacterOnLCD('r');
//        displayCharacterOnLCD('t');
//        displayCharacterOnLCD('i');
//        displayCharacterOnLCD('o');
//        displayCharacterOnLCD('n');
//        displayCharacterOnLCD(':');
        displayINTOnLCD(getTimerConfiguration());
        moveCursorToLocation(LCD_ROW_COUNT,LOOP_ZER0_INITIALIZER);
        frequency_change_req = LOOP_ZER0_INITIALIZER;
        *(lcd_string + frequency_change_req++) =('H');
        *(lcd_string + frequency_change_req++) =('A');
        *(lcd_string + frequency_change_req++) =('L');
        *(lcd_string + frequency_change_req++) =('T');
        *(lcd_string + frequency_change_req++) =('E');
        *(lcd_string + frequency_change_req++) =('D');
        *(lcd_string + frequency_change_req++) =(':');
        *(lcd_string + frequency_change_req++) =(NULL_CHAR);        
        displayStringOnLCD(lcd_string);
//        displayCharacterOnLCD('H');
//        displayCharacterOnLCD('A');
//        displayCharacterOnLCD('L');
//        displayCharacterOnLCD('T');
//        displayCharacterOnLCD('E');
//        displayCharacterOnLCD('D');
//        displayCharacterOnLCD(':');
        displayCharacterOnLCD(getTimerStatus()? 'N' : 'F');
        _delay_ms(LCD_DISPLAY_DELAY_IN_MS);
        
        resumeTimer();
        
        CLEAR_LCD;
        frequency_change_req = LOOP_ZER0_INITIALIZER;
        *(lcd_string + frequency_change_req++) =('R');
        *(lcd_string + frequency_change_req++) =('E');
        *(lcd_string + frequency_change_req++) =('S');
        *(lcd_string + frequency_change_req++) =('U');
        *(lcd_string + frequency_change_req++) =('M');
        *(lcd_string + frequency_change_req++) =('E');
        *(lcd_string + frequency_change_req++) =(' ');
        *(lcd_string + frequency_change_req++) =('C');
        *(lcd_string + frequency_change_req++) =('O');
        *(lcd_string + frequency_change_req++) =('U');
        *(lcd_string + frequency_change_req++) =('N');
        *(lcd_string + frequency_change_req++) =('T');
        *(lcd_string + frequency_change_req++) =('I');
        *(lcd_string + frequency_change_req++) =('N');
        *(lcd_string + frequency_change_req++) =('G');  
        *(lcd_string + frequency_change_req++) =('!');
        *(lcd_string + frequency_change_req++) =(NULL_CHAR);
        displayStringOnLCD(lcd_string);
        frequency_change_req = LOOP_ZER0_INITIALIZER;        
//        displayCharacterOnLCD('R');
//        displayCharacterOnLCD('E');
//        displayCharacterOnLCD('S');
//        displayCharacterOnLCD('U');
//        displayCharacterOnLCD('M');
//        displayCharacterOnLCD('E');
//        displayCharacterOnLCD('!');
    }
    
    if(seconds_counter == 7 && frequency_change_req == 0){
        frequency_change_req++;
        changeTimerClk_source(TIMER0_PRESCALER_CLK_BY_8);
        CLEAR_LCD;
        displayCharacterOnLCD('F');
        displayCharacterOnLCD('R');
        displayCharacterOnLCD('E');
        displayCharacterOnLCD('Q');
        displayCharacterOnLCD('U');
        displayCharacterOnLCD('E');
        displayCharacterOnLCD('N');
        displayCharacterOnLCD('C');
        displayCharacterOnLCD('Y');
        displayCharacterOnLCD(' ');
        displayCharacterOnLCD('C');
        displayCharacterOnLCD('H');
        displayCharacterOnLCD('A');
        displayCharacterOnLCD('N');
        displayCharacterOnLCD('N');
        displayCharacterOnLCD('G');
        moveCursorToLocation(LCD_ROW_COUNT,LOOP_ZER0_INITIALIZER);        
        displayCharacterOnLCD('E');
        displayCharacterOnLCD('D');
        displayCharacterOnLCD(' ');
        displayCharacterOnLCD('G');
        displayCharacterOnLCD('E');
        displayCharacterOnLCD('T');
        displayCharacterOnLCD(' ');
        displayCharacterOnLCD('R');
        displayCharacterOnLCD('E');        
        displayCharacterOnLCD('A');
        displayCharacterOnLCD('D');
        displayCharacterOnLCD('Y');
        displayCharacterOnLCD('!');
        _delay_ms(LCD_DISPLAY_DELAY_IN_MS);        
    }
    if(seconds_counter == 255){
        haltTimer();
    }
}