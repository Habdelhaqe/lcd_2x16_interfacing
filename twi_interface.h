/* 
 * File:   twi_interface.h
 * Author: Engs
 *
 * Created on 06 January 2022, 14:29
 */

#ifndef TWI_INTERFACE_H
#define	TWI_INTERFACE_H
    
    #include"atmega32a.h"
    /*
     * S: START condition
        Rs: REPEATED START condition
        R: Read bit (high level at SDA)
        W: Write bit (low level at SDA)
        A: Acknowledge bit (low level at SDA)
        !A: Not acknowledge bit (high level at SDA)
        Data: 8-bit data byte
        P: STOP condition
        SLA: Slave Address 
     */
    #define TWI_WAIT HIGH
    #define TWI_DONOT_WAIT LOW
    
    #define TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED 0x0
    #define TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED 0x1
    #define TWI_RESTART_SESSION_ON_NOT_ACK_RECEIVED 0x2
    
    #define TWI_ON_MASTER_TRANSMIT_DONT_CHANGE_SESSION_CONDITION_CONTINUE_TRANSMITTING_DATA 0x0
    #define TWI_ON_MASTER_TRANSMIT_REPEAT_START_FOR_NEW_SESSION 0x1
    #define TWI_ON_MASTER_TRANSMIT_STOP_SESSION 0x2
    #define TWI_ON_MASTER_TRANSMIT_RESTART_SESSION 0x3
    
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION 0x0
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION 0x1
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION 0x2
    #define TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION 0x3

    #define TWI_SESSION_MASK 0x03

    //the value should be used to cause min damage as possible to the system if used incorrectly
    #define TWI_IGNORE_ARGUMENT 0xFF

    /*
     *            Bit 7    6    5    4    3    2    1    0
                 TWAR TWA6 TWA5 TWA4 TWA3 TWA2 TWA1 TWA0 TWGCE
           Read/Write R/W  R/W  R/W  R/W  R/W  R/W  R/W  R/W
        Initial Value 1    1    1    1    1    1    1    0
     * ? Bit 0 ? TWGCE: TWI General Call Recognition Enable Bit 
       If set, this bit enables the recognition of a General Call given over the Two-wire Serial Bus
     */
    // SLA 0000 011 X(TWGCE)  
    #define TWI_OWN_SLA_IGNORE_GENERAL_CALL 0x06
    #define TWI_OWN_SLA_ENABLE_GENERAL_CALL 0x07

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
    
    //Two-wire Serial Bus will be released and not addressed slave mode entered
    #define _TWCR(R,B,H_L) SET_REST_REG_BIT(R,B,H_L)
    
/*    #define Realease_BUS_Enter_Not_Addressed_SLAVE_mode                         TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR \
                                                               , TWINT , HIGH ) , TWSTA , LOW ) , TWSTO , LOW ) , TWEN , HIGH )
*/
    #define Realease_BUS_Enter_Not_Addressed_SLAVE_mode TWCR = (HIGH << TWINT) | (HIGH << TWEN)

/*    #define Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(RECOG)            TWCR = _TWCR(_TWCR(_TWCR(_TWCR(_TWCR(TWCR \
                                                               , TWINT , HIGH ) , TWSTA , LOW ) , TWSTO , LOW ) , TWEA , (RECOG) ) , TWEN , HIGH )
*/
    #define Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(RECOG) TWCR = ((HIGH << TWINT) | (HIGH << TWEN)) &  (RECOG ? HIGH << TWEA : LOW)

    /*
     * this should be internally called
     * POLL DOWN SDA line @ SCL HIGH level To issue a P_COND to stop on going session with Slave and should another Master acquire the BUS 
     * there is no feed back on this (TWCR : TWINT is not affected) but when should it be called and could it cause an error?
     */
