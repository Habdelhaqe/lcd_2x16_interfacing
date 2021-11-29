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

FUN_RETURN_STATUS returnLCDCursorHome(void){
    //LCD RS control signal access command register
    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RS,CMD) ){
   
        //LCD RW control signal configured to write 
        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RW,WRITE)){
            
            //LCD EN control signal sending control PULS
            if(NO_ERRORS == generateLCDEnableControlPuls()){
                
                //write command to data bus lines
                if(NO_ERRORS == outControlSignalThroughPort(OUTD,CUSROR_HOME)){
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

FUN_RETURN_STATUS clearLCD(void){
    //LCD RS control signal access command register
    if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RS,CMD) ){
   
        //LCD RW control signal configured to write 
        if(NO_ERRORS == outControlSignalThroughPortPin(OUTB,LCD_RW,WRITE)){
            
            //LCD EN control signal sending control PULS
            if(NO_ERRORS == generateLCDEnableControlPuls()){
                
                //write command to data bus lines
                if(NO_ERRORS == outControlSignalThroughPort(OUTD,CLEAR_LCD)){
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
