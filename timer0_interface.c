#include "timer0_interfacing.h"

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
    
}
