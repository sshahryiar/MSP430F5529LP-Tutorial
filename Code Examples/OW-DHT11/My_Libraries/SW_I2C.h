#include "driverlib.h"
#include "delay.h"


#define SW_I2C_SDA_PORT GPIO_PORT_P8
#define SW_I2C_SCL_PORT GPIO_PORT_P8

#define SDA_pin         GPIO_PIN1
#define SCL_pin         GPIO_PIN2

#define SDA_DIR_OUT()   GPIO_setAsOutputPin(SW_I2C_SDA_PORT, SDA_pin)
#define SDA_DIR_IN()    GPIO_setAsInputPin(SW_I2C_SDA_PORT, SDA_pin)
#define SCL_DIR_OUT()   GPIO_setAsOutputPin(SW_I2C_SCL_PORT, SCL_pin)
#define SCL_DIR_IN()    GPIO_setAsInputPin(SW_I2C_SCL_PORT, SCL_pin)

#define SDA_HIGH()      GPIO_setOutputHighOnPin(SW_I2C_SDA_PORT, SDA_pin)
#define SDA_LOW()       GPIO_setOutputLowOnPin(SW_I2C_SDA_PORT, SDA_pin)
#define SCL_HIGH()      GPIO_setOutputHighOnPin(SW_I2C_SCL_PORT, SCL_pin)
#define SCL_LOW()       GPIO_setOutputLowOnPin(SW_I2C_SCL_PORT, SCL_pin)

#define SDA_IN()        GPIO_getInputPinValue(SW_I2C_SDA_PORT, SDA_pin)

#define I2C_ACK         0xFF
#define I2C_NACK        0x00

#define I2C_timeout     1000


void SW_I2C_init(void);
void SW_I2C_start(void);
void SW_I2C_stop(void);
unsigned char SW_I2C_read(unsigned char ack);
void SW_I2C_write(unsigned char value);
void SW_I2C_ACK_NACK(unsigned char mode);
unsigned char SW_I2C_wait_ACK(void);
