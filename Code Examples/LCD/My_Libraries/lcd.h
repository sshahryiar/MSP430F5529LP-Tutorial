#include "driverlib.h"
#include "delay.h"


#define LCD_RS_PORT                         GPIO_PORT_P8
#define LCD_RS_PIN                          GPIO_PIN1

#define LCD_EN_PORT                         GPIO_PORT_P8
#define LCD_EN_PIN                          GPIO_PIN2

#define LCD_D4_PORT                         GPIO_PORT_P2
#define LCD_D4_PIN                          GPIO_PIN3

#define LCD_D5_PORT                         GPIO_PORT_P3
#define LCD_D5_PIN                          GPIO_PIN7

#define LCD_D6_PORT                         GPIO_PORT_P2
#define LCD_D6_PIN                          GPIO_PIN6

#define LCD_D7_PORT                         GPIO_PORT_P4
#define LCD_D7_PIN                          GPIO_PIN0


#define LCD_RS_HIGH                         GPIO_setOutputHighOnPin(LCD_RS_PORT, LCD_RS_PIN)
#define LCD_RS_LOW                          GPIO_setOutputLowOnPin(LCD_RS_PORT, LCD_RS_PIN)

#define LCD_EN_HIGH                         GPIO_setOutputHighOnPin(LCD_EN_PORT, LCD_EN_PIN)
#define LCD_EN_LOW                          GPIO_setOutputLowOnPin(LCD_EN_PORT, LCD_EN_PIN)

#define LCD_DB4_HIGH                        GPIO_setOutputHighOnPin(LCD_D4_PORT, LCD_D4_PIN)
#define LCD_DB4_LOW                         GPIO_setOutputLowOnPin(LCD_D4_PORT, LCD_D4_PIN)

#define LCD_DB5_HIGH                        GPIO_setOutputHighOnPin(LCD_D5_PORT, LCD_D5_PIN)
#define LCD_DB5_LOW                         GPIO_setOutputLowOnPin(LCD_D5_PORT, LCD_D5_PIN)

#define LCD_DB6_HIGH                        GPIO_setOutputHighOnPin(LCD_D6_PORT, LCD_D6_PIN)
#define LCD_DB6_LOW                         GPIO_setOutputLowOnPin(LCD_D6_PORT, LCD_D6_PIN)

#define LCD_DB7_HIGH                        GPIO_setOutputHighOnPin(LCD_D7_PORT, LCD_D7_PIN)
#define LCD_DB7_LOW                         GPIO_setOutputLowOnPin(LCD_D7_PORT, LCD_D7_PIN)

#define clear_display                       0x01
#define goto_home                           0x02

#define cursor_direction_inc               (0x04 | 0x02)
#define cursor_direction_dec               (0x04 | 0x00)
#define display_shift                      (0x04 | 0x01)
#define display_no_shift                   (0x04 | 0x00)

#define display_on                         (0x08 | 0x04)
#define display_off                        (0x08 | 0x02)
#define cursor_on                          (0x08 | 0x02)
#define cursor_off                         (0x08 | 0x00)
#define blink_on                           (0x08 | 0x01)
#define blink_off                          (0x08 | 0x00)

#define _8_pin_interface                   (0x20 | 0x10)
#define _4_pin_interface                   (0x20 | 0x00)
#define _2_row_display                     (0x20 | 0x08)
#define _1_row_display                     (0x20 | 0x00)
#define _5x10_dots                         (0x20 | 0x40)
#define _5x7_dots                          (0x20 | 0x00)

#define DAT                                 1
#define CMD                                 0

#define dly                                 2


void LCD_DIO_init(void);
void LCD_init(void);
void LCD_send(unsigned char value, unsigned char mode);
void LCD_4bit_send(unsigned char lcd_data);
void LCD_putstr(char *lcd_string);
void LCD_putchar(char char_data);
void LCD_clear_home(void);
void LCD_goto(unsigned char x_pos, unsigned char y_pos);
void toggle_EN_pin(void);
void toggle_io(unsigned char lcd_data, unsigned char bit_pos, unsigned int PORT, unsigned int PIN);
