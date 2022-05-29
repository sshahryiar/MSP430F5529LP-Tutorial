#include "driverlib.h"
#include "delay.h"
#include "ST7735.h"
#include "MMA7455L.h"


void clock_init(void);


void main(void)
{
    signed char x_axis_8 = 0;
    signed char y_axis_8 = 0;
    signed char z_axis_8 = 0;

    WDT_A_hold(WDT_A_BASE);

    clock_init();
    ST7735_init();
    MMA7455L_init();

    ST7735_Set_Rotation(0x02);
    TFT_fill(BLACK);

    print_str(1, 100, 1, GREEN, BLACK, "X8:");
    print_str(1, 110, 1, GREEN, BLACK, "Y8:");
    print_str(1, 120, 1, GREEN, BLACK, "Z8:");



    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN7);

    GPIO_setDriveStrength(GPIO_PORT_P4,
                          GPIO_PIN7,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    while(1)
    {
        x_axis_8 = MMA7455L_read_axis_8(MMA7455L_X_out);
        y_axis_8 = MMA7455L_read_axis_8(MMA7455L_Y_out);
        z_axis_8 = MMA7455L_read_axis_8(MMA7455L_Z_out);

        print_C(45, 100, 1, GREEN, BLACK, x_axis_8);
        print_C(45, 110, 1, GREEN, BLACK, y_axis_8);
        print_C(45, 120, 1, GREEN, BLACK, z_axis_8);

        Draw_Circle(x_axis_8, x_axis_8, 2, YES, CYAN);

        GPIO_toggleOutputOnPin(GPIO_PORT_P4,
                               GPIO_PIN7);

        delay_ms(100);

        Draw_Circle(x_axis_8, x_axis_8, 2, YES, BLACK);
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
