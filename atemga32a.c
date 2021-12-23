/*
 * <avr/io.h> is already included
 * "common_types_defs.h" is already included
 */
#include "atmega32a.h"
#include "interfacing_connection_logic.h"

scan_fun_return fun_ret_status_and_data;

#define  ERR_CHECKER fun_ret_status_and_data.fun_return
#define SCANNED_DATA fun_ret_status_and_data.scanned_data

FUN_RETURN_STATUS setPortInOut(u8 port_number, u8 program_hole_port_out_or_in){
    
//    if(port_number == DDRA || port_number == DDRB || port_number == DDRC || 
//                        port_number == DDRD){
//        port_number = program_hole_port_out_or_in ? 
//                            ALL_PINS_CONFIG_OUT : ALL_PINS_CONFIG_IN ;
//        
//        return NO_ERRORS;
//    }else{
//        return ERR_WRONG_PORT_NUMBER;
//    }

    ERR_CHECKER = NO_ERRORS;
       
    switch(port_number){
       
        case IOA: //configuring DDRA => Port'A'
            if(program_hole_port_out_or_in){
                DDRA = ALL_PINS_CONFIG_OUT;
            }else{
                DDRA = ALL_PINS_CONFIG_IN;
            }
//            DDRA = program_hole_port_out_or_in ? 
//                        ALL_PINS_CONFIG_OUT : ALL_PINS_CONFIG_IN;
            break;
        
        case IOB: //configuring DDRB => Port'B'
            if(program_hole_port_out_or_in){
                DDRB = ALL_PINS_CONFIG_OUT;
            }else{
                DDRB = ALL_PINS_CONFIG_IN;
            }
//            DDRB = program_hole_port_out_or_in ? 
//                        ALL_PINS_CONFIG_OUT : ALL_PINS_CONFIG_IN;
            
            break;

        case IOC: //configuring DDRC => Port'C'
            if(program_hole_port_out_or_in){
                DDRC = ALL_PINS_CONFIG_OUT;
            }else{
                DDRC = ALL_PINS_CONFIG_IN;
            }
//            DDRC = program_hole_port_out_or_in ? 
//                        ALL_PINS_CONFIG_OUT : ALL_PINS_CONFIG_IN;            
            break;

        case IOD: //configuring DDRD => Port'D'
            if(program_hole_port_out_or_in){
                DDRD = ALL_PINS_CONFIG_OUT;
            }else{
                DDRD = ALL_PINS_CONFIG_IN;
            }
//            DDRD = program_hole_port_out_or_in ? 
//                        ALL_PINS_CONFIG_OUT : ALL_PINS_CONFIG_IN;            
            break;
        
        default:
            ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
    }
    
    return ERR_CHECKER;
}

FUN_RETURN_STATUS setPortPinInOut(u8 port_number ,
                                  u8 pin_number , 
                                  u8 program_port_pin_out_or_in){
    
    ERR_CHECKER = NO_ERRORS;
    
    if(pin_number>PIN7 || port_number>OUTD){
    
        ERR_CHECKER = ERR_WRONG_PIN_NUMBER;
    
    }else{
        port_number = (port_number == IOA) ? DDRA : 
                            (port_number == IOB) ? DDRB : 
                                (port_number == IOC) ? DDRC : DDRD;
        
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN( port_number , 
                                       pin_number , 
                                       program_port_pin_out_or_in);

//        switch(port_number){
//       
//            case IOA: //configuring DDRA => Port'A' PINx
////                if(program_port_pin_out_or_in){
////                    OUT_HIGH_ON_PIN(DDRA , pin_number);
////                }else{
////                    OUT_LOW_ON_PIN(DDRA , pin_number);
////                }
//                OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(DDRA,pin_number,program_port_pin_out_or_in);
//                break;
//        
//            case IOB: //configuring DDRB => Port'B' PINx
////                if(program_port_pin_out_or_in){
////                    OUT_HIGH_ON_PIN(DDRB , pin_number);
////                }else{
////                    OUT_LOW_ON_PIN(DDRB , pin_number);
////                }
//                OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(DDRA,pin_number,program_port_pin_out_or_in);
//                break;
//
//            case IOC: //configuring DDRC => Port'C' PINx
//                if(program_port_pin_out_or_in){
//                    OUT_HIGH_ON_PIN(DDRC , pin_number);
//                }else{
//                    OUT_LOW_ON_PIN(DDRC , pin_number);
//                }
//                break;
//
//            case IOD: //configuring DDRD => Port'D' PINx
//                if(program_port_pin_out_or_in){
//                    OUT_HIGH_ON_PIN(DDRD , pin_number);
//                }else{
//                    OUT_LOW_ON_PIN(DDRD , pin_number);
//                }
//                break;
//        
//            default:
//                ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
//        }      
    }
    return ERR_CHECKER;
}

