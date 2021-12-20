/* 
 * File:   timer0_interfacing.h
 * Author: Engs
 *
 * Created on 19 December 2021, 18:18
 */

#ifndef TIMER0_INTERFACING_H
#define	TIMER0_INTERFACING_H

    #include "common_types_defs.h"
    #include "atmega32a.h"
    #include <avr/iom32a.h>
    
    #define ENABLE_INTERRUPT  HIGH
    #define DISABLE_INTERRUPT LOW

    #define WGM_MASK_FOR_TCCR0       0xB7 // 1(WGM00)11 (WGM01)111
    #define WGM_INPUT_SECUIRTY_MASK  0x48 // 0(WGM00)00 (WGM01)000

    #define COM_MASK_FOR_TCCR0       0xCF // 11(COM01)(COM00) 1111
    #define COM_INPUT_SECUIRTY_MASK  0x30 // 00(COM01)(COM00) 0000

    #define CLK_MASK_FOR_TCCR0       0xF8 // 1111 1(CS2)(CS1)(CS0)
    #define CLK_INPUT_SECUIRTY_MASK  0x07 // 0000 0(CS2)(CS1)(CS0)

    //TCCR0 Bit 6, 3 ? WGM0[1:0]: Waveform Generation Mode
    #define NORMAL_MODE               0    // 0(WGM00=0)00 (WGM0=0)000
    #define PWD_PHASE_CORRECTION_MODE 0x40 // 0(WGM00=1)00 (WGM0=0)000
    #define CTC_MODE                  0x8  // 0(WGM00=0)00 (WGM0=1)000
    #define FAST_PWD_MODE             0x48 // 0(WGM00=1)00 (WGM0=1)000
    
    //TCCR0 Bit 5:4 ? COM0[1:0]: Compare Match Output Mode
    //NON_PWD
    #define NON_PWD_NORMAL_PORT_OPERATION_MODE 0
    #define NON_PWD_TOGLE_OC_ON_COMPARE_MATCH  0x10 
    #define NON_PWD_CLEAR_OC_ON_COMPARE_MATCH  0x20
    #define NON_PWD_SET_OC_ON_COMPARE_MATCH    0x30

    //FPWD                                             
    #define FAST_PWD_NORMAL_PORT_OPERATION_MODE               0
    #define FAST_PWD_RESERVED                                 0x10
    #define FAST_PWD_CLEAR_OC_ON_COMPARE_MATCH_NON_INVERTING  0x20
    #define FAST_PWD_SET_OC_ON_COMPARE_MATCH_INVERTING        0x30

    //PWD PHASE CORRECT                                             
    #define PHASE_CORRECT_PWD_NORMAL_PORT_OPERATION_MODE                0  
    #define PHASE_CORRECT_PWD_RESERVED                                  0x01
    #define PHASE_CORRECT_PWD_CLEAR_OC_UP_COUNTIN_SET_OC_DOWN_COUNTING  0x20
    #define PHASE_CORRECT_PWD_SET_OC__UP_COUNTIN_CLEAR_OC_DOWN_COUNTING 0x30

    //TCCR0 BitS 2:0 ? CS02:0: Clock Select            SC2     SC1     SC0
    #define STOP_TIMER                                 0  //   0       0       0 
    #define NO_PRESCALING                              1  //   0       0       1 
    #define TIMER0_PRESCALER_CLK_BY_8                  2  //   0       1       0
    #define TIMER0_PRESCALER_CLK_BY_64                 3  //   0       1       1
    #define TIMER0_PRESCALER_CLK_BY_256                4  //   1       0       0
    #define TIMER0_PRESCALER_CLK_BY_1024               5  //   1       0       1
    #define TIMER0_EXTERNAL_CLK_ON_T0_PIN_FALLING_EDGE 6  //   1       1       0
    #define TIMER0_EXTERNAL_CLK_ON_T0_PIN_RISING_EDGE  7  //   1       1       1
    
    //TCCR0 Bit 7 ? FOC0: Force Output Compare
    #define FORCE_OUTPUT_COMPARE_ON_OC0_PIN     SET_BIT((TCCR0), FOC0)
    #define FORCE_STROPE_FOR_OC0_PIN_INIT_BEFORE_SET_DIRECTION OUT_DATA_ON_REG_CHANGE_STATES((TCCR0) , 0x80)

    //STOP TIMER
    #define STOP_TIMER0 OUT_DATA_ON_REG_CHANGE_STATES((TCCR0) , CLK_MASK_FOR_TCCR0);

    //TIMSK Bit 1 ? OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
    #define ENABLE_OUTPUT_COMPARE_MATCH_INTERRUPT    SET_BIT((TIMSK) , OCIE0);
    #define DISABLE_OUTPUT_COMPARE_MATCH_INTERRUPT CLEAR_BIT((TIMSK) , OCIE0);

    //TIMSK Bit 0 ? TOIE0: Timer/Counter0 Overflow Interrupt Enable
    #define ENABLE_TIMER_OVER_FLOW_INTERRUPT      SET_BIT((TIMSK) , TOIE0);
    #define DISABLE_TIMER_OVER_FLOW_INTERRUPT   CLEAR_BIT((TIMSK) , TOIE0);

    void onInitTimer(u8 selected_clk_source , 
                     u8 selected_wave_gen_mode , 
                     u8 selected_compare_out_mode ,
                     u8 enable_disable_over_flow_interupt ,
                     u8 enable_disable_output_comnpare_interupt );
    
    void haltTimer(void);
    
    u8 getTimerConfiguration(void);
    
    u8 getTimerStatus(void);
    
    void resumeTimer(void);
    
    void changeTimerClk_source(u8 selected_new_clk_source_frequency);
    
#endif	/* TIMER0_INTERFACING_H */