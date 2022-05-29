#include "driverlib.h"
#include "delay.h"


#define MOSI_port                   GPIO_PORT_P3
#define MISO_port                   GPIO_PORT_P3
#define CLK_port                    GPIO_PORT_P2
#define CS_port                     GPIO_PORT_P3

#define MOSI_pin                    GPIO_PIN3
#define MISO_pin                    GPIO_PIN4
#define CLK_pin                     GPIO_PIN7
#define CS_pin                      GPIO_PIN2

#define MOSI_pin_high()             GPIO_setOutputHighOnPin(MOSI_port, MOSI_pin)
#define MOSI_pin_low()              GPIO_setOutputLowOnPin(MOSI_port, MOSI_pin)

#define get_MISO_pin()              GPIO_getInputPinValue(MISO_port, MISO_pin)

#define CLK_pin_high()              GPIO_setOutputHighOnPin(CLK_port, CLK_pin)
#define CLK_pin_low()               GPIO_setOutputLowOnPin(CLK_port, CLK_pin)

#define CS_pin_high()               GPIO_setOutputHighOnPin(CS_port, CS_pin)
#define CS_pin_low()                GPIO_setOutputLowOnPin(CS_port, CS_pin)

#define T_min             			0
#define T_max              			1024

#define count_max          			4096

#define no_of_pulses       			16

#define deg_C              			0
#define deg_F              			1
#define tmp_K              			2

#define open_contact       			0x04
#define close_contact      			0x00

#define scalar_deg_C       			0.25
#define scalar_deg_F_1     			1.8
#define scalar_deg_F_2     			32.0
#define scalar_tmp_K       			273.0

#define no_of_samples      			16


void SPI_DIO_init(void);
void USCI_SPI_init(void);
void MAX6675_init(void);
unsigned char MAX6675_get_ADC(unsigned int *ADC_data);
float MAX6675_get_T(unsigned int ADC_value, unsigned char T_unit);