FUN_RETURN_STATUS outControlSignalThroughPort(u8 port_number, u8 output_signal){

//    if(port_number == PORTA || port_number == PORTB || port_number == PORTC || 
//                        port_number == PORTD){
//        port_number = output_signal;
//        
//        return NO_ERRORS;
//    }else{
//        return ERR_WRONG_PORT_NUMBER;
//    }
//
    ERR_CHECKER = NO_ERRORS;
    
    switch(port_number){
       
        case OUTA: //Output Through Port'A'
            PORTA = output_signal;
            break;
        
        case OUTB: //Output Through Port'B'
            PORTB = output_signal; 
            break;
            
        case OUTC: //Output Through Port'C'
            PORTC = output_signal;
            break;

        case OUTD: //Output Through Port'D'
            PORTD = output_signal;
            break;
        
        default:
            ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
    }
    
    return ERR_CHECKER;    
}

FUN_RETURN_STATUS outControlSignalThroughPortPin(u8 port_number , 
                                                 u8 pin_number, 
                                                 u8 output_signal_high_or_low){

    ERR_CHECKER = NO_ERRORS;
    
    if(pin_number>PIN7 || port_number>OUTD){
    
        ERR_CHECKER = ERR_WRONG_PIN_NUMBER;
    
    }else{
        port_number = (port_number == OUTA) ? PORTA : 
                            (port_number == OUTB) ? PORTB : 
                                (port_number == OUTC) ? PORTC : PORTD;
        
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN( port_number, 
                                       pin_number , 
                                       output_signal_high_or_low);
    }
//        switch(port_number){
//       
//            case OUTA: //Output Through Port'A' PINx
//                if(output_signal_high_or_low){
//                    OUT_HIGH_ON_PIN(PORTA , pin_number);
//                }else{
//                    OUT_LOW_ON_PIN(PORTA , pin_number);
//                }
//                break;
//        
//            case OUTB: //Output Through Port'B' PINx
//                if(output_signal_high_or_low){
//                    OUT_HIGH_ON_PIN(PORTB , pin_number);
//                }else{
//                    OUT_LOW_ON_PIN(PORTB , pin_number);
//                }
//                break;
//
//            case OUTC: //Output Through Port'C' PINx
//                if(output_signal_high_or_low){
//                    OUT_HIGH_ON_PIN(PORTC , pin_number);
//                }else{
//                    OUT_LOW_ON_PIN(PORTC , pin_number);
//                }
//                break;
//
//            case OUTD: //Output Through Port'D' PINx
//                if(output_signal_high_or_low){
//                    OUT_HIGH_ON_PIN(PORTD , pin_number);
//                }else{
//                    OUT_LOW_ON_PIN(PORTD , pin_number);
//                }
//                break;
//        
//            default:
//                ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
//        }
//        
//    }
    return ERR_CHECKER;
}

scan_fun_return scanControlSignalThroughPort(u8 port_number){

//    if(port_number == PINA || port_number == PINB || port_number == PINC || 
//                        port_number == PIND){
//        SCANNED_DATA = port_number ;
//        ERR_CHECKER  = NO_ERRORS;
//    }else{
//        SCANNED_DATA  = LOW;
//        ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
//    }

    //initialization of fun_ret_status_and_data
    ERR_CHECKER   = NO_ERRORS;
    SCANNED_DATA  = LOW;
        
    switch(port_number){
       
        case INA: //Scan Signal coming Through Port'A'
            SCANNED_DATA = PINA;
            break;
        
        case INB: //Scan Signal coming Through Port'B'
            SCANNED_DATA = PINB;
            break;

        case INC: //Scan Signal coming Through Port'C'
            SCANNED_DATA = PINC;
            break;

        case IND: //Scan Signal coming Through Port'D'
            SCANNED_DATA = PIND;
            break;
        
        default:
            ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
    } 
    return fun_ret_status_and_data;
}

