#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_error.h"
#include "nrf_drv_clock.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

void clock_initialize(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

void bsp_event_handler(bsp_event_t evt)
{
    uint32_t err_code;

    switch(evt)
    {
        case BSP_EVENT_KEY_0:
            bsp_board_led_on(1);
            NRF_LOG_INFO("Led turned on!");
            break;

        case BSP_EVENT_KEY_1:
            bsp_board_led_off(1);
            NRF_LOG_INFO("Led turned off!");
            break;

        case BSP_EVENT_KEY_2:
            err_code =bsp_indication_set(BSP_INDICATE_FATAL_ERROR);
            APP_ERROR_CHECK(err_code);
            NRF_LOG_INFO("BSP_INDICATE_FATAL_ERROR");
            break;

        case BSP_EVENT_KEY_3:
            err_code =bsp_indication_set(BSP_INDICATE_IDLE);
            APP_ERROR_CHECK(err_code);
            NRF_LOG_INFO("BSP_INDICATE_IDLE");
            break;

        default:
            return;
    }
}

void bsp_configure(void)
{
    uint32_t err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_event_handler);
    APP_ERROR_CHECK(err_code);
}

int main(void)
{
    clock_initialize();

    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("Application code started!!!");

    NRF_LOG_FLUSH();

    while (true)
    {
        // Do nothing.
    }
}
/** @} */
