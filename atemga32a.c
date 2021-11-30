/*
 * <avr/io.h> is already included
 * "common_types_defs.h" is already included
 */
#include "atmega32a.h"

scan_fun_return fun_ret_status_and_data;

FUN_RETURN_STATUS setPortInOut(u8 port_number, u8 control_siganl_configuration){
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    switch(port_number){
       
        case IOA: //configuring DDRA => Port'A'
            if(control_siganl_configuration){
                DDRA = ALL_PINS_CONFIG_OUT;
            }else{
                DDRA = ALL_PINS_CONFIG_IN;
            }
            break;
        
        case IOB: //configuring DDRB => Port'B'
            if(control_siganl_configuration){
                DDRB = ALL_PINS_CONFIG_OUT;
            }else{
                DDRB = ALL_PINS_CONFIG_IN;
            }
            break;

        case IOC: //configuring DDRC => Port'C'
            if(control_siganl_configuration){
                DDRC = ALL_PINS_CONFIG_OUT;
            }else{
                DDRC = ALL_PINS_CONFIG_IN;
            }
            break;

        case IOD: //configuring DDRD => Port'D'
            if(control_siganl_configuration){
                DDRD = ALL_PINS_CONFIG_OUT;
            }else{
                DDRD = ALL_PINS_CONFIG_IN;
            }
            break;
        
        default:
            fn_return = ERR_WRONG_PORT_NUMBER;
    }
    
    return fn_return;
}

FUN_RETURN_STATUS setPortPinInOut(u8 port_number ,
                                  u8 pin_number , 
                                  u8 control_siganl_configuration){
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    if(pin_number>7){
    
        fn_return = ERR_WRONG_PIN_NUMBER;
    
    }else{
    
        switch(port_number){
       
            case IOA: //configuring DDRA => Port'A' PINx
                if(control_siganl_configuration){
                    OUT_HIGH_ON_PIN(DDRA , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRA , pin_number);
                }
                break;
        
            case IOB: //configuring DDRB => Port'B' PINx
                if(control_siganl_configuration){
                    OUT_HIGH_ON_PIN(DDRB , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRB , pin_number);
                }
                break;

            case IOC: //configuring DDRC => Port'C' PINx
                if(control_siganl_configuration){
                    OUT_HIGH_ON_PIN(DDRC , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRC , pin_number);
                }
                break;

            case IOD: //configuring DDRD => Port'D' PINx
                if(control_siganl_configuration){
                    OUT_HIGH_ON_PIN(DDRD , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRD , pin_number);
                }
                break;
        
            default:
                fn_return = ERR_WRONG_PORT_NUMBER;
        }
        
    }
    return fn_return;
}

FUN_RETURN_STATUS outControlSignalThroughPort(u8 port_number, u8 output_control_signal){

    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    switch(port_number){
       
        case OUTA: //Output Through Port'A'
            PORTA = output_control_signal;
//            if(output_control_signal){
//                PORTA = OUT_ALL_PINS_HIGH;
//            }else{
//                PORTA = OUT_ALL_PINS_LOW;
//            }
            break;
        
        case OUTB: //Output Through Port'B'
           PORTC = output_control_signal; 
//           if(output_control_signal){
//                PORTB = OUT_ALL_PINS_HIGH;
//            }else{
//                PORTB = OUT_ALL_PINS_LOW;
//            }
            break;
            
        case OUTC: //Output Through Port'C'
            PORTC = output_control_signal;
//           if(output_control_signal){
//                PORTC = OUT_ALL_PINS_HIGH;
//            }else{
//                PORTC = OUT_ALL_PINS_LOW;
//            }
            break;

        case OUTD: //Output Through Port'D'
            PORTD = output_control_signal;
//           if(output_control_signal){
//                PORTD = OUT_ALL_PINS_HIGH;
//            }else{
//                PORTD = OUT_ALL_PINS_LOW;
//            }
            break;
        
        default:
            fn_return = ERR_WRONG_PORT_NUMBER;
    }
    
    return fn_return;
    
}

