#include <libopencm3/stm32/rcc.h>

int main(void)
{
    /* Initialization */
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

    /* Main loop */
    while (1) {

    }
 
    return 0;
}
