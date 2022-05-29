#include "driverlib.h"


void GPIO_init(void);
void WDTA_init(void);


#pragma vector = WDT_VECTOR
__interrupt void WDT_A_ISR (void)
{
    GPIO_toggleOutputOnPin( GPIO_PORT_P1,
                            GPIO_PIN0);

    GPIO_toggleOutputOnPin( GPIO_PORT_P4,
                            GPIO_PIN7);
}


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    GPIO_init();
    WDTA_init();

    while(1)
    {
    };
}


void GPIO_init(void)
{
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

    GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                            GPIO_PIN0);

    GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                           GPIO_PIN7);
}


void WDTA_init(void)
{
    WDT_A_initIntervalTimer(WDT_A_BASE,
                            WDT_A_CLOCKSOURCE_SMCLK,
                            WDT_A_CLOCKDIVIDER_512K);

    SFR_clearInterrupt(SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT);

    SFR_enableInterrupt(SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT);

    WDT_A_start(WDT_A_BASE);

    __enable_interrupt();
}
