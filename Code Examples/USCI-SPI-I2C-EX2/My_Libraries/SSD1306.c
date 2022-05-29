#include "SSD1306.h"


static const unsigned char font_regular[92][6] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // sp
    0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,   // !
    0x00, 0x00, 0x07, 0x00, 0x07, 0x00,   // "
    0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,   // #
    0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $
    0x00, 0x62, 0x64, 0x08, 0x13, 0x23,   // %
    0x00, 0x36, 0x49, 0x55, 0x22, 0x50,   // &
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00,   // '
    0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,   // (
    0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,   // )
    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,   // *
    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,   // +
    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,   // ,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08,   // -
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00,   // .
    0x00, 0x20, 0x10, 0x08, 0x04, 0x02,   // /
    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,   // 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46,   // 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,   // 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,   // 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39,   // 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03,   // 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36,   // 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,   // 9
    0x00, 0x00, 0x36, 0x36, 0x00, 0x00,   // :
    0x00, 0x00, 0x56, 0x36, 0x00, 0x00,   // ;
    0x00, 0x08, 0x14, 0x22, 0x41, 0x00,   // <
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14,   // =
    0x00, 0x00, 0x41, 0x22, 0x14, 0x08,   // >
    0x00, 0x02, 0x01, 0x51, 0x09, 0x06,   // ?
    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,   // @
    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,   // B
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,   // C
    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,   // D
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,   // E
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,   // F
    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,   // G
    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,   // I
    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,   // J
    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,   // K
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,   // L
    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M
    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,   // O
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,   // P
    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q
    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,   // R
    0x00, 0x46, 0x49, 0x49, 0x49, 0x31,   // S
    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,   // T
    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,   // U
    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,   // V
    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,   // W
    0x00, 0x63, 0x14, 0x08, 0x14, 0x63,   // X
    0x00, 0x07, 0x08, 0x70, 0x08, 0x07,   // Y
    0x00, 0x61, 0x51, 0x49, 0x45, 0x43,   // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,   // [
    0x00, 0x02, 0x04, 0x08, 0x10, 0x20,   // \92
    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,   // ]
    0x00, 0x04, 0x02, 0x01, 0x02, 0x04,   // ^
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40,   // _
    0x00, 0x00, 0x01, 0x02, 0x04, 0x00,   // '
    0x00, 0x20, 0x54, 0x54, 0x54, 0x78,   // a
    0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,   // b
    0x00, 0x38, 0x44, 0x44, 0x44, 0x20,   // c
    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,   // d
    0x00, 0x38, 0x54, 0x54, 0x54, 0x18,   // e
    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,   // f
    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g
    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,   // h
    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,   // i
    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,   // j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,   // k
    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,   // l
    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,   // m
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,   // n
    0x00, 0x38, 0x44, 0x44, 0x44, 0x38,   // o
    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,   // p
    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,   // q
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,   // r
    0x00, 0x48, 0x54, 0x54, 0x54, 0x20,   // s
    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,   // t
    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,   // u
    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,   // v
    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,   // w
    0x00, 0x44, 0x28, 0x10, 0x28, 0x44,   // x
    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,   // z
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14    // horiz lines
};


static const unsigned char Number_Font[11][6] =
{
   0x00, 0x7F, 0x41, 0x41, 0x41, 0x7F, //0
   0x00, 0x00, 0x00, 0x41, 0x7F, 0x40, //1
   0x00, 0x79, 0x49, 0x49, 0x49, 0x4F, //2
   0x00, 0x41, 0x49, 0x49, 0x49, 0x7F, //3
   0x00, 0x0F, 0x08, 0x08, 0x08, 0x7F, //4
   0x00, 0x4F, 0x49, 0x49, 0x49, 0x79, //5
   0x00, 0x7F, 0x48, 0x48, 0x48, 0x78, //6
   0x00, 0x00, 0x01, 0x01, 0x01, 0x7F, //7
   0x00, 0x7F, 0x49, 0x49, 0x49, 0x7F, //8
   0x00, 0x0F, 0x09, 0x09, 0x09, 0x7F, //9
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00  //spc
};


void swap(signed int *a, signed int *b)
{
    signed int temp = 0x0000;

    temp = *b;
    *b = *a;
    *a = temp;
}


void I2C_DIO_init(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(I2C_port, (I2C_SDA_pin | I2C_SCL_pin));
}


