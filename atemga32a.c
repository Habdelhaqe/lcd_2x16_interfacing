/*
 * <avr/io.h> is already included
 * "common_types_defs.h" is already included
 */
#include "atmega32a.h"
#include "interfacing_connection_logic.h"

scan_fun_return fun_ret_status_and_data;

FUN_RETURN_STATUS setPortInOut(u8 port_number, u8 control_signal_configuration){
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    switch(port_number){
       
        case IOA: //configuring DDRA => Port'A'
            if(control_signal_configuration){
                DDRA = ALL_PINS_CONFIG_OUT;
            }else{
                DDRA = ALL_PINS_CONFIG_IN;
            }
            break;
        
        case IOB: //configuring DDRB => Port'B'
            if(control_signal_configuration){
                DDRB = ALL_PINS_CONFIG_OUT;
            }else{
                DDRB = ALL_PINS_CONFIG_IN;
            }
            break;

        case IOC: //configuring DDRC => Port'C'
            if(control_signal_configuration){
                DDRC = ALL_PINS_CONFIG_OUT;
            }else{
                DDRC = ALL_PINS_CONFIG_IN;
            }
            break;

        case IOD: //configuring DDRD => Port'D'
            if(control_signal_configuration){
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
                                  u8 control_signal_configuration){
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    if(pin_number>7){
    
        fn_return = ERR_WRONG_PIN_NUMBER;
    
    }else{
    
        switch(port_number){
       
            case IOA: //configuring DDRA => Port'A' PINx
                if(control_signal_configuration){
                    OUT_HIGH_ON_PIN(DDRA , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRA , pin_number);
                }
                break;
        
            case IOB: //configuring DDRB => Port'B' PINx
                if(control_signal_configuration){
                    OUT_HIGH_ON_PIN(DDRB , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRB , pin_number);
                }
                break;

            case IOC: //configuring DDRC => Port'C' PINx
                if(control_signal_configuration){
                    OUT_HIGH_ON_PIN(DDRC , pin_number);
                }else{
                    OUT_LOW_ON_PIN(DDRC , pin_number);
                }
                break;

            case IOD: //configuring DDRD => Port'D' PINx
                if(control_signal_configuration){
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

//FUN_RETURN_STATUS programPortPinInOut(u8 port_pin_number, 
//                                      u8 control_signal_configuration ){
//    
//    FUN_RETURN_STATUS fn_return = NO_ERRORS;
//
//    switch(port_pin_number){
//
//        case _PA_PIN0:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN0);
//                        } 
//                        break;                        
//        case _PA_PIN1:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN1);
//                        } 
//                        break;                        
//        case _PA_PIN2:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN2);
//                        } 
//                        break;                        
//        case _PA_PIN3:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN3);
//                        } 
//                        break;                        
//        case _PA_PIN4:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN5);
//                        } 
//                        break;                        
//        case _PA_PIN5:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN5);
//                        } 
//                        break;                        
//        case _PA_PIN6:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN6);
//                        } 
//                        break;                        
//        case _PA_PIN7:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRA,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN7);
//                        }
//                        break;
//
//        case _PB_PIN0:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN0);
//                        } 
//                        break;                        
//        case _PB_PIN1:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN1);
//                        } 
//                        break;                        
//        case _PB_PIN2:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN2);
//                        } 
//                        break;                        
//        case _PB_PIN3:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN3);
//                        } 
//                        break;                        
//        case _PB_PIN4:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN5);
//                        } 
//                        break;                        
//        case _PB_PIN5:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN5);
//                        } 
//                        break;                        
//        case _PB_PIN6:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN6);
//                        } 
//                        break;                        
//        case _PB_PIN7:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRB,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN7);
//                        }
//                        break;
//        
//        case _PC_PIN0:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN0);
//                        } 
//                        break;                        
//        case _PC_PIN1:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN1);
//                        } 
//                        break;                        
//        case _PC_PIN2:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN2);
//                        } 
//                        break;                        
//        case _PC_PIN3:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN3);
//                        } 
//                        break;                        
//        case _PC_PIN4:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN5);
//                        } 
//                        break;                        
//        case _PC_PIN5:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN5);
//                        } 
//                        break;                        
//        case _PC_PIN6:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN6);
//                        } 
//                        break;                        
//        case _PC_PIN7:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRC,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN7);
//                        }
//                        break;
//
//        case _PD_PIN0:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN0);
//                        } 
//                        break;                        
//        case _PD_PIN1:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN1);
//                        } 
//                        break;                        
//        case _PD_PIN2:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN2);
//                        } 
//                        break;                        
//        case _PD_PIN3:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN3);
//                        } 
//                        break;                        
//        case _PD_PIN4:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN5);
//                        } 
//                        break;                        
//        case _PD_PIN5:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN5);
//                        } 
//                        break;                        
//        case _PD_PIN6:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN6);
//                        } 
//                        break;                        
//        case _PD_PIN7:  if(control_signal_configuration){
//                            OUT_HIGH_ON_PIN(DDRD,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN7);
//                        }
//                        break;
//                        
//        default:
//            fn_return=ERR;
//    }
//    
//    return fn_return;
//} 

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

//FUN_RETURN_STATUS writeControlSignalOnPortPin(u8 port_pin_number , 
//                                              u8 control_signal_status){
//    FUN_RETURN_STATUS fn_return = NO_ERRORS;
//    
//    switch(port_pin_number){
//
//        case _PA_PIN0:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN0);
//                        } 
//                        break;                        
//        case _PA_PIN1:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN1);
//                        } 
//                        break;                        
//        case _PA_PIN2:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN2);
//                        } 
//                        break;                        
//        case _PA_PIN3:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN3);
//                        } 
//                        break;                        
//        case _PA_PIN4:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN4);
//                        } 
//                        break;                        
//        case _PA_PIN5:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN5);
//                        } 
//                        break;                        
//        case _PA_PIN6:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN6);
//                        } 
//                        break;                        
//        case _PA_PIN7:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTA,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN7);
//                        }
//                        break;
//
//        case _PB_PIN0:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN0);
//                        } 
//                        break;                        
//        case _PB_PIN1:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN1);
//                        } 
//                        break;                        
//        case _PB_PIN2:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN2);
//                        } 
//                        break;                        
//        case _PB_PIN3:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN3);
//                        } 
//                        break;                        
//        case _PB_PIN4:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN4);
//                        } 
//                        break;                        
//        case _PB_PIN5:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN5);
//                        } 
//                        break;                        
//        case _PB_PIN6:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN6);
//                        } 
//                        break;                        
//        case _PB_PIN7:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTB,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN7);
//                        }
//                        break;
//        
//        case _PC_PIN0:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN0);
//                        } 
//                        break;                        
//        case _PC_PIN1:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN1);
//                        } 
//                        break;                        
//        case _PC_PIN2:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN2);
//                        } 
//                        break;                        
//        case _PC_PIN3:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN3);
//                        } 
//                        break;                        
//        case _PC_PIN4:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN4);
//                        } 
//                        break;                        
//        case _PC_PIN5:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN5);
//                        } 
//                        break;                        
//        case _PC_PIN6:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN6);
//                        } 
//                        break;                        
//        case _PC_PIN7:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTC,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN7);
//                        }
//                        break;
//
//        case _PD_PIN0:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN0);
//                        } 
//                        break;                        
//        case _PD_PIN1:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN1);
//                        } 
//                        break;                        
//        case _PD_PIN2:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN2);
//                        } 
//                        break;                        
//        case _PD_PIN3:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN3);
//                        } 
//                        break;                        
//        case _PD_PIN4:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN4);
//                        } 
//                        break;                        
//        case _PD_PIN5:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN5);
//                        } 
//                        break;                        
//        case _PD_PIN6:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN6);
//                        } 
//                        break;                        
//        case _PD_PIN7:  if(control_signal_status){
//                            OUT_HIGH_ON_PIN(PORTD,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN7);
//                        }
//                        break;
//                        
//        default:
//            fn_return=ERR;
//    }
//     
//    return fn_return;
//}

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

    /*
     * better approach instead of switch case latency no need for: 
     *  u8 REG_NAME = UN_IDENTIFIED; statement
     *  any switch cases block
     *  #define PINA 0
     *  #define PINB 1
     *  #define PINC 2
     *  #define PIND 3
     *  #define _ADMUX  4
     *  #define _ADCSRA 5
     *  #define _SFIOR  6
     */
     
//    PIN_NUMBER = port_pin_number;
//    if(_PA_PIN0 <= port_pin_number && _PA_PIN7 >= port_pin_number){
//        
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(PORTA , PIN_NUMBER);
//    
//    }else if(_PB_PIN0 <= port_pin_number && _PB_PIN7 >= port_pin_number){
//    
//        PIN_NUMBER -= _PB_PIN0 ;
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(PORTB , PIN_NUMBER);
//    
//    }else if(_PC_PIN0 <= port_pin_number && _PC_PIN7 >= port_pin_number){
//    
//        PIN_NUMBER -=_PC_PIN0 ;
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(PORTC , PIN_NUMBER);
//    
//    }else if(_PD_PIN0 <= port_pin_number && _PD_PIN7 >= port_pin_number){
//    
//        PIN_NUMBER -=_PD_PIN0 ;
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(PORTD , PIN_NUMBER);
//    
//    }else if(ADMUX_MUX0 <= port_pin_number && ADMUX_REFS1 >= port_pin_number){
//    
//        PIN_NUMBER -= ADMUX_MUX0 ;
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(ADMUX , PIN_NUMBER);
//    
//    }else if(ADCSRA_ADPS0 <= port_pin_number && ADCSRA_ADEN >= port_pin_number){
//    
//        PIN_NUMBER -= ADCSRA_ADPS0 ;
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(ADCSRA , PIN_NUMBER);
//    
//    }else if(SFIOR_PSR10 <= port_pin_number && SFIOR_ADTS2 >= port_pin_number){
//    
//        PIN_NUMBER -= SFIOR_PSR10 ;
//        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(SFIOR , PIN_NUMBER);
//    
//    }else{
//        fun_ret_status_and_data.fun_return = ERR;
//    }
    
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
        
        case ADMUX_MUX0 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX0  ; break;
        case ADMUX_MUX1 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX1  ; break;
        case ADMUX_MUX2 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX2  ; break;
        case ADMUX_MUX3 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX3  ; break;
        case ADMUX_MUX4 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX4  ; break;
        case ADMUX_ADLAR: REG_NAME = _ADMUX ; PIN_NUMBER = ADLAR ; break;
        case ADMUX_REFS0: REG_NAME = _ADMUX ; PIN_NUMBER = REFS0 ; break;
        case ADMUX_REFS1: REG_NAME = _ADMUX ; PIN_NUMBER = REFS1 ; break;
        
        case ADCSRA_ADPS0: REG_NAME = _ADCSRA ; PIN_NUMBER = ADPS0 ; break;
        case ADCSRA_ADPS1: REG_NAME = _ADCSRA ; PIN_NUMBER = ADPS1 ; break;
        case ADCSRA_ADPS2: REG_NAME = _ADCSRA ; PIN_NUMBER = ADPS2 ; break;
        case ADCSRA_ADIE : REG_NAME = _ADCSRA ; PIN_NUMBER = ADIE  ; break;
        case ADCSRA_ADIF : REG_NAME = _ADCSRA ; PIN_NUMBER = ADIF  ; break;
        case ADCSRA_ADATE: REG_NAME = _ADCSRA ; PIN_NUMBER = ADATE ; break;
        case ADCSRA_ADSC : REG_NAME = _ADCSRA ; PIN_NUMBER = ADSC  ; break;
        case ADCSRA_ADEN : REG_NAME = _ADCSRA ; PIN_NUMBER = ADEN  ; break;

        case SFIOR_PSR10    : REG_NAME = _SFIOR ; PIN_NUMBER = PSR10 ; break;
        case SFIOR_PSR2     : REG_NAME = _SFIOR ; PIN_NUMBER = PSR2  ; break;
        case SFIOR_PUD      : REG_NAME = _SFIOR ; PIN_NUMBER = PUD   ; break;
        case SFIOR_ACME     : REG_NAME = _SFIOR ; PIN_NUMBER = ACME  ; break;
        case SFIOR_RESERVED : REG_NAME = _SFIOR ; PIN_NUMBER = PIN4  ; break;
        case SFIOR_ADTS0    : REG_NAME = _SFIOR ; PIN_NUMBER = ADTS0 ; break;
        case SFIOR_ADTS1    : REG_NAME = _SFIOR ; PIN_NUMBER = ADTS1 ; break;
        case SFIOR_ADTS2    : REG_NAME = _SFIOR ; PIN_NUMBER = ADTS2 ; break;

        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    //SCAN SINAL THROUGH THE PORT PIN
    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
        fun_ret_status_and_data.scanned_data = 
                SCAN_SIGANL_ON_PIN(REG_NAME,PIN_NUMBER);
    }
    
    return fun_ret_status_and_data;
}

/*
 * THIS CODE IS NOT WORKING!!!!!!
 * i thought the problem was that automatic variable \c u8 REG_NAME;
 * is not suitable for holding DDRx/PORTx/PINx as they are of any of types:
 * typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
 * typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
 * typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
 * typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
 * typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
 * found in <stdint.h>
 * so i tried using these types but it does not work also
 * so work around was to use 3 @switch blocks and it worked
 * i could use only one but the macro  OUT_HIGH_ON_PIN(REG , BIT_POS)
 * gives me problems:
 *      OUT_HIGH_ON_PIN( IOA == REG_NAME ? DDRA :
                         IOB == REG_NAME ? DDRB :
                         IOC == REG_NAME ? DDRC : DDRD, BIT_POS);

 *  CAUSE OF THE EVALUATION PASSED INSIDE THE MACRO
 */
FUN_RETURN_STATUS writeControlSignalOnPortPin(u8 port_pin_number , 
                                              u8 control_signal_status){
    //initialization of fun_ret_status_and_data 
    fun_ret_status_and_data.fun_return   = NO_ERRORS;

    //u8 REG_NAME = UN_IDENTIFIED;
    u8  BIT_POS = UN_IDENTIFIED;
    
    /*
     * better approach instead of switch case latency no need for: 
     *  u8 REG_NAME = UN_IDENTIFIED; statement
     *  any switch cases block
     *  #define OUTA 0
     *  #define OUTB 1
     *  #define OUTC 2
     *  #define OUTD 3
     *  #define _ADMUX  4
     *  #define _ADCSRA 5
     *  #define _SFIOR  6
     */
     
    BIT_POS = port_pin_number;
    if(_PA_PIN0 <= port_pin_number && _PA_PIN7 >= port_pin_number){
        
        OUT_CONDITIONED_SIGNAL_ON_PIN(PORTA , BIT_POS, control_signal_status);
    
    }else if(_PB_PIN0 <= port_pin_number && _PB_PIN7 >= port_pin_number){
    
        BIT_POS -= _PB_PIN0 ;
        OUT_CONDITIONED_SIGNAL_ON_PIN(PORTB , BIT_POS, control_signal_status);
    
    }else if(_PC_PIN0 <= port_pin_number && _PC_PIN7 >= port_pin_number){
    
        BIT_POS -=_PC_PIN0 ;
        OUT_CONDITIONED_SIGNAL_ON_PIN(PORTC , BIT_POS, control_signal_status);
    
    }else if(_PD_PIN0 <= port_pin_number && _PD_PIN7 >= port_pin_number){
    
        BIT_POS -=_PD_PIN0 ;
        OUT_CONDITIONED_SIGNAL_ON_PIN(PORTD , BIT_POS, control_signal_status);
    
    }else if(ADMUX_MUX0 <= port_pin_number && ADMUX_REFS1 >= port_pin_number){
    
        BIT_POS -= ADMUX_MUX0 ;
        OUT_CONDITIONED_SIGNAL_ON_PIN(ADMUX , BIT_POS, control_signal_status);
    
    }else if(ADCSRA_ADPS0 <= port_pin_number && ADCSRA_ADEN >= port_pin_number){
    
        BIT_POS -= ADCSRA_ADPS0 ;
        OUT_CONDITIONED_SIGNAL_ON_PIN(ADCSRA , BIT_POS, control_signal_status);
    
    }else if(SFIOR_PSR10 <= port_pin_number && SFIOR_ADTS2 >= port_pin_number){
    
        BIT_POS -= SFIOR_PSR10 ;
        OUT_CONDITIONED_SIGNAL_ON_PIN(SFIOR , BIT_POS, control_signal_status);
    
    }else{
        fun_ret_status_and_data.fun_return = ERR;
    }
    
//    switch(port_pin_number){
//
//        case _PA_PIN0:  REG_NAME = OUTA ; BIT_POS = PIN0; break;
//        case _PA_PIN1:  REG_NAME = OUTA ; BIT_POS = PIN1; break;
//        case _PA_PIN2:  REG_NAME = OUTA ; BIT_POS = PIN2; break;
//        case _PA_PIN3:  REG_NAME = OUTA ; BIT_POS = PIN3; break;
//        case _PA_PIN4:  REG_NAME = OUTA ; BIT_POS = PIN4; break;
//        case _PA_PIN5:  REG_NAME = OUTA ; BIT_POS = PIN5; break;
//        case _PA_PIN6:  REG_NAME = OUTA ; BIT_POS = PIN6; break;
//        case _PA_PIN7:  REG_NAME = OUTA ; BIT_POS = PIN7; break;
//        
//        case _PB_PIN0:  REG_NAME = OUTB ; BIT_POS = PIN0; break;
//        case _PB_PIN1:  REG_NAME = OUTB ; BIT_POS = PIN1; break;
//        case _PB_PIN2:  REG_NAME = OUTB ; BIT_POS = PIN2; break;
//        case _PB_PIN3:  REG_NAME = OUTB ; BIT_POS = PIN3; break;
//        case _PB_PIN4:  REG_NAME = OUTB ; BIT_POS = PIN4; break;
//        case _PB_PIN5:  REG_NAME = OUTB ; BIT_POS = PIN5; break;
//        case _PB_PIN6:  REG_NAME = OUTB ; BIT_POS = PIN6; break;
//        case _PB_PIN7:  REG_NAME = OUTB ; BIT_POS = PIN7; break;
//        
//        case _PC_PIN0:  REG_NAME = OUTC ; BIT_POS = PIN0; break;
//        case _PC_PIN1:  REG_NAME = OUTC ; BIT_POS = PIN1; break;
//        case _PC_PIN2:  REG_NAME = OUTC ; BIT_POS = PIN2; break;
//        case _PC_PIN3:  REG_NAME = OUTC ; BIT_POS = PIN3; break;
//        case _PC_PIN4:  REG_NAME = OUTC ; BIT_POS = PIN4; break;
//        case _PC_PIN5:  REG_NAME = OUTC ; BIT_POS = PIN5; break;
//        case _PC_PIN6:  REG_NAME = OUTC ; BIT_POS = PIN6; break;
//        case _PC_PIN7:  REG_NAME = OUTC ; BIT_POS = PIN7; break;
//
//        case _PD_PIN0:  REG_NAME = OUTD ; BIT_POS = PIN0; break;
//        case _PD_PIN1:  REG_NAME = OUTD ; BIT_POS = PIN1; break;
//        case _PD_PIN2:  REG_NAME = OUTD ; BIT_POS = PIN2; break;
//        case _PD_PIN3:  REG_NAME = OUTD ; BIT_POS = PIN3; break;
//        case _PD_PIN4:  REG_NAME = OUTD ; BIT_POS = PIN4; break;
//        case _PD_PIN5:  REG_NAME = OUTD ; BIT_POS = PIN5; break;
//        case _PD_PIN6:  REG_NAME = OUTD ; BIT_POS = PIN6; break;
//        case _PD_PIN7:  REG_NAME = OUTD ; BIT_POS = PIN7; break;
//        
//        case ADMUX_MUX0 : REG_NAME = _ADMUX ; BIT_POS = MUX0  ; break;
//        case ADMUX_MUX1 : REG_NAME = _ADMUX ; BIT_POS = MUX1  ; break;
//        case ADMUX_MUX2 : REG_NAME = _ADMUX ; BIT_POS = MUX2  ; break;
//        case ADMUX_MUX3 : REG_NAME = _ADMUX ; BIT_POS = MUX3  ; break;
//        case ADMUX_MUX4 : REG_NAME = _ADMUX ; BIT_POS = MUX4  ; break;
//        case ADMUX_ADLAR: REG_NAME = _ADMUX ; BIT_POS = ADLAR ; break;
//        case ADMUX_REFS0: REG_NAME = _ADMUX ; BIT_POS = REFS0 ; break;
//        case ADMUX_REFS1: REG_NAME = _ADMUX ; BIT_POS = REFS1 ; break;
//        
//        case ADCSRA_ADPS0: REG_NAME = _ADCSRA ; BIT_POS = ADPS0 ; break;
//        case ADCSRA_ADPS1: REG_NAME = _ADCSRA ; BIT_POS = ADPS1 ; break;
//        case ADCSRA_ADPS2: REG_NAME = _ADCSRA ; BIT_POS = ADPS2 ; break;
//        case ADCSRA_ADIE : REG_NAME = _ADCSRA ; BIT_POS = ADIE  ; break;
//        case ADCSRA_ADIF : REG_NAME = _ADCSRA ; BIT_POS = ADIF  ; break;
//        case ADCSRA_ADATE: REG_NAME = _ADCSRA ; BIT_POS = ADATE ; break;
//        case ADCSRA_ADSC : REG_NAME = _ADCSRA ; BIT_POS = ADSC  ; break;
//        case ADCSRA_ADEN : REG_NAME = _ADCSRA ; BIT_POS = ADEN  ; break;
//        
//        case SFIOR_PSR10    : REG_NAME = _SFIOR ; BIT_POS = PSR10 ; break;
//        case SFIOR_PSR2     : REG_NAME = _SFIOR ; BIT_POS = PSR2  ; break;
//        case SFIOR_PUD      : REG_NAME = _SFIOR ; BIT_POS = PUD   ; break;
//        case SFIOR_ACME     : REG_NAME = _SFIOR ; BIT_POS = ACME  ; break;
//        case SFIOR_RESERVED : REG_NAME = _SFIOR ; BIT_POS = PIN4  ; break;
//        case SFIOR_ADTS0    : REG_NAME = _SFIOR ; BIT_POS = ADTS0 ; break;
//        case SFIOR_ADTS1    : REG_NAME = _SFIOR ; BIT_POS = ADTS1 ; break;
//        case SFIOR_ADTS2    : REG_NAME = _SFIOR ; BIT_POS = ADTS2 ; break;
//
//        default:
//            fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    //Place Control Signal On The Selected Port Pin
//    if(NO_ERRORS == fun_ret_status_and_data.fun_return ){
//        //no check further for REG_NAME for wrong register number is needed 
//        if(control_signal_status){
//            switch(REG_NAME){
//                case OUTA : OUT_HIGH_ON_PIN(PORTA , BIT_POS); break;
//                case OUTB : OUT_HIGH_ON_PIN(PORTB , BIT_POS); break;
//                case OUTC : OUT_HIGH_ON_PIN(PORTC , BIT_POS); break;
//                case OUTD : OUT_HIGH_ON_PIN(PORTD , BIT_POS); break;
//                case _SFIOR: OUT_HIGH_ON_PIN(SFIOR , BIT_POS); break;
//                case _ADMUX: OUT_HIGH_ON_PIN(ADMUX , BIT_POS); break;
//                case _ADCSRA: OUT_HIGH_ON_PIN(ADCSRA , BIT_POS);
//            }
//        }else{
//            switch(REG_NAME){
//                case OUTA : OUT_LOW_ON_PIN(PORTA , BIT_POS); break;
//                case OUTB : OUT_LOW_ON_PIN(PORTB , BIT_POS); break;
//                case OUTC : OUT_LOW_ON_PIN(PORTC , BIT_POS); break;
//                case OUTD : OUT_LOW_ON_PIN(PORTD , BIT_POS); break;
//                case _SFIOR: OUT_LOW_ON_PIN(SFIOR , BIT_POS); break;
//                case _ADMUX: OUT_LOW_ON_PIN(ADMUX , BIT_POS); break;
//                case _ADCSRA: OUT_LOW_ON_PIN(ADCSRA , BIT_POS);
//            }
//        }
//    }
//    
    return fun_ret_status_and_data.fun_return;
}

/*
 * THIS CODE DOESN'T CONFIGURE PORT PINS FOR O/P !!!!!!!!
 * i thought the problem was that automatic variable \c u8 REG_NAME;
 * is not suitable for holding DDRx/PORTx/PINx as they are of any of types:
 * typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
 * typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
 * typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
 * typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
 * typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
 * found in <stdint.h>
 * so i tried using these types but it does not work also
 * so work around was to use 3 @switch blocks and it worked
 * i could use only one but the macro  OUT_HIGH_ON_PIN(REG , BIT_POS)
 * gives me problems:
 *      OUT_HIGH_ON_PIN( IOA == REG_NAME ? DDRA :
                         IOB == REG_NAME ? DDRB :
                         IOC == REG_NAME ? DDRC : DDRD, BIT_POS);

 *  CAUSE OF THE EVALUATION PASSED INSIDE THE MACRO
 */
FUN_RETURN_STATUS programPortPinInOut(u8 port_pin_number, 
                                      u8 control_signal_configuration ){
    
    //initialization of fun_ret_status_and_data 
    fun_ret_status_and_data.fun_return   = NO_ERRORS;

    u8 REG_NAME = UN_IDENTIFIED ,
       BIT_POS  = UN_IDENTIFIED;
    /*
     * better approach instead of switch case latency no need for: 
     *  u8 REG_NAME = UN_IDENTIFIED; statement
     *  any switch cases block
     *  #define IOA 0
     *  #define IOB 1
     *  #define IOC 2
     *  #define I0D 3
     */
     
//    BIT_POS = port_pin_number;
//    if(_PA_PIN0 <= port_pin_number && _PA_PIN7 >= port_pin_number){
//        
//        OUT_CONDITIONED_SIGNAL_ON_PIN(DDRA , BIT_POS, control_signal_configuration);
//    
//    }else if(_PB_PIN0 <= port_pin_number && _PB_PIN7 >= port_pin_number){
//    
//        BIT_POS -= _PB_PIN0 ;
//        OUT_CONDITIONED_SIGNAL_ON_PIN(DDRB , BIT_POS, control_signal_configuration);
//    
//    }else if(_PC_PIN0 <= port_pin_number && _PC_PIN7 >= port_pin_number){
//    
//        BIT_POS -=_PC_PIN0 ;
//        OUT_CONDITIONED_SIGNAL_ON_PIN(DDRC , BIT_POS, control_signal_configuration);
//    
//    }else if(_PD_PIN0 <= port_pin_number && _PD_PIN7 >= port_pin_number){
//    
//        BIT_POS -=_PD_PIN0 ;
//        OUT_CONDITIONED_SIGNAL_ON_PIN(DDRD , BIT_POS, control_signal_configuration);
//    
//    }else{
//        fun_ret_status_and_data.fun_return = ERR;
//    }
//    
    switch(port_pin_number){

        case _PA_PIN0:  REG_NAME = IOA ; BIT_POS = PIN0; break;
        case _PA_PIN1:  REG_NAME = IOA ; BIT_POS = PIN1; break;
        case _PA_PIN2:  REG_NAME = IOA ; BIT_POS = PIN2; break;
        case _PA_PIN3:  REG_NAME = IOA ; BIT_POS = PIN3; break;
        case _PA_PIN4:  REG_NAME = IOA ; BIT_POS = PIN4; break;
        case _PA_PIN5:  REG_NAME = IOA ; BIT_POS = PIN5; break;
        case _PA_PIN6:  REG_NAME = IOA ; BIT_POS = PIN6; break;
        case _PA_PIN7:  REG_NAME = IOA ; BIT_POS = PIN7; break;
        
        case _PB_PIN0:  REG_NAME = IOB ; BIT_POS = PIN0; break;
        case _PB_PIN1:  REG_NAME = IOB ; BIT_POS = PIN1; break;
        case _PB_PIN2:  REG_NAME = IOB ; BIT_POS = PIN2; break;
        case _PB_PIN3:  REG_NAME = IOB ; BIT_POS = PIN3; break;
        case _PB_PIN4:  REG_NAME = IOB ; BIT_POS = PIN4; break;
        case _PB_PIN5:  REG_NAME = IOB ; BIT_POS = PIN5; break;
        case _PB_PIN6:  REG_NAME = IOB ; BIT_POS = PIN6; break;
        case _PB_PIN7:  REG_NAME = IOB ; BIT_POS = PIN7; break;
        
        case _PC_PIN0:  REG_NAME = IOC ; BIT_POS = PIN0; break;
        case _PC_PIN1:  REG_NAME = IOC ; BIT_POS = PIN1; break;
        case _PC_PIN2:  REG_NAME = IOC ; BIT_POS = PIN2; break;
        case _PC_PIN3:  REG_NAME = IOC ; BIT_POS = PIN3; break;
        case _PC_PIN4:  REG_NAME = IOC ; BIT_POS = PIN4; break;
        case _PC_PIN5:  REG_NAME = IOC ; BIT_POS = PIN5; break;
        case _PC_PIN6:  REG_NAME = IOC ; BIT_POS = PIN6; break;
        case _PC_PIN7:  REG_NAME = IOC ; BIT_POS = PIN7; break;

        case _PD_PIN0:  REG_NAME = IOD ; BIT_POS = PIN0; break;
        case _PD_PIN1:  REG_NAME = IOD ; BIT_POS = PIN1; break;
        case _PD_PIN2:  REG_NAME = IOD ; BIT_POS = PIN2; break;
        case _PD_PIN3:  REG_NAME = IOD ; BIT_POS = PIN3; break;
        case _PD_PIN4:  REG_NAME = IOD ; BIT_POS = PIN4; break;
        case _PD_PIN5:  REG_NAME = IOD ; BIT_POS = PIN5; break;
        case _PD_PIN6:  REG_NAME = IOD ; BIT_POS = PIN6; break;
        case _PD_PIN7:  REG_NAME = IOD ; BIT_POS = PIN7; break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    //PROGRAMMIN/CONFIGURATION/SETTING OF THE PORT PINS
    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
        //no check further for REG_NAME for wrong register number is needed 
        if(control_signal_configuration){
            switch(REG_NAME){
                case IOA : OUT_HIGH_ON_PIN(DDRA , BIT_POS); break;
                case IOB : OUT_HIGH_ON_PIN(DDRB , BIT_POS); break;
                case IOC : OUT_HIGH_ON_PIN(DDRC , BIT_POS); break;
                case IOD : OUT_HIGH_ON_PIN(DDRD , BIT_POS);          
            }
        }else{
            switch(REG_NAME){
                case IOA : OUT_LOW_ON_PIN(DDRA , BIT_POS); break;
                case IOB : OUT_LOW_ON_PIN(DDRB , BIT_POS); break;
                case IOC : OUT_LOW_ON_PIN(DDRC , BIT_POS); break;
                case IOD : OUT_LOW_ON_PIN(DDRD , BIT_POS);          
            }
        }
    }
    
    return fun_ret_status_and_data.fun_return;
}