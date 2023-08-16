#include <libopencm3/stm32/rcc.h>   // Reset and Clock Controller
#include <libopencm3/stm32/gpio.h>  // GPIO

// Nice to define marcos for GPIO configuations
#define LED_RCC_PORT (RCC_GPIOC)
#define LED_PORT     (GPIOC)
#define LED_PIN      (GPIO13)

/* A simple delay function
 * 
 * Note: each cycle takes about 5 ticks under -Os optimization
*/
static void delay_cycles(uint32_t cycles)
{
    while (cycles--) {
        __asm__("nop");     // assembly of no operation
    }
}

int main(void)
{
    /* Initialization */

    // Setup system clock
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]); // set system clock

    // setup GPIO
    rcc_periph_clock_enable(LED_RCC_PORT);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);

    /* Main loop */
    while (1) {
        gpio_toggle(LED_PORT, LED_PIN);
        delay_cycles(84000000 / 5);     // delay 1s
    }
 
    return 0;
}
