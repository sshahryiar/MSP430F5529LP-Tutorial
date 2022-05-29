#include "driverlib.h"
#include "delay.h"


void clock_init(void);
void GPIO_init(void);
void timer_T0A5_init(void);


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    timer_T0A5_init();

    while(1)
    {
        if(Timer_A_getCounterValue(__MSP430_BASEADDRESS_T0A5__) >= 32768)
        {
            GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);

            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);
        }
        else
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                    GPIO_PIN0);

            GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);
        }
    };
}


void clock_init(void)
{
    PMM_setVCore(PMM_CORE_LEVEL_2);

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
}


void timer_T0A5_init(void)
{
    Timer_A_initContinuousModeParam ContinuousModeParam =
    {
         TIMER_A_CLOCKSOURCE_SMCLK,
         TIMER_A_CLOCKSOURCE_DIVIDER_1,
         TIMER_A_TAIE_INTERRUPT_DISABLE,
         TIMER_A_DO_CLEAR,
         false
    };

    Timer_A_stop(__MSP430_BASEADDRESS_T0A5__);

    Timer_A_clearTimerInterrupt(__MSP430_BASEADDRESS_T0A5__);

    Timer_A_initContinuousMode(__MSP430_BASEADDRESS_T0A5__,
                               &ContinuousModeParam);

    Timer_A_startCounter(__MSP430_BASEADDRESS_T0A5__,
                         TIMER_A_CONTINUOUS_MODE);
}