/*    #define TWIsendStopConditionUsePolling                                      TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR \
                                                                , TWINT , HIGH ), TWSTA , LOW ), TWSTO , HIGH ), TWEN , HIGH );
*/
    #define TWIsendStopConditionUsePolling  TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (HIGH << TWSTO);

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
    
    /*
     * function takes care of selection of frequency of SCL line CLK (polling line down to o/p LOW level or let line be/tri-state o/p HIGH level)
     * know frequency and prescalar (TWSR TWPS1,TWPS0)  TWBR gets calculated
     * consumes  many cycles cause of the MUL and DIV operations used in TWBR CALC
     */
    void initTWIselectingFrequency(u8 frequency_selection , 
                                   u8 prescalar_selection , 
                                   u8 incase_of_initiated_to_be_slave_enable_ack ,
                                   u8 enable_general_call );
    
    /*
     * function takes care of selection of frequency of SCL line CLK (polling line down to o/p LOW level or let line be/tri-state o/p HIGH level)
     * know BR assigned to TWBR and prescalar(TWSR TWPS1,TWPS0)
     * consumes  many cycles cause of the MUL and DIV operations used in TWBR CALC
     */
    void initTWIselectingBaudRate(u8 baud_rate_divisor_selection , 
                                  u8 prescalar_selection , 
                                  u8 incase_of_initiated_to_be_slave_enable_ack , 
                                  u8 enable_general_call);
    
    /*
     * this should be internally called
     * POLL DOWN SDA line @ SCL HIGH level To issue a S_COND ON SDA to notify/alert all devices on BUS
     * if success (TWSR = $08) then an attempt to acquire the BUS should be followed sending SLA_R/W
     * or success (TWSR = $10) then an attempt to acquire the BUS should be followed sending SLA_R/W SLA:same SL or another
     * else if BUS is busy ? trying to acquire the line during session of another Master sending SLA_R/W or Data or ACK during which SCL could be @ HIGH
     * level , may be it's not possible cause of the START/STOP Condition Control Unit Inside the BUS Control
     * the TWI_POLLING_TILL_JOB_IS_DONE halts the execution of function hance TWI stalled also CPU stalled 
     */
    u8 TWI_send_Start_RepeatedStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call);

    /*
     * this should be internally called
     * POLL DOWN SDA line @ SCL HIGH level To issue a RS_COND ON SDA to notify/alert all devices on BUS of the current extension of on going Master session
     * if success (TWSR = $10) then an attempt to acquire the BUS should be followed sending SLA_R/W SLA:same SL or another
     * else if BUS is busy ? this not illegal once acquired by Master RS_COND is OK But The Response Of SL may affect upcoming communication
     * the TWI_POLLING_TILL_JOB_IS_DONE halts the execution of function hance TWI stalled also CPU stalled 
     */
//    u8 TWIsendReapeatedStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call);
    
    /*
     * this should be internally called
     * POLL DOWN SDA line @ SCL HIGH level To issue a S_COND immediately after P_COND ON SDA to notify/alert all devices on BUS
     * if success (TWSR = $08) then an attempt to acquire the BUS should be followed sending SLA_R/W
     * else if BUS is busy ? trying to acquire the line during session of another Master sending SLA_R/W or Data or ACK during which SCL could be @ HIGH
     * level , may be it's not possible cause of the START/STOP Condition Control Unit Inside the BUS Control
     * the TWI_POLLING_TILL_JOB_IS_DONE halts the execution of function hance TWI stalled also CPU stalled 
     */
    u8 TWISendRestartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call);
    
    
    /*
     * caller wishes to start session with a slave should call this function which calls @TWI_send_Start_RepeatedStartConditionUsePolling 
     * if successful then SLA_R/W placed on SDA along with CLK generated on SCL now the arbitration could occur on the BUS known through the TWSR response
     * which is what the function returns
     * also the caller should not concern him self with the return the other functions talks care of that but he could if he wants
     */
    u8 TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
                                                  u8 enable_general_call ,
                                                  u8 enable_ack_when_in_receiving_mode ,
                                                  u8 SLA__R_W);

//    u8 TWIReinitiateSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
//                                                    u8 enable_general_call , 
//                                                    u8 twi_slave_addr_RX_or_TX);

    u8 TWIRestartSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
                                                 u8 enable_general_call ,
                                                 u8 enable_ack_when_in_receiving_mode ,
                                                 u8 SLA_R_W);

    u8 TWITransmitDataToSlaveTWIusingPolling(u8 data , 
                                         u8 force_transmit ,                                           
                                         u8 donot_change_session_cond_or_repeat_or_stop_or_restart_session ,
                                         u8 SLA_R_W_on_repeat_restart ,
                                         u8 enable_addressed_as_slave_when_arbitration_lost ,
                                         u8 enable_general_call ,
                                         u8 enable_ack_when_in_receiving_mode ,
                                         u8 on_lost_arbitration_initiate_another_start);
    
    scan_fun_return TWIReceiveDataFromSlaveTWIusingPolling(u8 received_data_ack_or_not , 
                                          u8 incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session , 
                                          u8 SLA_R_W_on_repeat_restart ,
                                          u8 enable_addressed_as_slave_when_arbitration_lost ,
                                          u8 enable_general_call ,
                                          u8 enable_ack_when_in_receiving_mode ,
                                          u8 on_lost_arbitration_initiate_another_start);
    
    u8 TWITransmitDataToMasterTWIusingPolling(u8 transmit_data ,
                                              u8 enable_ack ,                                           
                                              u8 enter_slave_no_add_mode_enable_recog_add_enable_start ,
                                              u8 SLA_R_W_on_repeat_restart ,   
                                              u8 enable_general_call);

    scan_fun_return TWIReceiveDataFromMasterTWIusingPolling(u8 received_data_ack_or_not , 
                                                            u8 enter_slave_no_add_mode_enable_recog_add_enable_start ,
                                                            u8 SLA_R_W_on_repeat_restart ,
                                                            u8 enable_general_call );
    
#endif	/* TWI_INTERFACE_H */