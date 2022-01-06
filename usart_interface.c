#include"usart_interface.h"
#include "interfacing_connection_logic.h"
/*
 *      once communication_mode is a SET then SYNC mode is selected for TX/RX
 * so XCK pin may not have to be programmed as o/p or i/p ??? it may be done automatically
 * upon selection of mode UCSRC|UMSEL is SET : UCSRC IS WRITTEN TO
 * 
 * what will happen if this is not needed and done programmatically though?
 * 
 */
static u8 is_usart_initialized = FALSE;
extern scan_fun_return fun_ret_status_and_data;

#define ERR_CHECKER fun_ret_status_and_data.fun_return

FUN_RETURN_STATUS init_USART(u8 enable_disable_TX,
        u8 enable_disable_RX,
        u8 enable_disable_data_reg_empty,
        u8 enable_disable_TX_completed,
        u8 enable_disable_RX_completed,
        u32 baud_rate_frequency,
        u8 frame_size,
        u8 communication_mode,
        u8 case_async_normal_double_rate,
        u8 case_sync_master_slave,
        u8 enable_disable_multi_processor_mode,
        u8 parity_mode,
        u8 stop_bits,
        u8 polarity_falling_rising) {
    
    if (is_usart_initialized &&
            (GET_BIT(UCSRA, TXC) || GET_BIT(UCSRA, RXC))) {
        ERR_CHECKER = ERR;
    } else {
        ERR_CHECKER = NO_ERRORS;
                
        u16 UBRR_REG = GET_UBRR_VALUE(baud_rate_frequency,
                communication_mode ? /*SYNC_MODE*/ SYNC_MODE_CLK_DIVISOR :
                case_async_normal_double_rate ? /*ASYNC_MODE_DOUBLE_RATE*/ ASYNC_MODE_DOUBLE_RATE_CLK_DIVISOR :
                /*ASYNC_MODE_NORAML_RATE*/ ASYNC_MODE_NORAML_RATE_CLK_DIVISOR);
                
        if (communication_mode) {
            //SYNC_MODE
            //case_sync_master_slave SET then pin is O/P MATER, rest pin is I/P SLAVE
            programPortPinInOut(XCK, case_sync_master_slave);
        }
                
        UBRRH = (u8)(UBRR_REG>>HIGHER_BYTE_SHIFT_FOR_UBRRH); //READABLE , SAFER , NEED SMART COMBILER FOR MAKING FAST ACC TRANSLATION
//        UBRRH = *((u8 *)&UBRR_REG + 1); //FASTER ,SAFER , DUMB COMPILER IS OK WITH IT
        UBRRL = (u8) UBRR_REG;        
                
        UCSRC = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT( UCSRC , URSEL , SET)
                , UPM1, parity_mode >> PARITY_MODE_UPM1_SHIFT)
                , UPM0, parity_mode & PARITY_MODE_UPM0_MASK)
                , USBS, stop_bits)
                , UCPOL, polarity_falling_rising)
                , UMSEL, communication_mode)
                , UCSZ1, frame_size & FRAME_SIZE_UCSZ1_MASK)
                , UCSZ0, frame_size & FRAME_SIZE_UCSZ0_MASK);

        UCSRA = SET_REST_REG_BIT(
                SET_REST_REG_BIT(UCSRA_INITIAL_VALUE, U2X, case_async_normal_double_rate)
                , MPCM, enable_disable_multi_processor_mode);


        UCSRB = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(UCSRB_INITIAL_VALUE, UCSZ2, frame_size >> FRAME_SIZE_UCSZ2_SHIFT)
                , TXCIE, enable_disable_TX_completed)
                , RXCIE, enable_disable_RX_completed)
                , UDRIE, enable_disable_data_reg_empty)
                , TXEN, enable_disable_TX)
                , RXEN, enable_disable_RX);

    }
    return ERR_CHECKER;
}

u8 getStatusOfUCSRA(void) {
    return (UCSRA);
}

u8 getStatusOfUCSRB(void) {
    return (UCSRB);
}

