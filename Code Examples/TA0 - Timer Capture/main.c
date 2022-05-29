#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


unsigned int pulse_ticks = 0;
unsigned int start_time = 0;
unsigned int end_time = 0;


void clock_init(void);
void GPIO_init(void);
void timer_T0A5_init(void);
void timer_T2A3_init(void);


#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
  switch(__even_in_range(TA0IV, 10))
  {
       case 0x00: break;             // None
       case 0x02:                    // CCR1 IFG
       {
           end_time = Timer_A_getCaptureCompareCount(TIMER_A0_BASE,
                                                     TIMER_A_CAPTURECOMPARE_REGISTER_1);

           pulse_ticks = (end_time - start_time);

           start_time = end_time;

           Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1);

           break;
       }
       case 0x04: break;             // CCR2 IFG
       case 0x06: break;             // CCR3 IFG
       case 0x08: break;             // CCR4 IFG
       case 0x0A: break;             // CCR5 IFG
       case 0x0C: break;             // CCR6 IFG
       case 0x0E:                    // TA0IFG
       {
           GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                                  GPIO_PIN0);

           break;
       }
       default:   _never_executed();
  }
}


void main(void)
{
    unsigned char i = 0;
    unsigned char settings_changed = false;
    unsigned long timer_clock_frequency = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    timer_T0A5_init();
    timer_T2A3_init();

    LCD_init();
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("PWM./Hz:");

    LCD_goto(0, 1);
    LCD_putstr("Cap./Hz:");

    timer_clock_frequency = UCS_getSMCLK();

    while(true)
    {

        if(GPIO_getInputPinValue(GPIO_PORT_P2,
                                 GPIO_PIN1) == false)
        {
            while(GPIO_getInputPinValue(GPIO_PORT_P2,
                                        GPIO_PIN1) == false);

            i++;

            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);

            delay_ms(100);

            GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);

            if(i > 5)
            {
                i = 0;
            }

            settings_changed = false;

        }

        switch(settings_changed)
        {
            case true:
            {
                print_I(8, 1, (timer_clock_frequency / pulse_ticks));
                delay_ms(100);
                break;
            }

            default:
            {
                switch(i)
                {
                    case 1:
                    {
                        LCD_goto(9, 0);
                        LCD_putstr("200  ");

                        Timer_A_outputPWMParam outputPWMParam = {0};

                        outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
                        outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
                        outputPWMParam.timerPeriod = 5000;
                        outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
                        outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
                        outputPWMParam.dutyCycle = 0;

                        Timer_A_outputPWM(TIMER_A2_BASE,
                                          &outputPWMParam);

                        Timer_A_setCompareValue(TIMER_A2_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                                2000);

                        break;
                    }

                    case 2:
                    {
                        LCD_goto(9, 0);
                        LCD_putstr("125  ");

                        Timer_A_outputPWMParam outputPWMParam = {0};

                        outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
                        outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
                        outputPWMParam.timerPeriod = 8000;
                        outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
                        outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
                        outputPWMParam.dutyCycle = 0;

                        Timer_A_outputPWM(TIMER_A2_BASE,
                                          &outputPWMParam);

                        Timer_A_setCompareValue(TIMER_A2_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                                4000);

                        break;
                    }

                    case 3:
                    {
                        LCD_goto(9, 0);
                        LCD_putstr("1000 ");

                        Timer_A_outputPWMParam outputPWMParam = {0};

                        outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
                        outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
                        outputPWMParam.timerPeriod = 1000;
                        outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
                        outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
                        outputPWMParam.dutyCycle = 0;

                        Timer_A_outputPWM(TIMER_A2_BASE,
                                          &outputPWMParam);

                        Timer_A_setCompareValue(TIMER_A2_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                                600);

                        break;
                    }

                    case 4:
                    {
                        LCD_goto(9, 0);
                        LCD_putstr("8000 ");

                        Timer_A_outputPWMParam outputPWMParam = {0};

                        outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
                        outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
                        outputPWMParam.timerPeriod = 125;
                        outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
                        outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
                        outputPWMParam.dutyCycle = 0;

                        Timer_A_outputPWM(TIMER_A2_BASE,
                                          &outputPWMParam);

                        Timer_A_setCompareValue(TIMER_A2_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                                60);

                        break;
                    }

                    case 5:
                    {
                        LCD_goto(9, 0);
                        LCD_putstr("2000 ");

                        Timer_A_outputPWMParam outputPWMParam = {0};

                        outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
                        outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
                        outputPWMParam.timerPeriod = 500;
                        outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
                        outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
                        outputPWMParam.dutyCycle = 0;

                        Timer_A_outputPWM(TIMER_A2_BASE,
                                          &outputPWMParam);

                        Timer_A_setCompareValue(TIMER_A2_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                                250);

                        break;
                    }

                    default:
                    {

                        LCD_goto(9, 0);
                        LCD_putstr("333.3");

                        Timer_A_outputPWMParam outputPWMParam = {0};

                        outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
                        outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
                        outputPWMParam.timerPeriod = 3000;
                        outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
                        outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
                        outputPWMParam.dutyCycle = 0;

                        Timer_A_outputPWM(TIMER_A2_BASE,
                                          &outputPWMParam);

                        Timer_A_setCompareValue(TIMER_A2_BASE,
                                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                                1500);

                        break;
                    }

                }

                settings_changed = true;

                break;
            }
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
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,
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

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                                               GPIO_PIN2);

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,
                                                GPIO_PIN4);
}


void timer_T0A5_init(void)
{
    Timer_A_initCaptureModeParam CaptureModeParam = {0};
    Timer_A_initContinuousModeParam ContinuousModeParam = {0};

    Timer_A_stop(TIMER_A0_BASE);
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);

    ContinuousModeParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    ContinuousModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    ContinuousModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    ContinuousModeParam.timerClear = TIMER_A_SKIP_CLEAR;
    ContinuousModeParam.startTimer = true;

    CaptureModeParam.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    CaptureModeParam.captureMode = TIMER_A_CAPTUREMODE_RISING_EDGE;
    CaptureModeParam.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;
    CaptureModeParam.synchronizeCaptureSource = TIMER_A_CAPTURE_ASYNCHRONOUS;
    CaptureModeParam.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;

    Timer_A_initContinuousMode(TIMER_A0_BASE,
                               &ContinuousModeParam);

    Timer_A_initCaptureMode(TIMER_A0_BASE,
                            &CaptureModeParam);

    __enable_interrupt();
}


void timer_T2A3_init(void)
{
    Timer_A_outputPWMParam outputPWMParam = {0};

    outputPWMParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    outputPWMParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_4;
    outputPWMParam.timerPeriod = 2000;
    outputPWMParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    outputPWMParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    outputPWMParam.dutyCycle = 0;

    Timer_A_outputPWM(TIMER_A2_BASE,
                      &outputPWMParam);

    Timer_A_setCompareValue(TIMER_A2_BASE,
                            TIMER_A_CAPTURECOMPARE_REGISTER_1,
                            1000);
}
