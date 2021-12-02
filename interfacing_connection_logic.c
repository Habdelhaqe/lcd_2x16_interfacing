#include"atmega32a.h"
#define F_CPU 16000000UL
#include"interfacing_connection_logic.h"

extern scan_fun_return fun_ret_status_and_data;

//FUN_RETURN_STATUS initLED(u8 which_led , u8 which_port){
//
//    //checking if argument are of correct value
//    if( (which_led == LED0 ||
//            which_led == LED1 ||
//                which_led == LED2) 
//                        && 
//                    (which_port == IOA ||
//                        which_port == IOB ||
//                            which_port == IOC ||
//                                which_port == IOD) ){
//    
//        //we are good to go
//        fun_ret_status_and_data.fun_return =
//                setPortPinInOut(which_port,which_led,OUTPUT);
//    }else{
//        fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS initBTN(u8 which_btn ,u8 which_port){
//
//    //checking if argument are of correct value
//    if( (which_btn == BTN0 ||
//            which_btn == BTN1 ||
//                which_btn == BTN2) 
//                        && 
//                    (which_port == IOA ||
//                        which_port == IOB ||
//                            which_port == IOC ||
//                                which_port == IOD) ){
//    
//        //we are good to go
//        fun_ret_status_and_data.fun_return =
//                setPortPinInOut(which_port,which_btn,INPUT);
//    }else{
//        fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS initLEDS(void){
//
//    if(NO_ERRORS == initLED(LED0)){
//        if(NO_ERRORS == initLED(LED1)){
//            if(NO_ERRORS == initLED(LED2)){
//                //also here nothing to do
//            }else{
//                //nothing to do for now may be call debug code
//            }
//        }else{
//            //nothing to do for now may be call debug code
//        }
//    }else{
//        //nothing to do for now may be call debug code
//    }
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS initBTNS(void){
//
//    if(NO_ERRORS == initBTN(BTN0)){
//        if(NO_ERRORS == initBTN(BTN1)){
//            if(NO_ERRORS == initBTN(BTN2)){
//                //also here nothing to do
//            }else{
//                //nothing to do for now may be call debug code
//            }
//        }else{
//            //nothing to do for now may be call debug code
//        }
//    }else{
//        //nothing to do for now may be call debug code
//    }
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS turnLEDOnOff(u8 which_led,u8 on_off_signal){
//    
//    switch(which_led){
//        
//        case LED0:
//            fun_ret_status_and_data.fun_return = 
//                    outControlSignalThroughPortPin(OUTC,LED0,on_off_signal);
//            break;
//            
//        case LED1:
//            fun_ret_status_and_data.fun_return = 
//                    outControlSignalThroughPortPin(OUTC,LED1,on_off_signal);
//            break;
//            
//        case LED2:
//            fun_ret_status_and_data.fun_return = 
//                    outControlSignalThroughPortPin(OUTD,LED2,on_off_signal);
//            break;
//        
//        default:
//            fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    return fun_ret_status_and_data.fun_return;
//}

//scan_fun_return isBTNPressed(u8 which_btn){
//    
//    switch(which_btn){
//        
//        case BTN0:
//            fun_ret_status_and_data = 
//                    scanControlSignalThroughPortPin(INB,BTN0);
//            break;
//            
//        case BTN1:
//            fun_ret_status_and_data = 
//                    scanControlSignalThroughPortPin(IND,BTN1);
//            break;
//            
//        case BTN2:
//            fun_ret_status_and_data = 
//                    scanControlSignalThroughPortPin(IND,BTN2);
//            break;
//        
//        default:
//            fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    fun_ret_status_and_data.scanned_data = 
//            fun_ret_status_and_data.scanned_data? BTN_PRESSED : BTN_UNPRSSED;
//    
//    return fun_ret_status_and_data;
//}

//scan_fun_return isLEDOnOrOFF(u8 which_led){
//    
//    switch(which_led){
//        
//        case LED0:
//            fun_ret_status_and_data = 
//                    scanControlSignalThroughPortPin(OUTC,LED0);
//            break;
//            
//        case LED1:
//            fun_ret_status_and_data = 
//                    scanControlSignalThroughPortPin(OUTC,LED1);
//            break;
//            
//        case LED2:
//            fun_ret_status_and_data = 
//                    scanControlSignalThroughPortPin(OUTD,LED2);
//            break;
//        
//        default:
//            fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    return fun_ret_status_and_data;
//}

//FUN_RETURN_STATUS configureLCDControlPins(void){
//    //LCD RS port pin configuration 
//    if(NO_ERRORS == setPortPinInOut(IOB,LCD_RS,OUTPUT) ){
//        //LCD RW port pin configuration
//        if(NO_ERRORS == setPortPinInOut(IOB,LCD_RW,OUTPUT)){
//            //LCD EN port pin configuration
//            if(NO_ERRORS == setPortPinInOut(IOB,LCD_EN,OUTPUT)){
//                //also nothing to do here yet
//            }else{
//                //nothing to do for now may be call debug code                
//            }
//        }else{
//            //nothing to do for now may be call debug code    
//        }
//    }else{
//        //nothing to do for now may be call debug code
//    }
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS configureLCDDataBusLines(void){
//    return setPortInOut(IOD,ALL_PINS_CONFIG_OUT);
//}
//FUN_RETURN_STATUS initLCD(u8 mode_LCD){
//    if(mode_LCD == _8BIT_1L_MODE || 
//            mode_LCD == _8BIT_2L_MODE || 
//                mode_LCD == _4BIT_1L_MODE || 
//                    mode_LCD == _4BIT_2L_MODE){
//        
//        //LCD operation mode
//        if(NO_ERRORS == outControlSignalThroughPort(OUTD,mode_LCD)){
//        
//            if(NO_ERRORS == outControlSignalThroughPort(OUTD,DISPLAY_ON_CUSROR_ON)){
//        
//                if(NO_ERRORS == outControlSignalThroughPort(OUTD,INC_DISPLAY_SHIFT_TO_RIGHT)){
//                
//                    if(NO_ERRORS == outControlSignalThroughPort(OUTD,CLEAR_DISPLAY)){
//                    
////                        if(NO_ERRORS == outControlSignalThroughPort(OUTD,CUSROR_HOME)){
////                            //nothing to do here yet                
////                        }else{
////                            //nothing to do for now may be call debug code
////                        }
//                        
//                    }else{
//                        //nothing to do for now may be call debug code
//                    }
//                
//                }else{
//                    //nothing to do for now may be call debug code
//                }
//        
//            }else{
//                //nothing to do for now may be call debug code        
//            }
//        
//        }else{
//            //nothing to do for now may be call debug code
//        }
//
//    }else{
//        fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS returnLCDCursorHome(void){
//    //LCD RS control signal access command register
//    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RS,CMD) ){
//   
//        //LCD RW control signal configured to write 
//        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RW,WRITE)){
//            
//            //LCD EN control signal sending control PULS
//            if(NO_ERRORS == generateLCDEnableControlPuls()){
//                
//                //write command to data bus lines
//                if(NO_ERRORS == outControlSignalThroughPort(OUTD,CUSROR_HOME)){
//                    //nothing to do here yet
//                }else{
//                    //nothing to do for now may be call debug code                
//                }
//                
//            }else{
//                //nothing to do for now may be call debug code
//            }
//            
//        }else{
//            //nothing to do for now may be call debug code
//        }
//    }else{
//        //nothing to do for now may be call debug code    
//    }
//    return fun_ret_status_and_data.fun_return;
//}

//FUN_RETURN_STATUS clearLCD(void){
//    //LCD RS control signal access command register
//    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RS,CMD) ){
//   
//        //LCD RW control signal configured to write 
//        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RW,WRITE)){
//            
//            //LCD EN control signal sending control PULS
//            if(NO_ERRORS == generateLCDEnableControlPuls()){
//                
//                //write command to data bus lines
//                if(NO_ERRORS == outControlSignalThroughPort(OUTD,CLEAR_DISPLAY)){
//                    //nothing to do here yet
//                }else{
//                    //nothing to do for now may be call debug code                
//                }
//                
//            }else{
//                //nothing to do for now may be call debug code
//            }
//            
//        }else{
//            //nothing to do for now may be call debug code
//        }
//    }else{
//        //nothing to do for now may be call debug code    
//    }
//    return fun_ret_status_and_data.fun_return;
//}

FUN_RETURN_STATUS initLED(u8 which_led ){
    
    if(LED0 == which_led || LED1 == which_led || LED2 == which_led  ){
        fun_ret_status_and_data.fun_return = 
               programPortPinInOut(which_led,OUTPUT);
    }else{
        fun_ret_status_and_data.fun_return = ERR; 
    }
        
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS initBTN(u8 which_btn){

    if(BTN0 == which_btn || BTN1 == which_btn || BTN2 == which_btn  ){
        fun_ret_status_and_data.fun_return = 
               programPortPinInOut(which_btn,INPUT);
    }else{
        fun_ret_status_and_data.fun_return = ERR; 
    }

    return fun_ret_status_and_data.fun_return;
}


void initLEDS(void){
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    initLED(LED0);
    initLED(LED1);
    initLED(LED2);
}

void initBTNS(){
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    initBTN(BTN0);
    initBTN(BTN1);
    initBTN(BTN2);
}

FUN_RETURN_STATUS turnLEDOnOff(u8 which_led,u8 on_off_signal){

    if(LED0 == which_led || LED1 == which_led || LED2 == which_led  ){
        fun_ret_status_and_data.fun_return = 
               writeControlSignalOnPortPin(which_led,on_off_signal);
    }else{
        fun_ret_status_and_data.fun_return = ERR; 
    }
     
    return fun_ret_status_and_data.fun_return;
}

scan_fun_return isBTNPressed(u8 which_btn){

    if(BTN0 == which_btn || BTN1 == which_btn || BTN2 == which_btn  ){
        fun_ret_status_and_data = 
               scanControlPassingThroughPortPin(which_btn);
    }else{
        fun_ret_status_and_data.fun_return = ERR; 
    }
   
    fun_ret_status_and_data.scanned_data = 
            fun_ret_status_and_data.scanned_data? BTN_PRESSED : BTN_UNPRSSED;
    
    return fun_ret_status_and_data;
}

scan_fun_return isLEDOnOrOFF(u8 which_led){

    if(LED0 == which_led || LED1 == which_led || LED2 == which_led  ){
        fun_ret_status_and_data =
               scanControlPassingThroughPortPin(which_led);
    }else{
        fun_ret_status_and_data.fun_return = ERR; 
    }
    
    fun_ret_status_and_data.scanned_data = 
        fun_ret_status_and_data.scanned_data? ON : OFF;

    return fun_ret_status_and_data;
}


void configureLCDControlPins(void){
    
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    
    //LCD RS port pin configuration 
    programPortPinInOut(LCD_RS,OUTPUT);

    //LCD RW port pin configuration
    programPortPinInOut(LCD_RW,OUTPUT);

    //LCD EN port pin configuration
    programPortPinInOut(LCD_EN,OUTPUT);
    
}


void configureLCDDataBusLines(void){
   
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
   programPortPinInOut(LCD_D0,OUTPUT);
   programPortPinInOut(LCD_D1,OUTPUT);
   programPortPinInOut(LCD_D2,OUTPUT);
   programPortPinInOut(LCD_D3,OUTPUT);
   programPortPinInOut(LCD_D4,OUTPUT);
   programPortPinInOut(LCD_D5,OUTPUT);
   programPortPinInOut(LCD_D6,OUTPUT);
   programPortPinInOut(LCD_D7,OUTPUT);
   
   //OR CALL THIS FOR WHOLE DDRD AS O/P 
   //setPortInOut(IOD,OUTPUT);
}

void generateLCDEnableControlPuls(void){
     //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    
    //pulse:__/-High for 10 ms-\_____________________
    writeControlSignalOnPortPin(LCD_EN,LOW);
    writeControlSignalOnPortPin(LCD_EN,HIGH);
    _delay_ms(PULSE_DELAY);
    writeControlSignalOnPortPin(LCD_EN,LOW);
}

void commandLCD(u8 pass_CMD_TO_LCD){
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    writeControlSignalOnPortPin(LCD_RW,WRITE);
    writeControlSignalOnPortPin(LCD_RS,CMD);
    outControlSignalThroughPort(OUTD,pass_CMD_TO_LCD);
    generateLCDEnableControlPuls();
}

void displayCharacterOnLCD(u8 character_toDisplay){
        //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    writeControlSignalOnPortPin(LCD_RW,WRITE);
    writeControlSignalOnPortPin(LCD_RS,DATA);
    outControlSignalThroughPort(OUTD,character_toDisplay);
    generateLCDEnableControlPuls();
}

void displayStringOnLCD(u8 *ptr_string){
    if(NULL == ptr_string){
    
    }else{
        //loop until encountering null char
//        while(ptr_string != NULL_CHAR){
//            displayCharacterOnLCD(*ptr_string);
//            ptr_string++;
//        }
        for(u8 i=0 , line=0 ; *(ptr_string+i) != NULL_CHAR ;i++ ){
            if(i>15 && !line ){
                moveCursorToLocation(2,0);
                line = 1 ;
            }
            displayCharacterOnLCD(*(ptr_string+i));
        }
    }
}

void displayINTOnLCD(int int_value_to_display){

        /*
         * the up coming code give me this warning
         * warning: pointer targets in passing argument 1 of 
         *  'displayStringOnLCD' differ in signedness [-Wpointer-sign]
         *  char (*char_buffer_to_int_value)[BUFFER_MAX_SIZE];
         */
        
    //u8 (*char_buffer_to_int_value)[BUFFER_MAX_SIZE]={NULL_CHAR};
    u8 char_buffer_to_int_value[BUFFER_MAX_SIZE]={NULL_CHAR};
    
//    itoa(int_value_to_display , 
//                /*casting to (char *) for itoa 2nd argument to overcome warning*/
//                *((char (*)[])char_buffer_to_int_value) , 
//                    DECIMAL_RADIX);
//        displayStringOnLCD(*char_buffer_to_int_value);
    itoa(int_value_to_display , *((char(*)[])&char_buffer_to_int_value) ,DECIMAL_RADIX);
        
    displayStringOnLCD(char_buffer_to_int_value);
}
void initLCD(void){
    
    //IGNORING THE ERROR RETURNED CAUSE I'M CALLING IT WITH THE CORRECT ARGS
    commandLCD(FUNCTION_SET);
    commandLCD(DISPLAY_ON_CUSROR_ON);    
    commandLCD(CLEAR_DISPLAY);
    commandLCD(LCD_OPERATION_MODE);
    commandLCD(FORCE_AT_BEGINNING);
    //commandLCD(DISPLAY_ON_CUSROR_OFF);
    
//    commandLCD(INC_DISPLAY_SHIFT_TO_RIGHT);
//    commandLCD(CUSROR_HOME);
     
}
void moveCursorToLocation(u8 row,u8 col){
    u8 address = FORCE_AT_BEGINNING;
    if(row){
        address += 0x40;
    }
    commandLCD(address+col);
}