#include "driverlib.h"
#include "delay.h"


void clock_init(void);
void GPIO_init(void);
void Comp_B_Plus(void);


#pragma vector = COMP_B_VECTOR
__interrupt void Comp_B_ISR(void)
{
    if(Comp_B_getInterruptStatus(COMP_B_BASE,
                                 COMP_B_OUTPUT_FLAG))
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                               GPIO_PIN7);

        Comp_B_clearInterrupt(COMP_B_BASE,
                              COMP_B_OUTPUT_FLAG);
    }
}


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    Comp_B_Plus();

    while(true)
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
    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN7);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                                               (GPIO_PIN0 + GPIO_PIN1));

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
                                                GPIO_PIN6);
}


void Comp_B_Plus(void)
{
    Comp_B_initParam Comp_B_Param = {0};

    Comp_B_Param.invertedOutputPolarity = COMP_B_NORMALOUTPUTPOLARITY;
    Comp_B_Param.positiveTerminalInput = COMP_B_INPUT0;
    Comp_B_Param.negativeTerminalInput = COMP_B_INPUT1;
    Comp_B_Param.outputFilterEnableAndDelayLevel = COMP_B_FILTEROUTPUT_DLYLVL3;
    Comp_B_Param.powerModeSelect = COMP_B_POWERMODE_NORMALMODE;

    Comp_B_init(COMP_B_BASE,
                &Comp_B_Param);

    Comp_B_enableInterrupt(COMP_B_BASE,
                           COMP_B_OUTPUT_INT);

    Comp_B_setInterruptEdgeDirection(COMP_B_BASE,
                                     COMP_B_RISINGEDGE);

    Comp_B_enable(COMP_B_BASE);

    __enable_interrupt();
}



