#include "driverlib.h"
#include "delay.h"


#define GATE_HIGH                   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2)
#define GATE_LOW                    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN2)

#define CLK_HIGH                    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN1)
#define CLK_LOW                     GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1)

#define A_HIGH                      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6)
#define A_LOW                       GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6)

#define B_HIGH                      GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0)
#define B_LOW                       GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0)

#define C_HIGH                      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN3)
#define C_LOW                       GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN3)

#define D_HIGH                      GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN7)
#define D_LOW                       GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN7)

#define SW                          GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN1)

#define top_seg                     4
#define bot_seg                     0

#define HIGH                        true
#define LOW                         false


const unsigned char num[0x0A] = {0xED, 0x21, 0x8F, 0xAB, 0x63, 0xEA, 0xEE, 0xA1, 0xEF, 0xEB};
unsigned char data_values[0x09] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


unsigned char n = 0x00;
unsigned char SW_in = 0x00;


void clock_init(void);
void GPIO_init(void);
void timer_T1A1_init(void);
void write_74HC164(register unsigned char value);
void write_74HC145(register unsigned char channel);
void show_LEDs(unsigned char LED1_state, unsigned char LED2_state, unsigned char LED3_state, unsigned char LED4_state);
void show_numbers(signed int value, unsigned char pos);


#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer_A_ISR(void)
{
    Timer_A_clearTimerInterrupt(TIMER_A1_BASE);

    write_74HC164(data_values[n]);
    write_74HC145(n);

    n++;

    if(n > 9)
    {
      n = 0;
    }
}


void main(void)
{
    signed int i = 0;
    signed int j = 9999;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    timer_T1A1_init();

    while(true)
    {
        switch(SW_in)
        {
             case 1:
             {
                 show_LEDs(1, 0, 0, 0);
                 break;
             }

             case 2:
             {
                 show_LEDs(0, 1, 0, 0);
                 break;
             }

             case 3:
             {
                 show_LEDs(0, 0, 1, 0);
                 break;
             }

             case 4:
             {
                 show_LEDs(0, 0, 0, 1);
                 break;
             }
        }

        SW_in = 0x00;

        i++;
        j--;

        if(i > 9999)
        {
            i = 0;
            j = 9999;
        }

        show_numbers(i, bot_seg);
        show_numbers(j, top_seg);

        delay_ms(100);
        show_LEDs(0, 0, 0, 0);
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
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);

    UCS_initClockSignal(UCS_ACLK,
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
}


void GPIO_init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P3,
                       GPIO_PIN1);

    GPIO_setAsOutputPin(GPIO_PORT_P2,
                        GPIO_PIN3);
    GPIO_setDriveStrength(GPIO_PORT_P2,
                          GPIO_PIN3,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P2,
                        GPIO_PIN6);

    GPIO_setDriveStrength(GPIO_PORT_P2,
                          GPIO_PIN6,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P3,
                        GPIO_PIN7);

    GPIO_setDriveStrength(GPIO_PORT_P3,
                          GPIO_PIN7,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN0);

    GPIO_setDriveStrength(GPIO_PORT_P4,
                          GPIO_PIN0,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P8,
                        GPIO_PIN1);

    GPIO_setDriveStrength(GPIO_PORT_P8,
                          GPIO_PIN1,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P8,
                        GPIO_PIN2);

    GPIO_setDriveStrength(GPIO_PORT_P8,
                          GPIO_PIN2,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);
}


void timer_T1A1_init(void)
{
    Timer_A_initUpModeParam UpModeParam = {0};

    UpModeParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    UpModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    UpModeParam.timerPeriod = 9999;
    UpModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    UpModeParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    UpModeParam.timerClear = TIMER_A_DO_CLEAR;
    UpModeParam.startTimer = true;

    Timer_A_initUpMode(TIMER_A1_BASE,
                       &UpModeParam);

    Timer_A_startCounter(TIMER_A1_BASE,
                         TIMER_A_UP_MODE);

    __enable_interrupt();
}


void write_74HC164(register unsigned char value)
{
  register unsigned char s = 0x08;

  while(s > 0)
  {
        if((value & 0x80) != 0x00)
        {
            GATE_HIGH;
        }
        else
        {
            GATE_LOW;
        }

        CLK_HIGH;
        CLK_LOW;

        value <<= 1;
        s--;
  };
}


