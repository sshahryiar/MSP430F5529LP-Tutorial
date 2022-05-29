#include "driverlib.h"
#include "delay.h"


#define SDO_PORT                                GPIO_PORT_P8
#define SCK_PORT                                GPIO_PORT_P8
#define STB_PORT                                GPIO_PORT_P3

#define SDO_pin                                 GPIO_PIN1
#define SCK_pin                                 GPIO_PIN2
#define STB_pin                                 GPIO_PIN7

#define SDO_DIR_OUT                             GPIO_setAsOutputPin(SDO_PORT, SDO_pin)
#define SCK_DIR_OUT                             GPIO_setAsOutputPin(SCK_PORT, SCK_pin)
#define STB_DIR_OUT                             GPIO_setAsOutputPin(STB_PORT, STB_pin)

#define SDO_HIGH                                GPIO_setOutputHighOnPin(SDO_PORT, SDO_pin)
#define SDO_LOW                                 GPIO_setOutputLowOnPin(SDO_PORT, SDO_pin)
#define SCK_HIGH                                GPIO_setOutputHighOnPin(SCK_PORT, SCK_pin)
#define SCK_LOW                                 GPIO_setOutputLowOnPin(SCK_PORT, SCK_pin)
#define STB_HIGH                                GPIO_setOutputHighOnPin(STB_PORT, STB_pin)
#define STB_LOW                                 GPIO_setOutputLowOnPin(STB_PORT, STB_pin)

#define clear_display                           0x01
#define goto_home                               0x02
         
#define cursor_direction_inc                    (0x04 | 0x02)
#define cursor_direction_dec                    (0x04 | 0x00)
#define display_shift                           (0x04 | 0x01)
#define display_no_shift                        (0x04 | 0x00)

#define display_on                              (0x08 | 0x04)
#define display_off                             (0x08 | 0x02)
#define cursor_on                               (0x08 | 0x02)
#define cursor_off                              (0x08 | 0x00)
#define blink_on                                (0x08 | 0x01)
#define blink_off                               (0x08 | 0x00)
                                    
#define _8_pin_interface                        (0x20 | 0x10)
#define _4_pin_interface                        (0x20 | 0x00)
#define _2_row_display                          (0x20 | 0x08)
#define _1_row_display                          (0x20 | 0x00)
#define _5x10_dots                              (0x20 | 0x40)
#define _5x7_dots                               (0x20 | 0x00)
                                   
#define dly                                     1

                                                                          
void SIPO(void);
void LCD_init(void);
void LCD_command(unsigned char value);
void LCD_send_data(unsigned char value); 
void LCD_4bit_send(unsigned char lcd_data);                                      
void LCD_putstr(char *lcd_string);
void LCD_putchar(char char_data);
void LCD_clear_home(void);
void LCD_goto(unsigned char x_pos, unsigned char y_pos);
