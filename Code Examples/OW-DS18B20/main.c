#include "driverlib.h"
#include "delay.h"
#include "one_wire.h"
#include "DS18B20.h"
#include "lcd.h"
#include "lcd_print.h"


void clock_init(void);


void main(void)
{
    float t = 0.0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();

    DS18B20_init();

    LCD_init();
    load_custom_symbol();

    LCD_goto(1, 0);
    LCD_putstr("MSP430 DS18B20");

    LCD_goto(0, 1);
    LCD_putstr("T/ C");
    print_symbol(2, 1, 0);

    while(1)
    {
        t = DS18B20_get_temperature();
        print_F(9, 1, t, 3);
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


