#include"atmega32a.h"
#include"interfacing_connection_logic.h"

extern scan_fun_return fun_ret_status_and_data;

FUN_RETURN_STATUS initLED(u8 which_led){
    
    switch(which_led){
        
        case LED0:
            fun_ret_status_and_data.fun_return = setPortPinInOut(IOC,PIN2,HIGH);
            break;
            
        case LED1:
            fun_ret_status_and_data.fun_return = setPortPinInOut(IOC,PIN7,HIGH);
            break;
            
        case LED2:
            fun_ret_status_and_data.fun_return = setPortPinInOut(IOD,PIN2,HIGH);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data.fun_return;
}

FUN_RETURN_STATUS initBNT(u8 which_btn){
    
    switch(which_btn){
        
        case BTTN0:
            fun_ret_status_and_data.fun_return = setPortPinInOut(IOB,PIN0,LOW);
            break;
            
        case BTTN1:
            fun_ret_status_and_data.fun_return = setPortPinInOut(IOD,PIN6,LOW);
            break;
            
        case BTTN2:
            fun_ret_status_and_data.fun_return = setPortPinInOut(IOD,PIN2,LOW);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
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
        
        case BTTN0:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(INB,PIN0);
            break;
            
        case BTTN1:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(IND,PIN6);
            break;
            
        case BTTN2:
            fun_ret_status_and_data = scanControlSignalThroughPortPin(IND,PIN2);
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    return fun_ret_status_and_data;
}
