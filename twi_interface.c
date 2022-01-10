#include"twi_interface.h"
#include "interfacing_connection_logic.h"

extern scan_fun_return fun_ret_status_and_data;

#define   ERR_CHECKER fun_ret_status_and_data.fun_return
#define RECEIVED_DATA fun_ret_status_and_data.scanned_data

void initTWIselectingBaudRate(u8 baud_rate_divisor_selection , 
                              u8 prescalar_selection , 
                              u8 incase_of_initiated_to_be_slave_enable_ack ,
                              u8 enable_general_call){
    TWBR = baud_rate_divisor_selection;
    TWSR = SET_REST_REG_BIT(SET_REST_REG_BIT(TWSR , TWPS0 , prescalar_selection & TWI_PRESCALAR_TWPS0_MASK) , 
            TWPS1 , prescalar_selection & TWI_PRESCALAR_TWPS1_MASK);
    
    if(incase_of_initiated_to_be_slave_enable_ack){
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR
//                , TWSTA , OFF )
//                , TWSTO , OFF ) 
//                , TWEN , ON )
//                , TWEA , TRUE);

        TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;        
        TWCR = (HIGH << TWEN) | (HIGH << TWEA) ; 
    }            
}

void initTWIselectingFrequency(u8 frequency_selection , 
                               u8 prescalar_selection , 
                               u8 incase_of_initiated_to_be_slave_enable_ack ,
                               u8 enable_general_call ){
    
    prescalar_selection &=TWI_PRESCALAR_MASK;
    
    TWSR = SET_REST_REG_BIT(SET_REST_REG_BIT(TWSR , TWPS0 , prescalar_selection & TWI_PRESCALAR_TWPS0_MASK) , 
            TWPS1 , prescalar_selection & TWI_PRESCALAR_TWPS1_MASK);
    
    TWBR = (F_CPU / frequency_selection - 16 ) / 2 / prescalar_selection == 3 ? 32 : 
                                                     prescalar_selection == 2 ? 16 : 
                                                         !prescalar_selection ? 1  : 4;

    if(incase_of_initiated_to_be_slave_enable_ack){
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR
//                , TWSTA , OFF ) 
//                , TWSTO , OFF ) 
//                , TWEN , ON )
//                , TWEA , TRUE);

        TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;        
        TWCR = (HIGH << TWEN) | (HIGH << TWEA) ; 
    }        
}

u8 TWI_send_Start_RepeatedStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
                                                   u8 enable_general_call){
    
    //i have no way to check if bus is ideal this is done by HW=> S/P Controller
    if(enable_addressed_as_slave_when_arbitration_lost){
       TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;
       enable_addressed_as_slave_when_arbitration_lost = enable_addressed_as_slave_when_arbitration_lost ? TRUE : FALSE; 
    }
    
//    TWCR = _TWCR(_TWCR(_TWCR(_TWCR(_TWCR(TWCR 
//            , TWINT , HIGH ) 
//            , TWSTA , HIGH ) 
//            , TWSTO , LOW ) 
//            , TWEN , HIGH )
//            , TWEA , enable_addressed_as_slave_when_arbitration_lost);
    
    TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (HIGH << TWSTA) | (enable_addressed_as_slave_when_arbitration_lost ? HIGH << TWEA : LOW); 
    TWI_POLLING_TILL_JOB_IS_DONE;    
    return TWI_GET_MACHINE_STAT;
}

