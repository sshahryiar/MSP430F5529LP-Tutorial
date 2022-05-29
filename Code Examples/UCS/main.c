#include "driverlib.h"
#include "delay.h"


void indicate(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                            GPIO_PIN7);

    delay_ms(20);

    GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                           GPIO_PIN7);

    delay_ms(20);
}


void toggle_LED(void)
{
    signed char i = 2;

    while(i > -1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                               GPIO_PIN0);

        delay_ms(40);
        i--;
    };

    GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                           GPIO_PIN0);
}


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsOutputPin(GPIO_PORT_P1,
                        GPIO_PIN0);

    GPIO_setDriveStrength(GPIO_PORT_P1,
                          GPIO_PIN0,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN7);

    GPIO_setDriveStrength(GPIO_PORT_P4,
                          GPIO_PIN7,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    indicate();
    toggle_LED();

    UCS_initClockSignal(UCS_MCLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    indicate();
    toggle_LED();

    UCS_initClockSignal(UCS_MCLK,
                        UCS_REFOCLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    indicate();
    toggle_LED();

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

    indicate();

    while (1)
    {
        toggle_LED();
    };
}
