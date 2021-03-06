/* 
 * File:   usart_interface.h
 * Author: Engs
 *
 * Created on 26 December 2021, 18:36
 */

#ifndef USART_INTERFACE_H
#define	USART_INTERFACE_H
    #include"atmega32a.h"

    #define IGNORE_ARGUMENT 0

    /*UBRR CALCULATION KNOWING THE FREQUENCY TO OPERATE ON
     *  pre_scaling the i/p source_system_freq
        UBRR = F_CPU(source_system_freq) / F_BD(known/agreed upon freq) - 1
     *  N depends on the mode: (TX/RX)
     *      sync Master/Slave mode: N = 2
     *      async Normal(U2X = 0 ): N = 16
     *      async Double Rate(U2X = 1) : N = 8
     *      
     */
    #define DIVISOR_SYNC_MASTER_SLAVE_MODE 2
    #define DIVISOR_ASYNC_DOUBLE_RATE_MODE 8
    #define      DIVISOR_ASYNC_NORMAL_MODE 16

    #define GET_UBRR_VALUE(BAUD_RATE_FREQUENY , DIVISOR) F_CPU / (BAUD_RATE_FREQUENY) / (DIVISOR) - 1

    #define XCK _PB_PIN0

    /*
     * UMSEL = 0 IF U2X REST NORMAL_RATE
     * CLEAR_BIT((UCSRC) , UMSEL);
       CLEAR_BIT((UCSRA) , U2X);
     */
    //#define ASYNC_NORAML_RATE_MODE 0

    /*
     * UMSEL = 0 IF U2X SET DOUBLE_RATE
     * CLEAR_BIT((UCSRC) , UMSEL);
         SET_BIT((UCSRA) , U2X);
     */
    //#define ASYNC_DOUBLE_RATE_MODE 2
        
    /*
     * UMSEL = 1 IF DDR_XCK SET MASTER
     * SET_BIT((UCSRC) , UMSEL);
       SET_BIT((DDRB) , PIN0);
     */
    //#define  SYNC_MASTER_MODE 1
    
    /*
     * UMSEL = 1 IF DDR_XCK REST SLAVE
     * SET_BIT((UCSRC) , UMSEL);
       CLEAR_BIT((DDRB) , PIN0);
     */    
    //#define  SYNC_SLAVE_MODE 3

    /*
        MPCM    0 -> 0
        U2X     1 -> 0
        UPE     2 -> 0
        DOR     3 -> 0
        FE      4 -> 0
        UDRE    5 -> 1
        TXC     6 -> 0
        RXC     7 -> 0
    */
    #define UCSRA_INITIAL_VALUE 0x20

    #define UCSRB_INITIAL_VALUE 0

    /*
     *  UCPOL   0 -> 0
        UCSZ0   1 -> 1
        UCSZ1   2 -> 1
        USBS    3 -> 0
        UPM0    4 -> 0
        UPM1    5 -> 0
        UMSEL   6 -> 0
        URSEL   7 -> 1
     */
    #define UCSRC_INITIAL_VALUE 0x86 //1000 0110

    #define ENABLE_DISABLE_USART_TX(EN_DIS)  SET_REST_REG_BIT((UCSRB) , TXEN , EN_DIS)

    #define ENABLE_DISABLE_USART_RX(EN_DIS)  SET_REST_REG_BIT((UCSRB) , RXEN , EN_DIS)

    #define ENABLE_DISABLE_USART_TX_COMPLETE_INTERRUPT(EN_DIS)  SET_REST_REG_BIT((UCSRB) , TXCIE , EN_DIS)

    #define ENABLE_DISABLE_USART_RX_COMPLETE_INTERRUPT(EN_DIS)  SET_REST_REG_BIT((UCSRB) , RXCIE , EN_DIS)

    #define ENABLE_DISABLE_USART_DATA_REG_EMPTY_INTERRUPT(EN_DIS)  SET_REST_REG_BIT((UCSRB) , UDRIE , EN_DIS)

    #define _2_OR_1_STOP_BIT(_2_OR_1_STB)  SET_REST_REG_BIT((UCSRB) , UDRIE , _2_OR_1_STOP_BIT)
    
    //#define PARITY_MODE_INPUT_MASK 0x30 //Ob 0011 0000
