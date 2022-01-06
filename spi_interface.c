#include "spi_interface.h"

void onInitSPI(u8 master_slave_mode,
        u8 enable_disable_spi,
        u8 clk_divisor,
        u8 clk_polarity,
        u8 clk_phase,
        u8 data_order,
        u8 enable_disaple_transmission_complete_interrupt) {

    if (master_slave_mode) {
        //configure SPI as master
        SPCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(SPCR, SPIE, enable_disaple_transmission_complete_interrupt)
                , SPE, enable_disable_spi)
                , DORD, data_order)
                , CPOL, clk_polarity)
                , CPHA, clk_phase)
                , MSTR, SET)
                , SPR1, clk_divisor & SPI_CLK_DIVISOR_SPR1_MASK)
                , SPR0, clk_divisor & SPI_CLK_DIVISOR_SPR0_MASK);

        SPSR = SET_REST_REG_BIT(SPSR, SPI2X, clk_divisor & SPI_CLK_DIVISOR_SPI2X_MASK);

        //program pins MOSI , SCK , SS
        programPortPinInOut(MOSI, OUTPUT);
        programPortPinInOut(SCK, OUTPUT);
        programPortPinInOut(SS, OUTPUT);
        
        _delay_ms(100);
        
    } else {
        //configure SPI as slave
        SPCR = SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(
                SET_REST_REG_BIT(SPCR, SPIE, enable_disaple_transmission_complete_interrupt)
                , SPE, enable_disable_spi)
                , DORD, data_order)
                , CPOL, clk_polarity)
                , CPHA, clk_phase)
                , MSTR, REST);

        //program pins MISO
        programPortPinInOut(MISO, OUTPUT);

    }

}

u8 transmitPacketViaSPIUsingPolling(u8 packet){
    
    // enable/sync slave
    writeControlSignalOnPortPin(SS , LOW);
    
    SPDR = packet;
    
    //stall MCU till TX/RX is Completed
    while(!GET_BIT(SPSR ,SPIF));
        
    //after TX is Completed SDPR Will Hold DATA TX Back
    return SPDR;
}

/*
 * this code does not work i still do not know why?!!
 * what's wrong with this logic
 */
//u8 transmitPacketViaSPIUsingINTER(u8 packet){
//    u8 last_received_packet = SPDR;
//    
//    // enable/sync slave
//    writeControlSignalOnPortPin(SS , LOW);
//    
//    //new TX packet : trigger new TX
//    SPDR = packet;
//        
//    return last_received_packet;
//}

void transmitPacketViaSPIUsingINTER(u8 packet){    
    // enable/sync slave chose the slave by selecting which port_pin to pull down
    writeControlSignalOnPortPin(SS , LOW);
    
    //new TX packet : trigger new TX
    SPDR = packet;
}

u8 receivePacketViaSPIUsingPolling(void){
    
    SPDR = ';';

    //stall MCU till TX/RX is Completed
    while(!GET_BIT(SPSR ,SPIF));
    
    return SPDR;
}

u8 receivePacketViaSPIUsingINTER(void){
    
    u8 last_received_packet = SPDR;
    
    //what to TX back : when new TX form Master
    SPDR = ';';
        
    return last_received_packet;
}