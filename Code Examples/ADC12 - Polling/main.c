#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"


void clock_init(void);
void GPIO_init(void);
void ADC12_init(void);
void REF_init(void);


void main(void)
{
    signed int ADC_Count = 0;
    signed long temp = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    GPIO_init();
    REF_init();
    ADC12_init();

    LCD_init();
    LCD_clear_home();
    load_custom_symbol();

    LCD_goto(0, 0);
    LCD_putstr("ADC :");

    LCD_goto(0, 1);
    LCD_putstr("T/ C:");
    print_symbol(2, 1, 0);

    while(1)
    {
        ADC_Count = ADC12_A_getResults(ADC12_A_BASE,
                                       ADC12_A_MEMORY_0);

        temp = ((((signed long)ADC_Count - 1855) * 667) / 4096);

        print_I(11, 0, ADC_Count);
        print_I(13, 1, temp);

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
    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN7);
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
    configureMemoryParam.inputSourceSelect = ADC12_A_INPUT_TEMPSENSOR;
    configureMemoryParam.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_INT;
    configureMemoryParam.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
    configureMemoryParam.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;

    ADC12_A_configureMemory(ADC12_A_BASE,
                            &configureMemoryParam);

    ADC12_A_enable(ADC12_A_BASE);

    ADC12_A_startConversion(ADC12_A_BASE,
                            ADC12_A_MEMORY_0,
                            ADC12_A_REPEATED_SINGLECHANNEL);
}


void REF_init(void)
{
    while(REF_ACTIVE == Ref_isRefGenBusy(REF_BASE));

    Ref_setReferenceVoltage(REF_BASE,
                            REF_VREF1_5V);

    Ref_enableReferenceVoltage(REF_BASE);

    __delay_cycles(100);
}
