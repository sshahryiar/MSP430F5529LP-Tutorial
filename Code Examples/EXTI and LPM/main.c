#include "driverlib.h"


unsigned char toggle = 0;


void GPIO_init(void);


#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    LPM3_EXIT;

    if(GPIO_getInterruptStatus(GPIO_PORT_P1,
                               GPIO_PIN1) != 0)
    {
        GPIO_clearInterrupt(GPIO_PORT_P1,
                            GPIO_PIN1);

        toggle = 1;
        _nop();
    }
}


void main(void)
{
    unsigned char i = 0;
    unsigned char j = 0;

    WDT_A_hold(WDT_A_BASE);

    GPIO_init();

    while(1)
    {
        for(j = 0; j < 10; j++)
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);

            __delay_cycles(1000000);
        }

        if(toggle)
        {
            for(i = 0; i <= 9; i++)
            {
                GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                                       GPIO_PIN7);

                __delay_cycles(100000);
            }

            toggle = 0;
        }

        LPM3;
    };
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

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,
                                         GPIO_PIN1);

    GPIO_clearInterrupt(GPIO_PORT_P1,
                        GPIO_PIN1);

    GPIO_selectInterruptEdge(GPIO_PORT_P1,
                             GPIO_PIN1,
                             GPIO_HIGH_TO_LOW_TRANSITION);

    GPIO_enableInterrupt(GPIO_PORT_P1,
                         GPIO_PIN1);

    __enable_interrupt();
}