scan_fun_return scanControlSignalThroughPortPin(u8 port_number, u8 pin_number){
    
    //initialization of fun_ret_status_and_data 
    ERR_CHECKER   = NO_ERRORS;
    SCANNED_DATA = LOW;
    
    if(pin_number>7){
    
        ERR_CHECKER = ERR_WRONG_PIN_NUMBER;
    
    }else{
        
        switch(port_number){
       
            case INA: //Scan Signal coming Through Port'A' PINx
                SCANNED_DATA = 
                        SCAN_SIGANL_ON_PIN(PINA ,pin_number);
                break;
        
            case INB: //Scan Signal coming Through Port'B' PINx
                SCANNED_DATA = 
                        SCAN_SIGANL_ON_PIN(PINB ,pin_number);
                break;

            case INC: //Scan Signal coming Through Port'C' PINx
                SCANNED_DATA = 
                        SCAN_SIGANL_ON_PIN(PINC ,pin_number);
                break;

            case IND: //Scan Signal coming Through Port'A' PINx
                SCANNED_DATA = 
                        SCAN_SIGANL_ON_PIN(PIND ,pin_number);
                break;
        
            default:
                ERR_CHECKER = ERR_WRONG_PORT_NUMBER;
        }
        
    }
    return fun_ret_status_and_data;
}

