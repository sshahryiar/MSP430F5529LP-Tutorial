#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


void clock_init(void);
void GPIO_init(void);
void ADC12_init(void);
void DMA_HW_init(void);


uint16_t memory_location = 0x0000;


#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR (void)
{
    switch (__even_in_range(DMAIV, 16))
    {
        case 0: break;  //None
        case 2:         //DMA0IFG = DMA Channel 0
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);

            break;
        }
        case 4: break;  //DMA1IFG = DMA Channel 1
        case 6: break;  //DMA2IFG = DMA Channel 2
        case 8: break;  //DMA3IFG = DMA Channel 3
        case 10: break; //DMA4IFG = DMA Channel 4
        case 12: break; //DMA5IFG = DMA Channel 5
        case 14: break; //DMA6IFG = DMA Channel 6
        case 16: break; //DMA7IFG = DMA Channel 7
        default: break;
    }
}


void main(void)
{
    unsigned int volt = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    ADC12_init();
    DMA_HW_init();

    LCD_init();
    LCD_clear_home();

    LCD_goto(0, 0);
    LCD_putstr("ADC :");

    LCD_goto(0, 1);
    LCD_putstr("V/mV:");

    while(1)
    {
        volt = ((memory_location * 3300.0) / 4095.0);

        print_I(11, 0, memory_location);
        print_I(11, 1, volt);

        GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                               GPIO_PIN7);
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

    UCS_turnOnLFXT1(UCS_XT1_DRIVE_0,
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
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                                               GPIO_PIN0);

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



void ADC12_init(void)
{
    ADC12_A_configureMemoryParam configureMemoryParam = {0};

    ADC12_A_init(ADC12_A_BASE,
                 ADC12_A_SAMPLEHOLDSOURCE_SC,
                 ADC12_A_CLOCKSOURCE_ACLK,
                 ADC12_A_CLOCKDIVIDER_1);

    ADC12_A_setupSamplingTimer(ADC12_A_BASE,
                               ADC12_A_CYCLEHOLD_768_CYCLES,
                               ADC12_A_CYCLEHOLD_4_CYCLES,
                               ADC12_A_MULTIPLESAMPLESENABLE);

    ADC12_A_setResolution(ADC12_A_BASE,
                          ADC12_A_RESOLUTION_12BIT);

    configureMemoryParam.memoryBufferControlIndex = ADC12_A_MEMORY_0;
    configureMemoryParam.inputSourceSelect = ADC12_A_INPUT_A0;
    configureMemoryParam.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
    configureMemoryParam.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
    configureMemoryParam.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;

    ADC12_A_configureMemory(ADC12_A_BASE,
                            &configureMemoryParam);

    ADC12_A_enable(ADC12_A_BASE);

    ADC12_A_startConversion(ADC12_A_BASE,
                            ADC12_A_MEMORY_0,
                            ADC12_A_REPEATED_SINGLECHANNEL);
}


void DMA_HW_init(void)
{
    DMA_initParam DMA_init_Param = {0};

    DMA_disableTransferDuringReadModifyWrite();

    DMA_init_Param.channelSelect = DMA_CHANNEL_0;
    DMA_init_Param.transferModeSelect = DMA_TRANSFER_REPEATED_SINGLE;
    DMA_init_Param.transferSize = 1;
    DMA_init_Param.triggerSourceSelect = DMA_TRIGGERSOURCE_24;
    DMA_init_Param.transferUnitSelect = DMA_SIZE_SRCWORD_DSTWORD;
    DMA_init_Param.triggerTypeSelect = DMA_TRIGGER_RISINGEDGE;

    DMA_init(&DMA_init_Param);

    DMA_setSrcAddress(DMA_CHANNEL_0,
                      ADC12_A_getMemoryAddressForDMA(ADC12_A_BASE,ADC12_A_MEMORY_0),
                      DMA_DIRECTION_UNCHANGED);

    DMA_setDstAddress(DMA_CHANNEL_0,
                      (uint32_t)(uintptr_t)&memory_location,
                      DMA_DIRECTION_INCREMENT);

    DMA_clearInterrupt(DMA_CHANNEL_0);

    DMA_enableInterrupt(DMA_CHANNEL_0);

    DMA_enableTransfers(DMA_CHANNEL_0);

    __enable_interrupt();
}
