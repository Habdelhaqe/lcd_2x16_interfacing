#include "timer0_interfacing.h"
#include "interfacing_connection_logic.h"

static u8 save_configuration_of_timer ,
          is_timer0_on; 

void onInitTimer(u8 selected_clk_source , 
                 u8 selected_wave_gen_mode , 
                 u8 selected_compare_out_mode ,
                 u8 enable_disable_over_flow_interupt ,
                 u8 enable_disable_output_comnpare_interupt ){
    
    if(enable_disable_over_flow_interupt){
        ENABLE_TIMER_OVER_FLOW_INTERRUPT;
    }else{
        DISABLE_TIMER_OVER_FLOW_INTERRUPT;
    }
    
    if(enable_disable_output_comnpare_interupt){
        ENABLE_OUTPUT_COMPARE_MATCH_INTERRUPT;
    }else{
        DISABLE_OUTPUT_COMPARE_MATCH_INTERRUPT;
    }
        
    TCCR0 = (selected_clk_source & CLK_INPUT_SECUIRTY_MASK) |
                (selected_wave_gen_mode & WGM_INPUT_SECUIRTY_MASK) |
                    (selected_compare_out_mode & COM_INPUT_SECUIRTY_MASK) ;
    
    is_timer0_on = ((selected_clk_source & CLK_INPUT_SECUIRTY_MASK) != OFF) ;
}

void haltTimer(void){
    save_configuration_of_timer = TCCR0;
    STOP_TIMER0;
    is_timer0_on = OFF ;
}

u8 getTimerConfiguration(void){
    return save_configuration_of_timer;
}

u8 getTimerStatus(void){
    return is_timer0_on;
}

void resumeTimer(void){
    if(!is_timer0_on){
        TCCR0 = getTimerConfiguration();
        is_timer0_on = ON;
    }
}

void changeTimerClkSource(u8 selected_new_clk_source_frequency){
    STOP_TIMER0;
    TCCR0 |= (selected_new_clk_source_frequency & CLK_INPUT_SECUIRTY_MASK);
}

void restTimerCounter(void){
    haltTimer();
    TCNT0 = BOTTOM;
    resumeTimer();
}

void setCompraeValue(u8 compare_value){
    OCR0 = compare_value;
    ENABLE_OUTPUT_COMPARE_MATCH_INTERRUPT;
}

void configureOutComparePinChangeCompareAndWaveMode(u8 selected_wave_gen_mode 
                                                    , u8 selected_compare_out_mode){
    
    selected_compare_out_mode &= COM_INPUT_SECUIRTY_MASK;
        
    if( selected_compare_out_mode != NON_PWD_NORMAL_PORT_OPERATION_MODE ){
        
        save_configuration_of_timer = TCCR0;
        
        FORCE_STROPE_FOR_OC0_PIN_INIT_BEFORE_SET_DIRECTION;

        programPortPinInOut(_PB_PIN3,OUTPUT); //OC0 PIN
       
        TCCR0 = (save_configuration_of_timer & CLK_INPUT_SECUIRTY_MASK) | 
                    selected_compare_out_mode |
                        (selected_wave_gen_mode & WGM_INPUT_SECUIRTY_MASK);
    }
    
}