void USCI_I2C_init(void)
{
    USCI_B_I2C_initMasterParam I2C_param = {0};

    I2C_DIO_init();

    I2C_param.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK;
    I2C_param.i2cClk = UCS_getSMCLK();
    I2C_param.dataRate = USCI_B_I2C_SET_DATA_RATE_400KBPS;

    USCI_B_I2C_initMaster(USCI_B0_BASE, &I2C_param);

    USCI_B_I2C_enable(USCI_B0_BASE);
}


void OLED_init(void)
{
     USCI_I2C_init();
     delay_ms(100);

     OLED_write((Set_Display_ON_or_OFF_CMD | Display_OFF), CMD);
     OLED_write(Set_Multiplex_Ratio_CMD, CMD);
     OLED_write(0x1F, CMD);
     OLED_write(Set_Display_Offset_CMD, CMD);
     OLED_write(0x00, CMD);
     OLED_write(Set_Display_Start_Line_CMD, CMD);
     OLED_write((Set_Segment_Remap_CMD | Column_Address_0_Mapped_to_SEG127), CMD);
     OLED_write((Set_COM_Output_Scan_Direction_CMD | Scan_from_COM63_to_0), CMD);
     OLED_write(Set_Common_HW_Config_CMD, CMD);
     OLED_write(0x02, CMD);
     OLED_write(Set_Contrast_Control_CMD, CMD);
     OLED_write(0x8F, CMD);
     OLED_write(Set_Entire_Display_ON_CMD, CMD);
     OLED_write(Set_Normal_or_Inverse_Display_CMD, CMD);
     OLED_write(Set_Display_Clock_CMD, CMD);
     OLED_write(0x80, CMD);
     OLED_write(Set_Pre_charge_Period_CMD, CMD);
     OLED_write(0x25, CMD);
     OLED_write(Set_VCOMH_Level_CMD, CMD);
     OLED_write(0x20, CMD);
     OLED_write(Set_Page_Address_CMD, CMD);
     OLED_write(0x00, CMD);
     OLED_write(0x03, CMD);
     OLED_write(Set_Page_Start_Address_CMD , CMD);
     OLED_write(Set_Higher_Column_Start_Address_CMD, CMD);
     OLED_write(Set_Lower_Column_Start_Address_CMD, CMD);
     OLED_write(Set_Memory_Addressing_Mode_CMD, CMD);
     OLED_write(0x02, CMD);
     OLED_write(Set_Charge_Pump_CMD, CMD);
     OLED_write(0x14, CMD);
     OLED_write((Set_Display_ON_or_OFF_CMD | Display_ON), CMD);

     delay_ms(100);

     OLED_clear_buffer();
     OLED_clear_screen();
}


void OLED_write(unsigned char value, unsigned char control_byte)
{
    USCI_B_I2C_setSlaveAddress(USCI_B0_BASE, SSD1306_I2C_Address);
    USCI_B_I2C_setMode(USCI_B0_BASE, USCI_B_I2C_TRANSMIT_MODE);

    USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE, control_byte);
    while(!USCI_B_I2C_masterIsStartSent(USCI_B0_BASE));
    USCI_B_I2C_masterSendMultiByteFinish(USCI_B0_BASE, value);

    while(USCI_B_I2C_isBusBusy(USCI_B0_BASE));
}


void OLED_gotoxy(unsigned char x_pos, unsigned char y_pos)
{
     OLED_write((Set_Page_Start_Address_CMD + y_pos), CMD);
     OLED_write(((x_pos & 0x0F) | Set_Lower_Column_Start_Address_CMD), CMD);
     OLED_write((((x_pos & 0xF0) >> 0x04) | Set_Higher_Column_Start_Address_CMD), CMD);
}


void OLED_fill(unsigned char bmp_data)
{
    unsigned char x_pos = 0x00;
    unsigned char page = 0x00;

    for(page = 0; page < y_max; page++)
    {
        OLED_gotoxy(x_min, page);
        
        USCI_B_I2C_setSlaveAddress(USCI_B0_BASE, SSD1306_I2C_Address);
        USCI_B_I2C_setMode(USCI_B0_BASE, USCI_B_I2C_TRANSMIT_MODE);

        USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE, DAT);
        while(!USCI_B_I2C_masterIsStartSent(USCI_B0_BASE));
        
        for(x_pos = x_min; x_pos < x_max; x_pos++)
        {
            USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE, bmp_data);
        }
        
        USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

        while(USCI_B_I2C_isBusBusy(USCI_B0_BASE));
    }
}


void OLED_clear_screen()
{
    OLED_fill(0x00);
}


void OLED_clear_buffer()
{
     unsigned int s = 0x0000;

     for(s = 0; s < buffer_size; s++)
     {
          buffer[s] = 0x00;
     }
}


