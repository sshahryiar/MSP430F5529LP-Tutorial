#include "driverlib.h"
#include "delay.h"
#include "DHT11.h"
#include "lcd.h"
#include "lcd_print.h"


extern unsigned char values[0x05];


void clock_init(void);


void main(void)
{
    unsigned char state = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();

    LCD_init();
    load_custom_symbol();

    DHT11_init();

    while(1)
    {
        state = get_data();

        switch(state)
        {
            case 1:
            {
            }
            case 2:
            {
                 LCD_clear_home();
                 LCD_putstr("No Sensor Found!");
                 break;
            }
            case 3:
            {
                 LCD_clear_home();
                 LCD_putstr("Checksum Error!");
                 break;
            }
            default:
            {
                 LCD_goto(0, 0);
                 LCD_putstr("R.H/ %:       ");

                 print_C(13, 0, values[0]);

                 LCD_goto(0, 1);
                 LCD_putstr("Tmp/");
                 print_symbol(4, 1, 0);
                 LCD_goto(5, 1);
                 LCD_putstr("C:");

                 if((values[2] & 0x80) == 1)
                 {
                     LCD_goto(13, 1);
                     LCD_putstr("-");
                 }
                 else
                 {
                     LCD_goto(13, 1);
                     LCD_putstr(" ");
                 }

                 print_C(13, 1, values[2]);
                 break;
            }
        }

        delay_ms(1000);
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

    UCS_initClockSignal(UCS_MCLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_SMCLK,
                        UCS_REFOCLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