scan_fun_return scanControlPassingThroughPortPin(u8 port_pin_number){
    //initialization of fun_ret_status_and_data 
    ERR_CHECKER   = NO_ERRORS;
    SCANNED_DATA  = LOW;

    //u8   REG_NAME = UN_IDENTIFIED;
    u8 PIN_NUMBER = UN_IDENTIFIED;

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
     
    PIN_NUMBER = port_pin_number;
    if(_PA_PIN0 <= port_pin_number && _PA_PIN7 >= port_pin_number){
        
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(PORTA , PIN_NUMBER);
    
    }else if(_PB_PIN0 <= port_pin_number && _PB_PIN7 >= port_pin_number){
    
        //PIN_NUMBER -= _PB_PIN0 ;
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(PORTB , (PIN_NUMBER - _PB_PIN0) );
    
    }else if(_PC_PIN0 <= port_pin_number && _PC_PIN7 >= port_pin_number){
    
        //PIN_NUMBER -=_PC_PIN0 ;
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(PORTC , (PIN_NUMBER -_PC_PIN0) );
    
    }else if(_PD_PIN0 <= port_pin_number && _PD_PIN7 >= port_pin_number){
    
        //PIN_NUMBER -=_PD_PIN0 ;
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(PORTD , (PIN_NUMBER -_PD_PIN0) );
    
    }else if(ADMUX_MUX0 <= port_pin_number && ADMUX_REFS1 >= port_pin_number){
    
        //PIN_NUMBER -= ADMUX_MUX0 ;
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(ADMUX , (PIN_NUMBER - ADMUX_MUX0) );
    
    }else if(ADCSRA_ADPS0 <= port_pin_number && ADCSRA_ADEN >= port_pin_number){
    
        //PIN_NUMBER -= ADCSRA_ADPS0 ;
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(ADCSRA , (PIN_NUMBER - ADCSRA_ADPS0) );
    
    }else if(SFIOR_PSR10 <= port_pin_number && SFIOR_ADTS2 >= port_pin_number){
    
        //PIN_NUMBER -= SFIOR_PSR10 ;
        SCANNED_DATA = SCAN_SIGANL_ON_PIN(SFIOR , (PIN_NUMBER - SFIOR_PSR10) );
    
    }else{
        ERR_CHECKER = ERR;
    }
    
//    switch(port_pin_number){
//
//        case _PA_PIN0:  REG_NAME = PINA ; PIN_NUMBER = PIN0; break;
//        case _PA_PIN1:  REG_NAME = PINA ; PIN_NUMBER = PIN1; break;
//        case _PA_PIN2:  REG_NAME = PINA ; PIN_NUMBER = PIN2; break;
//        case _PA_PIN3:  REG_NAME = PINA ; PIN_NUMBER = PIN3; break;
//        case _PA_PIN4:  REG_NAME = PINA ; PIN_NUMBER = PIN4; break;
//        case _PA_PIN5:  REG_NAME = PINA ; PIN_NUMBER = PIN5; break;
//        case _PA_PIN6:  REG_NAME = PINA ; PIN_NUMBER = PIN6; break;
//        case _PA_PIN7:  REG_NAME = PINA ; PIN_NUMBER = PIN7; break;
//        
//        case _PB_PIN0:  REG_NAME = PINB ; PIN_NUMBER = PIN0; break;
//        case _PB_PIN1:  REG_NAME = PINB ; PIN_NUMBER = PIN1; break;
//        case _PB_PIN2:  REG_NAME = PINB ; PIN_NUMBER = PIN2; break;
//        case _PB_PIN3:  REG_NAME = PINB ; PIN_NUMBER = PIN3; break;
//        case _PB_PIN4:  REG_NAME = PINB ; PIN_NUMBER = PIN4; break;
//        case _PB_PIN5:  REG_NAME = PINB ; PIN_NUMBER = PIN5; break;
//        case _PB_PIN6:  REG_NAME = PINB ; PIN_NUMBER = PIN6; break;
//        case _PB_PIN7:  REG_NAME = PINB ; PIN_NUMBER = PIN7; break;
//        
//        case _PC_PIN0:  REG_NAME = PINC ; PIN_NUMBER = PIN0; break;
//        case _PC_PIN1:  REG_NAME = PINC ; PIN_NUMBER = PIN1; break;
//        case _PC_PIN2:  REG_NAME = PINC ; PIN_NUMBER = PIN2; break;
//        case _PC_PIN3:  REG_NAME = PINC ; PIN_NUMBER = PIN3; break;
//        case _PC_PIN4:  REG_NAME = PINC ; PIN_NUMBER = PIN4; break;
//        case _PC_PIN5:  REG_NAME = PINC ; PIN_NUMBER = PIN5; break;
//        case _PC_PIN6:  REG_NAME = PINC ; PIN_NUMBER = PIN6; break;
//        case _PC_PIN7:  REG_NAME = PINC ; PIN_NUMBER = PIN7; break;
//
//        case _PD_PIN0:  REG_NAME = PIND ; PIN_NUMBER = PIN0; break;
//        case _PD_PIN1:  REG_NAME = PIND ; PIN_NUMBER = PIN1; break;
//        case _PD_PIN2:  REG_NAME = PIND ; PIN_NUMBER = PIN2; break;
//        case _PD_PIN3:  REG_NAME = PIND ; PIN_NUMBER = PIN3; break;
//        case _PD_PIN4:  REG_NAME = PIND ; PIN_NUMBER = PIN4; break;
//        case _PD_PIN5:  REG_NAME = PIND ; PIN_NUMBER = PIN5; break;
//        case _PD_PIN6:  REG_NAME = PIND ; PIN_NUMBER = PIN6; break;
//        case _PD_PIN7:  REG_NAME = PIND ; PIN_NUMBER = PIN7; break;
//        
//        case ADMUX_MUX0 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX0  ; break;
//        case ADMUX_MUX1 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX1  ; break;
//        case ADMUX_MUX2 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX2  ; break;
//        case ADMUX_MUX3 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX3  ; break;
//        case ADMUX_MUX4 : REG_NAME = _ADMUX ; PIN_NUMBER = MUX4  ; break;
//        case ADMUX_ADLAR: REG_NAME = _ADMUX ; PIN_NUMBER = ADLAR ; break;
//        case ADMUX_REFS0: REG_NAME = _ADMUX ; PIN_NUMBER = REFS0 ; break;
//        case ADMUX_REFS1: REG_NAME = _ADMUX ; PIN_NUMBER = REFS1 ; break;
//        
//        case ADCSRA_ADPS0: REG_NAME = _ADCSRA ; PIN_NUMBER = ADPS0 ; break;
//        case ADCSRA_ADPS1: REG_NAME = _ADCSRA ; PIN_NUMBER = ADPS1 ; break;
//        case ADCSRA_ADPS2: REG_NAME = _ADCSRA ; PIN_NUMBER = ADPS2 ; break;
//        case ADCSRA_ADIE : REG_NAME = _ADCSRA ; PIN_NUMBER = ADIE  ; break;
//        case ADCSRA_ADIF : REG_NAME = _ADCSRA ; PIN_NUMBER = ADIF  ; break;
//        case ADCSRA_ADATE: REG_NAME = _ADCSRA ; PIN_NUMBER = ADATE ; break;
//        case ADCSRA_ADSC : REG_NAME = _ADCSRA ; PIN_NUMBER = ADSC  ; break;
//        case ADCSRA_ADEN : REG_NAME = _ADCSRA ; PIN_NUMBER = ADEN  ; break;
//
//        case SFIOR_PSR10    : REG_NAME = _SFIOR ; PIN_NUMBER = PSR10 ; break;
//        case SFIOR_PSR2     : REG_NAME = _SFIOR ; PIN_NUMBER = PSR2  ; break;
//        case SFIOR_PUD      : REG_NAME = _SFIOR ; PIN_NUMBER = PUD   ; break;
//        case SFIOR_ACME     : REG_NAME = _SFIOR ; PIN_NUMBER = ACME  ; break;
//        case SFIOR_RESERVED : REG_NAME = _SFIOR ; PIN_NUMBER = PIN4  ; break;
//        case SFIOR_ADTS0    : REG_NAME = _SFIOR ; PIN_NUMBER = ADTS0 ; break;
//        case SFIOR_ADTS1    : REG_NAME = _SFIOR ; PIN_NUMBER = ADTS1 ; break;
//        case SFIOR_ADTS2    : REG_NAME = _SFIOR ; PIN_NUMBER = ADTS2 ; break;
//
//        default:
//            fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    //SCAN SINAL THROUGH THE PORT PIN
//    if(NO_ERRORS == ERR_CHECKER){
//        fun_ret_status_and_data.scanned_data = 
//                SCAN_SIGANL_ON_PIN(REG_NAME,PIN_NUMBER);
//    }
//    
    return fun_ret_status_and_data;
}

