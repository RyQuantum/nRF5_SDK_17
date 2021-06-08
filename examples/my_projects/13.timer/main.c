#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"

#define LED_1          NRF_GPIO_PIN_MAP(0,13)
#define LED_4          NRF_GPIO_PIN_MAP(0,16)

const nrfx_timer_t TIMER_LED = NRFX_TIMER_INSTANCE(0);


void timer0_handler(nrf_timer_event_t event_type, void* p_context)
{
    switch(event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            nrf_gpio_pin_toggle(LED_1);
            nrf_gpio_pin_toggle(LED_4);
            break;
        default:
            break;
    }
}

void timer_init(void)
{
    uint32_t err_code = NRF_SUCCESS;

    uint32_t time_ms = 300;

    uint32_t time_ticks;

    nrfx_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG;

    err_code = nrfx_timer_init(&TIMER_LED, &timer_cfg, timer0_handler);
    APP_ERROR_CHECK(err_code);

    time_ticks = nrfx_timer_ms_to_ticks(&TIMER_LED, time_ms);

    nrfx_timer_extended_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

}

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_4);

    nrf_gpio_pin_set(LED_1);
    nrf_gpio_pin_set(LED_4);

    timer_init();

    nrfx_timer_enable(&TIMER_LED);

    while (1)
    {
        __WFI();
    }
}

/** @} */
