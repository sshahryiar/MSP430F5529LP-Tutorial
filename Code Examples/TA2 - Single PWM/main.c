#include "driverlib.h"
#include "delay.h"


#define INC         1
#define DEC         0


void clock_init(void);
void GPIO_init(void);
void timer_T2A3_init(void);


void main(void)
{
    unsigned char dir = INC;
    unsigned int r = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    timer_T2A3_init();

    while(true)
    {
        if((r < 1500) && (dir == INC))
        {
            r++;
        }

        if((r == 1500) && (dir == INC))
        {
            dir = DEC;
        }

        if((r > 0) && (dir == DEC))
        {
            r--;
        }

        if((r == 0) && (dir == DEC))
        {
            dir = INC;
        }

        Timer_A_setCompareValue(TIMER_A2_BASE,
                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                (1000 + r));

        delay_ms(2);
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
                        UCS_CLOCK_DIVIDER_2);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


void GPIO_init(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,
                                                GPIO_PIN4);
}


void timer_T2A3_init(void)
{
    Timer_A_outputPWMParam outputPWMParam = {0};

    outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_2;
    outputPWMParam.timerPeriod = 20000;
    outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    outputPWMParam.dutyCycle = 0;

    Timer_A_outputPWM(TIMER_A2_BASE,
                      &outputPWMParam);

    Timer_A_setCompareValue(TIMER_A2_BASE,
                            TIMER_A_CAPTURECOMPARE_REGISTER_1,
                            1000);
}