u8 TWISendRestartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
                                     u8 enable_general_call){
    
    if((TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_ACK_has_been_received ||
       (TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received ||
            
       (TWI_GET_MACHINE_STAT) == TWI_SLA__R_has_been_transmitted_NOT_ACK_has_been_received ||
            
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_ACK_has_been_received ||   
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_NOT_ACK_has_been_received ||
            
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_ACK_has_been_returned ||   
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_NOT_ACK_has_been_returned  
       ){
        
        if(enable_addressed_as_slave_when_arbitration_lost){
            TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;
            enable_addressed_as_slave_when_arbitration_lost = enable_addressed_as_slave_when_arbitration_lost ? HIGH : LOW; 
        }
        
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(_TWCR(TWCR 
//                , TWINT , HIGH ) 
//                , TWSTA , HIGH ) 
//                , TWSTO , HIGH ) 
//                , TWEN , HIGH ) 
//                , TWEA , enable_addressed_as_slave_when_arbitration_lost);
        
        TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (HIGH << TWSTA) | (HIGH << TWSTO) | 
               (enable_addressed_as_slave_when_arbitration_lost ? HIGH << TWEA : LOW); 
        //wait for S_COND placed on BUS
        TWI_POLLING_TILL_JOB_IS_DONE;
    }else{
        //what that mean being here?    
    }
    return TWI_GET_MACHINE_STAT;
}


//TWI in MT mode And Addressing Slave TWI
u8 TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
                                              u8 enable_general_call , 
                                              u8 enable_ack_when_in_receiving_mode ,
                                              u8 SLA__R_W){
    
    //check if S_COND is TX successfully (Bus Is IDLE seize it)
    u8 response_code = TWI_send_Start_RepeatedStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call);
    
    displayINTOnLCD(response_code);
    
    //action made in case of S OR Rs is the same but TWSR code/response is different
    if(response_code == TWI_START_condition_has_been_trasnmitted || 
       response_code == TWI_repeated_START_condition_has_been_transmitted){
    
        TWDR = SLA__R_W;

//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//                , TWSTA , LOW ) 
//                , TWSTO , LOW ) 
//                , TWEN , HIGH ) 
//                , TWEA , enable_ack_when_in_receiving_mode ? TRUE : FALSE );
        
        TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (enable_ack_when_in_receiving_mode ? HIGH << TWEA : LOW) ; 

        
    }else if(response_code == TWI_Bus_error_due_to_an_illegal_START_or_STOP_condition){
        //BUS is Busy or what?
        /*
         * To recover from a bus error, the TWSTO Flag must set and TWINT must be cleared by writing a logic one to it. 
         * This causes the TWI to enter the not addressed slave mode and to clear the TWSTO Flag (no other bits in TWCR are affected). 
         * The SDA and SCL lines are released, and no STOP condition is transmitted.
         */
//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//                , TWSTA , LOW ) 
//                , TWSTO , HIGH ) 
//                , TWEN , HIGH );        

        TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (HIGH << TWSTO);
    
    }else if(response_code == TWI_No_relevant_state_information_available_TWINT_equals_0){
        //Wait or proceed current transfer
    }
    
    /*
     * wait for ACK back From Slave TWI OR lose Arbitration in case of success S OR Rs
     * wait for TWI to assert BUS ERROR handling
     */
    TWI_POLLING_TILL_JOB_IS_DONE;

    return TWSR;
}

/*
 * this function allow for Arbitration to happen
 */
u8 TWIRestartSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
                                             u8 enable_general_call , 
                                             u8 enable_ack_when_in_receiving_mode ,
                                             u8 SLA_R_W){

    //check if P THEN S_COND is successfully (Bus Is IDLE seize it)
    u8 response_code = TWISendRestartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call);
    
    if(response_code == TWI_START_condition_has_been_trasnmitted){
    
        TWDR = SLA_R_W;

//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//                , TWSTA , LOW ) 
//                , TWSTO , LOW ) 
//                , TWEN , HIGH ) 
//                , TWEA , enable_ack_when_in_receiving_mode ? TRUE : FALSE );
        
        TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (enable_ack_when_in_receiving_mode ? HIGH << TWEA : LOW) ; 
            
    }else if(response_code == TWI_Bus_error_due_to_an_illegal_START_or_STOP_condition){
        //BUS is Busy or what?
        /*
         * To recover from a bus error, the TWSTO Flag must set and TWINT must be cleared by writing a logic one to it. 
         * This causes the TWI to enter the not addressed slave mode and to clear the TWSTO Flag (no other bits in TWCR are affected). 
         * The SDA and SCL lines are released, and no STOP condition is transmitted.
         */
//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//                , TWSTA , LOW ) 
//                , TWSTO , HIGH ) 
//                , TWEN , HIGH );
        TWCR = (HIGH << TWINT) | (HIGH << TWEN) | (HIGH << TWSTO) ;
    }else if(response_code == TWI_No_relevant_state_information_available_TWINT_equals_0){
        //Wait or proceed current transfer
    }

    /*
     * wait for ACK back From Slave TWI OR lose Arbitration in case of success P THEN S
     * wait for TWI to assert BUS ERROR handling
     */
    TWI_POLLING_TILL_JOB_IS_DONE;
    
    return TWSR;
}

