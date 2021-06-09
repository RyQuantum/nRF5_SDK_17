#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"

#define LED_Pin1 NRF_GPIO_PIN_MAP(0, 13)
#define LED_INTERVAL APP_TIMER_TICKS(100)

APP_TIMER_DEF(m_app_timer_id);

static void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

static void app_timer_handler(void * p_context)
{
    nrf_gpio_pin_toggle(LED_Pin1);
}

static void timers_init(void)
{
    ret_code_t err_code;

    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_app_timer_id, APP_TIMER_MODE_REPEATED, app_timer_handler);
    APP_ERROR_CHECK(err_code);
    
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    
    nrf_gpio_cfg_output(LED_Pin1);
    lfclk_config();
    timers_init();
    uint32_t err_code = app_timer_start(m_app_timer_id, LED_INTERVAL, NULL);

    while (true)
    {
        // Do nothing.
    }
}
/** @} */
