/*
 * <avr/io.h> is already included
 * "common_types_defs.h" is already included
 */
#include "atmega32a.h"
#include "interfacing_connection_logic.h"

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

FUN_RETURN_STATUS programPortPinInOut(u8 port_pin_number, u8 control_siganl_configuration ){
    
//    u8 REG_NAME = UN_IDENTIFIED,
//       PIN_NUMBER = UN_IDENTIFIED;
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;

    switch(port_pin_number){

        case _PA_PIN0:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN0);
                        } 
                        break;                        
        case _PA_PIN1:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN1);
                        } 
                        break;                        
        case _PA_PIN2:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN2);
                        } 
                        break;                        
        case _PA_PIN3:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN3);
                        } 
                        break;                        
        case _PA_PIN4:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN5);
                        } 
                        break;                        
        case _PA_PIN5:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN5);
                        } 
                        break;                        
        case _PA_PIN6:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN6);
                        } 
                        break;                        
        case _PA_PIN7:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRA,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(DDRA,PIN7);
                        }
                        break;

        case _PB_PIN0:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN0);
                        } 
                        break;                        
        case _PB_PIN1:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN1);
                        } 
                        break;                        
        case _PB_PIN2:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN2);
                        } 
                        break;                        
        case _PB_PIN3:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN3);
                        } 
                        break;                        
        case _PB_PIN4:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN5);
                        } 
                        break;                        
        case _PB_PIN5:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN5);
                        } 
                        break;                        
        case _PB_PIN6:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN6);
                        } 
                        break;                        
        case _PB_PIN7:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRB,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(DDRB,PIN7);
                        }
                        break;
        
        case _PC_PIN0:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN0);
                        } 
                        break;                        
        case _PC_PIN1:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN1);
                        } 
                        break;                        
        case _PC_PIN2:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN2);
                        } 
                        break;                        
        case _PC_PIN3:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN3);
                        } 
                        break;                        
        case _PC_PIN4:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN5);
                        } 
                        break;                        
        case _PC_PIN5:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN5);
                        } 
                        break;                        
        case _PC_PIN6:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN6);
                        } 
                        break;                        
        case _PC_PIN7:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRC,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(DDRC,PIN7);
                        }
                        break;

        case _PD_PIN0:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN0);
                        } 
                        break;                        
        case _PD_PIN1:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN1);
                        } 
                        break;                        
        case _PD_PIN2:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN2);
                        } 
                        break;                        
        case _PD_PIN3:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN3);
                        } 
                        break;                        
        case _PD_PIN4:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN5);
                        } 
                        break;                        
        case _PD_PIN5:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN5);
                        } 
                        break;                        
        case _PD_PIN6:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN6);
                        } 
                        break;                        
        case _PD_PIN7:  if(control_siganl_configuration){
                            OUT_HIGH_ON_PIN(DDRD,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(DDRD,PIN7);
                        }
                        break;
                        
        default:
            fn_return=ERR;
    }
    
    //PROGRAMMIN/CONFIGURATION/SETTING OF THE PORT PINS
//    if(NO_ERRORS == fn_return){
//        if(control_siganl_configuration){
//            OUT_HIGH_ON_PIN(REG_NAME,PIN_NUMBER);
//        }else{
//            OUT_LOW_ON_PIN(REG_NAME,PIN_NUMBER);
//        }
//    }
    
    return fn_return;
} 


FUN_RETURN_STATUS outControlSignalThroughPort(u8 port_number, u8 output_control_signal){

    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    switch(port_number){
       
        case OUTA: //Output Through Port'A'
            PORTA = output_control_signal;
            break;
        
        case OUTB: //Output Through Port'B'
           PORTB = output_control_signal; 
            break;
            
        case OUTC: //Output Through Port'C'
            PORTC = output_control_signal;
            break;

        case OUTD: //Output Through Port'D'
            PORTD = output_control_signal;
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

FUN_RETURN_STATUS writeControlSignalOnPortPin(u8 port_pin_number , 
                                              u8 control_signal_status){
//    u8 REG_NAME = UN_IDENTIFIED,
//       PIN_NUMBER  = UN_IDENTIFIED;
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    switch(port_pin_number){

        case _PA_PIN0:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN0);
                        } 
                        break;                        
        case _PA_PIN1:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN1);
                        } 
                        break;                        
        case _PA_PIN2:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN2);
                        } 
                        break;                        
        case _PA_PIN3:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN3);
                        } 
                        break;                        
        case _PA_PIN4:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN5);
                        } 
                        break;                        
        case _PA_PIN5:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN5);
                        } 
                        break;                        
        case _PA_PIN6:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN6);
                        } 
                        break;                        
        case _PA_PIN7:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTA,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(PORTA,PIN7);
                        }
                        break;

        case _PB_PIN0:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN0);
                        } 
                        break;                        
        case _PB_PIN1:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN1);
                        } 
                        break;                        
        case _PB_PIN2:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN2);
                        } 
                        break;                        
        case _PB_PIN3:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN3);
                        } 
                        break;                        
        case _PB_PIN4:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN5);
                        } 
                        break;                        
        case _PB_PIN5:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN5);
                        } 
                        break;                        
        case _PB_PIN6:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN6);
                        } 
                        break;                        
        case _PB_PIN7:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTB,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(PORTB,PIN7);
                        }
                        break;
        
        case _PC_PIN0:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN0);
                        } 
                        break;                        
        case _PC_PIN1:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN1);
                        } 
                        break;                        
        case _PC_PIN2:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN2);
                        } 
                        break;                        
        case _PC_PIN3:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN3);
                        } 
                        break;                        
        case _PC_PIN4:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN5);
                        } 
                        break;                        
        case _PC_PIN5:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN5);
                        } 
                        break;                        
        case _PC_PIN6:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN6);
                        } 
                        break;                        
        case _PC_PIN7:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTC,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(PORTC,PIN7);
                        }
                        break;

        case _PD_PIN0:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN0);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN0);
                        } 
                        break;                        
        case _PD_PIN1:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN1);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN1);
                        } 
                        break;                        
        case _PD_PIN2:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN2);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN2);
                        } 
                        break;                        
        case _PD_PIN3:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN3);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN3);
                        } 
                        break;                        
        case _PD_PIN4:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN4);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN5);
                        } 
                        break;                        
        case _PD_PIN5:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN5);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN5);
                        } 
                        break;                        
        case _PD_PIN6:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN6);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN6);
                        } 
                        break;                        
        case _PD_PIN7:  if(control_signal_status){
                            OUT_HIGH_ON_PIN(PORTD,PIN7);
                        }else{
                            OUT_LOW_ON_PIN(PORTD,PIN7);
                        }
                        break;
                        
        default:
            fn_return=ERR;
    }
    
    //DRIVING SINAL THROUGH OUT THE PORT
