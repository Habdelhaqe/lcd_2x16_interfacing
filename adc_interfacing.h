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

    #define   CHANNEL_SECUIRTY_MASK 0x1F //0b 0001 1111
    #define   VOLTAGE_SECUIRTY_MASK 0xC0 //0b 1100 0000
    #define FREQUENCY_SECUIRTY_MASK 0x07 //0b 0000 0111

    /*Bit        7     6     5    4    3     2   1     0
     *ADMUX    REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
     *INIT Value 0     0     0    0    0     0   0     0
    */
    /*TAKING ADCH BIT1 BIT0 PLACING IT @ BIT9 BIT8 OF THE SECOND BYTE*/
    #define ADLAR_ADCH_SHIFT 8 
    /*TAKING ADCL BIT1 BIT0 PLACING IT @ BIT7 BIT6 OF THE FIRST BYTE*/
    #define ADLAR_ADCL_SHIFT 6 

    /*
     * supported REF Voltages 
     * ADMUX {B7:REFS1: SELECTOR FOR MUX I/PS AVCC,INTERNAL 2.56VREFERENCE 
     *        B6:REFS0: BIAS TO THE TRANSISITOR SELECT BETN LETTING AREF PASS
     *               OR THE VOLTAGE COMING THROUGH THE UPOVE MUX ALLOW TO PASS}
     */
    //ADMUX {REFS1:0 , REFS0:0} AREF, Internal Vref turned off
    #define VOLTAGE_AREF 			 0x00 // 0>>higer bits 7,6 => 00 00 0000
    //ADMUX {REFS1:0 , REFS0:1} AVCC with external capacitor at AREF pin
    #define VOLTAGE_AVCC 			 0x80 // 2>>higer bits 7,6 => 10 00 0000 
    //ADMUX {REFS1:1 , REFS0:1} Internal 2.56V Voltage Reference with external capacitor at AREF pin
    #define VOLTAGE_Internal_2_56_V  0xC0 // 3>>higer bits 7,6 => 11 00 0000
    //ADMUX {REFS1:1 , REFS0:0} NO USE TILL NOW
    #define VOLATGE_RESERVED 		 0x40 // 1>>higer bits 7,6 => 01 00 0000
   
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
     
    #define FREE_RUNNING_MODE             0x00 // 0>>higer bits 7:5 => 000 0 0000
    #define ANALOG_COMPARATOR_MODE        0x20 // 1>>higer bits 7:5 => 001 0 0000
    #define EXTERNAL_INTERRUPT_REQUEST    0x40 // 2>>higer bits 7:5 => 010 0 0000
    #define TIMER_COUNTER_0_COMAPRE_MATCH 0x60 // 3>>higer bits 7:5 => 011 0 0000
    #define TIMER_COUNTER_0_OVER_FLOW     0x80 // 4>>higer bits 7:5 => 100 0 0000
    #define TIMER_COUNTER_1_COMAPRE_MATCH 0xA0 // 5>>higer bits 7:5 => 101 0 0000
    #define TIMER_COUNTER_1_OVER_FLOW     0xC0 // 6>>higer bits 7:5 => 110 0 0000
    #define TIMER_COUNTER_1_CAPTURE_EVENT 0xE0 // 7>>higer bits 7:5 => 111 0 0000
    //THIS VALUE LOGIACLLY TRUE BUT CAN'T PASS THE RESERVED_BIT_4_NUMBER CHECK
    //#define CONVERSION_MANUAL_TRIGGER     0x0F // 7>>higer bits 7:5 => 111 1 0000
    #define CONVERSION_MANUAL_TRIGGER     0x0F // 7>>higer bits 7:5 => 111 1 0000

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
     */
    FUN_RETURN_STATUS initADCInternalCircuitry(u8 /*what channel signal on*/ ,
                                               u8 /*what voltage signal level*/,
                                               u8 /*left or right adjust*/,
                                               u8 /*what sampling frequency*/);
    
    FUN_RETURN_STATUS checkForSelectedChannel(u8 /*selected_channel*/);
    
    FUN_RETURN_STATUS checkForSelectedVoltage(u8 /*selected_voltage*/);

    FUN_RETURN_STATUS checkForSelectedFrequency(u8 /*selected_frequency*/);
    
    FUN_RETURN_STATUS checkForSelectedConversionMode(u8 /*selected_conversion_mode*/);

    /*
     * start converting the ANALOG signal to DGITAL representation selecting 
     * The operation mode manual/automatic conversion
     */
    FUN_RETURN_STATUS onStartConversion(u8 /*auto_manual_mode*/);
    
    /*
     * optain the o/p of the ADC through 2 REGs
     * ADCH ADCL
     */
    s16 onConversionComplete(void);

#endif	/* ADC_INTERFACING_H */

