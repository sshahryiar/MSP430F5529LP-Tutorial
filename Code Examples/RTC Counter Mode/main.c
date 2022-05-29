#include "driverlib.h"
#include "delay.h"


void clock_init(void);
void GPIO_init(void);
void RTC_init(void);


#pragma vector=RTC_VECTOR
__interrupt void RTC_A_ISR(void)
{
    switch (__even_in_range(RTCIV, 16))
    {
        case 0: break;  //No interrupts
        case 2: break;  //RTCRDYIFG
        case 4:         //RTCEVIFG
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);

            GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);

            break;
        }
        case 6: break;  //RTCAIFG
        case 8: break;  //RT0PSIFG
        case 10: break; //RT1PSIFG
        default: break;
    }
}


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    RTC_init();

    while(1)
    {
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
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT2CLK_SELECT,
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

    GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                           GPIO_PIN0);

    GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                            GPIO_PIN7);
}


void RTC_init(void)
{
    RTC_A_initCounter(RTC_A_BASE,
                      RTC_A_CLOCKSELECT_RT1PS,
                      RTC_A_COUNTERSIZE_16BIT);

    RTC_A_initCounterPrescale(RTC_A_BASE,
                              RTC_A_PRESCALE_0,
                              RTC_A_PSCLOCKSELECT_SMCLK,
                              RTC_A_PSDIVIDER_4);

    RTC_A_initCounterPrescale(RTC_A_BASE,
                              RTC_A_PRESCALE_1,
                              RTC_A_PSCLOCKSELECT_RT0PS,
                              RTC_A_PSDIVIDER_16);

    RTC_A_setCounterValue(RTC_A_BASE,
                          0);

    RTC_A_clearInterrupt(RTC_A_BASE,
                         RTC_A_TIME_EVENT_INTERRUPT);

    RTC_A_clearInterrupt(RTC_A_BASE,
                         RTC_A_PRESCALE_TIMER1_INTERRUPT);

    RTC_A_enableInterrupt(RTC_A_BASE,
                          RTC_A_TIME_EVENT_INTERRUPT);

    RTC_A_enableInterrupt(RTC_A_BASE,
                          RTC_A_PRESCALE_TIMER1_INTERRUPT);

    RTC_A_startClock(RTC_A_BASE);

    __enable_interrupt();
}

