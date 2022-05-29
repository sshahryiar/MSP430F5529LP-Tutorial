#include "driverlib.h"
#include "delay.h"


#define I2C_port                                  GPIO_PORT_P3

#define I2C_SDA_pin                               GPIO_PIN0
#define I2C_SCL_pin                               GPIO_PIN1

#define SSD1306_I2C_Address                       0x3C

#define DAT                                       0x60
#define CMD                                       0x00

#define Set_Lower_Column_Start_Address_CMD        0x00
#define Set_Higher_Column_Start_Address_CMD       0x10
#define Set_Memory_Addressing_Mode_CMD            0x20
#define Set_Column_Address_CMD                    0x21
#define Set_Page_Address_CMD                      0x22
#define Set_Display_Start_Line_CMD                0x40
#define Set_Contrast_Control_CMD                  0x81
#define Set_Charge_Pump_CMD                       0x8D
#define Set_Segment_Remap_CMD                     0xA0
#define Set_Entire_Display_ON_CMD                 0xA4
#define Set_Normal_or_Inverse_Display_CMD         0xA6
#define Set_Multiplex_Ratio_CMD                   0xA8
#define Set_Display_ON_or_OFF_CMD                 0xAE
#define Set_Page_Start_Address_CMD                0xB0
#define Set_COM_Output_Scan_Direction_CMD         0xC0
#define Set_Display_Offset_CMD                    0xD3
#define Set_Display_Clock_CMD                     0xD5
#define Set_Pre_charge_Period_CMD                 0xD9
#define Set_Common_HW_Config_CMD                  0xDA
#define Set_VCOMH_Level_CMD                       0xDB
#define Set_NOP_CMD                               0xE3

#define Horizontal_Addressing_Mode                0x00
#define Vertical_Addressing_Mode                  0x01
#define Page_Addressing_Mode                      0x02

#define Disable_Charge_Pump                       0x00
#define Enable_Charge_Pump                        0x04

#define Column_Address_0_Mapped_to_SEG0           0x00
#define Column_Address_0_Mapped_to_SEG127         0x01

#define Normal_Display                            0x00
#define Entire_Display_ON                         0x01

#define Non_Inverted_Display                      0x00
#define Inverted_Display                          0x01

#define Display_OFF                               0x00
#define Display_ON                                0x01

#define Scan_from_COM0_to_63                      0x00
#define Scan_from_COM63_to_0                      0x08

#define x_size                                    128
#define x_max                                     x_size
#define x_min                                     0
#define y_size                                    32
#define y_max                                     8
#define y_min                                     0

#define ON                                        1
#define OFF                                       0

#define YES                                       1
#define NO                                        0

#define ROUND                                     1
#define SQUARE                                    0

#define NUM                                       1
#define CHR                                       0

#define buffer_size                               512//(x_max * y_max)


unsigned char buffer[buffer_size];


void swap(signed int *a, signed int *b);
void I2C_DIO_init(void);
void USCI_I2C_init(void);
void OLED_init(void);
void OLED_write(unsigned char value, unsigned char control_byte);
void OLED_gotoxy(unsigned char x_pos, unsigned char y_pos);
void OLED_fill(unsigned char bmp_data);
void OLED_clear_screen(void);
void OLED_clear_buffer(void);
void OLED_cursor(unsigned char x_pos, unsigned char y_pos);
void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned char ch);
void print_string(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned char *ch);
void print_chr(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, signed int value);
void print_int(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, signed long value);
void print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned int value, unsigned char points);
void print_float(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, float value, unsigned char points);
void draw_bitmap(unsigned char xb, unsigned char yb, unsigned char xe, unsigned char ye, unsigned char *bmp_img);
void draw_pixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour);
void draw_line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char colour);
void draw_V_line(signed int x1, signed int y1, signed int y2, unsigned colour);
void draw_H_line(signed int x1, signed int x2, signed int y1, unsigned colour);
void draw_triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour);
void draw_rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char colour, unsigned char type);
void draw_rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char colour, unsigned char type);
void draw_circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char colour);
