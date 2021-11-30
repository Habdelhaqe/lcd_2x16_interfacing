#include"atmega32a.h"
#define F_CPU 16000000UL
#include"interfacing_connection_logic.h"

extern scan_fun_return fun_ret_status_and_data;

FUN_RETURN_STATUS initLED(u8 which_led){
    
    switch(which_led){
        
        case LED0:
            fun_ret_status_and_data.fun_return 
                    = setPortPinInOut(IOC,PIN2,OUTPUT);
            break;
            
        case LED1:
            fun_ret_status_and_data.fun_return 
                    = setPortPinInOut(IOC,PIN7,OUTPUT);
            break;
            
        case LED2:
            fun_ret_status_and_data.fun_return 
                    = setPortPinInOut(IOD,PIN2,OUTPUT);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS initBTN(u8 which_btn){
    
    switch(which_btn){
        
        case BTN0:
            fun_ret_status_and_data.fun_return = 
                    setPortPinInOut(IOB,PIN0,INPUT);
            break;
            
        case BTN1:
            fun_ret_status_and_data.fun_return = 
                    setPortPinInOut(IOD,PIN6,INPUT);
            break;
            
        case BTN2:
            fun_ret_status_and_data.fun_return = 
                    setPortPinInOut(IOD,PIN2,INPUT);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS initLEDS(void){

    if(NO_ERRORS == initLED(LED0)){
        if(NO_ERRORS == initLED(LED1)){
            if(NO_ERRORS == initLED(LED2)){
                //also here nothing to do
            }else{
                //nothing to do for now may be call debug code
            }
        }else{
            //nothing to do for now may be call debug code
        }
    }else{
        //nothing to do for now may be call debug code
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS initBTNS(void){

    if(NO_ERRORS == initBTN(BTN0)){
        if(NO_ERRORS == initBTN(BTN1)){
            if(NO_ERRORS == initBTN(BTN2)){
                //also here nothing to do
            }else{
                //nothing to do for now may be call debug code
            }
        }else{
            //nothing to do for now may be call debug code
        }
    }else{
        //nothing to do for now may be call debug code
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS signalLEDOnOff(u8 which_led,u8 on_off_signal){
    
    switch(which_led){
        
        case LED0:
            fun_ret_status_and_data.fun_return = 
                    outControlSignalThroughPortPin(OUTC,PIN2,on_off_signal);
            break;
            
        case LED1:
            fun_ret_status_and_data.fun_return = 
                    outControlSignalThroughPortPin(OUTC,PIN7,on_off_signal);
            break;
            
        case LED2:
            fun_ret_status_and_data.fun_return = 
                    outControlSignalThroughPortPin(OUTD,PIN2,on_off_signal);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data.fun_return;
}

scan_fun_return scanSignalFromBTN(u8 which_btn){
    
    switch(which_btn){
        
        case BTN0:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(INB,PIN0);
            break;
            
        case BTN1:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(IND,PIN6);
            break;
            
        case BTN2:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(IND,PIN2);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data;
}

scan_fun_return chekLEDOnOFF(u8 which_led){
    
    switch(which_led){
        
        case LED0:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(OUTC,PIN2);
            break;
            
        case LED1:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(OUTC,PIN7);
            break;
            
        case LED2:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(OUTD,PIN2);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data;
}

FUN_RETURN_STATUS configureLCDControlPins(void){
    //LCD RS port pin configuration 
    if(NO_ERRORS == setPortPinInOut(IOB,LCD_RS,OUTPUT) ){
        //LCD RW port pin configuration
        if(NO_ERRORS == setPortPinInOut(IOB,LCD_RW,OUTPUT)){
            //LCD EN port pin configuration
            if(NO_ERRORS == setPortPinInOut(IOB,LCD_EN,OUTPUT)){
                //also nothing to do here yet
            }else{
                //nothing to do for now may be call debug code                
            }
        }else{
            //nothing to do for now may be call debug code    
        }
    }else{
        //nothing to do for now may be call debug code
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS generateLCDEnableControlPuls(void){
    
    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_EN,LOW)){
        
        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_EN,HIGH)){
            
            _delay_ms(PULSE_DELAY);
            
            if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_EN,LOW)){
                //also nothing to do here yet    
            }else{
                //nothing to do for now may be call debug code           
            }
         
        }else{
            //nothing to do for now may be call debug code
        }
    
    }else{
        //nothing to do for now may be call debug code
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS commandLCD(u8 pass_CMD_TO_LCD){
    //LCD RS control signal access command register
    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RS,CMD) ){
   
        //LCD RW control signal configured to write 
        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RW,WRITE)){
            
            //write command to data bus lines
            if(NO_ERRORS == outControlSignalThroughPort(OUTD,pass_CMD_TO_LCD)){

                //LCD EN control signal sending control PULS
                if(NO_ERRORS == generateLCDEnableControlPuls()){
                    //nothing to do here yet
                }else{
                    //nothing to do for now may be call debug code                
                }
                
            }else{
                //nothing to do for now may be call debug code
            }
            
        }else{
            //nothing to do for now may be call debug code
        }
    }else{
        //nothing to do for now may be call debug code    
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS displayCharacterOnLCD(u8 character){
    //LCD RS control signal access data register
    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RS,DATA) ){
   
        //LCD RW control signal configured to write 
        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RW,WRITE)){
            
            //write command to data bus lines
            if(NO_ERRORS == outControlSignalThroughPort(OUTD,character)){

                //LCD EN control signal sending control PULS
                if(NO_ERRORS == generateLCDEnableControlPuls()){
                    //nothing to do here yet
                }else{
                    //nothing to do for now may be call debug code                
                }
                
            }else{
                //nothing to do for now may be call debug code
            }
            
        }else{
            //nothing to do for now may be call debug code
        }
    }else{
        //nothing to do for now may be call debug code    
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS displayStringOnLCD(u8 *ptr_string){
    if(NULL == ptr_string){
        fun_ret_status_and_data.fun_return=ERR;
    }else{
        //loop until encountering null char
        while(ptr_string != NULL_CHAR){
            
            if(NO_ERRORS == displayCharacterOnLCD(*ptr_string)){
                //proceed for next character in line
                ptr_string++;
                
            }else{
                //something gone wrong break for safety reasons
                break;
            }
        }
    
    }
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS displayINTOnLCD(int int_value_to_display){

    if(int_value_to_display==0){
    
        if(NO_ERRORS == displayCharacterOnLCD(NULL_CHAR)){
            //nothing to do here yet
        }else{
            //nothing to do for now may be call debug code
        }
    
    }else{
        /*
         * the up coming code give me this warning
         * warning: pointer targets in passing argument 1 of 
         *  'displayStringOnLCD' differ in signedness [-Wpointer-sign]
         *  char (*char_buffer_to_int_value)[BUFFER_MAX_SIZE];
         */
        u8 (*char_buffer_to_int_value)[BUFFER_MAX_SIZE]={NULL_CHAR};
        
        itoa(int_value_to_display , 
                /*casting to (char *) for itoa 2nd argument to overcome warning*/
                *((char (*)[])char_buffer_to_int_value) , 
                    DECIMAL_RADIX);
        
        if(NO_ERRORS == displayStringOnLCD(*char_buffer_to_int_value)){
            //nothing to do here yet
        }else{
            //nothing to do for now may be call debug code
        }
        
    }
    return fun_ret_status_and_data.fun_return;
}


FUN_RETURN_STATUS initLCD(u8 mode_LCD){
    if(mode_LCD == _8BIT_1L_MODE || 
            mode_LCD == _8BIT_2L_MODE || 
                mode_LCD == _4BIT_1L_MODE || 
                    mode_LCD == _4BIT_2L_MODE){
        
        //LCD operation mode
        if(NO_ERRORS == outControlSignalThroughPort(OUTD,mode_LCD)){
        
            if(NO_ERRORS == outControlSignalThroughPort(OUTD,DISPLAY_ON_CUSROR_ON)){
        
                if(NO_ERRORS == outControlSignalThroughPort(OUTD,INC_DISPLAY_SHIFT_TO_RIGHT)){
                
                    if(NO_ERRORS == outControlSignalThroughPort(OUTD,CLEAR_DISPLAY)){
                    
//                        if(NO_ERRORS == outControlSignalThroughPort(OUTD,CUSROR_HOME)){
//                            //nothing to do here yet                
//                        }else{
//                            //nothing to do for now may be call debug code
//                        }
                        
                    }else{
                        //nothing to do for now may be call debug code
                    }
                
                }else{
                    //nothing to do for now may be call debug code
                }
        
            }else{
                //nothing to do for now may be call debug code        
            }
        
        }else{
            //nothing to do for now may be call debug code
        }

    }else{
        fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data.fun_return;
}

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
