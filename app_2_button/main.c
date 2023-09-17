/******************************************************************************
 * app_2_button
 * 
 * Program 2: Toggle the built-in LED upon button press
 * 
 * Demostrate the setup of input GPIO with pull-up
 *****************************************************************************/
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdbool.h>

/* Pin definition */
// Built-in LED (PC13)
#define LED_RCC_PORT (RCC_GPIOC)
#define LED_PORT     (GPIOC)
#define LED_PIN      (GPIO13)

// Built-in push button (PA0) 
#define BTN_RCC_PORT (RCC_GPIOA)
#define BTN_PORT     (GPIOA)
#define BTN_PIN      (GPIO0)

static void delay_cycles(uint32_t cycles)
{
    while (cycles--) {
        __asm__("nop");     // assembly of no operation
    }
}

static bool read_btn_debounce(void)
{
    bool btn_state = gpio_get(BTN_PORT, BTN_PIN);

    if (!btn_state) {       // Pin state is false (LOW) when the button is pressed
        delay_cycles(8400000 / 100);     // ~50ms
        if (!gpio_get(BTN_PORT, BTN_PIN))
            return true;    // button is indeed pressed
    }

    return false;   // button not pressed
}

static void init(void)
{
    // Clock initialization
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
    rcc_periph_clock_enable(LED_RCC_PORT);
    rcc_periph_clock_enable(BTN_RCC_PORT);

    // Setup for LED
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);
    gpio_set(LED_PORT, LED_PIN);        // Set PC13 to HIGH to turn off the LED on boot

    // Setup for push button
    gpio_mode_setup(BTN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, BTN_PIN);    // Pull-up required
}

int main(void)
{
    /* Main variables */
    bool btn_pressed;   // For recording previous state of the button

    /* Initialization */
    init();

    /* Main loop */
    while (1) {
        if (read_btn_debounce()) {
            if (!btn_pressed)   // To make sure the LED will toggle once during a single press
                gpio_toggle(LED_PORT, LED_PIN);
            btn_pressed = true;
        }
        else {
            btn_pressed = false;
        }
    }
 
    return 0;
}
