#include <msp430.h>
#include "driverlib.h"
#include "delay.h"
#include "USCI_I2C.h"
#include "USCI_SPI.h"
#include "PCD8544.h"
#include "BH1750.h"


void clock_init(void);


void main(void)
{
    unsigned int LX = 0x0000;
    unsigned int tmp = 0x0000;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    PCD8544_init();
    BH1750_init();

    print_string(1, 3, "Lux:", ON);

    while(1)
    {
        tmp = get_lux_value(cont_H_res_mode1, 20);

        if(tmp > 10)
        {
            LX = tmp;
        }
        else
        {
            LX = get_lux_value(cont_H_res_mode1, 140);
        }

        print_int(35, 3, LX, ON);

        delay_ms(200);
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

    UCS_initClockSignal(UCS_FLLREF,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_4);

    UCS_initFLLSettle(MCLK_KHZ,
                      MCLK_FLLREF_RATIO);

    UCS_initClockSignal(UCS_SMCLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_4);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}
