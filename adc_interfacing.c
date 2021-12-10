#include"adc_interfacing.h"
extern scan_fun_return fun_ret_status_and_data;


FUN_RETURN_STATUS initADCInternalCircuitry(u8 which_ch_mode ,
                                           u8 voltage_ref,
                                           u8 sampling_freq){
        
    //check selected channel and mode(single channel / difference channels)    
    fun_ret_status_and_data.fun_return = checkForSelectedChannel(which_ch_mode);
    
    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
        OUT_DATA_ON_REG_CHANGE_STATES(which_ch_mode , CHANNEL_SECUIRTY_MASK);
        OUT_DATA_ON_REG_KEEP_STATES(ADMUX , which_ch_mode);
        
        fun_ret_status_and_data.fun_return = checkForSelectedVoltage(voltage_ref);

        if(NO_ERRORS == fun_ret_status_and_data.fun_return){
            SHIFT_REG_DATA_LEFT(voltage_ref , REFS0);
            OUT_DATA_ON_REG_KEEP_STATES(ADMUX , voltage_ref);
            
            //ADLAR SETTING IF NEEDED IT MAY CAUSE ERROR CAUSE OF THE MACRO
            //OUT_DATA_ON_REG_KEEP_STATES(ADMUX , (HIGH<<ADLAR));
            
            fun_ret_status_and_data.fun_return = checkForSelectedFrequency(sampling_freq);
            
            if(NO_ERRORS == fun_ret_status_and_data.fun_return){
                OUT_DATA_ON_REG_CHANGE_STATES(sampling_freq , 
                        FREQUENCY_SECUIRTY_MASK);
                OUT_DATA_ON_REG_KEEP_STATES(ADCSRA , sampling_freq);
                
                //ENABLE INTERRUPT AS LONG AS sie() IS CALLED
                writeControlSignalOnPortPin(ADCSRA_ADIE , HIGH);
                
                //CONFIGURE THE INTERRUPT
                //?????? MANGING THE ADSCRA->ADIF
                
                //ENABLE THE ADC
                writeControlSignalOnPortPin(ADCSRA_ADEN , HIGH);
                //OUT_DATA_ON_REG_KEEP_STATES(ADCSRA , (HIGH<<ADEN) );
                
            }else{
                //what an idiot!!
            }
            
        }else{
            //what an idiot!!
        }
    }else{
        //what an idiot!!
    }
    
    return fun_ret_status_and_data.fun_return;
}

s16 startConversionAndReturnConversionOutput(u8 auto_manual_mode){
    
    s16 adc_conversion_output;
    
    fun_ret_status_and_data.fun_return = checkForSelectedConversionMode(auto_manual_mode);
    
    if(NO_ERRORS == fun_ret_status_and_data.fun_return){
    
        if(CONVERSION_MANUAL_TRIGGER == auto_manual_mode){
            writeControlSignalOnPortPin(ADCSRA_ADSC , HIGH);
        }else{
            writeControlSignalOnPortPin(ADCSRA_ADEN , HIGH);
            writeControlSignalOnPortPin(SFIOR_ADTS0 , 
                    SCAN_SIGANL_ON_PIN(auto_manual_mode,ADTS0));
            writeControlSignalOnPortPin(SFIOR_ADTS1 , 
                    SCAN_SIGANL_ON_PIN(auto_manual_mode,ADTS1));
            writeControlSignalOnPortPin(SFIOR_ADTS2 , 
                    SCAN_SIGANL_ON_PIN(auto_manual_mode,ADTS2));
        }
    
        fun_ret_status_and_data = scanControlPassingThroughPortPin(ADMUX_ADLAR);
    
        if(fun_ret_status_and_data.fun_return == NO_ERRORS){
        
            adc_conversion_output = LOW;
        
            if(fun_ret_status_and_data.scanned_data == HIGH){
                //ADLAR=1 left adjusted data
//                OUT_DATA_ON_REG_KEEP_STATES( adc_conversion_output , 
//                        ( OUT_DATA_ON_REG_KEEP_STATES( adc_conversion_output 
//                          , (SHIFT_REG_DATA_LEFT(ADCL , ADLAR_ADCL_SHIFT))) ) );
                adc_conversion_output |= (ADCL << ADLAR_ADCL_SHIFT );
                adc_conversion_output |= (ADCH << ADLAR_ADCH_SHIFT);
            }else{
                //ADLAR=0 right adjusted data
//              OUT_DATA_ON_REG_KEEP_STATES( adc_conversion_output 
//                        , (SHIFT_REG_DATA_LEFT(ADCH , ADLAR_ADCH_SHIFT)) );
                adc_conversion_output |= ADCL;
                adc_conversion_output |= (ADCH << ADLAR_ADCH_SHIFT);
            
            }
        }else{
            //WHAT THE SHIT !!!!
            // ERR_SELECTING_CONVERSION_MODE USED TO REPORT ERROR HAS HAPPENED
            adc_conversion_output = ERR_SELECTING_CONVERSION_MODE;
        }
    }else{
        //WHAT THE SHIT !!!!
        // ERR_SELECTING_CONVERSION_MODE USED TO REPORT ERROR HAS HAPPENED
        adc_conversion_output = ERR_SELECTING_CONVERSION_MODE;
    }
    
    return adc_conversion_output;
}

FUN_RETURN_STATUS checkForSelectedChannel(u8 selected_channel){
    return ADC_VOLTAGE_0V_GND >= selected_channel && 
                 ADC_CHANNEL0 <= selected_channel  ? NO_ERRORS : ERR;
}

FUN_RETURN_STATUS checkForSelectedVoltage(u8 selected_voltage){
    return VOLTAGE_AREF != selected_voltage && 
           VOLTAGE_AVCC != selected_voltage && 
           VOLTAGE_Internal_2_56_V != selected_voltage ? ERR : NO_ERRORS;
}

FUN_RETURN_STATUS checkForSelectedFrequency(u8 selected_frequency){
    return PRESCALER_CLK_BY_128 >= selected_frequency && 
           PRESCALER_CLK_BY_2   <= selected_frequency  ? NO_ERRORS : ERR;
}

FUN_RETURN_STATUS checkForSelectedConversionMode(u8 selected_conversion_mode){
    return CONVERSION_MANUAL_TRIGGER >= selected_conversion_mode && 
           FREE_RUNNING_MODE         <= selected_conversion_mode  ? 
               NO_ERRORS : ERR;
}