/*
 * first check TWSR code which will be oriented  by calling one of :
 * @TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling
 * @TWIRestartSessionWithSalveTWIusingPolling
 * 
 * which abstracts calls to one of :
 * @TWI_send_Start_RepeatedStartConditionUsePolling
 * @TWISendRestartConditionUsePolling
 *  
 * the TX As Master will only happen when
 * TWSAR = TWI_SLA__W_has_been_transmitted_ACK_has_been_received
 *         OR TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received and in that case force_transmit is SET
 */
u8 TWITransmitDataToSlaveTWIusingPolling(u8 data , 
                                         u8 force_transmit ,                                           
                                         u8 donot_change_session_cond_or_repeat_or_stop_or_restart_session ,
                                         u8 SLA_R_W_on_repeat_restart ,
                                         u8 enable_addressed_as_slave_when_arbitration_lost ,
                                         u8 enable_general_call ,
                                         u8 enable_ack_when_in_receiving_mode ,
                                         u8 on_lost_arbitration_initiate_another_start){
    
    u8 wait_till_TWI_assert_the_job = TWI_WAIT ;

    if( (TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_ACK_has_been_received ||
        (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_ACK_has_been_received ||
        (force_transmit && (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_NOT_ACK_has_been_received) ||    
        (force_transmit && (TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received)){

        TWDR = data;

        //TWCR After Placing Data On The BUS/where or what to do after Data Placed?
        donot_change_session_cond_or_repeat_or_stop_or_restart_session &= TWI_SESSION_MASK;
        
        switch(donot_change_session_cond_or_repeat_or_stop_or_restart_session){
                
            case TWI_ON_MASTER_TRANSMIT_DONT_CHANGE_SESSION_CONDITION_CONTINUE_TRANSMITTING_DATA :

//                TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR 
//                        , TWINT , HIGH ) 
//                        , TWSTA , LOW ) 
//                        , TWSTO , LOW ) 
//                        , TWEN , HIGH );
                
                TWCR =  (HIGH << TWINT) | (HIGH << TWEN);
                break;
                
            case TWI_ON_MASTER_TRANSMIT_REPEAT_START_FOR_NEW_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                                        enable_general_call ,
                                                                        enable_ack_when_in_receiving_mode ,
                                                                        SLA_R_W_on_repeat_restart);
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
                break;
            
            case TWI_ON_MASTER_TRANSMIT_STOP_SESSION :
                TWIsendStopConditionUsePolling;
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
//                wait_till_TWI_assert_the_job = TWI_WAIT;
                break;
                
            case TWI_ON_MASTER_TRANSMIT_RESTART_SESSION :
                TWIRestartSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                          enable_general_call ,
                                                          enable_ack_when_in_receiving_mode ,  
                                                          SLA_R_W_on_repeat_restart);
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
                break;
        }
            
    }else if((TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__W_or_data_bytes_ALSO_Arbitration_lost_in_SLA__R_or_NOT_ACK_bit){
        
        if(on_lost_arbitration_initiate_another_start) {
            
            TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                                    enable_general_call ,
                                                                    enable_ack_when_in_receiving_mode ,
                                                                    SLA_R_W_on_repeat_restart);            
            wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
            
        }else{
            //Two-wire Serial Bus will be released and not addressed slave mode entered
            Realease_BUS_Enter_Not_Addressed_SLAVE_mode;
        }
            
    }else{
        //what will get logic here?
        wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
    } 
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }

    return TWSR;
}

scan_fun_return TWIReceiveDataFromSlaveTWIusingPolling(u8 received_data_ack_or_not , 
                                          u8 incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session , 
                                          u8 SLA_R_W_on_repeat_restart ,
                                          u8 enable_addressed_as_slave_when_arbitration_lost ,
                                          u8 enable_general_call ,
                                          u8 enable_ack_when_in_receiving_mode ,
                                          u8 on_lost_arbitration_initiate_another_start){
    
    u8 wait_till_TWI_assert_the_job = TWI_WAIT ;
    
    ERR_CHECKER = NO_ERRORS;
    
    if( (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_ACK_has_been_returned  ){
        
        RECEIVED_DATA = TWDR;
        
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(
//                _TWCR(TWCR , TWINT , HIGH )
//                , TWSTA , LOW ) 
//                , TWSTO , LOW ) 
//                , TWEN , HIGH ) 
//                , TWEA , received_data_ack_or_not ? TRUE : FALSE );
        TWCR = ( (HIGH << TWINT) | (HIGH << TWEN) ) | (received_data_ack_or_not ? (HIGH<< TWEA) : LOW) ;
    }else if((TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_NOT_ACK_has_been_returned){

        RECEIVED_DATA = TWDR;

        wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;

        incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session &= TWI_SESSION_MASK;
        
        if(incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session == TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED){

            TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                                    enable_general_call ,
                                                                    enable_ack_when_in_receiving_mode ,
                                                                    SLA_R_W_on_repeat_restart);
        
        }else if(incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session == TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWIsendStopConditionUsePolling;
        
        }else{
        
            TWIRestartSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                      enable_general_call , 
                                                      enable_ack_when_in_receiving_mode ,
                                                      SLA_R_W_on_repeat_restart);
        }
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_SLA__R_has_been_transmitted_ACK_has_been_received){
       
//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH )
//                , TWSTA , LOW ) 
//                , TWSTO , LOW ) 
//                , TWEN , HIGH ) 
//                , TWEA , received_data_ack_or_not ? HIGH : LOW );
                
        TWCR = ((HIGH << TWINT) | (HIGH << TWEN)) | (received_data_ack_or_not ? (HIGH << TWEA) : LOW) ;
        ERR_CHECKER = DATA_NOT_AVAILABLE ;
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_SLA__R_has_been_transmitted_NOT_ACK_has_been_received){

        wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;

        ERR_CHECKER = DATA_NOT_AVAILABLE ;

        /*
         * incase_of_nack_sent_back_repeat_or_stop_or_restart_session = 
         *          TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED : Repeated START will be transmitted
         *          TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED   : STOP condition will be transmitted and TWSTO Flag will be reset
         *          TWI_RESTART_SESSION_ON_NOT_ACK_RECEIVED: STOP condition followed by a START condition will be transmitted and TWSTO Flag will be reset
        */
        
        incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session &= TWI_SESSION_MASK;
        
        if(incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session == TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                                    enable_general_call ,
                                                                    enable_ack_when_in_receiving_mode ,    
                                                                    SLA_R_W_on_repeat_restart);
        
        }else if(incase_of_nack_sent_back_to_slave_repeat_or_stop_or_restart_session == TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWIsendStopConditionUsePolling;
        
        }else{
        
            TWIRestartSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                      enable_general_call , 
                                                      enable_ack_when_in_receiving_mode ,
                                                      SLA_R_W_on_repeat_restart);
        }
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__W_or_data_bytes_ALSO_Arbitration_lost_in_SLA__R_or_NOT_ACK_bit){

        ERR_CHECKER = DATA_NOT_AVAILABLE ;
        
        if(on_lost_arbitration_initiate_another_start) {

            TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling(enable_addressed_as_slave_when_arbitration_lost , 
                                                                    enable_general_call ,
                                                                    enable_ack_when_in_receiving_mode ,
                                                                    SLA_R_W_on_repeat_restart);            
            wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
            
        }else{
            //Two-wire Serial Bus will be released and not addressed slave mode entered
            Realease_BUS_Enter_Not_Addressed_SLAVE_mode;
        }
    }else{
        //what will get logic here?
        wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
    }
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }
    
    return fun_ret_status_and_data;
}

