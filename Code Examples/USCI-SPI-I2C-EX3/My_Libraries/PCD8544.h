#include "driverlib.h"
#include "delay.h"
#include "USCI_SPI.h"


#define RST_port                            GPIO_PORT_P6
#define CS_port                             GPIO_PORT_P6
#define DC_port                             GPIO_PORT_P6

#define RST_pin                             GPIO_PIN0
#define CS_pin                              GPIO_PIN1
#define DC_pin                              GPIO_PIN2

#define RST_pin_high()                      GPIO_setOutputHighOnPin(RST_port, RST_pin)
#define RST_pin_low()                       GPIO_setOutputLowOnPin(RST_port, RST_pin)

#define CS_pin_high()                       GPIO_setOutputHighOnPin(CS_port, CS_pin)
#define CS_pin_low()                        GPIO_setOutputLowOnPin(CS_port, CS_pin)

#define DC_pin_high()                       GPIO_setOutputHighOnPin(DC_port, DC_pin)
#define DC_pin_low()                        GPIO_setOutputLowOnPin(DC_port, DC_pin)

#define PCD8544_set_Y_addr                  0x40
#define PCD8544_set_X_addr                  0x80

#define PCD8544_set_temp                    0x04
#define PCD8544_set_bias                    0x10
#define PCD8544_set_VOP                     0x80

#define PCD8544_power_down                  0x04
#define PCD8544_entry_mode                  0x02
#define PCD8544_extended_instruction        0x01

#define PCD8544_display_blank               0x00
#define PCD8544_display_normal              0x04
#define PCD8544_display_all_on              0x01
#define PCD8544_display_inverted            0x05

#define PCD8544_function_set                0x20
#define PCD8544_display_control             0x08

#define CMD                                 0
#define DAT                                 1

#define X_max                               84
#define Y_max                               48
#define Rows                                6

#define BLACK                               0
#define WHITE                               1
#define PIXEL_XOR                           2

#define ON                                  1
#define OFF                                 0

#define NO                                  0
#define YES                                 1

#define buffer_size                         504


void PCD8544_init(void);
void PCD8544_reset(void);
void PCD8544_write(unsigned char type, unsigned char value);
void PCD8544_set_contrast(unsigned char value);
void PCD8544_set_cursor(unsigned char x_pos, unsigned char y_pos);
void PCD8544_print_char(unsigned char ch, unsigned char colour);
void PCD8544_print_custom_char(unsigned char *map);
void PCD8544_fill(unsigned char bufr);
void PCD8544_clear_buffer(unsigned char colour);
void PCD8544_clear_screen(unsigned char colour);
void print_image(const unsigned char *bmp);
void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char ch, unsigned char colour);
void print_string(unsigned char x_pos, unsigned char y_pos, unsigned char *ch, unsigned char colour);
void print_chr(unsigned char x_pos, unsigned char y_pos, signed int value, unsigned char colour);
void print_int(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char colour);
void print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points, unsigned char colour);
void print_float(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points, unsigned char colour);
void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour);
void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char colour);
void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char colour);
void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char colour);
