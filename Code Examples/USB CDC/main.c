#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "USB_app/usbConstructs.h"

#include "hal.h"


volatile uint8_t bCDCDataReceived_event = FALSE;


#define RX_BUFFER_SIZE  1
#define TX_BUFFER_SIZE  4

char dataBuffer[RX_BUFFER_SIZE] = "";
char nl[2] = "\n";
uint16_t count;


void ADC12_init(void);
void REF_init(void);


#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG ))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
            UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            SYSBERRIV = 0;
            USB_disable();
    }
}


void main (void)
{
    float tmp = 0.0;
    signed int ADC_Count = 0;
    signed long temp = 0;
    uint8_t tc[TX_BUFFER_SIZE] = {0x00, 0x00, '\r', '\n'};

    WDT_A_hold(WDT_A_BASE);

    PMM_setVCore(PMM_CORE_LEVEL_2);

    REF_init();

    ADC12_init();

    LCD_init();
    LCD_clear_home();

    LCD_goto(1, 0);
    LCD_putstr("MSP430 USB CDC");

    LCD_goto(0, 1);
    LCD_putstr("T/'C:");

    LCD_goto(11, 1);
    LCD_putstr("RX:");

    USBHAL_initPorts();
    USBHAL_initClocks(8000000);
    USB_setup(TRUE, TRUE);

    __enable_interrupt();

    while (1)
    {
        uint8_t ReceiveError = 0;
        uint8_t SendError = 0;

        ADC_Count = ADC12_A_getResults(ADC12_A_BASE,
                                       ADC12_A_MEMORY_0);

        tmp = (((float)ADC_Count * 1.5) / 4095.0);
        temp = ((tmp - 0.688) / 0.00252);

        print_C(6, 1, temp);

        switch (USB_getConnectionState())
        {
            case ST_ENUM_ACTIVE:
            {
                __disable_interrupt();
                if (!USBCDC_getBytesInUSBBuffer(CDC0_INTFNUM))
                {
                    __bis_SR_register(LPM0_bits + GIE);
                }

                __enable_interrupt();


                if (bCDCDataReceived_event)
                {
                    bCDCDataReceived_event = FALSE;

                    count = USBCDC_receiveDataInBuffer((uint8_t*)dataBuffer,
                                                       RX_BUFFER_SIZE,
                                                       CDC0_INTFNUM);
                    LCD_goto(15, 1);
                    LCD_putstr(dataBuffer);
                }

                tc[0] = ((temp / 10) + 0x30);
                tc[1] = ((temp % 10) + 0x30);

                if(USBCDC_sendDataInBackground((uint8_t*)tc,
                                               TX_BUFFER_SIZE,
                                               CDC0_INTFNUM,
                                               1))
                {
                    SendError = 0x01;
                    break;
                }

                break;

            }
            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                __bis_SR_register(LPM3_bits + GIE);
                _NOP();
                break;

            case ST_ENUM_IN_PROGRESS:
            default:;
        }

        if (ReceiveError || SendError)
        {
        }
    }
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
