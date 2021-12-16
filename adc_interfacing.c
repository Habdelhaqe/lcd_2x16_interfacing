#include"adc_interfacing.h"
#include "interfacing_connection_logic.h"

extern scan_fun_return fun_ret_status_and_data;

#define ERR_CHECKER fun_ret_status_and_data.fun_return
#define SCANNED_DATA fun_ret_status_and_data.scanned_data

void onInitADC(u8 select_channel_and_mode ,
                u8 select_voltage_ref ,
                u8 select_left_or_right_adjustment ,
                u8 select_input_source_frequency){
     
    ADCSRA = 0x88 | (select_input_source_frequency & FREQUENCY_SECUIRTY_MASK);

    ADMUX = (select_channel_and_mode & CHANNEL_SECUIRTY_MASK) 
                            |
            (select_left_or_right_adjustment & LEFT_RIGHT_SECUIRTY_MASK)
                            |
            (select_voltage_ref & VOLTAGE_SECUIRTY_MASK);
 }

void onStartConversion(u8 select_auto_or_manual_trigger){
    if(SINGLE_CONVERSION_MODE == select_auto_or_manual_trigger){
        //Set BIT6 ADSC OF ADCSRA and BIT5 ADTE is Cleared 
        ADCSRA |= START_MANUAL_CONVERSION_PROCESS;
    }else{
        /*
         * configure SFIOR :TRIGGER SELECT source (Sampling Frequency)
         *  Bit7 : ADTS2
         *  Bit6 : ADTS1
         *  Bit5 : ADTS0
         *  Bit4 : Reserved must be rest/cleared
         *  Bits3:0 is rest/cleared for now!!!!
         */
        SFIOR = select_auto_or_manual_trigger & AUTO_TRIGER_SECUIRTY_MASK;
        //Set BIT6 ADSC and BIT5 ADTE OF ADCSRA 
        ADCSRA |= START_AUTO_CONVERSION_PROCESS;
    }
}

s16 onConversionComplete(void){
    s16 conversion_result;
    //find out left or right adjust is set through scanning ADMUX : ADLAR
    if(LEFT_OR_RIGHT_ADJUST){
        //left adjustment case
        conversion_result = 
                (ADCL << SHIFT_ADCL_FOR_LEFT_ADJUST) 
                            | 
                (ADCH << ADLAR_ADCH_SHIFT);
        //safer may be faster
//        *(u8 *)(&conversion_result) = (ADCL << SHIFT_ADCL_FOR_LEFT_ADJUST);  
//        *((u8 *)(&conversion_result)+1) = ADCH;        
    }else{
        //right adjustment case
        //conversion_result = ADCL | (ADCH << ADLAR_ADCH_SHIFT);
        //safer may be faster
        *(u8 *)(&conversion_result) = ADCL;  
        *((u8 *)(&conversion_result)+1) = ADCH;        
    }
    return conversion_result;
}

s16 onConversionCompleteUsingPolling(void){     

    s16 conversion_output;
    /*
     * you should clear/rest ADIE(ADCSRA) to disable HW calling for ISR
     * even If The Application Layer implemented it
     * 
     * check for ADIF(ADCSRA):
     *  set(1) then the CONVERSION is COMPLETED and ADCH ,ADCL is UPDATED
     *      you should represent the data call @onConversionComplete();
     *  rest(0) then represent false data for the caller to check against
     *      example :     #define ERR_SELECTING_CONVERSION_MODE 0x8000
     */
    
    if(IS_CONVERSION_STARTED && IS_CONVERSION_COMPLETED){
        conversion_output = onConversionComplete();
        /*
         * as i saw examples they all relay on HW clearing the ADIF and
         * ADSC after the read is complete (ADCL then ADCH is read)
         * clearing the Interrupt flag setting the ADIF(ADCSRA) manually cause 
         * the code already satisfied the caller and represented the conversion 
         * data
        */
        //CLEAR_INTEERUPT;
        //CLEAR_BIT(ADCSRA,ADSC);   
    }else{
        conversion_output = CONVERSION_PROCESS_NOT_COMPLETE;    
    }
    return conversion_output;
}