void OLED_cursor(unsigned char x_pos, unsigned char y_pos)
{
    unsigned char s = 0x00;

    if(y_pos != 0x00)
    {
        if(x_pos == 1)
        {
            OLED_gotoxy(0x00, (y_pos + 0x02));
        }
        else
        {
            OLED_gotoxy((0x50 + ((x_pos - 0x02) * 0x06)), (y_pos + 0x02));
        }

        for(s = 0x00; s < 0x06; s++)
        {
            OLED_write(0xFF, DAT);
        }
    }
}


void draw_bitmap(unsigned char xb, unsigned char yb, unsigned char xe, unsigned char ye, unsigned char *bmp_img)
{
    unsigned int s = 0x0000;
    unsigned char x_pos = 0x00;
    unsigned char y_pos = 0x00;

    for(y_pos = yb; y_pos <= ye; y_pos++)
    {
        OLED_gotoxy(xb, y_pos);
        for(x_pos = xb; x_pos < xe; x_pos++)
        {
            OLED_write(bmp_img[s++], DAT);
        }
    }
}


void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned char ch)
{
    unsigned char chr = 0x00;
    unsigned char s = 0x00;
    
    switch(num_reg_state)
    {
        case NUM:
        {
            if((ch >= 48) && (ch <= 57))
            {
                chr = (ch - 48);
            }
            else
            {
                chr = 10;
            }
            break;
        }
        default:
        {
            chr = (ch - 0x20);
            break;
        }
    }

    if(x_pos > (x_max - 0x06))
    {
        x_pos = 0x00;
        y_pos++;
    }
    OLED_gotoxy(x_pos, y_pos);

    for(s = 0x00; s < 0x06; s++)
    {
        switch(num_reg_state)
        {
            case NUM:
            {
                OLED_write(Number_Font[chr][s], DAT);
                break;
            }
            default:
            {
                OLED_write(font_regular[chr][s], DAT);
                break;
            }
        }
    }
}


void print_string(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned char *ch)
{
    unsigned char s = 0x00;

    do
    {
        print_char(x_pos, y_pos, num_reg_state, ch[s++]);
        x_pos += 0x06;
     }while((ch[s] >= 0x20) && (ch[s] <= 0x7F));
}


void print_chr(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, signed int value)
{
    unsigned char ch = 0x00;

    if(value < 0x00)
    {
        print_char(x_pos, y_pos, CHR, '-');
        value = -value;
    }
    else
    {
        print_char(x_pos, y_pos, CHR, ' ');
    }

     if((value >= 100) && (value < 1000))
     {
         ch = (value / 100);
         print_char((x_pos + 6), y_pos, num_reg_state,  (48 + ch));
         ch = ((value % 100) / 10);
         print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));
         ch = (value % 10);
         print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));
     }
     else if((value >= 10) && (value < 100))
     {
         ch = ((value % 100) / 10);
         print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));
         ch = (value % 10);
         print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));
         print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
     }
     else if((value >= 0) && (value < 10))
     {
         ch = (value % 10);
         print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));
         print_char((x_pos + 12), y_pos, num_reg_state, 0x20);
         print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
     }
}


void print_int(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, signed long value)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        print_char(x_pos, y_pos, CHR, '-');
        value = -value;
    }
    else
    {
        print_char(x_pos, y_pos, CHR, ' ');
    }

    if((value >= 10000) && ((value < 100000)))
    {
        ch = (value / 10000);
        print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 10000)/ 1000);
        print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 1000) / 100);
        print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 100) / 10);
        print_char((x_pos + 24), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        print_char((x_pos + 30), y_pos, num_reg_state, (48 + ch));
    }

    else if((value >= 1000) && (value < 10000))
    {
        ch = ((value % 10000)/ 1000);
        print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 1000) / 100);
        print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 100) / 10);
        print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        print_char((x_pos + 24), y_pos, num_reg_state, (48 + ch));
        print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
    else if((value >= 100) && (value < 1000))
    {
        ch = ((value % 1000) / 100);
        print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = ((value % 100) / 10);
        print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));
        print_char((x_pos + 24), y_pos, num_reg_state, 0x20);
        print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
    else if((value >= 10) && (value < 100))
    {
        ch = ((value % 100) / 10);
        print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

        ch = (value % 10);
        print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));

        print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
        print_char((x_pos + 24), y_pos, num_reg_state, 0x20);
        print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
    else if((value >= 0) && (value < 10))
    {
        ch = (value % 10);
        print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));
        print_char((x_pos + 12), y_pos, num_reg_state, 0x20);
        print_char((x_pos + 18), y_pos, num_reg_state, 0x20);
        print_char((x_pos + 24), y_pos, num_reg_state, 0x20);
        print_char((x_pos + 30), y_pos, num_reg_state, 0x20);
    }
}


