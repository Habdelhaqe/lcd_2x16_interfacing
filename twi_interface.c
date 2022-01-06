#include"twi_interface.h"

extern scan_fun_return fun_ret_status_and_data;

#define   ERR_CHECKER fun_ret_status_and_data.fun_return
#define RECEIVED_DATA fun_ret_status_and_data.scanned_data

void initTWIselectingBaudRate(u8 baud_rate_divisor_selection , u8 prescalar_selection){
    TWBR = baud_rate_divisor_selection;
    TWSR = SET_REST_REG_BIT(SET_REST_REG_BIT(TWSR , TWPS0 , prescalar_selection & TWI_PRESCALAR_TWPS0_MASK) , 
            TWPS1 , prescalar_selection & TWI_PRESCALAR_TWPS1_MASK);
}

/*
 * consumes  many cycles cause of the MUL and DIV operations
 */
void initTWIselectingFrequency(u8 frequency_selection, u8 prescalar_selection){
    
    prescalar_selection &=TWI_PRESCALAR_MASK;
    
    TWSR = SET_REST_REG_BIT(SET_REST_REG_BIT(TWSR , TWPS0 , prescalar_selection & TWI_PRESCALAR_TWPS0_MASK) , 
            TWPS1 , prescalar_selection & TWI_PRESCALAR_TWPS1_MASK);
    
    TWBR = (F_CPU / frequency_selection - 16 ) / 2 / prescalar_selection == 3 ? 32 : 
                                                     prescalar_selection == 2 ? 16 : 
                                                         !prescalar_selection ? 1  : 4;
}

//MASTER mode Initiate Session From IDLE BUS
u8 TWIsendStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call){
    /*
     * TWCR TWINT TWEA                                            TWSTA TWSTO TWWC TWEN ? TWIE
      Value 1     enable_addressed_as_slave_when_arbitration_lost 1     0     X    1    0 X
     */
 
    if(enable_addressed_as_slave_when_arbitration_lost){
       TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;
       enable_addressed_as_slave_when_arbitration_lost = enable_addressed_as_slave_when_arbitration_lost ? HIGH : LOW; 
    }
    
    TWCR = SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
            , TWSTA , HIGH ) 
            , TWSTO , LOW ) 
            , TWEN , HIGH )
            , TWEA , enable_addressed_as_slave_when_arbitration_lost);
    
    TWI_POLLING_TILL_JOB_IS_DONE;
    
    return TWI_GET_MACHINE_STAT;
}

//MASTER mode Initiate Session From Seized BUS
u8 TWIsendReapeatedStartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call){

    /*
     * TWCR TWINT TWEA                                            TWSTA TWSTO TWWC TWEN ? TWIE
      Value 1     enable_addressed_as_slave_when_arbitration_lost 1     0     X    1    0 X
     */

    if(enable_addressed_as_slave_when_arbitration_lost){
        TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;
       enable_addressed_as_slave_when_arbitration_lost = enable_addressed_as_slave_when_arbitration_lost ? HIGH : LOW; 
    }
    
    TWCR = SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
            , TWSTA , HIGH ) 
            , TWSTO , LOW ) 
            , TWEN , HIGH )
            , TWEA , enable_addressed_as_slave_when_arbitration_lost );
    
    TWI_POLLING_TILL_JOB_IS_DONE;
    
    return TWI_GET_MACHINE_STAT;
}

//MASTER mode Close Opened Session Free BUS
void TWIsendStopConditionUsePolling(void){
    /*
     * TWCR TWINT TWEA TWSTA TWSTO TWWC TWEN ? TWIE
      Value 1     X    0     1     X    1    0 X
     */
    TWCR = SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(
            SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
            , TWSTA , LOW ) 
            , TWSTO , HIGH ) 
            , TWEN , HIGH );

}

u8 TWIRestartConditionUsePolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call){
    
    if((TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_ACK_has_been_received ||
       (TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received ||
            
       (TWI_GET_MACHINE_STAT) == TWI_SLA__R_has_been_transmitted_NOT_ACK_has_been_received ||
            
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_ACK_has_been_received ||   
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_NOT_ACK_has_been_received ||
            
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_ACK_has_been_returned ||   
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_NOT_ACK_has_been_returned  
       ){
        
       /*
        * TWCR TWINT TWEA                                            TWSTA TWSTO TWWC TWEN ? TWIE
         Value 1     enable_addressed_as_slave_when_arbitration_lost 1     1     X    1    0 X
        */

        if(enable_addressed_as_slave_when_arbitration_lost){
            TWAR = enable_general_call ? TWI_OWN_SLA_ENABLE_GENERAL_CALL : TWI_OWN_SLA_IGNORE_GENERAL_CALL;
            enable_addressed_as_slave_when_arbitration_lost = enable_addressed_as_slave_when_arbitration_lost ? HIGH : LOW; 
        }
        
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                , TWSTA , HIGH ) 
                , TWSTO , HIGH ) 
                , TWEN , HIGH ) 
                , TWEA , enable_addressed_as_slave_when_arbitration_lost);
    
        //wait for S_COND placed on BUS
        TWI_POLLING_TILL_JOB_IS_DONE;
    }else{
        //what that mean being here?    
    }
    return TWI_GET_MACHINE_STAT;
}

//TWI in MT mode And Addressing Slave TWI
u8 TWIinitiateSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call , u8 twi_slave_addr_RX_or_TX){
    
    //check if S_COND is TX successfully (Bus Is IDLE seize it) 
    if(TWIsendStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call) == TWI_START_condition_has_been_trasnmitted){
    
        TWDR = twi_slave_addr_RX_or_TX;

       /*
        * TWCR TWINT TWEA TWSTA TWSTO TWWC TWEN ? TWIE
         Value 1     X    0     0     X    1    0 X
        */
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                , TWSTA , LOW ) 
                , TWSTO , LOW ) 
                , TWEN , HIGH );
    
        //wait for ACK back From Slave TWI OR lose Arbitration
        TWI_POLLING_TILL_JOB_IS_DONE;
        
    }else{
        //BUS is Busy or what?
    }
    
    return TWSR;
}

/*
 * this function allow for Arbitration to happen
 */
u8 TWIRestartSessionWithSalveTWIusingPolling(u8 enable_addressed_as_slave_when_arbitration_lost , u8 enable_general_call , u8 twi_slave_addr_RX_or_TX){

    //check if S_COND is TX successfully (Bus Is IDLE seize it) 
    if(TWIRestartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call) == TWI_START_condition_has_been_trasnmitted){
    
        TWDR = twi_slave_addr_RX_or_TX;

       /*
        * TWCR TWINT TWEA TWSTA TWSTO TWWC TWEN ? TWIE
         Value 1     X    0     0     X    1    0 X
        */
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                , TWSTA , LOW ) 
                , TWSTO , LOW ) 
                , TWEN , HIGH );
    
        //wait for ACK back From Slave TWI OR lose Arbitration
        TWI_POLLING_TILL_JOB_IS_DONE;
        
    }else{
        //BUS is Busy or what?
    }
    
    return TWSR;
}

/*
 * first check TWSR code which will be oriented  by calling one of :
 * @TWIinitiateSessionWithSalveTWIusingPolling
 * @TWIRestartSessionWithSalveTWIusingPolling
 * 
 * which abstracts calls to one of :
 * @TWIsendStartConditionUsePolling
 * @TWIRestartConditionUsePolling
 *  
 * the TX As Master will only happen when
 * TWSAR = TWI_SLA__W_has_been_transmitted_ACK_has_been_received
 *         OR TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received and in that case force_transmit is SET
 */