s16 onConversionCompleteUsingPollingSpeedy(void){

    return ( /*IS_CONVERSION_STARTED &&*/ IS_CONVERSION_COMPLETED) ? 
                onConversionComplete()  
                        :
                LEFT_OR_RIGHT_ADJUST ? 
                    CONVERSION_PROCESS_NOT_COMPLETE_LEFT_ADJUST 
                            : 
                        CONVERSION_PROCESS_NOT_COMPLETE;
}
 
//FUN_RETURN_STATUS checkForSelectedChannel(u8 selected_channel){
//    return ADC_VOLTAGE_0V_GND >= selected_channel && 
//                 ADC_CHANNEL0 <= selected_channel  ? NO_ERRORS : ERR;
//}

//FUN_RETURN_STATUS checkForSelectedVoltage(u8 selected_voltage){
//    /*
//     *the choice must take in concidration the cycles count for using:
//     *  >= or != statement and how compilers compiles it into machine/assembly
//     *  instruction(s) so to compare using
//     *  2(>=) or 4(!=)  statements 
//     *  
//     */
//    
//    //this is to checks only should take less cycles but can't function now
////    return VOLTAGE_Internal_2_56_V >= selected_voltage && 
////                      VOLTAGE_AREF <= selected_voltage  ? NO_ERRORS : ERR;
//    
//    //4 checks should take more cycles
//    return VOLTAGE_AREF == selected_voltage ||
//           VOLTAGE_AVCC == selected_voltage ||
//		   VOLATGE_RESERVED == selected_voltage ||	
//           VOLTAGE_Internal_2_56_V == selected_voltage ? NO_ERRORS :ERR;
//}

//FUN_RETURN_STATUS checkForSelectedFrequency(u8 selected_frequency){
//    return PRESCALER_CLK_BY_128 >= selected_frequency && 
//           PRESCALER_CLK_BY_2   <= selected_frequency  ? NO_ERRORS : ERR;
//}

//FUN_RETURN_STATUS checkForSelectedConversionMode(u8 selected_conversion_mode){
//    /*
//     * ~GET_BIT(selected_conversion_mode , RESERVED_BIT_4_NUMBER) 
//     *  checks for RESERVED_BIT TO BE 0 => TRUE
//     * No other value will pass except: 
//     * #define FREE_RUNNING_MODE             0x00 
//     * #define ANALOG_COMPARATOR_MODE        0x20 
//     * #define EXTERNAL_INTERRUPT_REQUEST    0x40 
//     * #define TIMER_COUNTER_0_COMAPRE_MATCH 0x60 
//     * #define TIMER_COUNTER_0_OVER_FLOW     0x80 
//     * #define TIMER_COUNTER_1_COMAPRE_MATCH 0xA0 
//     * #define TIMER_COUNTER_1_OVER_FLOW     0xC0 
//     * #define TIMER_COUNTER_1_CAPTURE_EVENT 0xE0 
//     * #define SINGLE_CONVERSION_MODE     0x0F 
//     */
//    return (~GET_BIT(selected_conversion_mode , RESERVED_BIT_4_NUMBER)) &&  
//		   TIMER_COUNTER_1_CAPTURE_EVENT >= selected_conversion_mode && 
//           FREE_RUNNING_MODE <= selected_conversion_mode  ? NO_ERRORS : ERR;
//}

