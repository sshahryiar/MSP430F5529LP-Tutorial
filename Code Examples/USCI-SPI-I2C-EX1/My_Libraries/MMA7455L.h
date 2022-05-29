#include "driverlib.h"
#include "delay.h"


#define I2C_port                             GPIO_PORT_P4

#define I2C_SDA_pin                          GPIO_PIN1
#define I2C_SCL_pin                          GPIO_PIN2

#define MMA7455L_address                     0x1D
                                                
#define MMA7455L_X_out_L                     0x00  
#define MMA7455L_X_out_H                     0x01  
#define MMA7455L_Y_out_L                     0x02  
#define MMA7455L_Y_out_H                     0x03    
#define MMA7455L_Z_out_L                     0x04  
#define MMA7455L_Z_out_H                     0x05    
#define MMA7455L_X_out                       0x06    
#define MMA7455L_Y_out                       0x07  
#define MMA7455L_Z_out                       0x08      
#define MMA7455L_STATUS                      0x09  
#define MMA7455L_DETSRC                      0x0A  
#define MMA7455L_TOUT                        0x0B
#define MMA7455L_RSV1                        0x0C
#define MMA7455L_I2C_Address                 0x0D
#define MMA7455L_User_Info                   0x0E
#define MMA7455L_Who_Am_I                    0x0F
#define MMA7455L_X_offset_L                  0x10  
#define MMA7455L_X_offset_H                  0x11  
#define MMA7455L_Y_offset_L                  0x12  
#define MMA7455L_Y_offset_H                  0x13    
#define MMA7455L_Z_offset_L                  0x14  
#define MMA7455L_Z_offset_H                  0x15 
#define MMA7455L_MCTL                        0x16
#define MMA7455L_INTRST                      0x17
#define MMA7455L_CTL1                        0x18
#define MMA7455L_CTL2                        0x19
#define MMA7455L_LDTH                        0x1A
#define MMA7455L_PDTH                        0x1B
#define MMA7455L_PW                          0x1C
#define MMA7455L_LT                          0x1D
#define MMA7455L_TW                          0x1E
#define MMA7455L_RSV2                        0x1F    

#define MMA_7455_2G_MODE                     0x05 
#define MMA_7455_4G_MODE                     0x09     
#define MMA_7455_8G_MODE                     0x01


void I2C_DIO_init(void);
void USCI_I2C_init(void);
void MMA7455L_init(void);
void MMA7455L_write_byte(unsigned char address, unsigned char value);
void MMA7455L_write_word(unsigned char address, unsigned int value);
unsigned char MMA7455L_read_byte(unsigned char address);
unsigned int MMA7455L_read_word(unsigned char address);
signed char MMA7455L_read_axis_8(unsigned char axis);
signed int MMA7455L_read_axis_10(unsigned char axis);