u8 TWITransmitDataToSlaveTWIusingPolling(u8 data , 
                                         u8 force_transmit ,                                           
                                         u8 repeat_or_stop_or_restart_session , 
                                         u8 enable_addressed_as_slave_when_arbitration_lost ,
                                         u8 enable_general_call ,    
                                         u8 on_lost_arbitration_initiate_another_start){
    
    u8 wait_till_TWI_assert_the_job = HIGH;

    if( (TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_ACK_has_been_received ||
        (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_ACK_has_been_received ||
        (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_transmitted_NOT_ACK_has_been_received ||    
        (force_transmit && (TWI_GET_MACHINE_STAT) == TWI_SLA__W_has_been_transmitted_NOT_ACK_has_been_received)){

        TWDR = data;
        
        repeat_or_stop_or_restart_session &= TWI_SESSION_MASK;
        
        switch(repeat_or_stop_or_restart_session){
                
            case TWI_ON_MASTER_TRANSMIT_DONT_CHANGE_SESSION_CONDITION :
                /*
                * TWCR TWINT TWEA TWSTA TWSTO TWWC TWEN ? TWIE
                 Value 1     X    0     0     X    1    0 X
                */
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEN , HIGH );              
                break;
                
            case TWI_ON_MASTER_TRANSMIT_REPEAT_SESSION :
                TWIsendReapeatedStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost,enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
                break;
            
            case TWI_ON_MASTER_TRANSMIT_STOP_SESSION :
                TWIsendStopConditionUsePolling();
                wait_till_TWI_assert_the_job = LOW;
                break;
                
            case TWI_ON_MASTER_TRANSMIT_RESTART_SESSION :
                TWIRestartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
                break;                
        }
            
    }else if((TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__W_or_data_bytes_ALSO_Arbitration_lost_in_SLA__R_or_NOT_ACK_bit){
        
        if(on_lost_arbitration_initiate_another_start) {
            
            TWIsendStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call);
            wait_till_TWI_assert_the_job = LOW;
            
        }else{
            //Two-wire Serial Bus will be released and not addressed slave mode entered
            TWCR = SET_REST_REG_BIT(
                    SET_REST_REG_BIT(
                    SET_REST_REG_BIT(
                    SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                    , TWSTA , LOW ) 
                    , TWSTO , LOW ) 
                    , TWEN , HIGH );    
        }
            
    }else{
        wait_till_TWI_assert_the_job = LOW;
    } 
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }

    return TWSR;
}

scan_fun_return TWIReceiveDataFromSlaveTWIusingPolling(u8 received_data_ack_or_not , 
                                          u8 incase_of_nack_sent_back_repeat_or_stop_or_restart_session , 
                                          u8 enable_addressed_as_slave_when_arbitration_lost ,
                                          u8 enable_general_call ,    
                                          u8 on_lost_arbitration_initiate_another_start){
    
    u8 wait_till_TWI_assert_the_job = HIGH ;
    
    ERR_CHECKER = NO_ERRORS;
    
    if( (TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_ACK_has_been_returned  ){
        
        RECEIVED_DATA = TWDR;
        
        /*
         * received_data_ack_or_not = 1 : Data byte will be received and NOT ACK will be returned
         * ELSE                         : Data byte will be received and ACK will be returned
        * TWCR TWINT TWEA                        TWSTA TWSTO TWWC TWEN ? TWIE
         Value 1     received_data_ack_or_not    0     0     X    1    0 X
        */
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH )
                , TWSTA , LOW ) 
                , TWSTO , LOW ) 
                , TWEN , HIGH ) 
                , TWEA , received_data_ack_or_not ? HIGH : LOW );
            
    }else if((TWI_GET_MACHINE_STAT) == TWI_Data_byte_has_been_received_NOT_ACK_has_been_returned){

        RECEIVED_DATA = TWDR;

        wait_till_TWI_assert_the_job = LOW;

        /*
         * incase_of_nack_sent_back_repeat_or_stop_or_restart_session = 
         *          TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED : Repeated START will be transmitted
         *          TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED   : STOP condition will be transmitted and TWSTO Flag will be reset
         *          TWI_RESTART_SESSION_ON_NOT_ACK_RECEIVED: STOP condition followed by a START condition will be transmitted and TWSTO Flag will be reset
        */
        
        incase_of_nack_sent_back_repeat_or_stop_or_restart_session &= TWI_SESSION_MASK;
        
        if(incase_of_nack_sent_back_repeat_or_stop_or_restart_session == TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWIsendReapeatedStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost,enable_general_call);
        
        }else if(incase_of_nack_sent_back_repeat_or_stop_or_restart_session == TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWIsendStopConditionUsePolling();
        
        }else{
        
            TWIRestartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost,enable_general_call);
        
        }
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_SLA__R_has_been_transmitted_ACK_has_been_received){
       
        /*
         * no data available yet we prepare TWI to ACK or NOT
         * received_data_ack_or_not = 1 : Data byte will be received and ACK will be returned
         * ELSE                         : Data byte will be received and NOT ACK will be returned
        * TWCR TWINT TWEA                        TWSTA TWSTO TWWC TWEN ? TWIE
         Value 1     received_data_ack_or_not    0     0     X    1    0 X
        */

        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH )
                , TWSTA , LOW ) 
                , TWSTO , LOW ) 
                , TWEN , HIGH ) 
                , TWEA , received_data_ack_or_not ? HIGH : LOW );
        
        ERR_CHECKER = DATA_NOT_AVAILABLE ;
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_SLA__R_has_been_transmitted_NOT_ACK_has_been_received){

        wait_till_TWI_assert_the_job = LOW;

        ERR_CHECKER = DATA_NOT_AVAILABLE ;

        /*
         * incase_of_nack_sent_back_repeat_or_stop_or_restart_session = 
         *          TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED : Repeated START will be transmitted
         *          TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED   : STOP condition will be transmitted and TWSTO Flag will be reset
         *          TWI_RESTART_SESSION_ON_NOT_ACK_RECEIVED: STOP condition followed by a START condition will be transmitted and TWSTO Flag will be reset
        */
        
        incase_of_nack_sent_back_repeat_or_stop_or_restart_session &= TWI_SESSION_MASK;
        
        if(incase_of_nack_sent_back_repeat_or_stop_or_restart_session == TWI_REPEAT_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWIsendReapeatedStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost,enable_general_call);
        
        }else if(incase_of_nack_sent_back_repeat_or_stop_or_restart_session == TWI_STOP_SESSION_ON_NOT_ACK_RECEIVED){
        
            TWIsendStopConditionUsePolling();
        
        }else{
        
            TWIRestartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost,enable_general_call);
    
        }
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__W_or_data_bytes_ALSO_Arbitration_lost_in_SLA__R_or_NOT_ACK_bit){

        ERR_CHECKER = DATA_NOT_AVAILABLE ;
        
        if(on_lost_arbitration_initiate_another_start) {
            
            TWIsendStartConditionUsePolling(enable_addressed_as_slave_when_arbitration_lost , enable_general_call);
            wait_till_TWI_assert_the_job = LOW;
            
        }else{
            //Two-wire Serial Bus will be released and not addressed slave mode entered
            TWCR = SET_REST_REG_BIT(
                    SET_REST_REG_BIT(
                    SET_REST_REG_BIT(
                    SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                    , TWSTA , LOW ) 
                    , TWSTO , LOW ) 
                    , TWEN , HIGH );    
        }
        
    }
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }
    
    return fun_ret_status_and_data;
}

