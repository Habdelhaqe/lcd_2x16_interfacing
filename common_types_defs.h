/* 
 * File:   common_types_defs.h
 * Author: Eng Ahmed
 *
 * Created on November 28, 2021, 10:08 AM
 */

#ifndef ENG_AHMED_DEFS_H
    #define	ENG_AHMED_DEFS_H 9742
    
    #define NULL (void *)0
    #define NULL_CHAR '\0'
    #define CARRIAGE_RETURN 13
    #define NEW_LINE 10
    #define LINE_FEED CARRIAGE_RETURN & NEW_LINE

    //SIGNALS STATUS
    #define HIGH 1
    #define LOW  0
    
    //LOGIC STATUS
    #define TRUE  1
    #define FALSE 0
    
    //SIGNALLING DISCRIPTION AND STATUS
    #define OUTPUT HIGH
    #define INPUT  LOW

    #define SET HIGH
    #define REST LOW
    #define CLEAR LOW

    //BIT ARITHIMETICS
    #define    SET_BIT(REG , BIT_LOCATION)     REG |= (HIGH<<BIT_LOCATION)
    #define  CLEAR_BIT(REG , BIT_LOCATION)     REG &= ~(HIGH<<BIT_LOCATION)
    #define TOGGLE_BIT(REG , BIT_LOCATION)     REG ^= (HIGH<<BIT_LOCATION)
    #define    GET_BIT(REG , BIT_LOCATION)     (REG & (HIGH<<BIT_LOCATION))

    #define    SET_BIT_DELAY_UPDATE(REG , BIT_LOCATION)     (REG) | (HIGH<<(BIT_LOCATION))
    #define  CLEAR_BIT_DELAY_UPDATE(REG , BIT_LOCATION)     (REG) & ~(HIGH<<(BIT_LOCATION))
    #define TOGGLE_BIT_DELAY_UPDATE(REG , BIT_LOCATION)     (REG) ^ (HIGH<<(BIT_LOCATION))

    /*
     * this is not wright to do cause you don't want to modify or change
     * the register value you want to read a specific bit either to be
     * HIGH/LOW
     */
    //#define    GET_BIT(REG , BIT_LOCATION)     REG &= HIGH<<BIT_LOCATION
    
    /*
     * LM35 connected to 5V bias so max o/p is 1.5V ---> 150 ºC (max ºC)
     * so to display ºC of i/p on LCD equation:
     *  Temp(ºC) = ADC_conversion_output(voltage in 10 digit representation) * 150(max ºC) * 5 / 1.5(max o/p voltage of LM35 5V biased) * 1023(max digital representation for 5V)
     *  Temp = 0.48875855327468230694037145650049 * ADC_conversion_output;
     */
    #define DIGITAL_REPRESENTATION_LM35V_FOR_1_C 0.48875855327468230694037145650049

    #define HW_INITIALIZATION_DELAY_IN_MS 10
    #define LCD_DISPLAY_DELAY_IN_MS 1000
    #define VISIT_ALL_LCD_IN_MS 100

    typedef unsigned char  u8;
    typedef unsigned short u16;
    typedef   signed short s16;
    typedef   signed int   s32;
    typedef unsigned int   u32;
#endif	/* COMMON_TYPES_DEFS_H */