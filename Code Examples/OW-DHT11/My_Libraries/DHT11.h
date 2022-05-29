#include "driverlib.h"
#include "delay.h"


#define HIGH  					1
#define LOW 					0

#define DHT11_PORT              GPIO_PORT_P3

#define DHT11_pin               GPIO_PIN7

#define DHT11_DIR_OUT()         GPIO_setAsOutputPin(DHT11_PORT, DHT11_pin)
#define DHT11_DIR_IN()          GPIO_setAsInputPin(DHT11_PORT, DHT11_pin)

#define DHT11_pin_HIGH()        GPIO_setOutputHighOnPin(DHT11_PORT, DHT11_pin)
#define DHT11_pin_LOW()         GPIO_setOutputLowOnPin(DHT11_PORT, DHT11_pin)

#define DHT11_pin_IN()   		GPIO_getInputPinValue(DHT11_PORT, DHT11_pin)


void DHT11_init(void);
unsigned char get_byte(void);
unsigned char get_data(void);
