#include "MMA7455L.h"


void I2C_DIO_init(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(I2C_port, (I2C_SDA_pin | I2C_SCL_pin));
}


void USCI_I2C_init(void)
{
    USCI_B_I2C_initMasterParam I2C_param = {0};

    I2C_DIO_init();

    I2C_param.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK;
    I2C_param.i2cClk = UCS_getSMCLK();
    I2C_param.dataRate = USCI_B_I2C_SET_DATA_RATE_100KBPS;

    USCI_B_I2C_initMaster(USCI_B1_BASE, &I2C_param);

    USCI_B_I2C_enable(USCI_B1_BASE);
}


void MMA7455L_init(void)
{
    USCI_I2C_init();  
    MMA7455L_write_byte(MMA7455L_CTL1, 0x80);
    MMA7455L_write_byte(MMA7455L_MCTL, MMA_7455_2G_MODE);
}


void MMA7455L_write_byte(unsigned char address, unsigned char value)
{
    USCI_B_I2C_setSlaveAddress(USCI_B1_BASE, MMA7455L_address);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_TRANSMIT_MODE);

    USCI_B_I2C_masterSendMultiByteStart(USCI_B1_BASE, address);
    while(!USCI_B_I2C_masterIsStartSent(USCI_B1_BASE));
    USCI_B_I2C_masterSendMultiByteFinish(USCI_B1_BASE, value);

    while(USCI_B_I2C_isBusBusy(USCI_B1_BASE));
}


void MMA7455L_write_word(unsigned char address, unsigned int value)
{
    unsigned char lb = 0x00;
    unsigned char hb = 0x00;

    lb = ((unsigned char)value);
    value >>= 8;
    hb = ((unsigned char)value);

    MMA7455L_write_byte(address, lb);
    MMA7455L_write_byte((address + 1), hb);
}


unsigned char MMA7455L_read_byte(unsigned char address)
{
    unsigned char value = 0x00;

    USCI_B_I2C_setSlaveAddress(USCI_B1_BASE, MMA7455L_address);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_TRANSMIT_MODE);

    USCI_B_I2C_masterSendStart(USCI_B1_BASE);
    USCI_B_I2C_masterSendSingleByte(USCI_B1_BASE, address);

    USCI_B_I2C_setSlaveAddress(USCI_B1_BASE, MMA7455L_address);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_RECEIVE_MODE);

    USCI_B_I2C_masterReceiveSingleStart(USCI_B1_BASE);
    value = USCI_B_I2C_masterReceiveSingle(USCI_B1_BASE);

    while(USCI_B_I2C_isBusBusy(USCI_B1_BASE));

    return value;
}


unsigned int MMA7455L_read_word(unsigned char address)
{
    unsigned char lb = 0x00;
    unsigned int hb = 0x0000;

    USCI_B_I2C_setSlaveAddress(USCI_B1_BASE, MMA7455L_address);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_TRANSMIT_MODE);

    USCI_B_I2C_masterSendStart(USCI_B1_BASE);
    USCI_B_I2C_masterSendSingleByte(USCI_B1_BASE, address);

    USCI_B_I2C_setSlaveAddress(USCI_B1_BASE, MMA7455L_address);
    USCI_B_I2C_setMode(USCI_B1_BASE, USCI_B_I2C_RECEIVE_MODE);

    USCI_B_I2C_masterReceiveMultiByteStart(USCI_B1_BASE);
    lb = USCI_B_I2C_masterReceiveMultiByteNext(USCI_B1_BASE);
    hb = USCI_B_I2C_masterReceiveMultiByteFinish(USCI_B1_BASE);

    USCI_B_I2C_masterReceiveMultiByteStop(USCI_B1_BASE);

    while(USCI_B_I2C_isBusBusy(USCI_B1_BASE));

    hb <<= 8;
    hb |= lb;

    return hb;
}


signed char MMA7455L_read_axis_8(unsigned char axis)
{
    return ((signed char)MMA7455L_read_byte(axis));
}


signed int MMA7455L_read_axis_10(unsigned char axis)
{
    return ((signed int)MMA7455L_read_word(axis) & 0x03FF);
}
