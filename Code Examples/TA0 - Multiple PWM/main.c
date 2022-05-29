#include "driverlib.h"
#include "delay.h"


#define steps 32


void clock_init(void);
void GPIO_init(void);
void timer_T0A5_init(void);


void main(void)
{
    unsigned char i = 0x00;

    const unsigned int duty1_value[steps] = {0, 6424, 12786, 19026, 25082, 30896, 36413, 41579, 46344, 50664,
                                             54494, 57801, 60550, 62716, 64278, 65220, 65534, 65218, 64272, 62708, 60540,
                                             57788, 54480, 50647, 46326, 41558, 36391, 30873, 25057, 19000, 12760, 6397};

    const unsigned int duty2_value[steps] = {57801, 60550, 62716, 64278, 65220, 65534, 65218, 64272, 62708, 60540,
                                             57788, 54480, 50647, 46326, 41558, 36391, 30873, 25057, 19000, 12760,
                                             6397, 0, 6424, 12786, 19026, 25082, 30896, 36413, 41579, 46344, 50664, 54494};

    const unsigned int duty3_value[steps] = {57788, 54480, 50647, 46326, 41558, 36391, 30873, 25057, 19000, 12760,
                                             6397, 0, 6424, 12786, 19026, 25082, 30896, 36413, 41579, 46344, 50664,
                                             54494, 57801, 60550, 62716, 64278, 65220, 65534, 65218, 64272, 62708, 60540};


    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    timer_T0A5_init();

    while(true)
    {
        for(i = 0; i < steps; i++)
        {
            Timer_A_setCompareValue(TIMER_A0_BASE,
                                    TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                    duty1_value[i]);

            Timer_A_setCompareValue(TIMER_A0_BASE,
                                    TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                    duty2_value[i]);

            Timer_A_setCompareValue(TIMER_A0_BASE,
                                    TIMER_A_CAPTURECOMPARE_REGISTER_3,
                                    duty3_value[i]);

            delay_ms(250);
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

    UCS_turnOnLFXT1(UCS_XT1_DRIVE_0,
                    UCS_XCAP_3);

    UCS_initClockSignal(UCS_MCLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_SMCLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


void GPIO_init(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
                                                (GPIO_PIN2 + GPIO_PIN3 + GPIO_PIN4));
}


void timer_T0A5_init(void)
{
    Timer_A_initCompareModeParam CompareModeParam1 = {0};
    Timer_A_initCompareModeParam CompareModeParam2 = {0};
    Timer_A_initCompareModeParam CompareModeParam3 = {0};

    Timer_A_initContinuousModeParam ContinuousModeParam = {0};

    ContinuousModeParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    ContinuousModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    ContinuousModeParam.timerClear = TIMER_A_DO_CLEAR;
    ContinuousModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    ContinuousModeParam.startTimer = false;

    CompareModeParam1.compareInterruptEnable = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    CompareModeParam1.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    CompareModeParam1.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    CompareModeParam1.compareValue = 0;

    CompareModeParam2.compareInterruptEnable = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    CompareModeParam2.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    CompareModeParam2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    CompareModeParam2.compareValue = 0;

    CompareModeParam3.compareInterruptEnable = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    CompareModeParam3.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    CompareModeParam3.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    CompareModeParam3.compareValue = 0;

    Timer_A_initCompareMode(TIMER_A0_BASE,
                            &CompareModeParam1);

    Timer_A_initCompareMode(TIMER_A0_BASE,
                            &CompareModeParam2);

    Timer_A_initCompareMode(TIMER_A0_BASE,
                            &CompareModeParam3);

    Timer_A_initContinuousMode(TIMER_A0_BASE,
                               &ContinuousModeParam);

    Timer_A_startCounter(TIMER_A0_BASE,
                         TIMER_A_CONTINUOUS_MODE);
}
