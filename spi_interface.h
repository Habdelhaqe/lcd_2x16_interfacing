/* 
 * File:   spi_interface.h
 * Author: Engs
 *
 * Created on 31 December 2021, 18:32
 */

#ifndef SPI_INTERFACE_H
#define	SPI_INTERFACE_H
    
    #include "interfacing_connection_logic.h"
    
    #define IGNORE_ARGUMENT 0

    #define SPI_MASTER_MODE 1
    #define SPI_SLAVE_MODE 0

    #define SPI_CLK_DIVISOR_BY_4   0 //SP12X = 0
    #define SPI_CLK_DIVISOR_BY_16  1 //SP12X = 0
    #define SPI_CLK_DIVISOR_BY_64  2 //SP12X = 0
    #define SPI_CLK_DIVISOR_BY_128 3 //SP12X = 0
    #define SPI_CLK_DIVISOR_BY_2   4 //SP12X = 1
    #define SPI_CLK_DIVISOR_BY_8   5 //SP12X = 1
    #define SPI_CLK_DIVISOR_BY_32  6 //SP12X = 1
    #define SPI_CLK_DIVISOR_BY_64_DOUBLE_SPEED  7 //SP12X = 1

    #define SPI_CLK_DIVISOR_SPR0_MASK 1
    #define SPI_CLK_DIVISOR_SPR1_MASK 2
    #define SPI_CLK_DIVISOR_SPI2X_MASK 0

    #define SPI_CLK_POLARITY_RISE_LEADING_FALL_TRAILLING 0 //SCK is  low when idle.
    #define SPI_CLK_POLARITY_FALL_LEADING_RISE_TRAILLING 1 //SCK is high when idle.

    #define SPI_CLK_PHASE_SAMPLE_ON_LEADING_EDGE   0 //SAMPLE on leading/first edge
    #define SPI_CLK_PHASE_SAMPLE_ON_TRAILLING_EDGE 1 //SAMPLE on trailing/last edge

    #define  SPI_ENABLE_INTERRUPT_TRANSIMSION_COMPLETED_FLAG 1 //SPIE = 1
    #define SPI_DISABLE_INTERRUPT_TRANSIMSION_COMPLETED_FLAG 0 //SPIE = 0

    #define   SPI_ENABLE_INTER SET_BIT(SPCR , SPIE)
    #define  SPI_DISABLE_INTER CLEAR_BIT(SPCR , SPIE)

    #define   SPI_ENABLE_MASTER SET_BIT(SPCR , MSTR)
    #define   SPI_ENABLE_SLAVE CLEAR_BIT(SPCR , MSTR)

    #define  SPI_UNIT_ENABLE 1 //SPE = 1
    #define SPI_UNIT_DISABLE 0 //SPE = 0

    #define SPI_TRANSIMT_LSB_FIRST 1 //SPIE = 1
    #define SPI_TRANSIMT_MSB_FIRST 0 //SPIE = 0
    
    //CONNECTION_PINS
    #define  SCK _PB_PIN7
    #define MISO _PB_PIN6
    #define MOSI _PB_PIN5
    #define   SS _PB_PIN4

    #define SPI_TRANSMIT_USING_INTERRUPT_COMPLETED(PACKET) SPDR = PACKET
    #define  SPI_RECEIVE_USING_INTERRUPT_COMPLETED         SPDR

    void onInitSPI(u8 master_slave_mode , 
                   u8 enable_disable_spi , 
                   u8 clk_divisor , 
                   u8 clk_polarity , 
                   u8 clk_phase , 
                   u8 data_order , 
                   u8 enable_disaple_transmission_complete_interrupt );
    
    u8 transmitPacketViaSPIUsingPolling(u8 packet);

//    u8 transmitPacketViaSPIUsingINTER(u8 packet);
    
    void transmitPacketViaSPIUsingINTER(u8 packet);

    u8 receivePacketViaSPIUsingPolling(void);

    u8 receivePacketViaSPIUsingINTER(void);

#endif	/* SPI_INTERFACE_H */