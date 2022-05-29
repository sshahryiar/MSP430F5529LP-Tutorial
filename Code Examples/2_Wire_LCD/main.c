#include "driverlib.h"
#include "delay.h"
#include "lcd.h"


void clock_init(void);
void show_value(unsigned char value);


void main(void)
{
    unsigned char s = 0x00;

    char txt1[] = {"MICROARENA"};
    char txt2[] = {"SShahryiar"};
    char txt3[] = {"MSP430F5529LP"};
    char txt4[] = {"Launchpad!"};

    WDT_A_hold(WDT_A_BASE);

    clock_init();

    LCD_init();

    LCD_clear_home();

    LCD_goto(3, 0);
    LCD_putstr(txt1);
    LCD_goto(3, 1);
    LCD_putstr(txt2);
    delay_ms(4000);

    LCD_clear_home();

    for(s = 0; s < 13; s++)
    {
        LCD_goto((1 + s), 0);
        LCD_putchar(txt3[s]);
        delay_ms(60);
    }
    for(s = 0; s < 10; s++)
    {
        LCD_goto((3 + s), 1);
        LCD_putchar(txt4[s]);
        delay_ms(60);
    }
    delay_ms(4000);

    s = 0;
    LCD_clear_home();

    LCD_goto(3, 0);
    LCD_putstr(txt1);

    while(1)
    {
        show_value(s);
        s++;
        delay_ms(400);
    };
}


void clock_init(void)
{
    PMM_setVCore(PMM_CORE_LEVEL_3);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
                                               (GPIO_PIN4 | GPIO_PIN2));

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5,
                                                (GPIO_PIN5 | GPIO_PIN3));

    UCS_setExternalClockSource(XT1_FREQ,
                               XT2_FREQ);

    UCS_turnOnXT2(UCS_XT2_DRIVE_4MHZ_8MHZ);

    UCS_turnOnLFXT1(UCS_XT1_DRIVE_0,
                    UCS_XCAP_3);

    UCS_initClockSignal(UCS_FLLREF,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_4);

    UCS_initFLLSettle(MCLK_KHZ,
                      MCLK_FLLREF_RATIO);

    UCS_initClockSignal(UCS_SMCLK,
                        UCS_REFOCLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


void show_value(unsigned char value)
{
   unsigned char ch = 0x00;

   ch = ((value / 100) + 0x30);
   LCD_goto(6, 1);
   LCD_putchar(ch);

   ch = (((value / 10) % 10) + 0x30);
   LCD_goto(7, 1);
   LCD_putchar(ch);

   ch = ((value % 10) + 0x30);
   LCD_goto(8, 1);
   LCD_putchar(ch);
}
