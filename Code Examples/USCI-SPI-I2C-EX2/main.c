#include "driverlib.h"
#include "delay.h"
#include "SSD1306.h"
#include "MAX6675.h"


extern unsigned char buffer[buffer_size];


void clock_init(void);


void main(void)
{
    float t = 0;
    unsigned int ti = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    OLED_init();
    MAX6675_init();

    while(1)
    {
        MAX6675_get_ADC(&ti);
        t = MAX6675_get_T(ti, deg_C);

        print_float(40, 10, NUM, t, 1);

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

    UCS_turnOnLFXT1(UCS_XT1_DRIVE_3,
                    UCS_XCAP_3);

    UCS_initClockSignal(UCS_FLLREF, UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_4);

    UCS_initFLLSettle(MCLK_KHZ, MCLK_FLLREF_RATIO);

    UCS_initClockSignal(UCS_SMCLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_4);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}