u8 TWITransmitDataToMasterTWIusingPolling(u8 transmit_data ,
                                         u8 enable_ack ,                                           
                                         u8 no_add_mode_start_or_not_ack_or_not , 
                                         u8 enable_general_call){
    
    u8 wait_till_TWI_assert_the_job = HIGH;
    
    if((TWI_GET_MACHINE_STAT) == TWI_Own_SLA__R_has_been_received_ACK_has_been_returned || 
       (TWI_GET_MACHINE_STAT) == TWI_Data_byte_in_TWDR_has_been_transmitted_ACK_has_been_received ||
       (TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__R_W_as_master_own_SLA__R_has_been_received_ACK_has_been_returned ){
        
        TWDR = transmit_data ;
        
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                , TWEA , enable_ack ? HIGH : LOW ) 
                , TWSTO , LOW ) 
                , TWEN , HIGH );
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Data_byte_in_TWDR_has_been_transmitted_NOT_ACK_has_been_received ||
             (TWI_GET_MACHINE_STAT) == TWI_Last_data_byte_in_TWDR_has_been_transmitted_TWEA_equals_0_ACK_has_been_received ){
        
        no_add_mode_start_or_not_ack_or_not &= TWI_SESSION_MASK;
        
        switch(no_add_mode_start_or_not_ack_or_not){
            //Switched to the not addressed Slave mode; no recognition of own SLA or GCA
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION :
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEA , LOW ) 
                        , TWEN , HIGH );
                break;
            
            //Switched to the not addressed Slave mode;own SLA will be recognized;    
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION :
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEA , HIGH ) 
                        , TWEN , HIGH );
                break;
                
            //Switched to the not addressed Slave mode;no recognition of own SLA or GCA; a START condition will be transmitted when the bus becomes free   
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION :
                TWIsendStartConditionUsePolling(LOW , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
                break;

            /*Switched to the not addressed Slave mode; own SLA will be recognized;GCA will be recognized if TWGCE = ?1?;a START condition will be 
             *transmitted when the bus becomes free
             */                
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION :
                TWIsendStartConditionUsePolling(HIGH , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
        }
        
    }
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }
    
    return TWSR;
}