u8 TWITransmitDataToMasterTWIusingPolling(u8 transmit_data ,
                                          u8 enable_ack ,                                           
                                          u8 enter_slave_no_add_mode_enable_recog_add_enable_start ,
                                          u8 SLA_R_W_on_repeat_restart ,   
                                          u8 enable_general_call){
    
    u8 wait_till_TWI_assert_the_job = TWI_WAIT;
    
    if((TWI_GET_MACHINE_STAT) == TWI_Own_SLA__R_has_been_received_ACK_has_been_returned || 
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_in_TWDR_has_been_transmitted_ACK_has_been_received ||
       (TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__R_W_as_master_own_SLA__R_has_been_received_ACK_has_been_returned ){
        
        TWDR = transmit_data ;
        
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR 
//                , TWINT , HIGH )
//                , TWEA , enable_ack ? TRUE : FALSE ) 
//                , TWSTO , LOW ) 
//                , TWEN , HIGH );
                
        TWCR = ((HIGH << TWINT) | (HIGH << TWEN)) | (enable_ack ? (HIGH << TWEA) : LOW);  
    }else if((TWI_GET_MACHINE_STAT) == TWI_Data_byte_in_TWDR_has_been_transmitted_NOT_ACK_has_been_received ||
             (TWI_GET_MACHINE_STAT) == TWI_Last_data_byte_in_TWDR_has_been_transmitted_TWEA_equals_0_ACK_has_been_received ){
        
        enter_slave_no_add_mode_enable_recog_add_enable_start &= TWI_SESSION_MASK;
        
        switch(enter_slave_no_add_mode_enable_recog_add_enable_start){
            //Switched to the not addressed Slave mode; no recognition of own SLA or GCA
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION :
                Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(FALSE);
                break;
            
            //Switched to the not addressed Slave mode;own SLA will be recognized;    
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION :
                Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(TRUE);
                break;
                
            //Switched to the not addressed Slave mode;no recognition of own SLA or GCA; a START condition will be transmitted when the bus becomes free   
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling( FALSE , 
                                                                         enable_general_call ,
                                                                         FALSE ,   
                                                                         SLA_R_W_on_repeat_restart);            
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
                break;

            /*Switched to the not addressed Slave mode; own SLA will be recognized;GCA will be recognized if TWGCE = ?1?;a START condition will be 
             *transmitted when the bus becomes free
             */                
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling( FALSE , 
                                                                         enable_general_call ,
                                                                         TRUE ,   
                                                                         SLA_R_W_on_repeat_restart);            
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
        }
        
    }else{
        //what will get logic here?
        wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
    }
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }
    
    return TWSR;
}

