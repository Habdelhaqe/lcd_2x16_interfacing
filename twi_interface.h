/* 
 * File:   twi_interface.h
 * Author: Engs
 *
 * Created on 06 January 2022, 14:29
 */

#ifndef TWI_INTERFACE_H
#define	TWI_INTERFACE_H
    
    #include"atmega32a.h"

    #define TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED 0x0
    #define TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED 0x1
    #define TWI_RESTART_SESSION_ON_NOT_ACK_RECEIVED 0x2
    
    #define TWI_ON_MASTER_TRANSMIT_DONT_CHANGE_SESSION_CONDITION 0x0
    #define TWI_ON_MASTER_TRANSMIT_REPEAT_SESSION 0x1
    #define TWI_ON_MASTER_TRANSMIT_STOP_SESSION 0x2
    #define TWI_ON_MASTER_TRANSMIT_RESTART_SESSION 0x3
    
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION 0x0
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION 0x1
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION 0x2
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION 0x3

    #define TWI_SESSION_MASK 0x03


    /*
     *            Bit 7    6    5    4    3    2    1    0
                 TWAR TWA6 TWA5 TWA4 TWA3 TWA2 TWA1 TWA0 TWGCE
           Read/Write R/W  R/W  R/W  R/W  R/W  R/W  R/W  R/W
        Initial Value 1    1    1    1    1    1    1    0
     * ? Bit 0 ? TWGCE: TWI General Call Recognition Enable Bit 
       If set, this bit enables the recognition of a General Call given over the Two-wire Serial Bus
     */

    #define TWI_OWN_SLA_IGNORE_GENERAL_CALL 0x02
    #define TWI_OWN_SLA_ENABLE_GENERAL_CALL 0x03


    /*
     *        Bit 7    6    5    4    3    2 1     0
             TWSR TWS7 TWS6 TWS5 TWS4 TWS3 ? TWPS1 TWPS0
       Read/Write R     R   R    R    R    R R/W   R/W
    Initial Value 1     1   1    1    1    0 0     0
     */
    #define TWI_PRESCALAR_TWPS0_MASK 0x01
    #define TWI_PRESCALAR_TWPS1_MASK 0x02
    #define TWI_PRESCALAR_MASK 0x03

    //TWSR =>                       TWPS1 TWPS0
    #define TWI_PRESCALAR_1     0 //  0     0 
    #define TWI_PRESCALAR_4     1 //  0     1
    #define TWI_PRESCALAR_16    2 //  1     0
    #define TWI_PRESCALAR_64    3 //  1     1

    //TWSR 7:3 TWS7:TWS3
    #define TWI_STATUS_MACHINE_MASK 0xF8

    //MT MODE RESPONSES
    #define TWI_START_condition_has_been_trasnmitted 0x08
    #define TWI_repeated_START_condition_has_been_transmitted 0x10
    #define TWI_SLA__W_has_been_transmitted_ACK_has_been_received 0x18
    #define TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received 0x20
    #define TWI_Data_byte_has_been_transmitted_ACK_has_been_received 0x28
    #define TWI_Data_byte_has_been_transmitted_NOT_ACK_has_been_received 0x30
    #define TWI_Arbitration_lost_in_SLA__W_or_data_bytes_ALSO_Arbitration_lost_in_SLA__R_or_NOT_ACK_bit 0x38
    
    //MR MODE RESPONSES
    //the same as above    
    //#define TWI_START_condition_has_been_trasnmitted 0x08
    //#define TWI_repeated_START_condition_has_been_transmitted 0x10
    //#define TWI_Arbitration_lost_in_SLA__W_or_data_bytes_ALSO_Arbitration_lost_in_SLA__R_or_NOT_ACK_bit 0x38
    #define TWI_SLA__R_has_been_transmitted_ACK_has_been_received 0x40
    #define TWI_SLA__R_has_been_transmitted_NOT_ACK_has_been_received 0x48
    #define TWI_Data_byte_has_been_received_ACK_has_been_returned 0x50
    #define TWI_Data_byte_has_been_received_NOT_ACK_has_been_returned 0x58
    
    //SR MODE RESPONSES
    #define TWI_Own_SLA__W_has_been_received_ACK_has_been_returned 0x60
    #define TWI_Arbitration_lost_in_SLA__R_W_as_master_own_SLA__W_has_been_received_ACK_has_been_returned 0x68
    #define TWI_General_call_address_has_been_received_ACK_has_been_returned 0x70
    #define TWI_Arbitration_lost_in_SLA__R_W_as_master_General_call_address_has_been_received_ACK_has_been_returned 0x78
    #define TWI_Previously_addressed_with_own_SLA__W_data_has_been_received_ACK_has_been_returned 0x80
    #define TWI_Previously_addressed_with_own_SLA__W_data_has_been_received_NOT_ACK_has_been_returned 0x88
    #define TWI_Previously_addressed_with_general_call_data_has_been_received_ACK_has_been_returned 0x90
    #define TWI_Previously_addressed_with_general_call_data_has_been_received_NOT_ACK_has_been_returned 0x98
    #define TWI_A_STOP_condition_or_repeated_START_condition_has_been_received_while_still_addressed_as_slave 0xA0

    //ST MODE RESPONSES
    #define TWI_Own_SLA__R_has_been_received_ACK_has_been_returned 0xA8
    #define TWI_Arbitration_lost_in_SLA__R_W_as_master_own_SLA__R_has_been_received_ACK_has_been_returned 0xB0
    #define TWI_Data_byte_in_TWDR_has_been_transmitted_ACK_has_been_received 0xB8
    #define TWI_Data_byte_in_TWDR_has_been_transmitted_NOT_ACK_has_been_received 0xC0
    #define TWI_Last_data_byte_in_TWDR_has_been_transmitted_TWEA_equals_0_ACK_has_been_received 0xC8

    //Miscellaneous States
    #define TWI_No_relevant_state_information_available_TWINT_equals_0 0xF8
    #define TWI_Bus_error_due_to_an_illegal_START_or_STOP_condition 0x00

    #define TWI_GET_MACHINE_STAT MASK_8_BIT_REG(TWSR , TWI_STATUS_MACHINE_MASK)

    #define TWI_POLLING_TILL_JOB_IS_DONE while(!GET_BIT(TWCR , TWINT))
    
    /*
     * SCL frequency = CPU Clock frequency / (16 +2 * TWBR * 4 ^ TWPS)
     */

     
     /*
      *           Bit 7     6   5    4    3    2    1    0
                 TWDR TWD7 TWD6 TWD5 TWD4 TWD3 TWD2 TWD1 TWD0 
           Read/Write R/W  R/W  R/W  R/W  R/W  R/W  R/W  R/W
        Initial Value 1    1    1    1    1    1    1    1 
      */

    /*
     *            Bit 7    6    5    4    3    2    1    0
                 TWAR TWA6 TWA5 TWA4 TWA3 TWA2 TWA1 TWA0 TWGCE 
           Read/Write R/W  R/W  R/W  R/W  R/W  R/W  R/W  R/W
        Initial Value 1    1    1    1    1    1    1    0
    */
    
    void initTWIselectingFrequency(u8 frequency_selection , u8 prescalar_selection);
    
    void initTWIselectingBaudRate(u8 baud_rate_divisor_selection , u8 prescalar_selection);
    
    //this should be internally called
    u8 TWIsendStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call);

    //this should be internally called
    u8 TWIsendReapeatedStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call);
    
    //this should be internally called
    u8 TWIRestartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call);
    
    //this should be internally called
    void TWIsendStopConditionUsePolling(void);
    
    u8 TWIinitiateSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call , u8 twi_slave_addr_RX_or_TX);

    u8 TWIRestartSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call ,u8 twi_slave_addr_RX_or_TX);

    u8 TWITransmitDataToSlaveTWIusingPolling(u8 data , 
                                         u8 force_transmit ,                                           
                                         u8 repeat_or_stop_or_restart_session , 
                                         u8 enable_addressed_as_slave_when_arbitration_lost ,
                                         u8 enable_general_call ,    
                                         u8 on_lost_arbitration_initiate_another_start);
    
    scan_fun_return TWIReceiveDataFromSlaveTWIusingPolling(u8 received_data_ack_or_not , 
                                          u8 incase_of_nack_sent_back_repeat_or_stop_or_restart_session , 
                                          u8 enable_addressed_as_slave_when_arbitration_lost ,
                                          u8 enable_general_call ,    
                                          u8 on_lost_arbitration_initiate_another_start);
    
    u8 TWITransmitDataToMasterTWIusingPolling(u8 transmit_data ,
                                         u8 enable_ack ,                                           
                                         u8 no_add_mode_start_or_not_ack_or_not , 
                                         u8 enable_general_call);

    scan_fun_return TWIReceiveDataFromMasterTWIusingPolling(u8 received_data_ack_or_not , 
                                          u8 no_add_mode_start_or_not_ack_or_not , 
                                          u8 enable_general_call );
    
#endif	/* TWI_INTERFACE_H */