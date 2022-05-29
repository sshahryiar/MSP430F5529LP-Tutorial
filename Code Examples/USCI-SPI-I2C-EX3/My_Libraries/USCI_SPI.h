#include <msp430.h>
#include "driverlib.h"


#define USCI_A0_MOSI_port                   GPIO_PORT_P3
#define USCI_A0_MISO_port                   GPIO_PORT_P3
#define USCI_A0_CLK_port                    GPIO_PORT_P2

#define USCI_A0_MOSI_pin                    GPIO_PIN3
#define USCI_A0_MISO_pin                    GPIO_PIN4
#define USCI_A0_CLK_pin                     GPIO_PIN7

#define USCI_A1_MOSI_port                   GPIO_PORT_P4
#define USCI_A1_MISO_port                   GPIO_PORT_P4
#define USCI_A1_CLK_port                    GPIO_PORT_P4

#define USCI_A1_MOSI_pin                    GPIO_PIN4
#define USCI_A1_MISO_pin                    GPIO_PIN5
#define USCI_A1_CLK_pin                     GPIO_PIN0

#define USCI_B0_MOSI_port                   GPIO_PORT_P3
#define USCI_B0_MISO_port                   GPIO_PORT_P3
#define USCI_B0_CLK_port                    GPIO_PORT_P3

#define USCI_B0_MOSI_pin                    GPIO_PIN0
#define USCI_B0_MISO_pin                    GPIO_PIN1
#define USCI_B0_CLK_pin                     GPIO_PIN2

#define USCI_B1_MOSI_port                   GPIO_PORT_P4
#define USCI_B1_MISO_port                   GPIO_PORT_P4
#define USCI_B1_CLK_port                    GPIO_PORT_P4

#define USCI_B1_MOSI_pin                    GPIO_PIN1
#define USCI_B1_MISO_pin                    GPIO_PIN2
#define USCI_B1_CLK_pin                     GPIO_PIN3


void SPI_USCI_A0_init(void);
void SPI_USCI_A0_write(unsigned char tx_data);
unsigned char SPI_USCI_A0_read(void);
unsigned char SPI_USCI_A0_transfer(unsigned char tx_data);

void SPI_USCI_A1_init(void);
void SPI_USCI_A1_write(unsigned char tx_data);
unsigned char SPI_USCI_A1_read(void);
unsigned char SPI_USCI_A1_transfer(unsigned char tx_data);

void SPI_USCI_B0_init(void);
void SPI_USCI_B0_write(unsigned char tx_data);
unsigned char SPI_USCI_B0_read(void);
unsigned char SPI_USCI_B0_transfer(unsigned char tx_data);

void SPI_USCI_B1_init(void);
void SPI_USCI_B1_write(unsigned char tx_data);
unsigned char SPI_USCI_B1_read(void);
unsigned char SPI_USCI_B1_transfer(unsigned char tx_data);