scan_fun_return TWIReceiveDataFromMasterTWIusingPolling(u8 received_data_ack_or_not , 
                                                        u8 enter_slave_no_add_mode_enable_recog_add_enable_start ,
                                                        u8 SLA_R_W_on_repeat_restart ,
                                                        u8 enable_general_call ){
    
    u8 wait_till_TWI_assert_the_job = TWI_WAIT;
    
    ERR_CHECKER = NO_ERRORS;
    
    if((TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_own_SLA__W_data_has_been_received_ACK_has_been_returned || 
       (TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_general_call_data_has_been_received_ACK_has_been_returned ){
        
        RECEIVED_DATA = TWDR;
        
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR 
//                , TWINT , HIGH )
//                , TWSTO , LOW ) 
//                , TWEN  , HIGH ) 
//                , TWEA  , received_data_ack_or_not ? TRUE : FALSE );

        TWCR = ((HIGH << TWINT) | (HIGH << TWEN)) | (received_data_ack_or_not ? (HIGH << TWEA) : LOW);  
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_own_SLA__W_data_has_been_received_NOT_ACK_has_been_returned || 
             (TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_general_call_data_has_been_received_NOT_ACK_has_been_returned){

        RECEIVED_DATA = TWDR;
        
        enter_slave_no_add_mode_enable_recog_add_enable_start &= TWI_SESSION_MASK;
        
        switch(enter_slave_no_add_mode_enable_recog_add_enable_start){
            //Switched to the not addressed Slave mode; no recognition of own SLA or GCA            
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION :
                Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(FALSE);
                break;
            
            //Switched to the not addressed Slave mode;own SLA will be recognized;    
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION :
                Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(TRUE);
                break;
                
            //Switched to the not addressed Slave mode;no recognition of own SLA or GCA; a START condition will be transmitted when the bus becomes free   
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling( FALSE , 
                                                                         enable_general_call ,
                                                                         FALSE ,   
                                                                         SLA_R_W_on_repeat_restart);            
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
                break;

            /*Switched to the not addressed Slave mode; own SLA will be recognized;GCA will be recognized if TWGCE = ?1?;a START condition will be 
             *transmitted when the bus becomes free
             */                
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling( FALSE , 
                                                                         enable_general_call ,
                                                                         TRUE ,   
                                                                         SLA_R_W_on_repeat_restart);            
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
        }
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Own_SLA__W_has_been_received_ACK_has_been_returned || 
             (TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__R_W_as_master_own_SLA__W_has_been_received_ACK_has_been_returned ||
             (TWI_GET_MACHINE_STAT) == TWI_General_call_address_has_been_received_ACK_has_been_returned ||
             (TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__R_W_as_master_General_call_address_has_been_received_ACK_has_been_returned){
        
        ERR_CHECKER = DATA_NOT_AVAILABLE;
        
//        TWCR = _TWCR(_TWCR(_TWCR(_TWCR(TWCR 
//                , TWINT , HIGH )
//                , TWSTO , LOW ) 
//                , TWEN  , HIGH ) 
//                , TWEA  , received_data_ack_or_not ? HIGH : LOW );
        TWCR = ((HIGH << TWINT) | (HIGH << TWEN)) | (received_data_ack_or_not ? (HIGH << TWEA) : LOW);  
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_A_STOP_condition_or_repeated_START_condition_has_been_received_while_still_addressed_as_slave){

        ERR_CHECKER = DATA_NOT_AVAILABLE;
        
        enter_slave_no_add_mode_enable_recog_add_enable_start &= TWI_SESSION_MASK;
        
        switch(enter_slave_no_add_mode_enable_recog_add_enable_start){
            //Switched to the not addressed Slave mode; no recognition of own SLA or GCA            
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION :
                Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(FALSE);
                break;
            
            //Switched to the not addressed Slave mode;own SLA will be recognized;    
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION :
                Realease_BUS_Enter_Not_Addressed_SLAVE_mode_RECOG(TRUE);
                break;
                
            //Switched to the not addressed Slave mode;no recognition of own SLA or GCA; a START condition will be transmitted when the bus becomes free   
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling( FALSE , 
                                                                         enable_general_call ,
                                                                         FALSE ,   
                                                                         SLA_R_W_on_repeat_restart);            
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
                break;

            /*Switched to the not addressed Slave mode; own SLA will be recognized;GCA will be recognized if TWGCE = ?1?;a START condition will be 
             *transmitted when the bus becomes free
             */                
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION :
                TWI_initiate_Re_initiateSessionWithSalveTWIusingPolling( FALSE , 
                                                                         enable_general_call ,
                                                                         TRUE ,   
                                                                         SLA_R_W_on_repeat_restart);            
                wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
        }        
    }else{
        //what will get logic here?
        wait_till_TWI_assert_the_job = TWI_DONOT_WAIT;
    }
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }
   
    return fun_ret_status_and_data;
}

//MASTER mode Initiate Session From Seized BUS
//u8 TWIsendReapeatedStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call){
//
//    /*
//     * TWCR TWINT TWEA                                            TWSTA TWSTO TWWC TWEN ? TWIE
//      Value 1     enable_addressed_as_slave_when_arbitration_lost 1     0     X    1    0 X
//     */
//
//    if(enable_addressed_as_slave_when_arbitration_lost){
//       TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;
//       enable_addressed_as_slave_when_arbitration_lost = enable_addressed_as_slave_when_arbitration_lost ? HIGH : LOW; 
//    }
//    
//    TWCR = SET_REST_REG_BIT(
//            SET_REST_REG_BIT(
//            SET_REST_REG_BIT(
//            SET_REST_REG_BIT(
//            SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//            , TWSTA , HIGH ) 
//            , TWSTO , LOW ) 
//            , TWEN , HIGH )
//            , TWEA , enable_addressed_as_slave_when_arbitration_lost );
//    
//    TWI_POLLING_TILL_JOB_IS_DONE;
//    
//    return TWI_GET_MACHINE_STAT;
//}

//u8 TWIReinitiateSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , 
//                                              u8 enable_general_call , 
//                                              u8 twi_slave_addr_RX_or_TX){
//    
//    //check if S_COND is TX successfully (Bus Is IDLE seize it)
//    u8 response_code = TWI_send_Start_RepeatedStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call);
//    
//    if(response_code == TWI_repeated_START_condition_has_been_transmitted){
//    
//        TWDR = twi_slave_addr_RX_or_TX;
//
//       /*
//        * TWCR TWINT TWEA TWSTA TWSTO TWWC TWEN ? TWIE
//         Value 1     X    0     0     X    1    0 X
//        */
//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//                , TWSTA , LOW ) 
//                , TWSTO , LOW ) 
//                , TWEN , HIGH );
//    
//        //wait for ACK back From Slave TWI OR lose Arbitration
//        TWI_POLLING_TILL_JOB_IS_DONE;
//        
//    }else if(response_code == TWI_Bus_error_due_to_an_illegal_START_or_STOP_condition){
//        //BUS is Busy or what?
//        /*
//         * To recover from a bus error, the TWSTO Flag must set and TWINT must be cleared by writing a logic one to it. 
//         * This causes the TWI to enter the not addressed slave mode and to clear the TWSTO Flag (no other bits in TWCR are affected). 
//         * The SDA and SCL lines are released, and no STOP condition is transmitted.
//         */
//        TWCR = SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(
//                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
//                , TWSTA , LOW ) 
//                , TWSTO , HIGH ) 
//                , TWEN , HIGH );
//        
//        //wait for TWI to assert job
//        TWI_POLLING_TILL_JOB_IS_DONE;
//    }
//    
//    return TWSR;
//}
