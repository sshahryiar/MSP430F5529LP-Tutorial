#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


#define INFOA_START     0x1980
#define INFOA_END       0x19FF

#define INFOB_START     0x1900
#define INFOB_END       0x197F

#define INFOC_START     0x1880
#define INFOC_END       0x18FF

#define INFOD_START     0x1800
#define INFOD_END       0x187F


void clock_init(void);
void GPIO_init(void);
char Flash_Read_Char(unsigned int address);
unsigned int Flash_Read_Word(unsigned int address);


void main(void)
{
    unsigned char s = 0x00;
    unsigned char temp = 0x00;
    unsigned char value[2] = {0x00, 0x00};
    unsigned char set_values[4] = {33, 64, 99, 16};
    unsigned int status = 0x0000;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();

    LCD_init();
    LCD_clear_home();

    CRC_setSeed(CRC_BASE,
                0xABCD);

    CRC_set8BitData(CRC_BASE,
                    Flash_Read_Char(INFOB_START));

    temp = CRC_getResult(CRC_BASE);

    LCD_goto(0, 0);
    LCD_putstr("Checking CRC");

    LCD_goto(0, 1);
    LCD_putstr("STO");

    LCD_goto(8, 1);
    LCD_putstr("CRC");

    print_C(3, 1, Flash_Read_Char(INFOB_START + 1));
    print_C(11, 1, temp);

    delay_ms(1600);

    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("INFO A Seg.");

    if(temp != Flash_Read_Char(INFOB_START + 1))
    {
        do
        {
            FlashCtl_eraseSegment((unsigned char *)INFOB_START);

            status = FlashCtl_performEraseCheck((unsigned char *)INFOB_START,
                                                128);
        }while (status == STATUS_FAIL);
    }

    if((GPIO_getInputPinValue(GPIO_PORT_P2,
                              GPIO_PIN1) == false))
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                GPIO_PIN7);

        FlashCtl_unlockInfoA();

        do
        {
            FlashCtl_eraseSegment((unsigned char *)INFOA_START);

            status = FlashCtl_performEraseCheck((unsigned char *)INFOA_START,
                                                128);
        }while (status == STATUS_FAIL);

        FlashCtl_write8(set_values,
                        (unsigned char *)INFOA_START,
                        4);

        FlashCtl_lockInfoA();

        LCD_goto(0, 1);
        LCD_putstr("Set: 33 64 99 16");

        delay_ms(2600);

        GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                               GPIO_PIN7);
    }

    else
    {
        LCD_goto(0, 1);
        LCD_putstr("Read");

        for(s = 0; s < 4; s++)
        {
            temp = Flash_Read_Char(INFOA_START + s);
            print_C(5, 1, s);
            print_C(13, 1, temp);
            delay_ms(2000);
        }
    }


    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("INFO B Seg.");


    temp = Flash_Read_Char(INFOB_START);
    LCD_goto(0, 1);
    LCD_putstr("WR: ---");
    LCD_goto(9, 1);
    LCD_putstr("RD:");
    print_C(12, 1, temp);
    delay_ms(2000);

    temp = 0;

    while(1)
    {
        if(GPIO_getInputPinValue(GPIO_PORT_P1,
                                 GPIO_PIN1) == false)
        {
            while(GPIO_getInputPinValue(GPIO_PORT_P1,
                                        GPIO_PIN1) == false);

            print_C(3, 1, value[0]);

            do
            {
                FlashCtl_eraseSegment((unsigned char *)INFOB_START);

                status = FlashCtl_performEraseCheck((unsigned char *)INFOB_START,
                                                    128);
            }while (status == STATUS_FAIL);

            CRC_setSeed(CRC_BASE,
                        0xABCD);

            CRC_set8BitData(CRC_BASE,
                            value[0]);

            value[1] = CRC_getResult(CRC_BASE);

            FlashCtl_write8(value,
                            (unsigned char *)INFOB_START,
                            2);

            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);

            delay_ms(1000);

            GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);

        }

        delay_ms(20);

        print_C(3, 1, value[0]);
        value[0] = temp++;

        delay_ms(200);
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


char Flash_Read_Char(unsigned int address)
{
    char value = 0x00;
    char *FlashPtr = (char *)address;

    value = *FlashPtr;

    return value;
}


unsigned int Flash_Read_Word(unsigned int address)
{
    unsigned int value = 0x0000;
    unsigned int *FlashPtr = (unsigned int *)address;

    value = *FlashPtr;

    return value;
}
