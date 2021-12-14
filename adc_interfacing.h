/* 
 * File:   adc_interfacing.h
 * Author: Engs
 *
 * Created on 10 December 2021, 17:54
 */

#ifndef ADC_INTERFACING_H

#include "atmega32a.h"

    #define	ADC_INTERFACING_H
    
    /*
     * ADC MUX input channels for supporting of 8 different 
     * voltage/signals to same ADC Unit through The Selection control signal
     * applied to the MUX you can switch bet them selecting 1 channel @ a time
     * or if differential mode selecting 2 channels @ time 
     */ 
    //SINGLE MODE ONLY 1 I/P(VOLTAGE/SIGNAL) TO DEAL WITH
                           //ADMUX 43 210
    #define ADC_CHANNEL0 0 //ADC0  00 000
    #define ADC_CHANNEL1 1 //ADC1  00 001
    #define ADC_CHANNEL2 2 //ADC2  00 010
    #define ADC_CHANNEL3 3 //ADC3  00 011
    #define ADC_CHANNEL4 4 //ADC4  00 100
    #define ADC_CHANNEL5 5 //ADC5  00 101
    #define ADC_CHANNEL6 6 //ADC6  00 110
    #define ADC_CHANNEL7 7 //ADC7  00 111
    
    //DEFERENCE MODE2 I/PS (VOLTAGE/SIGNAL) TO GET DEFERNCE AND APPLY GAIN?
                                                              //ADMUX  43 210 GAIN(X)
    #define ADC_CHANNEL0_DEF_W_ADC_CHANNEL0_10   8 //ADC0(+) - ADC0(-) 01 000  10
    #define ADC_CHANNEL1_DEF_W_ADC_CHANNEL0_10   9 //ADC1(+) - ADC0(-) 01 001  10
    #define ADC_CHANNEL0_DEF_W_ADC_CHANNEL0_200 10 //ADC0(+) - ADC0(-) 01 010  200
    #define ADC_CHANNEL1_DEF_W_ADC_CHANNEL0_200 11 //ADC1(+) - ADC0(-) 01 011  200
    #define ADC_CHANNEL2_DEF_W_ADC_CHANNEL2_10  12 //ADC2(+) - ADC2(-) 01 100  10
    #define ADC_CHANNEL3_DEF_W_ADC_CHANNEL2_10  13 //ADC3(+) - ADC2(-) 01 101  10
    #define ADC_CHANNEL2_DEF_W_ADC_CHANNEL2_200 14 //ADC2(+) - ADC2(-) 01 110  200
    #define ADC_CHANNEL3_DEF_W_ADC_CHANNEL2_200 15 //ADC3(+) - ADC2(-) 01 111  200
    #define ADC_CHANNEL0_DEF_W_ADC_CHANNEL1     16 //ADC0(+) - ADC1(-) 10 000  1
    #define ADC_CHANNEL1_DEF_W_ADC_CHANNEL1     17 //ADC1(+) - ADC1(-) 10 001  1
    #define ADC_CHANNEL2_DEF_W_ADC_CHANNEL1     18 //ADC2(+) - ADC1(-) 10 010  1
    #define ADC_CHANNEL3_DEF_W_ADC_CHANNEL1     19 //ADC3(+) - ADC1(-) 10 011  1
    #define ADC_CHANNEL4_DEF_W_ADC_CHANNEL1     20 //ADC4(+) - ADC1(-) 10 100  1
    #define ADC_CHANNEL5_DEF_W_ADC_CHANNEL1     21 //ADC5(+) - ADC1(-) 10 101  1
    #define ADC_CHANNEL6_DEF_W_ADC_CHANNEL1     22 //ADC6(+) - ADC1(-) 10 110  1
    #define ADC_CHANNEL7_DEF_W_ADC_CHANNEL1     23 //ADC7(+) - ADC1(-) 10 111  1
    #define ADC_CHANNEL0_DEF_W_ADC_CHANNEL2     24 //ADC0(+) - ADC2(-) 11 000  1
    #define ADC_CHANNEL1_DEF_W_ADC_CHANNEL2     25 //ADC1(+) - ADC2(-) 11 001  1
    #define ADC_CHANNEL2_DEF_W_ADC_CHANNEL2     26 //ADC2(+) - ADC2(-) 11 010  1
    #define ADC_CHANNEL3_DEF_W_ADC_CHANNEL2     27 //ADC3(+) - ADC2(-) 11 011  1
    #define ADC_CHANNEL4_DEF_W_ADC_CHANNEL2     28 //ADC4(+) - ADC2(-) 11 100  1
    #define ADC_CHANNEL5_DEF_W_ADC_CHANNEL2     29 //ADC5(+) - ADC2(-) 11 101  1
    #define ADC_VOLTAGE_1_22V_VBG               30 //       N/A        11 110  N/A
    #define ADC_VOLTAGE_0V_GND                  31 //       N/A        11 111  N/A

    #define    CHANNEL_SECUIRTY_MASK 0x1F //0b 0001 1111
    #define    VOLTAGE_SECUIRTY_MASK 0xC0 //0b 1100 0000
    #define LEFT_RIGHT_SECUIRTY_MASK 0x20 //0b 0010 0000
    #define  FREQUENCY_SECUIRTY_MASK 0x07 //0b 0000 0111

    #define START_MANUAL_CONVERSION_PROCESS 0x40 //0b 0100 0000
    #define   START_AUTO_CONVERSION_PROCESS 0x60 //0b 0110 0000

    #define  ADC_ENABLE_SET_AUTO_TRIGGER_OFF 0x88 //0b 1000 1000
    #define          ADC_SET_AUTO_TRIGGER_ON 0x20 //0b 0010 1000


    /*Bit        7     6     5    4    3     2   1     0
     *ADMUX    REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
     *INIT Value 0     0     0    0    0     0   0     0
    */
    /*TAKING ADCH BIT1 BIT0 PLACING IT @ BIT9 BIT8 OF THE SECOND BYTE*/
    #define ADLAR_ADCH_SHIFT 8 
    /*TAKING ADCL BIT1 BIT0 PLACING IT @ BIT7 BIT6 OF THE FIRST BYTE*/
    #define SHIFT_ADCL_FOR_LEFT_ADJUST 6 

    /*
     * supported REF Voltages 
     * ADMUX {B7:REFS1: SELECTOR FOR MUX I/PS AVCC,INTERNAL 2.56VREFERENCE 
     *        B6:REFS0: BIAS TO THE TRANSISITOR SELECT BETN LETTING AREF PASS
     *               OR THE VOLTAGE COMING THROUGH THE UPOVE MUX ALLOW TO PASS}
     */
    //ADMUX {REFS1:0 , REFS0:0} AREF, Internal Vref turned off
    #define VOLTAGE_AREF 			 0x00 // 0>>higer bits 7,6 => 00 00 0000
    //ADMUX {REFS1:0 , REFS0:1} AVCC with external capacitor at AREF pin
    #define VOLTAGE_AVCC 			 0x40 // 2>>higer bits 7,6 => 01 00 0000 
    //ADMUX {REFS1:1 , REFS0:1} Internal 2.56V Voltage Reference with external capacitor at AREF pin
    #define VOLTAGE_Internal_2_56_V  0xC0 // 3>>higer bits 7,6 => 11 00 0000
    //ADMUX {REFS1:1 , REFS0:0} NO USE TILL NOW
    #define VOLATGE_RESERVED 		 0x80 // 1>>higer bits 7,6 => 10 00 0000
   
	#define LEFT_ADJUST  0x20 // 1>>higer bits 5 => 00 1 0 0000
	#define RIGHT_ADJUST 0x00 // 0>>higer bits 5 => 00 0 0 0000

    /*
     * Bit          7    6    5     4    3    2     1     0
     * ADCSRA     ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0 
     * Read/Write  R/W  R/W  R/W   R/W  R/W  R/W   R/W   R/W
     * INIT Value   0    0    0     0    0    0     0     0
     */
    #define ADC_ENABLE_AND_INTERRUPT_ENABLE 0x88 // ob 1000 1000

    /*
     * sampling frequency or the controlling frequency of the entire ADC with 
     * respect to the CLK signal of the MicroController note that the latency 
     * of the entire system of ADC calculated from the time the start control
     * signal arrives to the ADC control pin ADCSR: ADSC(manual control) 
     * OR ADATE(for automatic triggering) to the time the ADCL REG holds the 
     * data is 25*(sampling time) (first initialization time) reduced to 
     * 13*(sampling time)
     * 7-BIT ADC PRESCALER to MUX between 6 CLK/SAMPLING FREQ SELECTED_BY / 
     * DRIVING_SIGNAL_THROUGH : 
     *  ADCSRA AD CTRL. & STATUS REGISTER A?: ADPS2 , ADPS1 , ADPS0 
     */
    //ADCSRA :                         ADPS2 , ADPS1 , ADPS0 
    #define PRESCALER_CLK_BY_2   0  //   0       0       0
    //#define PRESCALER_CLK_BY_2 1  //   0       0       1
    #define PRESCALER_CLK_BY_4   2  //   0       1       0
    #define PRESCALER_CLK_BY_8   3  //   0       1       1
    #define PRESCALER_CLK_BY_16  4  //   1       0       0
    #define PRESCALER_CLK_BY_32  5  //   1       0       1
    #define PRESCALER_CLK_BY_64  6  //   1       1       0
    #define PRESCALER_CLK_BY_128 7  //   1       1       1

    /*
     * Bit          7     6     5   4   3   2    1    0
     * SFIOR      ADTS2 ADTS1 ADTS0 ? ACME PUD PSR2 PSR10 
     * Read/Write  R/W   R/W   R/W  R  R/W R/W  R/W  R/W
     * INIT Value   0     0     0   0   0   0    0    0
     */
     
    #define FREE_RUNNING_MODE             0x00 // 0>>higher bits 7:5 => 000 0 0000
    #define ANALOG_COMPARATOR_MODE        0x20 // 1>>higher bits 7:5 => 001 0 0000
    #define EXTERNAL_INTERRUPT_REQUEST    0x40 // 2>>higher bits 7:5 => 010 0 0000
    #define TIMER_COUNTER_0_COMAPRE_MATCH 0x60 // 3>>higher bits 7:5 => 011 0 0000
    #define TIMER_COUNTER_0_OVER_FLOW     0x80 // 4>>higher bits 7:5 => 100 0 0000
    #define TIMER_COUNTER_1_COMAPRE_MATCH 0xA0 // 5>>higher bits 7:5 => 101 0 0000
    #define TIMER_COUNTER_1_OVER_FLOW     0xC0 // 6>>higher bits 7:5 => 110 0 0000
    #define TIMER_COUNTER_1_CAPTURE_EVENT 0xE0 // 7>>higher  bits 7:5 => 111 0 0000
    //THIS VALUE LOGIACLLY TRUE BUT CAN'T PASS THE RESERVED_BIT_4_NUMBER CHECK
    //#define      SINGLE_CONVERSION_MODE 0x0F // 7>>higher  bits 7:5 => 111 1 0000
    #define        SINGLE_CONVERSION_MODE 0x0F // 7>>higher bits 7:5 => 111 1 0000

    #define ERR_SELECTING_CONVERSION_MODE 0xFD00
    
    #define AUTO_TRIGER_SECUIRTY_MASK 0xE0 //0b 1110 0000
    #define RESERVED_BIT_4_CLEAR_MASK 0xEF //0b 1110 111
	#define RESERVED_BIT_4_NUMBER     PIN4  

    /*
     * initialize ADC internal circuitry to the desired logic levels
     * configure/program the ADC controls to the specific needs through
     * manipulation of :
     *1) ADMUX    REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
     * channel and difference/single mode selection MUX4 MUX3 MUX2 MUX1 MUX0
     * voltage ref through REFS1 REFS0
     * ADLAR controls the form of the 10bit o/p on ADCH ADCL
     *  0 : ADCH(BIT1: ADC9  , BIT0: ADC8) ADCL( BIT7: ADC7 -> BIT0:ADC0 )
     *  1 : ADCH(BIT7: ADC9 -> BIT0: ADC2) ADCL( BIT7: ADC1 -> BIT6:ADC0 )
     * 2) ADCSRA  ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
     *  sampling frequency controls via ADPS2 ADPS1 ADPS0
     *  trigger mode through ADSC ADATE applied to a trigger circuitry 
     *      controlled also by interrupt flags and ADTS{2 1 0}
     *  enable the ADC through ADEN
     *  receive Interrupt flag on the ADIF
     *  enable for Interrupt through ADIE
     *  the ADIF and ADIE goes through AND Gate To Trigger Interrupt or not
     * 
     */
    FUN_RETURN_STATUS initADCInternalCircuitry(u8 which_ch_mode /*what channel signal on*/ ,
                                               u8 voltage_ref /*what voltage signal level*/,
                                               u8 left_adjust/*left or right adjust*/,
                                               u8 sampling_freq/*what sampling frequency*/);
    /*
     * on ADMUX
     * configure the channel and mode(single/differntial) 
     *  @select_channel_and_mode Masked with 0x1F
     *  "If these bits are changed during a conversion, the change will not go 
     *      in effect until this conversion is complete (ADIF in ADCSRA is set)"
     * 
     * configure voltage ref
     *  @select_voltage_ref Masked with 0xC0
     *  "If these bits are changed during a conversion, the change will not go 
     *     in effect until this conversion is complete (ADIF in ADCSRA is set)"
     * 
     * configure left or right
     *  @select_left_or_right_adjustment Masked with 0x20
     *  "Changing the ADLAR bit will affect the ADC Data Register immediately, 
     *     regardless of any ongoing conversions"
     * 
     * on ADCSRA
     * configure the ADC to work in first place = ENABLE
     *  SET ADEN(BIT7)
     *  "Turning the ADC off while a conversion is in progress, will 
     *      terminate this conversion."
     * 
     * configure interrupt service of ADC = enable it to signal 
     *  "COMPLETE CONVERSION" set ADIE(BIT3)
     * 
     * configure ADC_clock/latency of conversion process
     *  ADPS2 ADPS1 ADPS0 BITS 2,1,0
     * 
     * left out BITS :
     * 
     *      6 : ADSC STARTING CONVERSION PROCESS
     *          "in Single Conversion mode, write this bit to one to start each 
     *           conversion. 
     *           In Free Running Mode, write this bit to one to start the first 
     *           conversion. 
     *           The first conversion after ADSC has been written after the ADC 
     *           has been enabled, or if ADSC is written at the same time as 
     *           the ADC is enabled, will take 25 ADC clock cycles instead of 
     *           the normal13. 
     *           This first conversion performs initialization of the ADC.
     *           ADSC will read as one as long as a conversion is in progress. 
     *           When the conversion is complete, it returns to zero.
     *           Writing zero to this bit has no effect"
     * 
     *      5 : ADTE AUTO TRIGGER ENABLE => you need with it SFIOR configured
     * 
     *      4 : ADIF should Report back  "COMPLETE CONVERSION INTERRUPT"
     *         "ADIF is cleared by hardware when executing the corresponding 
     *          interrupt handling vector.
     *          Beware that if doing a Read-Modify-Write on ADCSRA, a pending 
     *          interrupt can be disabled"
     * note: (ADIE(1) & ADIE(1)) => INTERRUPT SERVICE OF ADC IS TRIGGERED 
     *  ISR(ADC_vect) is called
     * 
     * there is no need for any kind of check to be done :
     *      @checkForSelectedChannel
     *      @checkForSelectedVoltage
     *      @checkForSelectedFrequency
     * 
     */
    void onInitADC(u8 select_channel_and_mode ,u8 select_voltage_ref ,
                   u8 select_left_or_right_adjustement ,
                   u8 select_input_source_frequency);
    
    FUN_RETURN_STATUS checkForSelectedChannel(u8 selected_channel);
    
    FUN_RETURN_STATUS checkForSelectedVoltage(u8 selected_voltage);

    FUN_RETURN_STATUS checkForSelectedFrequency(u8 selected_input_source_frequency);
    
    FUN_RETURN_STATUS checkForSelectedConversionMode(u8 selected_conversion_mode);

    /*
     * start converting the ANALOG signal to DGITAL representation selecting 
     * The operation mode manual/automatic conversion
     */
    FUN_RETURN_STATUS startConversion(u8 auto_manual_mode);
    
    /* in case of Single Conversion mode AKA manual trigger
     *      Set BIT6 ADSC OF ADCSRA and BIT5 ADTE is Cleared
     * in case of Auto Triggered Conversion trigger mode AKA auto trigger
     *      Set BIT6 ADSC OF ADCSRA and Set BIT5 ADTE  
     *      configure SFIOR :TRIGGER SELECT source (Sampling Frequency)
     *          Bit7 : ADTS2
     *          Bit6 : ADTS1
     *          Bit5 : ADTS0
     *          Bit4 : Reserved must be rest/cleared
     *          Bits3:0 is rest/cleared for now!!!!
     *      auto_manual_mode Masked with 0xE0
    */
    void onStartConversion(u8 auto_manual_mode);
    
    /*
     * obtain the o/p of the ADC through 2 REGs
     * ADCH ADCL
     */
    s16 conversionComplete(void);
    
    /*
     * ADC conversion is of 10 BITS precession so signed short AKA s16 is 
     * suitable to represent the result available through :
     *      ADCH , ADCL
     * right adjustment : ADLAR is rest/cleared (ADMUX)
     *      ADCH(BITS 1,2) ADCL(ALL BITS)
     * left adjustment : ADLAR is set (ADMUX)
     *      ADCH(ALL BITS) ADCL(BITS 7,6)
     * 
     * "When ADCL is read, the ADC Data Register is not updated until ADCH is 
     *  read. 
     *  Consequently, if the result is left adjusted and no more than 8-bit 
     *  precision is required, it is sufficient to read ADCH. 
     *  Otherwise, ADCL must be read first, then ADCH.
     *  The ADLAR bit in ADMUX, and the MUXn bits in ADMUX affect the way 
     *  the result is read from the registers. 
     *  If ADLAR is set, the result is left adjusted. 
     *  If ADLAR is cleared (default), the result is right adjusted."
     */
    s16 onConversionComplete(void); 
    
    s16 onConversionCompleteUsingPolling(void);
    
#endif	/* ADC_INTERFACING_H */

