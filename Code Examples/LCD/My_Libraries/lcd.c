#include "lcd.h"


void LCD_DIO_init(void)
{
    GPIO_setAsOutputPin(LCD_RS_PORT, LCD_RS_PIN);
    GPIO_setAsOutputPin(LCD_EN_PORT, LCD_EN_PIN);
    GPIO_setAsOutputPin(LCD_D4_PORT, LCD_D4_PIN);
    GPIO_setAsOutputPin(LCD_D5_PORT, LCD_D5_PIN);
    GPIO_setAsOutputPin(LCD_D6_PORT, LCD_D6_PIN);
    GPIO_setAsOutputPin(LCD_D7_PORT, LCD_D7_PIN);

    _delay_cycles(100);
}


void LCD_init(void)
{
    LCD_DIO_init();

    LCD_RS_LOW;
    delay_ms(dly);
    toggle_EN_pin();

    LCD_send(0x33, CMD);
    LCD_send(0x32, CMD);

    LCD_send((_4_pin_interface | _2_row_display | _5x7_dots), CMD);
    LCD_send((display_on | cursor_off | blink_off), CMD);
    LCD_send((clear_display), CMD);
    LCD_send((cursor_direction_inc | display_no_shift), CMD);
}

void LCD_send(unsigned char value, unsigned char type)

{
    switch(type)
    {
      case DAT:
      {
          LCD_RS_HIGH;
         break;
      }
      default:
      {
         LCD_RS_LOW;
         break;
      }
    }

    LCD_4bit_send(value);
}


void LCD_4bit_send(unsigned char lcd_data)
{
    toggle_io(lcd_data, 7, LCD_D7_PORT, LCD_D7_PIN);
    toggle_io(lcd_data, 6, LCD_D6_PORT, LCD_D6_PIN);
    toggle_io(lcd_data, 5, LCD_D5_PORT, LCD_D5_PIN);
    toggle_io(lcd_data, 4, LCD_D4_PORT, LCD_D4_PIN);

    toggle_EN_pin();

    toggle_io(lcd_data, 3, LCD_D7_PORT, LCD_D7_PIN);
    toggle_io(lcd_data, 2, LCD_D6_PORT, LCD_D6_PIN);
    toggle_io(lcd_data, 1, LCD_D5_PORT, LCD_D5_PIN);
    toggle_io(lcd_data, 0, LCD_D4_PORT, LCD_D4_PIN);

    toggle_EN_pin();
}


void LCD_putstr(char *lcd_string)
{
    do
    {
        LCD_send(*lcd_string++, DAT);
    }while(*lcd_string != '\0');
}


void LCD_putchar(char char_data)
{
    LCD_send(char_data, DAT);
}


void LCD_clear_home(void)
{
    LCD_send(clear_display, CMD);
    LCD_send(goto_home, CMD);
}


void LCD_goto(unsigned char x_pos, unsigned char y_pos)
{
    if(y_pos == 0)
    {
        LCD_send((0x80 | x_pos), CMD);
    }
    else
    {
        LCD_send((0x80 | 0x40 | x_pos), CMD);
    }
}


void toggle_EN_pin(void)
{
    LCD_EN_HIGH;
    delay_ms(dly);
    LCD_EN_LOW;
    delay_ms(dly);
}


void toggle_io(unsigned char lcd_data, unsigned char bit_pos, unsigned int PORT, unsigned int PIN)
{
    unsigned char temp = 0x00;

    temp = (0x01 & (lcd_data >> bit_pos));

    switch(temp)
    {
        case 0:
        {
            GPIO_setOutputLowOnPin(PORT, PIN);
            break;
        }

        default:
        {
            GPIO_setOutputHighOnPin(PORT, PIN);
            break;
        }
    }
}