//FUN_RETURN_STATUS initADCInternalCircuitry(u8 which_ch_mode ,
//                                           u8 voltage_ref ,
//                                           u8 left_adjust ,
//                                           u8 sampling_freq){
//
//
////    //check selected channel and mode(single channel / difference channels)    
////    fun_ret_status_and_data.fun_return = 
////            checkForSelectedChannel(which_ch_mode);
////    
////    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
////        OUT_DATA_ON_REG_CHANGE_STATES(which_ch_mode , CHANNEL_SECUIRTY_MASK);
////        OUT_DATA_ON_REG_KEEP_STATES(ADMUX , which_ch_mode);
////        
////        fun_ret_status_and_data.fun_return = 
////                checkForSelectedVoltage(voltage_ref);
////
////        if(NO_ERRORS == fun_ret_status_and_data.fun_return){
////            SHIFT_REG_DATA_LEFT(voltage_ref , REFS0);
////            OUT_DATA_ON_REG_KEEP_STATES(ADMUX , voltage_ref);
////            
////            //ADLAR SETTING IF NEEDED IT MAY CAUSE ERROR CAUSE OF THE MACRO
////            //OUT_DATA_ON_REG_KEEP_STATES(ADMUX , (HIGH<<ADLAR));
////            
////            fun_ret_status_and_data.fun_return = 
////                    checkForSelectedFrequency(sampling_freq);
////            
////            if(NO_ERRORS == fun_ret_status_and_data.fun_return){
////                OUT_DATA_ON_REG_CHANGE_STATES(sampling_freq , 
////                        FREQUENCY_SECUIRTY_MASK);
////                OUT_DATA_ON_REG_KEEP_STATES(ADCSRA , sampling_freq);
////                
////                //ENABLE INTERRUPT AS LONG AS sie() IS CALLED
////                writeControlSignalOnPortPin(ADCSRA_ADIE , HIGH);
////                
////                //CONFIGURE THE INTERRUPT
////                //?????? MANGING THE ADSCRA->ADIF
////                
////                //ENABLE THE ADC
////                writeControlSignalOnPortPin(ADCSRA_ADEN , HIGH);
////                //OUT_DATA_ON_REG_KEEP_STATES(ADCSRA , (HIGH<<ADEN) );
////                
////            }else{
////                //what an idiot!!
////            }
////            
////        }else{
////            //what an idiot!!
////        }
////    }else{
////        //what an idiot!!
////    }
//    
//    //TRYING TO OPTIMIZE OPERATION AND KEEPING EVERY THING CONFIGURABLE
//    ERR_CHECKER = checkForSelectedChannel(which_ch_mode) || 
//                    checkForSelectedVoltage(voltage_ref) || 
//                        checkForSelectedFrequency(sampling_freq);
//    //FUN_RETURN_STATUS.NO_ERRORS is 0 so any value except 0 will be an error
//    if(!ERR_CHECKER /*!ZER0 ==> NO ERROS ALL ARGUMENTS ARE SOUND*/){
//		
//        /*
//         * ADMUX configuration :
//         *  selected channel and mode => bits 4:0
//         *  selected voltage => bits 7,6
//         *  selected left/right adjust => bit 5
//         */
//        
//        COMBINE_8_BIT_REG_W_DATA_KEEP(
//
//			ADMUX 
//				, 
//
//			COMBINE_8_BIT_REG_W_DATA(
//			
//				!left_adjust ? RIGHT_ADJUST : LEFT_ADJUST 
//					, 
//                COMBINE_8_BIT_REG_W_DATA(
//        
//                    MASK_8_BIT_REG(which_ch_mode , CHANNEL_SECUIRTY_MASK)
//                        ,
//                    MASK_8_BIT_REG(voltage_ref , VOLTAGE_SECUIRTY_MASK) 
//                
//                )
//                
//			)
//
//		);
//        
//        /*
//         * ADCSRA configuration:
//         *  selected pre-scaler frequency => bits 2:0
//         *  enable ADC Circuitry => bit 7 set
//         *  enable ADC Interrupt Service => bit 3 set
//         *      so 0x88 will do both
//         */
//        
//    	COMBINE_8_BIT_REG_W_DATA_KEEP( 
//			ADCSRA
//			,
//			COMBINE_8_BIT_REG_W_DATA( 
//                MASK_8_BIT_REG(sampling_freq , FREQUENCY_SECUIRTY_MASK)
//                    , ADC_ENABLE_AND_INTERRUPT_ENABLE
//			)
//		);
//        
//    }else{
//        //what's wrong with you studio :(
//    }
//    return ERR_CHECKER;
//}