u8 getStatusOfUCSRC(void) {
    return (UCSRC);
}

void flushUSART_RX_Buffers(void) {
    //AS WE FLUSH RX8 FE PE DOR WILL NOT MATTER TO BE READ OR CHECKED OUT
    while (GET_BIT(UCSRA, RXC)) {
        *((u8 *) NULL) = UDR;
    }
}

u16 getUBRR(void){
	return UBRRL | (UBRRH<<HIGHER_BYTE_SHIFT_FOR_UBRRH) ;
//	return UBRRH ;
}

void transmitMSGviaUSARTusingPolling(u16 msg){
    if(GET_BIT(UCSRB , UCSZ2)){
        //9 BITS msg
    }else{
        //5 , 6 , 7 , 8 BITS msg
        while(!GET_BIT(UCSRA , UDRE));
        UDR = (u8) msg;
    }
}

void transmitMSGviaUSARTusingPollingOnTXC(u16 msg){
    
    if(GET_BIT(UCSRB , UCSZ2)){
        //9 BITS msg
    }else{
        //5 , 6 , 7 , 8 BITS msg
        turnLEDOnOff(LED0 , ON);
        UDR = (u8) msg;
        /*
         *  polling is on the opposite side of the equation that is : 
         * after placing MSG on UDR i/o location wait till the TX buffer and the
         * Shift REG transmits hole MSG out the USART unit wasting the feature of 
         * TX buffer (DORE flag) in doing so
         */
        while(!GET_BIT(UCSRA , TXC));
        turnLEDOnOff(LED0 , OFF);
    }

}
void transmitMSGviaUSARTusingINTER(u16 msg){
    if(GET_BIT(UCSRB , UCSZ2)){
        //9 BITS MSG
    }else{
        //5 , 6 , 7 , 8 BITS MSG
        /*
         * using polling cause you may transmit 2 or more characters @ 1 time
         * that is you call the function 2 or more to transmit data @ each 
         * ISR(TXC) call
         * note if you only call it 1 time @ each ISR(TXC) call the only delay
         * is the check !GET_BIT(UCSRA ,UDRE) which will always be :
         *      UDRE = 1 is set so the TX is idle ready for business 
         */
        while(!GET_BIT(UCSRA ,UDRE));
        UDR = (u8) msg;
    }
}

/*
 * idea is to use the UDRE flag through UDRIE interrupt to handle sending of 
 * long messages more than 1 character 
 */
void initiateTransimission(void){
    //right now all i am going to do is to enable the UDRIE flag 
    ENABLE_DATA_REGISTER_EMPTY_INTERRUPT_FOR_USART_RECEIVER;
}
u16 receiveMSGviaUSARTusingPolling(void){
    
    while(!(GET_BIT(UCSRA , RXC)));
    
//    u16 msg = LOW;
//    
//    if(GET_BIT(UCSRB , UCSZ2)){
//        msg = (GET_BIT(UCSRB , RXB8)) << HIGHER_BYTE_SHIFT_FOR_UBRRH; 
//    }
//    
//    msg |= UDR;
//    
//    return msg;
    
    //a check for FE PE DOR before processeding with data receiving
    turnLEDOnOff(LED0 , GET_BIT(UCSRA , FE));
    turnLEDOnOff(LED1 , GET_BIT(UCSRA , DOR));
    if(GET_BIT(UCSRC , UPM1)){
        turnLEDOnOff(LED2 , GET_BIT(UCSRA , UPE));
    }
        
    return GET_BIT(UCSRB , UCSZ2) ? (GET_BIT(UCSRB , RXB8)) << HIGHER_BYTE_SHIFT_FOR_UBRRH | UDR : UDR;
}

u16 receiveMSGviaUSARTusingINTER(void){
    return GET_BIT(UCSRB , UCSZ2) ? (GET_BIT(UCSRB , RXB8)) << HIGHER_BYTE_SHIFT_FOR_UBRRH | UDR : UDR;
}