FUN_RETURN_STATUS writeControlSignalOnPortPin(u8 port_pin_number , 
                                              u8 output_signal_high_or_low){
    //initialization of fun_ret_status_and_data 
    ERR_CHECKER = NO_ERRORS;

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
        
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(PORTA , BIT_POS, output_signal_high_or_low);
    
    }else if(_PB_PIN0 <= port_pin_number && _PB_PIN7 >= port_pin_number){
    
        //BIT_POS -= _PB_PIN0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(PORTB , (BIT_POS - _PB_PIN0) , output_signal_high_or_low);
    
    }else if(_PC_PIN0 <= port_pin_number && _PC_PIN7 >= port_pin_number){
    
        //BIT_POS -=_PC_PIN0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(PORTC , (BIT_POS - _PC_PIN0) , output_signal_high_or_low);
    
    }else if(_PD_PIN0 <= port_pin_number && _PD_PIN7 >= port_pin_number){
    
        //BIT_POS -=_PD_PIN0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(PORTD , (BIT_POS - _PD_PIN0) , output_signal_high_or_low);
    
    }else if(ADMUX_MUX0 <= port_pin_number && ADMUX_REFS1 >= port_pin_number){
    
        //BIT_POS -= ADMUX_MUX0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(ADMUX , (BIT_POS - ADMUX_MUX0) , output_signal_high_or_low);
    
    }else if(ADCSRA_ADPS0 <= port_pin_number && ADCSRA_ADEN >= port_pin_number){
    
        //BIT_POS -= ADCSRA_ADPS0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(ADCSRA , (BIT_POS - ADCSRA_ADPS0) , output_signal_high_or_low);
    
    }else if(SFIOR_PSR10 <= port_pin_number && SFIOR_ADTS2 >= port_pin_number){
    
        //BIT_POS -= SFIOR_PSR10 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(SFIOR , (BIT_POS - SFIOR_PSR10) , output_signal_high_or_low);
    
    }else{
        ERR_CHECKER = ERR;
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
//        if(output_signal_high_or_low){
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
    return ERR_CHECKER;
}