void write_74HC145(register unsigned char channel)
{
    A_LOW;
    B_LOW;
    C_LOW;
    D_LOW;

    switch(channel)
    {
        case 0:
        {
            if(SW == LOW)
            {
                SW_in = 1;
            }

            break;
        }

        case 1:
        {
            A_HIGH;
            B_LOW;
            C_LOW;
            D_LOW;

            break;
        }

        case 2:
        {
            A_LOW;
            B_HIGH;
            C_LOW;
            D_LOW;

            break;
        }

        case 3:
        {
            A_HIGH;
            B_HIGH;
            C_LOW;
            D_LOW;

            break;
        }

        case 4:
        {
            A_LOW;
            B_LOW;
            C_HIGH;
            D_LOW;

            break;
        }

        case 5:
        {
            A_HIGH;
            B_LOW;
            C_HIGH;
            D_LOW;

            break;
        }

        case 6:
        {
            A_LOW;
            B_HIGH;
            C_HIGH;
            D_LOW;

            break;
        }

        case 7:
        {
            A_HIGH;
            B_HIGH;
            C_HIGH;
            D_LOW;

            if(SW == LOW)
            {
                SW_in = 2;
            }

            break;
        }

        case 8:
        {
            A_LOW;
            B_LOW;
            C_LOW;
            D_HIGH;

            if(SW == LOW)
            {
                SW_in = 3;
            }

            break;
        }

        case 9:
        {
            A_HIGH;
            B_LOW;
            C_LOW;
            D_HIGH;

            if(SW == LOW)
            {
                SW_in = 4;
            }

            break;
        }
    }
}


void show_LEDs(unsigned char LED1_state, unsigned char LED2_state, unsigned char LED3_state, unsigned char LED4_state)
{
  switch(LED1_state)
  {
    case HIGH:
    {
        data_values[8] |= 0x80;
        break;
    }
    case LOW:
    {
        data_values[8] &= 0x7F;
        break;
    }
  }

  switch(LED2_state)
  {
    case HIGH:
    {
       data_values[8] |= 0x40;
       break;
    }
    case LOW:
    {
       data_values[8] &= 0xBF;
       break;
    }
  }

  switch(LED3_state)
  {
    case HIGH:
    {
       data_values[8] |= 0x08;
       break;
    }
    case LOW:
    {
       data_values[8] &= 0xF7;
       break;
    }
  }

  switch(LED4_state)
  {
    case HIGH:
    {
       data_values[8] |= 0x02;
       break;
    }
    case LOW:
    {
       data_values[8] &= 0xFD;
       break;
    }
  }
}


void show_numbers(signed int value, unsigned char pos)
{
  register unsigned char ch = 0x00;

  if((value >= 0) && (value <= 9))
  {
    ch = (value % 10);
    data_values[(0 + pos)] = num[ch];
    data_values[(1 + pos)] = 0x00;
    data_values[(2 + pos)] = 0x00;
    data_values[(3 + pos)] = 0x00;
  }
  else if((value > 9) && (value <= 99))
  {
    ch = (value % 10);
    data_values[(0 + pos)] = num[ch];
    ch = ((value / 10) % 10);
    data_values[(1 + pos)] = num[ch];
    data_values[(2 + pos)] = 0x00;
    data_values[(3 + pos)] = 0x00;
  }
  else if((value > 99) && (value <= 999))
  {
    ch = (value % 10);
    data_values[(0 + pos)] = num[ch];
    ch = ((value / 10) % 10);
    data_values[(1 + pos)] = num[ch];
    ch = ((value / 100) % 10);
    data_values[(2 + pos)] = num[ch];
    data_values[(3 + pos)] = 0x00;
  }
  else if((value > 999) && (value <= 9999))
  {
    ch = (value % 10);
    data_values[(0 + pos)] = num[ch];
    ch = ((value / 10) % 10);
    data_values[(1 + pos)] = num[ch];
    ch = ((value / 100) % 10);
    data_values[(2 + pos)] = num[ch];
    ch = (value / 1000);
    data_values[(3 + pos)] = num[ch];
  }
}
