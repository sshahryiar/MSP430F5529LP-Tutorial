#include "USCI_I2C.h"


void I2C_USCI_B0_init(unsigned char address)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_B0_I2C_port, (USCI_B0_I2C_SDA_pin | USCI_B0_I2C_SCL_pin));
    
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = (UCMST | UCMODE_3 | UCSYNC);
    UCB0CTL1 = (UCSSEL_2 | UCSWRST);
    UCB0BR0 = 50;
    UCB0I2CSA = address;
    UCB0CTL1 &= ~UCSWRST;
}


void I2C_USCI_B0_set_address(unsigned char address)
{
    UCB0CTL1 |= UCSWRST;
    UCB0I2CSA = address;
    UCB0CTL1 &= ~UCSWRST;
}


unsigned char I2C_USCI_B0_read_byte(unsigned char address)
{
    while(UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= (UCTR | UCTXSTT);

    while(!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = address;

    while(!(UCB0IFG & UCTXIFG));
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    UCB0IFG &= ~UCTXIFG;

    while(UCB0CTL1 & UCTXSTT);
    UCB0CTL1 |= UCTXSTP;

    return UCB0RXBUF;
}


unsigned char I2C_USCI_B0_read_word(unsigned char address,unsigned char *value, unsigned char length)
{
    unsigned char i = 0;

    while(UCB0CTL1 & UCTXSTP);

    UCB0CTL1 |= (UCTR | UCTXSTT);

    while(!(UCB0IFG & UCTXIFG));
    
    UCB0IFG &= ~UCTXIFG;
    
    if(UCB0IFG & UCNACKIFG)
    {
        return UCB0STAT;
    }

    UCB0TXBUF = address;

    while(!(UCB0IFG & UCTXIFG));
    
    if(UCB0IFG & UCNACKIFG)
    {
        return UCB0STAT;
    }

    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    UCB0IFG &= ~UCTXIFG;
    
    while(UCB0CTL1 & UCTXSTT);

    do
    {
        while (!(UCB0IFG & UCRXIFG));
        UCB0IFG &= ~UCTXIFG;
        value[i] = UCB0RXBUF;
        i++;
    }while(i < (length - 1));

    while (!(UCB0IFG & UCRXIFG));

    UCB0IFG &= ~UCTXIFG;
    UCB0CTL1 |= UCTXSTP;
    value[length - 1] = UCB0RXBUF;
    UCB0IFG &= ~UCTXIFG;

    return 0;
}


unsigned char I2C_USCI_B0_write_byte(unsigned char address, unsigned char value)
{
    while(UCB0CTL1 & UCTXSTP);

    UCB0CTL1 |= (UCTR | UCTXSTT);

    while(!(UCB0IFG & UCTXIFG));
    
    if(UCB0IFG & UCNACKIFG)
    {
        return UCB0STAT;
    }

    UCB0TXBUF = address;

    while(!(UCB0IFG & UCTXIFG));

    if(UCB0IFG & UCNACKIFG)
    {
        return UCB0STAT;
    }

    UCB0TXBUF = value;

    while(!(UCB0IFG & UCTXIFG));

    if(UCB0IFG & UCNACKIFG)
    {
        return UCB0STAT;
    }

    UCB0CTL1 |= UCTXSTP;
    UCB0IFG &= ~UCTXIFG;

    return 0;
}


void I2C_USCI_B1_init(unsigned char address)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(USCI_B1_I2C_port, (USCI_B1_I2C_SDA_pin | USCI_B1_I2C_SCL_pin));

    UCB1CTL1 |= UCSWRST;
    UCB1CTL0 = (UCMST | UCMODE_3 | UCSYNC);
    UCB1CTL1 = (UCSSEL_2 | UCSWRST);
    UCB1BR0 = 10;
    UCB1I2CSA = address;
    UCB1CTL1 &= ~UCSWRST;
}


void I2C_USCI_B1_set_address(unsigned char address)
{
    UCB1CTL1 |= UCSWRST;
    UCB1I2CSA = address;
    UCB1CTL1 &= ~UCSWRST;
}


unsigned char I2C_USCI_B1_read_byte(unsigned char address)
{
    while(UCB1CTL1 & UCTXSTP);
    UCB1CTL1 |= (UCTR | UCTXSTT);

    while(!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = address;

    while(!(UCB1IFG & UCTXIFG));
    UCB1CTL1 &= ~UCTR;
    UCB1CTL1 |= UCTXSTT;
    UCB1IFG &= ~UCTXIFG;

    while(UCB1CTL1 & UCTXSTT);
    UCB1CTL1 |= UCTXSTP;

    return UCB1RXBUF;
}


unsigned char I2C_USCI_B1_read_word(unsigned char address,unsigned char *value, unsigned char length)
{
    unsigned char i = 0;

    while(UCB1CTL1 & UCTXSTP);

    UCB1CTL1 |= (UCTR | UCTXSTT);

    while(!(UCB1IFG & UCTXIFG));

    UCB1IFG &= ~UCTXIFG;

    if(UCB1IFG & UCNACKIFG)
    {
        return UCB1STAT;
    }

    UCB1TXBUF = address;

    while(!(UCB1IFG & UCTXIFG));

    if(UCB1IFG & UCNACKIFG)
    {
        return UCB1STAT;
    }

    UCB1CTL1 &= ~UCTR;
    UCB1CTL1 |= UCTXSTT;
    UCB1IFG &= ~UCTXIFG;

    while(UCB1CTL1 & UCTXSTT);

    do
    {
        while (!(UCB1IFG & UCRXIFG));
        UCB1IFG &= ~UCTXIFG;
        value[i] = UCB1RXBUF;
        i++;
    }while(i < (length - 1));

    while (!(UCB1IFG & UCRXIFG));

    UCB1IFG &= ~UCTXIFG;
    UCB1CTL1 |= UCTXSTP;
    value[length - 1] = UCB1RXBUF;
    UCB1IFG &= ~UCTXIFG;

    return 0;
}


unsigned char I2C_USCI_B1_write_byte(unsigned char address, unsigned char value)
{
    while(UCB1CTL1 & UCTXSTP);

    UCB1CTL1 |= (UCTR | UCTXSTT);

    while(!(UCB1IFG & UCTXIFG));

    if(UCB1IFG & UCNACKIFG)
    {
        return UCB1STAT;
    }

    UCB1TXBUF = address;

    while(!(UCB1IFG & UCTXIFG));

    if(UCB1IFG & UCNACKIFG)
    {
        return UCB1STAT;
    }

    UCB1TXBUF = value;

    while(!(UCB1IFG & UCTXIFG));

    if(UCB1IFG & UCNACKIFG)
    {
        return UCB1STAT;
    }

    UCB1CTL1 |= UCTXSTP;
    UCB1IFG &= ~UCTXIFG;

    return 0;
}