FUN_RETURN_STATUS programPortPinInOut(u8 port_pin_number, 
                                      u8 program_port_pin_out_or_in ){
    
    //initialization of fun_ret_status_and_data 
    ERR_CHECKER   = NO_ERRORS;

//    u8 REG_NAME = UN_IDENTIFIED ;
    u8 BIT_POS  = UN_IDENTIFIED;
    /*
     * better approach instead of switch case latency no need for: 
     *  u8 REG_NAME = UN_IDENTIFIED; statement
     *  any switch cases block
     *  #define IOA 0
     *  #define IOB 1
     *  #define IOC 2
     *  #define I0D 3
     */
     
    BIT_POS = port_pin_number;
    if(_PA_PIN0 <= port_pin_number && _PA_PIN7 >= port_pin_number){
        
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(DDRA , BIT_POS, program_port_pin_out_or_in);
    
    }else if(_PB_PIN0 <= port_pin_number && _PB_PIN7 >= port_pin_number){
    
        //BIT_POS -= _PB_PIN0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(DDRB , (BIT_POS - _PB_PIN0) , program_port_pin_out_or_in);
    
    }else if(_PC_PIN0 <= port_pin_number && _PC_PIN7 >= port_pin_number){
    
        //BIT_POS -=_PC_PIN0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(DDRC , (BIT_POS - _PC_PIN0) , program_port_pin_out_or_in);
    
    }else if(_PD_PIN0 <= port_pin_number && _PD_PIN7 >= port_pin_number){
    
        //BIT_POS -=_PD_PIN0 ;
        OUT_HIGH_OR_LOW_SIGNAL_ON_PIN(DDRD , (BIT_POS - _PD_PIN0) , program_port_pin_out_or_in);
    
    }else{
        ERR_CHECKER = ERR;
    }
    
//    switch(port_pin_number){
//
//        case _PA_PIN0:  REG_NAME = IOA ; BIT_POS = PIN0; break;
//        case _PA_PIN1:  REG_NAME = IOA ; BIT_POS = PIN1; break;
//        case _PA_PIN2:  REG_NAME = IOA ; BIT_POS = PIN2; break;
//        case _PA_PIN3:  REG_NAME = IOA ; BIT_POS = PIN3; break;
//        case _PA_PIN4:  REG_NAME = IOA ; BIT_POS = PIN4; break;
//        case _PA_PIN5:  REG_NAME = IOA ; BIT_POS = PIN5; break;
//        case _PA_PIN6:  REG_NAME = IOA ; BIT_POS = PIN6; break;
//        case _PA_PIN7:  REG_NAME = IOA ; BIT_POS = PIN7; break;
//        
//        case _PB_PIN0:  REG_NAME = IOB ; BIT_POS = PIN0; break;
//        case _PB_PIN1:  REG_NAME = IOB ; BIT_POS = PIN1; break;
//        case _PB_PIN2:  REG_NAME = IOB ; BIT_POS = PIN2; break;
//        case _PB_PIN3:  REG_NAME = IOB ; BIT_POS = PIN3; break;
//        case _PB_PIN4:  REG_NAME = IOB ; BIT_POS = PIN4; break;
//        case _PB_PIN5:  REG_NAME = IOB ; BIT_POS = PIN5; break;
//        case _PB_PIN6:  REG_NAME = IOB ; BIT_POS = PIN6; break;
//        case _PB_PIN7:  REG_NAME = IOB ; BIT_POS = PIN7; break;
//        
//        case _PC_PIN0:  REG_NAME = IOC ; BIT_POS = PIN0; break;
//        case _PC_PIN1:  REG_NAME = IOC ; BIT_POS = PIN1; break;
//        case _PC_PIN2:  REG_NAME = IOC ; BIT_POS = PIN2; break;
//        case _PC_PIN3:  REG_NAME = IOC ; BIT_POS = PIN3; break;
//        case _PC_PIN4:  REG_NAME = IOC ; BIT_POS = PIN4; break;
//        case _PC_PIN5:  REG_NAME = IOC ; BIT_POS = PIN5; break;
//        case _PC_PIN6:  REG_NAME = IOC ; BIT_POS = PIN6; break;
//        case _PC_PIN7:  REG_NAME = IOC ; BIT_POS = PIN7; break;
//
//        case _PD_PIN0:  REG_NAME = IOD ; BIT_POS = PIN0; break;
//        case _PD_PIN1:  REG_NAME = IOD ; BIT_POS = PIN1; break;
//        case _PD_PIN2:  REG_NAME = IOD ; BIT_POS = PIN2; break;
//        case _PD_PIN3:  REG_NAME = IOD ; BIT_POS = PIN3; break;
//        case _PD_PIN4:  REG_NAME = IOD ; BIT_POS = PIN4; break;
//        case _PD_PIN5:  REG_NAME = IOD ; BIT_POS = PIN5; break;
//        case _PD_PIN6:  REG_NAME = IOD ; BIT_POS = PIN6; break;
//        case _PD_PIN7:  REG_NAME = IOD ; BIT_POS = PIN7; break;
//        
//        default:
//            fun_ret_status_and_data.fun_return = ERR;
//    }
//    
//    //PROGRAMMIN/CONFIGURATION/SETTING OF THE PORT PINS
//    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
//        //no check further for REG_NAME for wrong register number is needed 
//        if(program_port_pin_out_or_in){
//            switch(REG_NAME){
//                case IOA : OUT_HIGH_ON_PIN(DDRA , BIT_POS); break;
//                case IOB : OUT_HIGH_ON_PIN(DDRB , BIT_POS); break;
//                case IOC : OUT_HIGH_ON_PIN(DDRC , BIT_POS); break;
//                case IOD : OUT_HIGH_ON_PIN(DDRD , BIT_POS);          
//            }
//        }else{
//            switch(REG_NAME){
//                case IOA : OUT_LOW_ON_PIN(DDRA , BIT_POS); break;
//                case IOB : OUT_LOW_ON_PIN(DDRB , BIT_POS); break;
//                case IOC : OUT_LOW_ON_PIN(DDRC , BIT_POS); break;
//                case IOD : OUT_LOW_ON_PIN(DDRD , BIT_POS);          
//            }
//        }
//    }
    
    return ERR_CHECKER;
}

