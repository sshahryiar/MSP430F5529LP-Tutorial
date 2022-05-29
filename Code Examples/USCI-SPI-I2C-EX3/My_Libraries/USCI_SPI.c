#include "USCI_SPI.h"


void SPI_USCI_A0_init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(USCI_A0_MISO_port, USCI_A0_MISO_pin);

    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_A0_MOSI_port, USCI_A0_MOSI_pin);
    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_A0_CLK_port, USCI_A0_CLK_pin);

    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 = UCCKPH | UCMSB | UCMST | UCMODE_1 | UCSYNC;
    UCA0CTL1 = UCSSEL_2;
    UCA0BR0 = 4;
    UCA0BR1 = 0;
    UCA0CTL1 &= ~UCSWRST;
}


void SPI_USCI_A0_write(unsigned char tx_data)
{
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = tx_data;
    while(UCA0STAT & UCBUSY);
}


unsigned char SPI_USCI_A0_read(void)
{
    unsigned char rx_data = 0;

    while(!(UCA0IFG & UCRXIFG));
    rx_data = UCA0RXBUF;
    while(UCA0STAT & UCBUSY);

    return rx_data;
}


unsigned char SPI_USCI_A0_transfer(unsigned char tx_data)
{
    unsigned char rx_data = 0;

    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = tx_data;
    while(UCA0STAT & UCBUSY);

    while(!(UCA0IFG & UCRXIFG));
    rx_data = UCA0RXBUF;
    while(UCA0STAT & UCBUSY);

    return rx_data;
}


void SPI_USCI_A1_init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(USCI_A1_MISO_port, USCI_A1_MISO_pin);

    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_A1_MOSI_port, USCI_A1_MOSI_pin);
    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_A1_CLK_port, USCI_A1_CLK_pin);

    UCA1CTL1 |= UCSWRST;
    UCA1CTL0 = UCCKPH | UCMSB | UCMST | UCMODE_1 | UCSYNC;
    UCA1CTL1 = UCSSEL_2;
    UCA1BR0 = 8;
    UCA1BR1 = 0;
    UCA1CTL1 &= ~UCSWRST;
}


void SPI_USCI_A1_write(unsigned char tx_data)
{
    while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = tx_data;
    while(UCA1STAT & UCBUSY);
}


unsigned char SPI_USCI_A1_read(void)
{
    unsigned char rx_data = 0;

    while(!(UCA1IFG & UCRXIFG));
    rx_data = UCA1RXBUF;
    while(UCA1STAT & UCBUSY);

    return rx_data;
}


unsigned char SPI_USCI_A1_transfer(unsigned char tx_data)
{
    unsigned char rx_data = 0;

    while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = tx_data;
    while(UCA1STAT & UCBUSY);

    while(!(UCA1IFG & UCRXIFG));
    rx_data = UCA1RXBUF;
    while(UCA1STAT & UCBUSY);

    return rx_data;
}


void SPI_USCI_B0_init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(USCI_B0_MISO_port, USCI_B0_MISO_pin);

    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_B0_MOSI_port, USCI_B0_MOSI_pin);
    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_B0_CLK_port, USCI_B0_CLK_pin);

    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCCKPH | UCMSB | UCMST | UCMODE_1 | UCSYNC;
    UCB0CTL1 = UCSSEL_2;
    UCB0BR0 = 8;
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;
}


void SPI_USCI_B0_write(unsigned char tx_data)
{
    while(!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = tx_data;
    while(UCB0STAT & UCBUSY);
}


unsigned char SPI_USCI_B0_read(void)
{
    unsigned char rx_data = 0;

    while(!(UCB0IFG & UCRXIFG));
    rx_data = UCB0RXBUF;
    while(UCB0STAT & UCBUSY);

    return rx_data;
}


unsigned char SPI_USCI_B0_transfer(unsigned char tx_data)
{
    unsigned char rx_data = 0;

    while(!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = tx_data;
    while(UCB0STAT & UCBUSY);

    while(!(UCB0IFG & UCRXIFG));
    rx_data = UCB0RXBUF;
    while(UCB0STAT & UCBUSY);

    return rx_data;
}


void SPI_USCI_B1_init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(USCI_B1_MISO_port, USCI_B1_MISO_pin);

    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_B1_MOSI_port, USCI_B1_MOSI_pin);
    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_B1_CLK_port, USCI_B1_CLK_pin);

    UCB1CTL1 |= UCSWRST;
    UCB1CTL0 = UCCKPH | UCMSB | UCMST | UCMODE_1 | UCSYNC;
    UCB1CTL1 = UCSSEL_2;
    UCB1BR0 = 8;
    UCB1BR1 = 0;
    UCB1CTL1 &= ~UCSWRST;
}


void SPI_USCI_B1_write(unsigned char tx_data)
{
    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = tx_data;
    while(UCB1STAT & UCBUSY);
}


unsigned char SPI_USCI_B1_read(void)
{
    unsigned char rx_data = 0;

    while(!(UCB1IFG & UCRXIFG));
    rx_data = UCB1RXBUF;
    while(UCB1STAT & UCBUSY);

    return rx_data;
}


unsigned char SPI_USCI_B1_transfer(unsigned char tx_data)
{
    unsigned char rx_data = 0;

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = tx_data;
    while(UCB1STAT & UCBUSY);

    while(!(UCB1IFG & UCRXIFG));
    rx_data = UCB1RXBUF;
    while(UCB1STAT & UCBUSY);

    return rx_data;
}

