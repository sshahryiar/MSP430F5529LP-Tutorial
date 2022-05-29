#define XT1_FREQ          32768
#define XT2_FREQ          4000000
#define MCLK_FREQ         25000000

#define XT1_KHZ           (XT1_FREQ / 1000)
#define XT2_KHZ           (XT2_FREQ / 1000)
#define MCLK_KHZ          (MCLK_FREQ / 1000)

#define scale_factor       4

#define MCLK_FLLREF_RATIO (MCLK_KHZ / (XT2_KHZ / scale_factor))

#define CPU_F             ((double)MCLK_FREQ)

#define delay_us(delay)   __delay_cycles((long)(CPU_F*(((double)delay)/1000000.0)))
#define delay_ms(delay)   __delay_cycles((long)(CPU_F*(((double)delay)/1000.0)))
