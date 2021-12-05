#include "phone_keypad.h"
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

FUN_RETURN_STATUS driveBiasSiganlThroughKeypad(u8 keypad_1_siganl ,
                                  u8 keypad_2_siganl ,
                                  u8 keypad_3_siganl){
    //drive bias signal (HIGH) on : KEYPAD_1_PIN , KEYPAD_2_PIN ,KEYPAD_3_PIN
    
    FUN_RETURN_STATUS err_checker = NO_ERRORS;
    
    if( (HIGH == keypad_1_siganl && HIGH == keypad_2_siganl) ||
           (HIGH == keypad_1_siganl && HIGH == keypad_3_siganl) || 
                (HIGH == keypad_2_siganl && HIGH == keypad_3_siganl) ){
        err_checker = ERR;
    }
    
    if(NO_ERRORS == err_checker){
        //IGNORING THE ERROR RETURNED CAUSE I'M CALLING THE SHOOTS
        writeControlSignalOnPortPin(KEYPAD_1_PIN , keypad_1_siganl ? HIGH : LOW);
        writeControlSignalOnPortPin(KEYPAD_2_PIN , keypad_2_siganl ? HIGH : LOW);
        writeControlSignalOnPortPin(KEYPAD_3_PIN , keypad_3_siganl ? HIGH : LOW);
    }else{
        //what to do with the idiot user except to report back to the caller
    }
    return err_checker;
}

u8 getPressedKey(void){
    u8 pressedKey = UN_IDENTIFIED ,
            iterator , 
                selected_key;
    
//    typedef union col_selection{
//    
//        typedef struct {
//            u8 b0 : 1;
//            u8 b1 : 1;
//            u8 b2 : 1;
//        } bit_field;
//        
//        u8 col;
//    
//    }col_selection;
  
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
        
        driveBiasSiganlThroughKeypad( column==KEYPAD_1_PIN? HIGH : LOW , 
                                      column==KEYPAD_2_PIN? HIGH : LOW , 
                                      column==KEYPAD_3_PIN? HIGH : LOW );
        
        for(iterator = KEYPAD_A_PIN , 
            selected_key = ( column == KEYPAD_1_PIN ? KEYPAD_BTN1 : 
                           ( column == KEYPAD_2_PIN ? KEYPAD_BTN2 : 
                                                      KEYPAD_BTN3) )
                ; 
            iterator <= KEYPAD_D_PIN 
                ;
            iterator++ , selected_key += KEY_OFFSET
           ){
            
            //loop body find if key pressed in selected column and line 
            
            if(HIGH == scanControlPassingThroughPortPin(iterator).scanned_data){
                pressedKey = selected_key;
                break;
            }
            
        }
        
        //check if we that a key is pressed
        if( UN_IDENTIFIED != pressedKey ){
            break;
        }else{
            //continue to second test
        }
    }

    return pressedKey;

}
