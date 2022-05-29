#include <msp430.h>
#include "driverlib.h"


#define USCI_B0_I2C_port                                  GPIO_PORT_P3

#define USCI_B0_I2C_SDA_pin                               GPIO_PIN0
#define USCI_B0_I2C_SCL_pin                               GPIO_PIN1

#define USCI_B1_I2C_port                                  GPIO_PORT_P4

#define USCI_B1_I2C_SDA_pin                               GPIO_PIN1
#define USCI_B1_I2C_SCL_pin                               GPIO_PIN2


void I2C_USCI_B0_init(unsigned char address);
void I2C_USCI_B0_set_address(unsigned char address);
unsigned char I2C_USCI_B0_read_byte(unsigned char address);
unsigned char I2C_USCI_B0_read_word(unsigned char address,unsigned char *value, unsigned char length);
unsigned char I2C_USCI_B0_write_byte(unsigned char address, unsigned char value);

void I2C_USCI_B1_init(unsigned char address);
void I2C_USCI_B1_set_address(unsigned char address);
unsigned char I2C_USCI_B1_read_byte(unsigned char address);
unsigned char I2C_USCI_B1_read_word(unsigned char address,unsigned char *value, unsigned char length);
unsigned char I2C_USCI_B1_write_byte(unsigned char address, unsigned char value);