//FUN_RETURN_STATUS programPortPinInOut(u8 port_pin_number, 
//                                      u8 program_port_pin_out_or_in ){
//    
//    FUN_RETURN_STATUS fn_return = NO_ERRORS;
//
//    switch(port_pin_number){
//
//        case _PA_PIN0:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN0);
//                        } 
//                        break;                        
//        case _PA_PIN1:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN1);
//                        } 
//                        break;                        
//        case _PA_PIN2:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN2);
//                        } 
//                        break;                        
//        case _PA_PIN3:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN3);
//                        } 
//                        break;                        
//        case _PA_PIN4:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN5);
//                        } 
//                        break;                        
//        case _PA_PIN5:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN5);
//                        } 
//                        break;                        
//        case _PA_PIN6:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN6);
//                        } 
//                        break;                        
//        case _PA_PIN7:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRA,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRA,PIN7);
//                        }
//                        break;
//
//        case _PB_PIN0:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN0);
//                        } 
//                        break;                        
//        case _PB_PIN1:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN1);
//                        } 
//                        break;                        
//        case _PB_PIN2:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN2);
//                        } 
//                        break;                        
//        case _PB_PIN3:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN3);
//                        } 
//                        break;                        
//        case _PB_PIN4:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN5);
//                        } 
//                        break;                        
//        case _PB_PIN5:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN5);
//                        } 
//                        break;                        
//        case _PB_PIN6:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN6);
//                        } 
//                        break;                        
//        case _PB_PIN7:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRB,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRB,PIN7);
//                        }
//                        break;
//        
//        case _PC_PIN0:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN0);
//                        } 
//                        break;                        
//        case _PC_PIN1:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN1);
//                        } 
//                        break;                        
//        case _PC_PIN2:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN2);
//                        } 
//                        break;                        
//        case _PC_PIN3:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN3);
//                        } 
//                        break;                        
//        case _PC_PIN4:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN5);
//                        } 
//                        break;                        
//        case _PC_PIN5:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN5);
//                        } 
//                        break;                        
//        case _PC_PIN6:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN6);
//                        } 
//                        break;                        
//        case _PC_PIN7:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRC,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRC,PIN7);
//                        }
//                        break;
//
//        case _PD_PIN0:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN0);
//                        } 
//                        break;                        
//        case _PD_PIN1:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN1);
//                        } 
//                        break;                        
//        case _PD_PIN2:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN2);
//                        } 
//                        break;                        
//        case _PD_PIN3:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN3);
//                        } 
//                        break;                        
//        case _PD_PIN4:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN5);
//                        } 
//                        break;                        
//        case _PD_PIN5:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN5);
//                        } 
//                        break;                        
//        case _PD_PIN6:  if(program_port_pin_out_or_in){
//                            OUT_HIGH_ON_PIN(DDRD,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(DDRD,PIN6);
//                        } 
//                        break;                        
//        case _PD_PIN7:  if(program_port_pin_out_or_in){
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

