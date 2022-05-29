#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


void clock_init(void);
void timer_T0A5_init(void);


void main(void)
{
    unsigned int i = 0;
    unsigned int j = 0;

    signed long res = 0;
    signed int num1 = 263;
    signed int num2 = 249;
    unsigned int timer_count = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    timer_T0A5_init();

    LCD_init();
    LCD_clear_home();

    LCD_goto(4, 0);
    LCD_putstr("Software");
    LCD_goto(1, 1);
    LCD_putstr("Multiplication");

    delay_ms(2000);
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("263(x)249=");
    LCD_goto(0, 1);
    LCD_putstr("T.CNT = ");

    Timer_A_startCounter(__MSP430_BASEADDRESS_T0A5__,
                         TIMER_A_CONTINUOUS_MODE);

    for(i = 0; i < num1; i++)
    {
        for(j = 0; j < num2; j++)
        {
            res++;
        }
    }

    timer_count = Timer_A_getCounterValue(__MSP430_BASEADDRESS_T0A5__);

    Timer_A_stop(__MSP430_BASEADDRESS_T0A5__);

    print_I(10, 0, res);
    print_I(10, 1, timer_count);

    delay_ms(4000);
    LCD_clear_home();


    res = 0;
    timer_count = 0;
    Timer_A_clear(__MSP430_BASEADDRESS_T0A5__);

    LCD_goto(4, 0);
    LCD_putstr("Hardware");
    LCD_goto(1, 1);
    LCD_putstr("Multiplication");

    delay_ms(2000);
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("263(x)249=");
    LCD_goto(0, 1);
    LCD_putstr("T.CNT = ");

    Timer_A_startCounter(__MSP430_BASEADDRESS_T0A5__,
                         TIMER_A_CONTINUOUS_MODE);

    MPY32_setOperandOne16Bit(MPY32_MULTIPLY_UNSIGNED,
                             num1);

    MPY32_setOperandTwo16Bit(num2);

    res = MPY32_getResult();

    timer_count = Timer_A_getCounterValue(__MSP430_BASEADDRESS_T0A5__);

    Timer_A_stop(__MSP430_BASEADDRESS_T0A5__);

    print_I(10, 0, res);
    print_I(10, 1, timer_count);

    delay_ms(4000);


    num1 = -99;
    num2 = 660;

    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("Signed Software");
    LCD_goto(1, 1);
    LCD_putstr("Multiplication");

    delay_ms(2000);
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("-99(x)660=");
    LCD_goto(0, 1);
    LCD_putstr("T.CNT = ");

    Timer_A_startCounter(__MSP430_BASEADDRESS_T0A5__,
                         TIMER_A_CONTINUOUS_MODE);

    res = (((signed long)num1) * ((signed long)num2));

    timer_count = Timer_A_getCounterValue(__MSP430_BASEADDRESS_T0A5__);

    Timer_A_stop(__MSP430_BASEADDRESS_T0A5__);

    print_I(10, 0, res);
    print_I(10, 1, timer_count);

    delay_ms(4000);
    LCD_clear_home();


    res = 0;
    timer_count = 0;

    Timer_A_clear(__MSP430_BASEADDRESS_T0A5__);

    LCD_goto(0, 0);
    LCD_putstr("Signed Hardware");
    LCD_goto(1, 1);
    LCD_putstr("Multiplication");

    delay_ms(2000);
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("-99(x)660=");
    LCD_goto(0, 1);
    LCD_putstr("T.CNT = ");

    Timer_A_startCounter(__MSP430_BASEADDRESS_T0A5__,
                         TIMER_A_CONTINUOUS_MODE);

    MPY32_setOperandOne16Bit(MPY32_MULTIPLY_SIGNED,
                             num1);

    MPY32_setOperandTwo16Bit(num2);

    res = MPY32_getResult();

    timer_count = Timer_A_getCounterValue(__MSP430_BASEADDRESS_T0A5__);

    Timer_A_stop(__MSP430_BASEADDRESS_T0A5__);

    print_I(10, 0, res);
    print_I(10, 1, timer_count);

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
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
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

    Timer_A_initContinuousMode(__MSP430_BASEADDRESS_T0A5__,
                               &ContinuousModeParam);
}