void print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, unsigned int value, unsigned char points)
{
    unsigned char ch = 0x00;

    print_char(x_pos, y_pos, CHR, '.');

    ch = (value / 1000);
    print_char((x_pos + 6), y_pos, num_reg_state, (48 + ch));

    if(points > 1)
    {
        ch = ((value % 1000) / 100);
        print_char((x_pos + 12), y_pos, num_reg_state, (48 + ch));


        if(points > 2)
        {
            ch = ((value % 100) / 10);
            print_char((x_pos + 18), y_pos, num_reg_state, (48 + ch));

            if(points > 3)
            {
                ch = (value % 10);
                print_char((x_pos + 24), y_pos, num_reg_state, (48 + ch));
            }
        }
    }
}


void print_float(unsigned char x_pos, unsigned char y_pos, unsigned char num_reg_state, float value, unsigned char points)
{
    signed long tmp = 0x00;

    tmp = value;
    print_int(x_pos, y_pos, num_reg_state, tmp);
    tmp = ((value - tmp) * 10000);

    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if((value >= 10000) && (value < 100000))
    {
        print_decimal((x_pos + 36), y_pos, num_reg_state, tmp, points);
    }
    else if((value >= 1000) && (value < 10000))
    {
        print_decimal((x_pos + 30), y_pos, num_reg_state, tmp, points);
    }
    else if((value >= 100) && (value < 1000))
    {
        print_decimal((x_pos + 24), y_pos, num_reg_state, tmp, points);
    }
    else if((value >= 10) && (value < 100))
    {
        print_decimal((x_pos + 18), y_pos, num_reg_state, tmp, points);
    }
    else if(value < 10)
    {
        print_decimal((x_pos + 12), y_pos, num_reg_state, tmp, points);
        if((value) < 0)
        {
            print_char(x_pos, y_pos, CHR, '-');
        }
        else
        {
            print_char(x_pos, y_pos, CHR, ' ');
        }
    }
}


void draw_pixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour)
{
    unsigned char value = 0x00;
    unsigned char page = 0x00;
    unsigned char bit_pos = 0x00;

    page = (y_pos / y_max);
    bit_pos = (y_pos - (page * y_max));
    value = buffer[((page * x_max) + x_pos)];

    if((colour & YES) != NO)
    {
        value |= (1 << bit_pos);
    }
    else
    {
        value &= (~(1 << bit_pos));
    }

    buffer[((page * x_max) + x_pos)] = value;
    OLED_gotoxy(x_pos, page);
    OLED_write(value, DAT);
}


