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
    
    u8 DDRx = UN_IDENTIFIED,
       PINx = UN_IDENTIFIED;
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;

    switch(port_pin_number){

        case _PA_PIN0:  DDRx = DDRA ; PINx = PIN0; break;
        case _PA_PIN1:  DDRx = DDRA ; PINx = PIN1; break;
        case _PA_PIN2:  DDRx = DDRA ; PINx = PIN2; break;
        case _PA_PIN3:  DDRx = DDRA ; PINx = PIN3; break;
        case _PA_PIN4:  DDRx = DDRA ; PINx = PIN4; break;
        case _PA_PIN5:  DDRx = DDRA ; PINx = PIN5; break;
        case _PA_PIN6:  DDRx = DDRA ; PINx = PIN6; break;
        case _PA_PIN7:  DDRx = DDRA ; PINx = PIN7; break;
        
        case _PB_PIN0:  DDRx = DDRB ; PINx = PIN0; break;
        case _PB_PIN1:  DDRx = DDRB ; PINx = PIN1; break;
        case _PB_PIN2:  DDRx = DDRB ; PINx = PIN2; break;
        case _PB_PIN3:  DDRx = DDRB ; PINx = PIN3; break;
        case _PB_PIN4:  DDRx = DDRB ; PINx = PIN4; break;
        case _PB_PIN5:  DDRx = DDRB ; PINx = PIN5; break;
        case _PB_PIN6:  DDRx = DDRB ; PINx = PIN6; break;
        case _PB_PIN7:  DDRx = DDRB ; PINx = PIN7; break;
        
        case _PC_PIN0:  DDRx = DDRC ; PINx = PIN0; break;
        case _PC_PIN1:  DDRx = DDRC ; PINx = PIN1; break;
        case _PC_PIN2:  DDRx = DDRC ; PINx = PIN2; break;
        case _PC_PIN3:  DDRx = DDRC ; PINx = PIN3; break;
        case _PC_PIN4:  DDRx = DDRC ; PINx = PIN4; break;
        case _PC_PIN5:  DDRx = DDRC ; PINx = PIN5; break;
        case _PC_PIN6:  DDRx = DDRC ; PINx = PIN6; break;
        case _PC_PIN7:  DDRx = DDRC ; PINx = PIN7; break;

        case _PD_PIN0:  DDRx = DDRD ; PINx = PIN0; break;
        case _PD_PIN1:  DDRx = DDRD ; PINx = PIN1; break;
        case _PD_PIN2:  DDRx = DDRD ; PINx = PIN2; break;
        case _PD_PIN3:  DDRx = DDRD ; PINx = PIN3; break;
        case _PD_PIN4:  DDRx = DDRD ; PINx = PIN4; break;
        case _PD_PIN5:  DDRx = DDRD ; PINx = PIN5; break;
        case _PD_PIN6:  DDRx = DDRD ; PINx = PIN6; break;
        case _PD_PIN7:  DDRx = DDRD ; PINx = PIN7; break;
        
        default:
            fn_return=ERR;
    }
    
    //PROGRAMMIN/CONFIGURATION/SETTING OF THE PORT PINS
    if(NO_ERRORS == fn_return){
        if(control_siganl_configuration){
            OUT_HIGH_ON_PIN(DDRx,PINx);
            //DDRx |= HIGH << PINx;
        }else{
            OUT_LOW_ON_PIN(DDRx,PINx);
            //DDRx &= ~(HIGH<<PINx);
        }
    }
    
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
    u8 PORTx = UN_IDENTIFIED,
       PINx  = UN_IDENTIFIED;
    
    FUN_RETURN_STATUS fn_return = NO_ERRORS;
    
    switch(port_pin_number){

        case _PA_PIN0:  PORTx = PORTA ; PINx = PIN0; break;
        case _PA_PIN1:  PORTx = PORTA ; PINx = PIN1; break;
        case _PA_PIN2:  PORTx = PORTA ; PINx = PIN2; break;
        case _PA_PIN3:  PORTx = PORTA ; PINx = PIN3; break;
        case _PA_PIN4:  PORTx = PORTA ; PINx = PIN4; break;
        case _PA_PIN5:  PORTx = PORTA ; PINx = PIN5; break;
        case _PA_PIN6:  PORTx = PORTA ; PINx = PIN6; break;
        case _PA_PIN7:  PORTx = PORTA ; PINx = PIN7; break;
        
        case _PB_PIN0:  PORTx = PORTB ; PINx = PIN0; break;
        case _PB_PIN1:  PORTx = PORTB ; PINx = PIN1; break;
        case _PB_PIN2:  PORTx = PORTB ; PINx = PIN2; break;
        case _PB_PIN3:  PORTx = PORTB ; PINx = PIN3; break;
        case _PB_PIN4:  PORTx = PORTB ; PINx = PIN4; break;
        case _PB_PIN5:  PORTx = PORTB ; PINx = PIN5; break;
        case _PB_PIN6:  PORTx = PORTB ; PINx = PIN6; break;
        case _PB_PIN7:  PORTx = PORTB ; PINx = PIN7; break;
        
        case _PC_PIN0:  PORTx = PORTC ; PINx = PIN0; break;
        case _PC_PIN1:  PORTx = PORTC ; PINx = PIN1; break;
        case _PC_PIN2:  PORTx = PORTC ; PINx = PIN2; break;
        case _PC_PIN3:  PORTx = PORTC ; PINx = PIN3; break;
        case _PC_PIN4:  PORTx = PORTC ; PINx = PIN4; break;
        case _PC_PIN5:  PORTx = PORTC ; PINx = PIN5; break;
        case _PC_PIN6:  PORTx = PORTC ; PINx = PIN6; break;
        case _PC_PIN7:  PORTx = PORTC ; PINx = PIN7; break;

        case _PD_PIN0:  PORTx = PORTD ; PINx = PIN0; break;
        case _PD_PIN1:  PORTx = PORTD ; PINx = PIN1; break;
        case _PD_PIN2:  PORTx = PORTD ; PINx = PIN2; break;
        case _PD_PIN3:  PORTx = PORTD ; PINx = PIN3; break;
        case _PD_PIN4:  PORTx = PORTD ; PINx = PIN4; break;
        case _PD_PIN5:  PORTx = PORTD ; PINx = PIN5; break;
        case _PD_PIN6:  PORTx = PORTD ; PINx = PIN6; break;
        case _PD_PIN7:  PORTx = PORTD ; PINx = PIN7; break;
        
        default:
            fn_return=ERR;
    }
    
    //DRIVING SINAL THROUGH OUT THE PORT
    if(NO_ERRORS == fn_return){
        if(control_signal_status){
            OUT_HIGH_ON_PIN(PORTx,PINx);
        }else{
            OUT_LOW_ON_PIN(PORTx,PINx);
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

scan_fun_return scanControlPassingThroughPortPin(u8 port_pin_number){
    //initialization of fun_ret_status_and_data 
    fun_ret_status_and_data.fun_return   = NO_ERRORS;
    fun_ret_status_and_data.scanned_data = LOW;

    u8 PINx = UN_IDENTIFIED,
       PIN_NUMx = UN_IDENTIFIED;
    
    switch(port_pin_number){

        case _PA_PIN0:  PINx = PINA ; PIN_NUMx = PIN0; break;
        case _PA_PIN1:  PINx = PINA ; PIN_NUMx = PIN1; break;
        case _PA_PIN2:  PINx = PINA ; PIN_NUMx = PIN2; break;
        case _PA_PIN3:  PINx = PINA ; PIN_NUMx = PIN3; break;
        case _PA_PIN4:  PINx = PINA ; PIN_NUMx = PIN4; break;
        case _PA_PIN5:  PINx = PINA ; PIN_NUMx = PIN5; break;
        case _PA_PIN6:  PINx = PINA ; PIN_NUMx = PIN6; break;
        case _PA_PIN7:  PINx = PINA ; PIN_NUMx = PIN7; break;
        
        case _PB_PIN0:  PINx = PINB ; PIN_NUMx = PIN0; break;
        case _PB_PIN1:  PINx = PINB ; PIN_NUMx = PIN1; break;
        case _PB_PIN2:  PINx = PINB ; PIN_NUMx = PIN2; break;
        case _PB_PIN3:  PINx = PINB ; PIN_NUMx = PIN3; break;
        case _PB_PIN4:  PINx = PINB ; PIN_NUMx = PIN4; break;
        case _PB_PIN5:  PINx = PINB ; PIN_NUMx = PIN5; break;
        case _PB_PIN6:  PINx = PINB ; PIN_NUMx = PIN6; break;
        case _PB_PIN7:  PINx = PINB ; PIN_NUMx = PIN7; break;
        
        case _PC_PIN0:  PINx = PINC ; PIN_NUMx = PIN0; break;
        case _PC_PIN1:  PINx = PINC ; PIN_NUMx = PIN1; break;
        case _PC_PIN2:  PINx = PINC ; PIN_NUMx = PIN2; break;
        case _PC_PIN3:  PINx = PINC ; PIN_NUMx = PIN3; break;
        case _PC_PIN4:  PINx = PINC ; PIN_NUMx = PIN4; break;
        case _PC_PIN5:  PINx = PINC ; PIN_NUMx = PIN5; break;
        case _PC_PIN6:  PINx = PINC ; PIN_NUMx = PIN6; break;
        case _PC_PIN7:  PINx = PINC ; PIN_NUMx = PIN7; break;

        case _PD_PIN0:  PINx = PIND ; PIN_NUMx = PIN0; break;
        case _PD_PIN1:  PINx = PIND ; PIN_NUMx = PIN1; break;
        case _PD_PIN2:  PINx = PIND ; PIN_NUMx = PIN2; break;
        case _PD_PIN3:  PINx = PIND ; PIN_NUMx = PIN3; break;
        case _PD_PIN4:  PINx = PIND ; PIN_NUMx = PIN4; break;
        case _PD_PIN5:  PINx = PIND ; PIN_NUMx = PIN5; break;
        case _PD_PIN6:  PINx = PIND ; PIN_NUMx = PIN6; break;
        case _PD_PIN7:  PINx = PIND ; PIN_NUMx = PIN7; break;
        
        default:
            fun_ret_status_and_data.fun_return = ERR;
    }
    
    //SCAN SINAL THROUGH THE PORT PIN
    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
        fun_ret_status_and_data.scanned_data = SCAN_SIGANL_ON_PIN(PINx,PIN_NUMx);
    }
    
    return fun_ret_status_and_data;
}
