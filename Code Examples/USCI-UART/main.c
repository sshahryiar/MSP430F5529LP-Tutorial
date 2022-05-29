#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


char RX_Data = 0;
char TX_Data = 0;


void clock_init(void);
void GPIO_init(void);
void USCI_UART_init(void);


#pragma vector = USCI_A1_VECTOR
__interrupt void UART_ISR(void)
{
    switch(__even_in_range(UCA1IV, 4))
    {
        case 0x00:      // None
        {
            break;
        }

        case 0x02:      //Data RX
        {
            RX_Data = USCI_A_UART_receiveData(USCI_A1_BASE);

            GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);

            break;
        }

        case 0x04:      //TX Buffer Empty
        {
            break;
        }
    }
}


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    clock_init();

    USCI_UART_init();

    GPIO_init();

    LCD_init();
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("MSP430 USCI UART");
    LCD_goto(0, 1);
    LCD_putstr("TXD: ");
    LCD_goto(10, 1);
    LCD_putstr("RXD: ");

    while(1)
    {
        TX_Data = RX_Data;

        GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                               GPIO_PIN0);

        USCI_A_UART_transmitData(USCI_A1_BASE,
                                 TX_Data);

        while(USCI_A_UART_getInterruptStatus(USCI_A1_BASE,
                                             USCI_A_UART_TRANSMIT_INTERRUPT_FLAG) == 0);

        LCD_goto(5, 1);
        LCD_putchar(TX_Data);

        LCD_goto(15, 1);
        LCD_putchar(RX_Data);

        delay_ms(900);
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
                        UCS_CLOCK_DIVIDER_4);

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

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                               GPIO_PIN5);

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4,
                                                GPIO_PIN4);
}


void USCI_UART_init(void)
{
    USCI_A_UART_initParam UART_Param = {0};

    UART_Param.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK;
    UART_Param.clockPrescalar = 3;
    UART_Param.firstModReg = 0;
    UART_Param.secondModReg = 3;
    UART_Param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    UART_Param.parity = USCI_A_UART_NO_PARITY;
    UART_Param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    UART_Param.uartMode = USCI_A_UART_MODE;
    UART_Param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    USCI_A_UART_init(USCI_A1_BASE,
                     &UART_Param);

    USCI_A_UART_resetDormant(USCI_A1_BASE);

    USCI_A_UART_enable(USCI_A1_BASE);

    USCI_A_UART_enableInterrupt(USCI_A1_BASE,
                                USCI_A_UART_RECEIVE_INTERRUPT);

    __enable_interrupt();

}