scan_fun_return TWIReceiveDataFromMasterTWIusingPolling(u8 received_data_ack_or_not , 
                                          u8 no_add_mode_start_or_not_ack_or_not , 
                                          u8 enable_general_call ){
    
    u8 wait_till_TWI_assert_the_job = HIGH;
    
    ERR_CHECKER = NO_ERRORS;
    
    if((TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_own_SLA__W_data_has_been_received_ACK_has_been_returned || 
       (TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_general_call_data_has_been_received_ACK_has_been_returned ){
        
        RECEIVED_DATA = TWDR;
        
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH )
                , TWSTO , LOW ) 
                , TWEN , HIGH ) 
                , TWEA , received_data_ack_or_not ? HIGH : LOW );
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_own_SLA__W_data_has_been_received_NOT_ACK_has_been_returned || 
             (TWI_GET_MACHINE_STAT) == TWI_Previously_addressed_with_general_call_data_has_been_received_NOT_ACK_has_been_returned){

        RECEIVED_DATA = TWDR;
        
        no_add_mode_start_or_not_ack_or_not &= TWI_SESSION_MASK;
        
        switch(no_add_mode_start_or_not_ack_or_not){
            //Switched to the not addressed Slave mode; no recognition of own SLA or GCA
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION :
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEA , LOW ) 
                        , TWEN , HIGH );
                break;
            
            //Switched to the not addressed Slave mode;own SLA will be recognized;    
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION :
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEA , HIGH ) 
                        , TWEN , HIGH );
                break;
                
            //Switched to the not addressed Slave mode;no recognition of own SLA or GCA; a START condition will be transmitted when the bus becomes free   
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION :
                TWIsendStartConditionUsePolling(LOW , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
                break;

            /*Switched to the not addressed Slave mode; own SLA will be recognized;GCA will be recognized if TWGCE = ?1?;a START condition will be 
             *transmitted when the bus becomes free
             */                
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION :
                TWIsendStartConditionUsePolling(HIGH , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
        }
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_Own_SLA__W_has_been_received_ACK_has_been_returned || 
             (TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__R_W_as_master_own_SLA__W_has_been_received_ACK_has_been_returned ||
             (TWI_GET_MACHINE_STAT) == TWI_General_call_address_has_been_received_ACK_has_been_returned ||
             (TWI_GET_MACHINE_STAT) == TWI_Arbitration_lost_in_SLA__R_W_as_master_General_call_address_has_been_received_ACK_has_been_returned){
        
        ERR_CHECKER = DATA_NOT_AVAILABLE;
        
        TWCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(TWCR , TWINT , HIGH )
                , TWSTO , LOW ) 
                , TWEN , HIGH ) 
                , TWEA , received_data_ack_or_not ? HIGH : LOW );
        
    }else if((TWI_GET_MACHINE_STAT) == TWI_A_STOP_condition_or_repeated_START_condition_has_been_received_while_still_addressed_as_slave){

        ERR_CHECKER = DATA_NOT_AVAILABLE;
        
        no_add_mode_start_or_not_ack_or_not &= TWI_SESSION_MASK;
        
        switch(no_add_mode_start_or_not_ack_or_not){
            //Switched to the not addressed Slave mode; no recognition of own SLA or GCA
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SESSION :
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEA , LOW ) 
                        , TWEN , HIGH );
                break;
            
            //Switched to the not addressed Slave mode;own SLA will be recognized;    
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SESSION :
                TWCR = SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(
                        SET_REST_REG_BIT(TWCR , TWINT , HIGH ) 
                        , TWSTA , LOW ) 
                        , TWSTO , LOW ) 
                        , TWEA , HIGH ) 
                        , TWEN , HIGH );
                break;
                
            //Switched to the not addressed Slave mode;no recognition of own SLA or GCA; a START condition will be transmitted when the bus becomes free   
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_NO_ACK_SWITCH_MASTER_SESSION :
                TWIsendStartConditionUsePolling(LOW , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
                break;

            /*Switched to the not addressed Slave mode; own SLA will be recognized;GCA will be recognized if TWGCE = ?1?;a START condition will be 
             *transmitted when the bus becomes free
             */                
            case TWI_ON_SLAVE_TRANSMIT_NO_ADD_ACK_SWITCH_MASTER_SESSION :
                TWIsendStartConditionUsePolling(HIGH , enable_general_call);
                wait_till_TWI_assert_the_job = LOW;
        }
        
    }
    
    if(wait_till_TWI_assert_the_job){
        TWI_POLLING_TILL_JOB_IS_DONE;
    }
    
    return fun_ret_status_and_data;
}