//    #define NO_PARITY_MODE 0
//    #define RESERVED_PARITY_MODE 0x10 // 0bxx01 xxxx
//    #define EVEN_PARITY_MODE 0x20  // 0bxx10 xxxx
//    #define ODD_PARITY_MODE 0x30   // 0bxx11 xxxx

    #define  			 SYNC_MODE_CLK_DIVISOR 2
    #define ASYNC_MODE_NORAML_RATE_CLK_DIVISOR 16
    #define ASYNC_MODE_DOUBLE_RATE_CLK_DIVISOR 8
    
    #define      PARITY_MODE_NON 0
    #define PARITY_MODE_RESERVED 1
    #define     PARITY_MODE_EVEN 2  
    #define      PARITY_MODE_ODD 3

    #define      PARITY_MODE_UPM1_SHIFT 1
    #define      PARITY_MODE_UPM0_MASK  1

    #define ASYNC_MODE 0
    #define  SYNC_MODE 1
    
    #define SYNC_MODE_MASTER 0
    #define  SYNC_MODE_SLAVE 1
    
    #define ASYNC_MODE_NORAML_RATE 0
    #define ASYNC_MODE_DOUBLE_RATE 1

    #define  POLARITY_RISING_EDGE 0
    #define POLARITY_FALLING_EDGE 1

    #define _1_STOP_BIT 0
    #define _2_STOP_BIT 1

    #define FRAME_SIZE_5_BITS 0
    #define FRAME_SIZE_6_BITS 1
    #define FRAME_SIZE_7_BITS 2
    #define FRAME_SIZE_8_BITS 3
    #define FRAME_SIZE_9_BITS 7
    #define     FRAME_SIZE_R1 4
    #define     FRAME_SIZE_R2 5
    #define     FRAME_SIZE_R3 6
    #define FRAME_SIZE_UCSZ2_SHIFT 2
    #define FRAME_SIZE_UCSZ1_MASK  2
    #define FRAME_SIZE_UCSZ0_MASK  1

