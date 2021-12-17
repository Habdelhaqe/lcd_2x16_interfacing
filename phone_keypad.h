#ifndef PHONE_KEYPAD_HEADER

#define PHONE_KEYPAD_HEADER
    #include"atmega32a.h"
    #define ASCI_0 0x30
    #define ASCI_STAR 0x2A //*
    #define ASCI_POUND 0x23 //#

    //keypad connections
    #define KEYPAD_A_PIN _PC_PIN4 // LINE A i/p to Microcontroller BTNS 1,2,3 
    #define KEYPAD_B_PIN _PC_PIN5 // LINE B i/p to Microcontroller BTNS 4,5,6
    #define KEYPAD_C_PIN _PC_PIN6 // LINE C i/p to Microcontroller BTNS 7,8,9
    #define KEYPAD_D_PIN _PC_PIN7 // LINE D i/p to Microcontroller BTNS *,0,#

    #define KEYPAD_1_PIN _PA_PIN4 // COL 1 o/p From MicroController BTNS 1,4,7,*
    #define KEYPAD_2_PIN _PA_PIN5 // COL 2 o/p From MicroController BTNS 2,5,8,0
    #define KEYPAD_3_PIN _PA_PIN6 // COL 3 o/p From MicroController BTNS 3,6,7,#

    #define KEYPAD_BTN1      1
    #define KEYPAD_BTN2      2
    #define KEYPAD_BTN3      3
    #define KEYPAD_BTN4      4
    #define KEYPAD_BTN5      5
    #define KEYPAD_BTN6      6
    #define KEYPAD_BTN7      7
    #define KEYPAD_BTN8      8
    #define KEYPAD_BTN9      9
    #define KEYPAD_BTN_STAR  10 //*
    #define KEYPAD_BTN0      11
    #define KEYPAD_BTN_POUND 12 //# : HASH / POUND SIGN    
    //-------------------------------------------------------------------------
    
    #define KEY_OFFSET 3
    
    /*
     * program/configure the connection pins and ports on Microcontroller
     * 
     * 4 lines/rows i/p to Microcontroller for checking which line/row has
     * a HIGH signal on it
     * KEYPAD_A_PIN _PC_PIN4 // LINE A i/p to Microcontroller BTNS 1,2,3 
     * KEYPAD_B_PIN _PC_PIN5 // LINE B i/p to Microcontroller BTNS 4,5,6
     * KEYPAD_C_PIN _PC_PIN6 // LINE C i/p to Microcontroller BTNS 7,8,9
     * KEYPAD_D_PIN _PC_PIN7 // LINE D i/p to Microcontroller BTNS *,0,#
     * 
     * 3 columns o/p from Microcontroller for checking which button on the
     * selected column passing a HIGH signal to it
     * KEYPAD_1_PIN _PA_PIN4 // COL 1 o/p From MicroController BTNS 1,4,7,*
     * KEYPAD_2_PIN _PA_PIN5 // COL 2 o/p From MicroController BTNS 2,5,8,0
     * KEYPAD_3_PIN _PA_PIN6 // COL 3 o/p From MicroController BTNS 3,6,7,#
     * 
     */
    void initKeypad(void);
        
    /*
     * finding out which key is pressed if any via using function
     * \c FUN_RETURN_STATUS driveBiasSiganlThroughKeypad(u8,u8,u8);
     * to drive a signal through each column of the keypad and then 
     * got through each line/row checking for a HIGH signal passing through it
     * function returns the key pressed indicator:
     *  KEYPAD_BTNx where x:0->9 along with 
     *  KEYPAD_BTN_STAR for * AND KEYPAD_BTN_POUND for #
     * if no key is pressed then UN_IDENTIFIED is returned
     */
    u8 getPressedKey(void);
    
    void dispalyKeyAsChar(u8 key);
#endif