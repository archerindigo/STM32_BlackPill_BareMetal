/******************************************************************************
 * app_3_systick
 * 
 * Program 3: Use system tick timer to record system up-time and toggle the LED
 * in a more accurate timing
 * 
 * Demostrate the use of systick and interrupt handler
 *****************************************************************************/

#include <libopencm3/stm32/rcc.h>   // Reset and Clock Controller
#include <libopencm3/stm32/gpio.h>  // GPIO
#include <libopencm3/cm3/systick.h> // System Tick Timer
#include <libopencm3/cm3/vector.h>  // Vector table
#include <stdint.h>

/* System configuration */
#define SYSTICK_FREQ (1000)         // Target frequency of system tick timer

/* Pin configuration */
#define LED_RCC_PORT (RCC_GPIOC)
#define LED_PORT     (GPIOC)
#define LED_PIN      (GPIO13)

/* Global variables */
volatile uint64_t uptime_ms = 0;    // use volatile as the comiler may not know
                                    // that the variable will be updated by sys_tick_handler

void sys_tick_handler(void)
{
    uptime_ms++;
}

/*
 * Initialization of clock related sutff
 */
static void setup_rcc(void)
{
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]); // set system clock
}

/*
 * Initialization of GPIOs
 */
static void setup_gpio(void)
{
    rcc_periph_clock_enable(LED_RCC_PORT);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);
}

static void setup_systick(void)
{
    systick_set_frequency(SYSTICK_FREQ, rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ].ahb_frequency);
    systick_counter_enable();
    systick_interrupt_enable();
}

int main(void)
{
    /* Initialization */
    setup_rcc();
    setup_gpio();
    setup_systick();

    uint32_t start_time = uptime_ms;

    /* Main loop */
    while (1) {
        if (1000 <= uptime_ms - start_time) {   // toggle the LED every 1s
            start_time = uptime_ms;     // mark the time first
            gpio_toggle(LED_PORT, LED_PIN);
        }
    }
 
    return 0;
}