//    #define USART_TX_INPUT_MASK 0x08 //Ob 0000 1000
//    #define ENABLE_USART_TX 0x08 //ob xxxx 1000
//    #define DIABLE_USART_TX 0 //ob xxxx 0000
    #define DISABLE_USART_TX REST
    #define  ENABLE_USART_TX SET

    #define DISABLE_USART_RX REST
    #define  ENABLE_USART_RX SET

    #define DISABLE_DATA_REG_EMPTY_INTERRUPT REST
    #define  ENABLE_DATA_REG_EMPTY_INTERRUPT SET

    #define DISABLE_TRANSMIT_COMPLETE_INTERRUPT REST
    #define  ENABLE_TRANSMIT_COMPLETE_INTERRUPT SET

    #define DISABLE_RECEIVE_COMPLETE_INTERRUPT REST
    #define  ENABLE_RECEIVE_COMPLETE_INTERRUPT SET

    #define DISABLE_MULTI_PROCESSOR_COMMUNICATION_MODE REST
    #define  ENABLE_MULTI_PROCESSOR_COMMUNICATION_MODE SET

    #define HIGHER_BYTE_SHIFT_FOR_UBRRH 8

    #define ENABLE_USART_TRANSMITTER SET_BIT(UCSRB , TXEN);    
    /*
     * ANY BINDING TX WILL BE COMMITED BEFORE DISABLE TX
     */
    #define DISABLE_USART_TRANSMITTER CLEAR_BIT(UCSRB , TXEN);

    #define ENABLE_USART_RECEIVER SET_BIT(UCSRB , RXEN);
    /*
     * RECEIVER DISACRDS ANY BINDING AND SHUTDOWN IMMEDIATLY
     */
    #define DISABLE_USART_RECEIVER CLEAR_BIT(UCSRB , RXEN);

    #define ENABLE_DATA_REGISTER_EMPTY_INTERRUPT_FOR_USART_RECEIVER SET_BIT(UCSRB , UDRIE);
    #define DISABLE_DATA_REGISTER_EMPTY_INTERRUPT_FOR_USART_RECEIVER CLEAR_BIT(UCSRB , UDRIE);

    #define ENABLE_TRASMIT_COMPLETE_INTERRUPT_FOR_USART_TRASMITTER SET_BIT(UCSRB , TXCIE);
    #define DISABLE_TRASMIT_COMPLETE_INTERRUPT_FOR_USART_TRASMITTER CLEAR_BIT(UCSRB , TXCIE);

    #define ENABLE_RECEIVE_COMPLETE_INTERRUPT_FOR_USART_RECEIVER SET_BIT(UCSRB , RXCIE);
    #define DISABLE_RECEIVE_COMPLETE_INTERRUPT_FOR_USART_RECEIVER CLEAR_BIT(UCSRB , RXCIE);

    #define ENABLE_ASYNC_NORMAL_RATE_MODE CLEAR_BIT(UCSRA , U2X);
    #define ENABLE_ASYNC_DOUBLE_RATE_MODE SET_BIT(UCSRA , U2X);

    #define ENABLE_MULTI_PROCESSOR_MODE SET_BIT(UCSRA , MPCM);
    #define DISABLE_MULTI_PROCESSOR_MODE CLEAR_BIT(UCSRA , MPCM);

    #define ENABLE_DISABLE_PARITY_MODE_CHOSE_ASLSO_EVEN_OR_ODD( EN_DIS , ODD_EVEN ) UCSRC = SET_REST_REG_BIT(UCSRC , UPM1 , EN_DIS );\
                                                                                     if(EN_DIS){\
                                                                                        UCSRC = SET_REST_REG_BIT(UCSRC , UPM0 , ODD_EVEN);\
                                                                                     }else{\
                                                                                     }
    #define ENABLE_2_STOP_BITS SET_BIT(UCSRC , USBS);
    #define DISABLE_2_STOP_BITS SET_BIT(UCSRC , USBS);

    #define CHANGE_POLARITY(FALLING_RISING)  UCSRC = SET_REST_REG_BIT(UCSRC , UCPOL , FALLING_RISING )

    #define CHANGE_FRAME_SIZE(FRAME_SIZE) UCSRC = SET_REST_REG_BIT(SET_REST_REG_BIT(UCSRC , UCSZ1 , FRAME_SIZE & FRAME_SIZE_UCSZ1_MASK) , UCSZ0 , FRAME_SIZE & FRAME_SIZE_UCSZ0_MASK);\
                                          UCSRB = SET_REST_REG_BIT(UCSRB , UCSZ2 , FRAME_SIZE >> FRAME_SIZE_UCSZ2_SHIFT );
    
    #define SEND_CHARACTER_TO_USART_FOR_TX(MSG) UDR = MSG;

FUN_RETURN_STATUS init_USART(u8 enable_disable_TX , 
					u8 enable_disable_RX , 
						u8 enable_disable_data_reg_empty , 
							u8 enable_disable_TX_completed , 
								u8 enable_disable_RX_completed , 
									u32 baud_rate_frequency ,
										u8 frame_size , 
											u8 communication_mode , 
												u8 case_async_normal_double_rate , 
													u8 case_sync_master_slave ,
                                                        u8 enable_disable_multi_processor_mode ,
                                                            u8 parity_mode , 
                                                                u8 stop_bits , 
                                                                    u8 polarity_falling_rising);

u8 getStatusOfUCSRA(void);

u8 getStatusOfUCSRB(void);

u8 getStatusOfUCSRC(void);

void flushUSART_RX_Buffers(void);

u16 getUBRR(void);

void transmitMSGviaUSARTusingPolling(u16 msg);

void transmitMSGviaUSARTusingPollingOnTXC(u16 msg);

void transmitMSGviaUSARTusingINTER(u16 msg);

u16 receiveMSGviaUSARTusingPolling(void);

u16 receiveMSGviaUSARTusingINTER(void);

void initiateTransimission(void);

#endif	/* USART_INTERFACE_H */