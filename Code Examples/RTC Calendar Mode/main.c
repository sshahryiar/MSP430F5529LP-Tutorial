#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


Calendar current_Time;
unsigned char update_time = false;


void clock_init(void);
void GPIO_init(void);
void RTC_init(void);
void display_year(unsigned char x_pos, unsigned char y_pos, unsigned int value);
void display_time_date(unsigned char x_pos, unsigned char y_pos, unsigned char value);
unsigned int change_value(unsigned char x_pos, unsigned char y_pos, signed int value, signed int value_min, signed int value_max, unsigned char value_type);
void set_RTC(void);


#pragma vector = RTC_VECTOR
__interrupt void RTC_A_ISR (void)
{
    switch(__even_in_range(RTCIV, 16))
    {
        case 0: break;  //No interrupts
        case 2:         //RTCRDYIFG
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);

            current_Time = RTC_A_getCalendarTime(RTC_A_BASE);

            update_time = true;

            break;
        }
        case 4: break;  //RTCEVIFG
        case 6: break;  //RTCAIFG
        case 8: break;  //RT0PSIFG
        case 10: break; //RT1PSIFG
        case 12: break; //Reserved
        case 14: break; //Reserved
        case 16: break; //Reserved
        default: break;
    }
}


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    RTC_init();
    LCD_init();

    LCD_clear_home();

    LCD_goto(6, 0);
    LCD_putstr(":  :");

    LCD_goto(5, 1);
    LCD_putstr("/  /");

    while(1)
    {

        set_RTC();

         if(update_time)
         {
             display_time_date(4, 0, current_Time.Hours);
             display_time_date(7, 0, current_Time.Minutes);
             display_time_date(10, 0, current_Time.Seconds);
             display_time_date(3, 1, current_Time.DayOfMonth);
             display_time_date(6, 1, current_Time.Month);
             display_year(9, 1, current_Time.Year);
             update_time = 0;
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
}


void RTC_init(void)
{
    current_Time.Seconds = 30;
    current_Time.Minutes = 10;
    current_Time.Hours = 10;
    current_Time.DayOfWeek = 1;
    current_Time.DayOfMonth = 1;
    current_Time.Month = 1;
    current_Time.Year = 2000;

    RTC_A_initCalendar(RTC_A_BASE,
                       &current_Time,
                       RTC_A_FORMAT_BINARY);

    RTC_A_setCalendarEvent(RTC_A_BASE,
                           RTC_A_CALENDAREVENT_MINUTECHANGE);

    RTC_A_clearInterrupt(RTC_A_BASE,
                         (RTCRDYIFG | RTCTEVIFG | RTCAIFG));

    RTC_A_enableInterrupt(RTC_A_BASE,
                          (RTCRDYIE | RTCTEVIE | RTCAIE));

    RTC_A_startClock(RTC_A_BASE);

    __enable_interrupt();
}


void display_year(unsigned char x_pos, unsigned char y_pos, unsigned int value)
{
    unsigned char tmp = 0;

    tmp = (value / 100);
    display_time_date(x_pos, y_pos, tmp);
    tmp = (value % 100);
    display_time_date((x_pos + 2), y_pos, tmp);
}


void display_time_date(unsigned char x_pos, unsigned char y_pos, unsigned char value)
{
    unsigned char ch = 0;

    ch = (value / 10);
    LCD_goto(x_pos, y_pos);
    LCD_putchar((ch + 0x30));

    ch = (value % 10);
    LCD_goto((1 + x_pos), y_pos);
    LCD_putchar((ch + 0x30));
}


unsigned int change_value(unsigned char x_pos, unsigned char y_pos, signed int value, signed int value_min, signed int value_max, unsigned char value_type)
{
    while(1)
    {
        LCD_goto(x_pos, y_pos);

        switch(value_type)
        {
            case 1:
            {
                LCD_putstr("    ");
                break;
            }
            default:
            {
                LCD_putstr("  ");
                break;
            }
        }

        delay_ms(60);

        if(GPIO_getInputPinValue(GPIO_PORT_P1,
                                 GPIO_PIN1) == false)
        {
            value++;
        }

        if(value > value_max)
        {
            value = value_min;
        }

        switch(value_type)
        {
            case 1:
            {
                display_year(x_pos, y_pos, ((unsigned int)value));
                break;
            }
            default:
            {
                display_time_date(x_pos, y_pos, ((unsigned char)value));
                break;
            }
        }
        delay_ms(90);

        if(GPIO_getInputPinValue(GPIO_PORT_P2,
                                 GPIO_PIN1) == false)
        {
            while(GPIO_getInputPinValue(GPIO_PORT_P2,
                                        GPIO_PIN1) == false);

            delay_ms(200);
            return value;
        }
    };
}


void set_RTC(void)
{
    if(GPIO_getInputPinValue(GPIO_PORT_P2,
                             GPIO_PIN1) == false)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                GPIO_PIN0);

        while(GPIO_getInputPinValue(GPIO_PORT_P2,
                                    GPIO_PIN1) == false);

        RTC_A_disableInterrupt(RTC_A_BASE,
                               (RTCRDYIE | RTCTEVIE | RTCAIE));

        RTC_A_holdClock(RTC_A_BASE);

        __disable_interrupt();

        update_time = false;

        current_Time.Hours = change_value(4, 0, current_Time.Hours, 0, 23, 0);

        current_Time.Minutes = change_value(7, 0, current_Time.Minutes, 0, 59, 0);

        current_Time.Seconds = change_value(10, 0, current_Time.Seconds, 0, 59, 0);

        current_Time.DayOfMonth = change_value(3, 1, current_Time.DayOfMonth, 1, 31, 0);

        current_Time.Month = change_value(6, 1, current_Time.Month, 1, 12, 0);

        current_Time.Year = change_value(9, 1, current_Time.Year, 1970, 2099, 1);

        GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                               GPIO_PIN0);

        RTC_A_initCalendar(RTC_A_BASE,
                           &current_Time,
                           RTC_A_FORMAT_BINARY);

        RTC_A_clearInterrupt(RTC_A_BASE,
                             (RTCRDYIFG | RTCTEVIFG | RTCAIFG));

        RTC_A_enableInterrupt(RTC_A_BASE,
                              (RTCRDYIE | RTCTEVIE | RTCAIE));

        RTC_A_startClock(RTC_A_BASE);

        __enable_interrupt();
    }
}