void draw_line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char colour)
{
    signed int dx = 0x0000;
    signed int dy = 0x0000;
    signed int stepx = 0x0000;
    signed int stepy = 0x0000;
    signed int fraction = 0x0000;

    dy = (y2 - y1);
    dx = (x2 - x1);

    if (dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    if (dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }
    else
    {
        stepx = 1;
    }

    dx <<= 1;
    dy <<= 1;

    draw_pixel(x1, y1, colour);

    if(dx > dy)
    {
        fraction = (dy - (dx >> 1));
        while (x1 != x2)
        {
            if(fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;
            }

            x1 += stepx;
            fraction += dy;

            draw_pixel(x1, y1, colour);
        }
    }
    else
    {
        fraction = (dx - (dy >> 1));
        while (y1 != y2)
        {
            if (fraction >= 0)
            {
                x1 += stepx;
                fraction -= dy;
            }

            y1 += stepy;
            fraction += dx;

            draw_pixel(x1, y1, colour);
        }
    }
}


void draw_V_line(signed int x1, signed int y1, signed int y2, unsigned colour)
{
    if(y1 > y2)
    {
       swap(&y1, &y2);
    }

    while(y2 > (y1 - 1))
    {
        draw_pixel(x1, y2, colour);
        y2--;
    }
}


void draw_H_line(signed int x1, signed int x2, signed int y1, unsigned colour)
{
    if(x1 > x2)
    {
       swap(&x1, &x2);
    }

    while(x2 > (x1 - 1))
    {
        draw_pixel(x2, y1, colour);
        x2--;
    }
}


void draw_triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour)
{
    signed int a = 0;
    signed int b = 0;
    signed int sa = 0;
    signed int sb = 0;
    signed int yp = 0;
    signed int last = 0;
    signed int dx12 = 0;
    signed int dx23 = 0;
    signed int dx13 = 0;
    signed int dy12 = 0;
    signed int dy23 = 0;
    signed int dy13 = 0;

    switch(fill)
    {
        case YES:
        {
            if(y1 > y2)
            {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }
            if(y2 > y3)
            {
                swap(&y3, &y2);
                swap(&x3, &x2);
            }
            if(y1 > y2)
            {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }

            if(y1 == y3)
            {
                a = b = x1;

                if(x2 < a)
                {
                    a = x2;
                }
                else if(x2 > b)
                {
                    b = x2;
                }
                if(x2 < a)
                {
                    a = x3;
                }
                else if(x3 > b)
                {
                    b = x3;
                }

                draw_H_line(a, (a + (b - (a + 1))), y1, colour);
                return;
            }

            dx12 = (x2 - x1);
            dy12 = (y2 - y1);
            dx13 = (x3 - x1);
            dy13 = (y3 - y1);
            dx23 = (x3 - x2);
            dy23 = (y3 - y2);
            sa = 0,
            sb = 0;

            if(y2 == y3)
            {
                last = y2;
            }
            else
            {
                last = (y2 - 1);
            }

            for(yp = y1; yp <= last; yp++)
            {
                a = (x1 + (sa / dy12));
                b = (x1 + (sb / dy13));
                sa += dx12;
                sb += dx13;
                if(a > b)
                {
                    swap(&a, &b);
                }
                draw_H_line(a, (a + (b - (a + 1))), yp, colour);
            }

            sa = (dx23 * (yp - y2));
            sb = (dx13 * (yp - y1));
            for(; yp <= y3; yp++)
            {
                a = (x2 + (sa / dy23));
                b = (x1 + (sb / dy13));
                sa += dx23;
                sb += dx13;

                if(a > b)
                {
                    swap(&a, &b);
                }
                draw_H_line(a, (a + (b - (a + 1))), yp, colour);
            }


            break;
        }
        default:
        {
            draw_line(x1, y1, x2, y2, colour);
            draw_line(x2, y2, x3, y3, colour);
            draw_line(x3, y3, x1, y1, colour);
            break;
        }
    }
}


void draw_rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char colour, unsigned char type)
{
     unsigned short i = 0x00;
     unsigned short xmin = 0x00;
     unsigned short xmax = 0x00;
     unsigned short ymin = 0x00;
     unsigned short ymax = 0x00;

     if(fill != NO)
     {
        if(x1 < x2)
        {
           xmin = x1;
           xmax = x2;
        }
        else
        {
           xmin = x2;
           xmax = x1;
        }

        if(y1 < y2)
        {
           ymin = y1;
           ymax = y2;
        }
        else
        {
           ymin = y2;
           ymax = y1;
        }

        for(; xmin <= xmax; ++xmin)
        {
           for(i = ymin; i <= ymax; ++i)
           {
               draw_pixel(xmin, i, colour);
           }
         }
     }

     else
     {
        draw_line(x1, y1, x2, y1, colour);
        draw_line(x1, y2, x2, y2, colour);
        draw_line(x1, y1, x1, y2, colour);
        draw_line(x2, y1, x2, y2, colour);
     }

     if(type != SQUARE)
     {
         draw_pixel(x1, y1, ~colour);
         draw_pixel(x1, y2, ~colour);
         draw_pixel(x2, y1, ~colour);
         draw_pixel(x2, y2, ~colour);
     }
}


void draw_circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char colour)
{
   signed int a = 0x0000;
   signed int b = 0x0000;
   signed int P = 0x0000;

   b = radius;
   P = (1 - b);

   do
   {
        if(fill != NO)
        {
           draw_line((xc - a), (yc + b), (xc + a), (yc + b), colour);
           draw_line((xc - a), (yc - b), (xc + a), (yc - b), colour);
           draw_line((xc - b), (yc + a), (xc + b), (yc + a), colour);
           draw_line((xc - b), (yc - a), (xc + b), (yc - a), colour);
        }
        else
        {
           draw_pixel((xc + a), (yc + b), colour);
           draw_pixel((xc + b), (yc + a), colour);
           draw_pixel((xc - a), (yc + b), colour);
           draw_pixel((xc - b), (yc + a), colour);
           draw_pixel((xc + b), (yc - a), colour);
           draw_pixel((xc + a), (yc - b), colour);
           draw_pixel((xc - a), (yc - b), colour);
           draw_pixel((xc - b), (yc - a), colour);
        }

        if(P < 0)
        {
           P += (3 + (2 * a++));
        }
        else
        {
           P += (5 + (2 * ((a++) - (b--))));
        }
    }while(a <= b);
}