//FUN_RETURN_STATUS writeControlSignalOnPortPin(u8 port_pin_number , 
//                                              u8 output_signal_high_or_low){
//    FUN_RETURN_STATUS fn_return = NO_ERRORS;
//    
//    switch(port_pin_number){
//
//        case _PA_PIN0:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN0);
//                        } 
//                        break;                        
//        case _PA_PIN1:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN1);
//                        } 
//                        break;                        
//        case _PA_PIN2:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN2);
//                        } 
//                        break;                        
//        case _PA_PIN3:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN3);
//                        } 
//                        break;                        
//        case _PA_PIN4:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN4);
//                        } 
//                        break;                        
//        case _PA_PIN5:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN5);
//                        } 
//                        break;                        
//        case _PA_PIN6:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN6);
//                        } 
//                        break;                        
//        case _PA_PIN7:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTA,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTA,PIN7);
//                        }
//                        break;
//
//        case _PB_PIN0:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN0);
//                        } 
//                        break;                        
//        case _PB_PIN1:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN1);
//                        } 
//                        break;                        
//        case _PB_PIN2:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN2);
//                        } 
//                        break;                        
//        case _PB_PIN3:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN3);
//                        } 
//                        break;                        
//        case _PB_PIN4:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN4);
//                        } 
//                        break;                        
//        case _PB_PIN5:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN5);
//                        } 
//                        break;                        
//        case _PB_PIN6:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN6);
//                        } 
//                        break;                        
//        case _PB_PIN7:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTB,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTB,PIN7);
//                        }
//                        break;
//        
//        case _PC_PIN0:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN0);
//                        } 
//                        break;                        
//        case _PC_PIN1:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN1);
//                        } 
//                        break;                        
//        case _PC_PIN2:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN2);
//                        } 
//                        break;                        
//        case _PC_PIN3:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN3);
//                        } 
//                        break;                        
//        case _PC_PIN4:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN4);
//                        } 
//                        break;                        
//        case _PC_PIN5:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN5);
//                        } 
//                        break;                        
//        case _PC_PIN6:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN6);
//                        } 
//                        break;                        
//        case _PC_PIN7:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTC,PIN7);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTC,PIN7);
//                        }
//                        break;
//
//        case _PD_PIN0:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN0);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN0);
//                        } 
//                        break;                        
//        case _PD_PIN1:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN1);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN1);
//                        } 
//                        break;                        
//        case _PD_PIN2:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN2);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN2);
//                        } 
//                        break;                        
//        case _PD_PIN3:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN3);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN3);
//                        } 
//                        break;                        
//        case _PD_PIN4:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN4);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN4);
//                        } 
//                        break;                        
//        case _PD_PIN5:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN5);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN5);
//                        } 
//                        break;                        
//        case _PD_PIN6:  if(output_signal_high_or_low){
//                            OUT_HIGH_ON_PIN(PORTD,PIN6);
//                        }else{
//                            OUT_LOW_ON_PIN(PORTD,PIN6);
//                        } 
//                        break;                        
//        case _PD_PIN7:  if(output_signal_high_or_low){
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