FUN_RETURN_STATUS outControlSignalThroughPortPin(u8 port_number , 
                                                 u8 pin_number, 
                                                 u8 output_control_signal){

    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    if(pin_number>7){
    
        fn_return = ERR_WRONG_PIN_NUMBER;
    
    }else{
    
        switch(port_number){
       
            case OUTA: //Output Through Port'A' PINx
                if(output_control_signal){
                    OUT_HIGH_ON_PIN(PORTA , pin_number);
                }else{
                    OUT_LOW_ON_PIN(PORTA , pin_number);
                }
                break;
        
            case OUTB: //Output Through Port'B' PINx
                if(output_control_signal){
                    OUT_HIGH_ON_PIN(PORTB , pin_number);
                }else{
                    OUT_LOW_ON_PIN(PORTB , pin_number);
                }
                break;

            case OUTC: //Output Through Port'C' PINx
                if(output_control_signal){
                    OUT_HIGH_ON_PIN(PORTC , pin_number);
                }else{
                    OUT_LOW_ON_PIN(PORTC , pin_number);
                }
                break;

            case OUTD: //Output Through Port'D' PINx
                if(output_control_signal){
                    OUT_HIGH_ON_PIN(PORTD , pin_number);
                }else{
                    OUT_LOW_ON_PIN(PORTD , pin_number);
                }
                break;
        
            default:
                fn_return = ERR_WRONG_PORT_NUMBER;
        }
        
    }
    return fn_return;
}

scan_fun_return scanControlSignalThroughPort(u8 port_number){
    
    //initialization of fun_ret_status_and_data
    fun_ret_status_and_data.fun_return   = NO_ERRORS;
    fun_ret_status_and_data.scanned_data = LOW;
        
    switch(port_number){
       
        case INA: //Scan Signal coming Through Port'A'
            fun_ret_status_and_data.scanned_data = PINA;
            break;
        
        case INB: //Scan Signal coming Through Port'B'
            fun_ret_status_and_data.scanned_data = PINB;
            break;

        case INC: //Scan Signal coming Through Port'C'
            fun_ret_status_and_data.scanned_data = PINC;
            break;

        case IND: //Scan Signal coming Through Port'D'
            fun_ret_status_and_data.scanned_data = PIND;
            break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR_WRONG_PORT_NUMBER;
    }
    
    return fun_ret_status_and_data;
}

scan_fun_return scanControlSignalThroughPortPin(u8 port_number, u8 pin_number){
    
    //initialization of fun_ret_status_and_data
    
    fun_ret_status_and_data.fun_return   = NO_ERRORS;
    fun_ret_status_and_data.scanned_data = LOW;
    
    if(pin_number>7){
    
        fun_ret_status_and_data.fun_return = ERR_WRONG_PIN_NUMBER;
    
    }else{
        
        switch(port_number){
       
            case INA: //Scan Signal coming Through Port'A' PINx
                fun_ret_status_and_data.scanned_data = 
                        SCAN_SIGANL_ON_PIN(PINA ,pin_number);
                break;
        
            case INB: //Scan Signal coming Through Port'B' PINx
                fun_ret_status_and_data.scanned_data = 
                        SCAN_SIGANL_ON_PIN(PINB ,pin_number);
                break;

            case INC: //Scan Signal coming Through Port'C' PINx
                fun_ret_status_and_data.scanned_data = 
                        SCAN_SIGANL_ON_PIN(PINC ,pin_number);
                break;

            case IND: //Scan Signal coming Through Port'A' PINx
                fun_ret_status_and_data.scanned_data = 
                        SCAN_SIGANL_ON_PIN(PIND ,pin_number);
                break;
        
            default:
                fun_ret_status_and_data.fun_return = ERR_WRONG_PORT_NUMBER;
        }
        
    }
    
    return fun_ret_status_and_data;
}
