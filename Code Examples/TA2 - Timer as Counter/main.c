#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


void clock_init(void);
void GPIO_init(void);
void timer_T2A3_init(void);


void main(void)
{
    signed int value = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    timer_T2A3_init();
    LCD_init();

    LCD_clear_home();

    LCD_goto(1, 0);
    LCD_putstr("TA2 as Counter");

    LCD_goto(0, 1);
    LCD_putstr("Count:");


    while(true)
    {
        value = Timer_A_getCounterValue(TIMER_A2_BASE);
        print_C(12, 1, value);

        if((value > 20) && (value < 40))
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                    GPIO_PIN0);

            GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);
        }

        else if((value > 40) && (value < 60))
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);

            GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);
        }

        else if((value > 60) && (value < 120))
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                    GPIO_PIN0);

            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);
        }

        else
        {
            GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);

            GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);
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
                        UCS_CLOCK_DIVIDER_4);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


void GPIO_init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,
                                               GPIO_PIN2);

    GPIO_setAsOutputPin(GPIO_PORT_P1,
                        GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN7);
}


void timer_T2A3_init(void)
{
    Timer_A_initUpModeParam UpModeParam = {0};

    UpModeParam.clockSource = TIMER_A_CLOCKSOURCE_EXTERNAL_TXCLK;
    UpModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    UpModeParam.timerPeriod = 120;
    UpModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    UpModeParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    UpModeParam.timerClear = TIMER_A_SKIP_CLEAR;
    UpModeParam.startTimer = true;

    Timer_A_stop(TIMER_A2_BASE);

    Timer_A_clearTimerInterrupt(TIMER_A2_BASE);

    Timer_A_initUpMode(TIMER_A2_BASE,
                       &UpModeParam);
}