//FUN_RETURN_STATUS startConversion(u8 auto_manual_mode){
//        
//    ERR_CHECKER = checkForSelectedConversionMode(auto_manual_mode);
//    displayCharacterOnLCD('S');
//    _delay_ms(100);
//    
//    if(!ERR_CHECKER){
//        
//        //ADCSRA_ADSC MUST BE HIGH TO START CONVERSION IN WHAT EVER MODE SELECTED
//        writeControlSignalOnPortPin(ADCSRA_ADSC , HIGH);
//        
//        /*
//         * SFIOR : Bit 4 -  Reserved Bit This bit is reserved for future use in 
//         * the ATmega32A. For ensuring compatibility with future devices, 
//         * this bit must be written zero when SFIOR is written.
//         */
//        
//        //grade against studio who/it manipulates SFIOR manually
//        CLEAR_BIT ( SFIOR , RESERVED_BIT_4_NUMBER);
//
//        if(SINGLE_CONVERSION_MODE != auto_manual_mode){
//            
//            //THIS CODE CONFIGURES PIN BY PIN SO TOO MANY CYCLES WASTED
////            writeControlSignalOnPortPin(SFIOR_ADTS0 , 
////                    SCAN_SIGANL_ON_PIN(auto_manual_mode,ADTS0));
////            writeControlSignalOnPortPin(SFIOR_ADTS1 , 
////                    SCAN_SIGANL_ON_PIN(auto_manual_mode,ADTS1));
////            writeControlSignalOnPortPin(SFIOR_ADTS2 , 
////                    SCAN_SIGANL_ON_PIN(auto_manual_mode,ADTS2));
//            
//            COMBINE_8_BIT_REG_W_DATA_KEEP(
//                SFIOR 
//                    , 
//                MASK_8_BIT_REG(
//                    MASK_8_BIT_REG(auto_manual_mode , AUTO_TRIGER_SECUIRTY_MASK)
//                        ,
//                    RESERVED_BIT_4_CLEAR_MASK    
//                )
//            );
//            
//        }
//    
//    }else{
//        //WHAT THE SHIT !!!!
//    }
//    return ERR_CHECKER;
//}

//s16 conversionComplete(void){
//
//    s16 conversion_output;
//    
//    //find out if user chose left/right adjust scanning the ADMUX:ADLAR PIN
//    fun_ret_status_and_data 
//               = scanControlPassingThroughPortPin(ADMUX_ADLAR);
//        
//    if(!ERR_CHECKER){
//        if(SCANNED_DATA == HIGH){
//            //ADLAR IS SET left adjusted data
////           OUT_DATA_ON_REG_KEEP_STATES( conversion_output , 
////                    ( OUT_DATA_ON_REG_KEEP_STATES( conversion_output 
////                       , (SHIFT_REG_DATA_LEFT(ADCL , SHIFT_ADCL_FOR_LEFT_ADJUST))) ) );
//
////            conversion_output = (ADCL << SHIFT_ADCL_FOR_LEFT_ADJUST ) 
////                                            | 
////                                    (ADCH << ADLAR_ADCH_SHIFT);
//
//            //ADLAR IS SET left adjusted data
//			//CASTING IS A MUST!!! IN (u8)(SHIFT_REG_DATA_LEFT_NO_KEEP(ADCL , SHIFT_ADCL_FOR_LEFT_ADJUST)) 
//            conversion_output = 
//                    COMBINE_8_BIT_REG_W_DATA(
//                        (u8)(SHIFT_REG_DATA_LEFT_NO_KEEP(ADCL , SHIFT_ADCL_FOR_LEFT_ADJUST)) 
//                                ,
//                        (SHIFT_REG_DATA_LEFT_NO_KEEP(ADCH , ADLAR_ADCH_SHIFT)) 
//                    );
//        }else{
//            //ADLAR IS CLEARED right adjusted data
////          OUT_DATA_ON_REG_KEEP_STATES( conversion_output 
////                    , (SHIFT_REG_DATA_LEFT(ADCH , ADLAR_ADCH_SHIFT)) );
////            conversion_output = ADCL | (ADCH << ADLAR_ADCH_SHIFT);
//            conversion_output = 
//                    COMBINE_8_BIT_REG_W_DATA(
//                        ADCL 
//                            ,
//                        (SHIFT_REG_DATA_LEFT_NO_KEEP(ADCH , ADLAR_ADCH_SHIFT)) 
//                    );            
//        }
//        
//    }else{
//        //WHAT THE SHIT !!!!
//        /*
//         * reporting that conversion isn't yet completed (request reading 
//         * too soon) or there is some shit happens via o/p on the higher bits
//         * 15:10 1111 11XX XXXX XXXX => NAY VALUE IN BETN 0XFD00:OX0400
//         * OR JUST USE 0X80000 WILL ALSO SUFFICE BUT REMEMBER TO CHECK SMART
//         * USING 0X0400 THE GET_BIT(conversion_output , 10) 
//         *  IF 1 => ERROR
//         *     0 => SUCCESS IN CONVERSION GO ON WITH DATA MANIPULATION 
//         */
//        conversion_output = ERR_SELECTING_CONVERSION_MODE;
//    }
//    //return 0x03;
//    return conversion_output;
//}
