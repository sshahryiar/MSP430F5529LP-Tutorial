#include "driverlib.h"
#include "delay.h"


#define DS18B20_PORT				    GPIO_PORT_P3

#define DS18B20_PIN 					GPIO_PIN7

#define DS18B20_OUTPUT()				GPIO_setAsOutputPin(DS18B20_PORT, DS18B20_PIN)
#define DS18B20_INPUT()					GPIO_setAsInputPin(DS18B20_PORT, DS18B20_PIN)

#define DS18B20_IN()					GPIO_getInputPinValue(DS18B20_PORT, DS18B20_PIN)

#define DS18B20_OUT_HIGH()				GPIO_setOutputHighOnPin(DS18B20_PORT, DS18B20_PIN)
#define DS18B20_OUT_LOW()               GPIO_setOutputLowOnPin(DS18B20_PORT, DS18B20_PIN)

#define TRUE                            1
#define FALSE                           0



unsigned char onewire_reset(void) ;
void onewire_write_bit(unsigned char bit_value);
unsigned char onewire_read_bit(void);
void onewire_write(unsigned char value);    
unsigned char onewire_read(void);
