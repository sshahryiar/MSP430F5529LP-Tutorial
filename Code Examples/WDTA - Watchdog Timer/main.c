#include "driverlib.h"
#include "delay.h"


void clock_init(void);
void GPIO_init(void);
void WDTA_init(void);


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    WDTA_init();

    while(1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                               GPIO_PIN0);

        delay_ms(600);

        WDT_A_resetTimer(WDT_A_BASE);

        if(GPIO_getInputPinValue(GPIO_PORT_P1,
                                 GPIO_PIN1) == false)
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);

            while(1);
        }
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
                        UCS_CLOCK_DIVIDER_2);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


void GPIO_init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,
                                         GPIO_PIN1);

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

    GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                           GPIO_PIN0);

    GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                           GPIO_PIN7);
}


void WDTA_init(void)
{
    WDT_A_initWatchdogTimer(WDT_A_BASE,
                            WDT_A_CLOCKSOURCE_VLOCLK,
                            WDT_A_CLOCKDIVIDER_32K);

    WDT_A_start(WDT_A_BASE);

    WDT_A_resetTimer(WDT_A_BASE);
}
