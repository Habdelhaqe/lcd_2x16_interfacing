#include"interrupt_configuration.h"

FUN_RETURN_STATUS initInterruptService(u8 interrupt_pin_number ,
                                        u8 interrupt_control_mode){
    
    FUN_RETURN_STATUS err_checker = NO_ERRORS;
    
    if( (INT0 != interrupt_pin_number && 
            INT1 != interrupt_pin_number && 
                INT2 != interrupt_pin_number) 
                    ||
            INTERRUPT_RISING_EDGE_MODE < interrupt_control_mode
                    ){
        
        err_checker = ERR;
        
    }else{
        
        //configure the interrupt signal mode
        switch(interrupt_pin_number){
            case INT1:
                SHIFT_REG_DATA_LEFT(interrupt_control_mode , 
                        INTERRUPT_INT1_SHIFT);
            case INT0: 
                //MCUCR |= interrupt_control_mode;
                OUT_DATA_ON_REG_KEEP_STATES( MCUCR , interrupt_control_mode);
                break;
            case INT2:
                if(INTERRUPT_RISING_EDGE_MODE == interrupt_control_mode){
                    OUT_HIGH_ON_PIN(MCUCSR ,ISC2);
                }else{
                    OUT_LOW_ON_PIN(MCUCSR , ISC2);
                }
        }
        
        //enable the interrupt service
        OUT_HIGH_ON_PIN(GICR , interrupt_pin_number);
    }
    
    return err_checker;
}