//    if(NO_ERRORS == fn_return){
//        if(control_signal_status){
//            OUT_HIGH_ON_PIN(REG_NAME,PIN_NUMBER);
//        }else{
//            OUT_LOW_ON_PIN(REG_NAME,PIN_NUMBER);
//        }
//    }
 
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

scan_fun_return scanControlPassingThroughPortPin(u8 port_pin_number){
    //initialization of fun_ret_status_and_data 
    fun_ret_status_and_data.fun_return   = NO_ERRORS;
    fun_ret_status_and_data.scanned_data = LOW;

    u8 REG_NAME = UN_IDENTIFIED,
       PIN_NUMBER = UN_IDENTIFIED;
    
    switch(port_pin_number){

        case _PA_PIN0:  REG_NAME = PINA ; PIN_NUMBER = PIN0; break;
        case _PA_PIN1:  REG_NAME = PINA ; PIN_NUMBER = PIN1; break;
        case _PA_PIN2:  REG_NAME = PINA ; PIN_NUMBER = PIN2; break;
        case _PA_PIN3:  REG_NAME = PINA ; PIN_NUMBER = PIN3; break;
        case _PA_PIN4:  REG_NAME = PINA ; PIN_NUMBER = PIN4; break;
        case _PA_PIN5:  REG_NAME = PINA ; PIN_NUMBER = PIN5; break;
        case _PA_PIN6:  REG_NAME = PINA ; PIN_NUMBER = PIN6; break;
        case _PA_PIN7:  REG_NAME = PINA ; PIN_NUMBER = PIN7; break;
        
        case _PB_PIN0:  REG_NAME = PINB ; PIN_NUMBER = PIN0; break;
        case _PB_PIN1:  REG_NAME = PINB ; PIN_NUMBER = PIN1; break;
        case _PB_PIN2:  REG_NAME = PINB ; PIN_NUMBER = PIN2; break;
        case _PB_PIN3:  REG_NAME = PINB ; PIN_NUMBER = PIN3; break;
        case _PB_PIN4:  REG_NAME = PINB ; PIN_NUMBER = PIN4; break;
        case _PB_PIN5:  REG_NAME = PINB ; PIN_NUMBER = PIN5; break;
        case _PB_PIN6:  REG_NAME = PINB ; PIN_NUMBER = PIN6; break;
        case _PB_PIN7:  REG_NAME = PINB ; PIN_NUMBER = PIN7; break;
        
        case _PC_PIN0:  REG_NAME = PINC ; PIN_NUMBER = PIN0; break;
        case _PC_PIN1:  REG_NAME = PINC ; PIN_NUMBER = PIN1; break;
        case _PC_PIN2:  REG_NAME = PINC ; PIN_NUMBER = PIN2; break;
        case _PC_PIN3:  REG_NAME = PINC ; PIN_NUMBER = PIN3; break;
        case _PC_PIN4:  REG_NAME = PINC ; PIN_NUMBER = PIN4; break;
        case _PC_PIN5:  REG_NAME = PINC ; PIN_NUMBER = PIN5; break;
        case _PC_PIN6:  REG_NAME = PINC ; PIN_NUMBER = PIN6; break;
        case _PC_PIN7:  REG_NAME = PINC ; PIN_NUMBER = PIN7; break;

        case _PD_PIN0:  REG_NAME = PIND ; PIN_NUMBER = PIN0; break;
        case _PD_PIN1:  REG_NAME = PIND ; PIN_NUMBER = PIN1; break;
        case _PD_PIN2:  REG_NAME = PIND ; PIN_NUMBER = PIN2; break;
        case _PD_PIN3:  REG_NAME = PIND ; PIN_NUMBER = PIN3; break;
        case _PD_PIN4:  REG_NAME = PIND ; PIN_NUMBER = PIN4; break;
        case _PD_PIN5:  REG_NAME = PIND ; PIN_NUMBER = PIN5; break;
        case _PD_PIN6:  REG_NAME = PIND ; PIN_NUMBER = PIN6; break;
        case _PD_PIN7:  REG_NAME = PIND ; PIN_NUMBER = PIN7; break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    //SCAN SINAL THROUGH THE PORT PIN
    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(REG_NAME,PIN_NUMBER);
    }
    
    return fun_ret_status_and_data;
}
