/* 
 * File:   common_types_defs.h
 * Author: Eng Ahmed
 *
 * Created on November 28, 2021, 10:08 AM
 */

#ifndef ENG_AHMED_DEFS_H
    #define	ENG_AHMED_DEFS_H 9742
    
    //SIGNALS STATUS
    #define HIGH 1
    #define LOW  0
    
    //LOGIC STATUS
    #define TRUE  1
    #define FALSE 0
    
    //BIT ARITHIMETICS
    #define    SET_BIT(REG , BIT_LOCATION)     REG |= HIGH<<BIT_LOCATION
    #define  CLEAR_BIT(REG , BIT_LOCATION)     REG &= ~(HIGH<<BIT_LOCATION)
    #define TOGGLE_BIT(REG , BIT_LOCATION)     REG ^= HIGH<<BIT_LOCATION
    #define    GET_BIT(REG , BIT_LOCATION)     REG & HIGH<<BIT_LOCATION ? HIGH : LOW
    /*
     * this is not wright to do cause you don't want to modify or change
     * the register value you want to read a specific bit either to be
     * HIGH/LOW
     */
    //#define    GET_BIT(REG , BIT_LOCATION)     REG &= HIGH<<BIT_LOCATION
    
    //8PINS MAPING
    #define PIN0 0
    #define PIN1 1
    #define PIN2 2
    #define PIN3 3
    #define PIN4 4
    #define PIN5 5
    #define PIN6 6
    #define PIN7 7

#endif	/* COMMON_TYPES_DEFS_H */
