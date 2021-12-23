#include "phone_keypad.h"
#include "interfacing_connection_logic.h"
#include <util/delay.h>

void initKeypad(void){
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING THE SHOOTS
    //program/configure connection pins
    programPortPinInOut(KEYPAD_A_PIN , INPUT);
    programPortPinInOut(KEYPAD_B_PIN , INPUT);
    programPortPinInOut(KEYPAD_C_PIN , INPUT);
    programPortPinInOut(KEYPAD_D_PIN , INPUT);

    programPortPinInOut(KEYPAD_1_PIN , OUTPUT);
    programPortPinInOut(KEYPAD_2_PIN , OUTPUT);
    programPortPinInOut(KEYPAD_3_PIN , OUTPUT);       
}


u8 getPressedKey(void){
    u8 pressedKey = UN_IDENTIFIED ,
            iterator , 
                selected_key;
      
    /*
     * logic for find out which key is pressed if any
     * outer loop iteration 1:
     *  column == KEYPAD_1_PIN
     *  checking for 
     *      KEYPAD_BTN0 or 
     *      KEYPAD_BTN4 or 
     *      KEYPAD_BTN7 or 
     *      KEYPAD_BTN_STAR
     *  inner loop iteration :
     *      iterator : start KEYPAD_A_PIN -> end KEYPAD_D_PIN
     * 
     * outer loop iteration 2:
     *  column == KEYPAD_2_PIN
     *  checking for 
     *      KEYPAD_BTN2 or 
     *      KEYPAD_BTN5 or 
     *      KEYPAD_BTN8 or 
     *      KEYPAD_BTN0
     *  inner loop iteration :
     *      iterator : start KEYPAD_A_PIN -> end KEYPAD_D_PIN
     *
     * outer loop iteration 3:
     *  column == KEYPAD_3_PIN
     *  checking for 
     *      KEYPAD_BTN3 or 
     *      KEYPAD_BTN6 or 
     *      KEYPAD_BTN9 or 
     *      KEYPAD_BTN_POUND
     *  inner loop iteration :
     *      iterator : start KEYPAD_A_PIN -> end KEYPAD_D_PIN
    */
        
    for(u8 column = KEYPAD_1_PIN ; column <= KEYPAD_3_PIN ; column++){
        
        if(column == KEYPAD_1_PIN){
            selected_key = KEYPAD_BTN1;
            writeControlSignalOnPortPin(KEYPAD_1_PIN , HIGH );
            writeControlSignalOnPortPin(KEYPAD_2_PIN , LOW );
            writeControlSignalOnPortPin(KEYPAD_3_PIN , LOW );
        }else if(column == KEYPAD_2_PIN){
            selected_key = KEYPAD_BTN2;
            writeControlSignalOnPortPin(KEYPAD_1_PIN , LOW );
            writeControlSignalOnPortPin(KEYPAD_2_PIN , HIGH );
            writeControlSignalOnPortPin(KEYPAD_3_PIN , LOW );
        }else{
            selected_key = KEYPAD_BTN3;
            writeControlSignalOnPortPin(KEYPAD_1_PIN , LOW );
            writeControlSignalOnPortPin(KEYPAD_2_PIN , LOW );
            writeControlSignalOnPortPin(KEYPAD_3_PIN , HIGH );
        }

        for(iterator = KEYPAD_A_PIN ; iterator <= KEYPAD_D_PIN ; iterator++ , 
                                                selected_key += KEY_OFFSET){
            dispalyKeyAsChar(selected_key);
            displayCharacterOnLCD(' ');            
            //loop body find if key pressed in selected column and line 
            if(scanControlPassingThroughPortPin(iterator).scanned_data){
                pressedKey = selected_key;
                turnLEDOnOff(LED0,ON);
                _delay_ms(3000);
                break;
            }
            
            _delay_ms(200);
        }
        _delay_ms(200);
        commandLCD(CLEAR_DISPLAY);
 
        //check if we that a key is pressed
        if( UN_IDENTIFIED != pressedKey ){
            break;
        }else{
            //continue to second test
        }
    }

    return pressedKey;
}

void dispalyKeyAsChar(u8 key){
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
}