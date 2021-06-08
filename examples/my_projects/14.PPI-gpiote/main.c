#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"

#define LED_Pin1 NRF_GPIO_PIN_MAP(0,13)
#define Btn_Pin1 11

static nrf_ppi_channel_t ppi_channel;

void interrupt_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{

}

static void gpiote_pins_init(void)
{
    uint32_t err_code = NRF_SUCCESS;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    // create the configurations for input pin interrupt
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    // initialize the interrupt pin
    err_code = nrf_drv_gpiote_in_init(Btn_Pin1, &in_config, interrupt_pin_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
    err_code = nrf_drv_gpiote_out_init(LED_Pin1, &out_config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_out_task_enable(LED_Pin1);

    nrf_drv_gpiote_in_event_enable(Btn_Pin1, true);
}

static void ppi_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    uint32_t btn_evt_addr;
    uint32_t led_task_addr;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_alloc(&ppi_channel);
    APP_ERROR_CHECK(err_code);

    btn_evt_addr = nrf_drv_gpiote_in_event_addr_get(Btn_Pin1);
    led_task_addr = nrf_drv_gpiote_out_task_addr_get(LED_Pin1);

    err_code = nrf_drv_ppi_channel_assign(ppi_channel, btn_evt_addr, led_task_addr);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_enable(ppi_channel);
    APP_ERROR_CHECK(err_code);
}

int main(void)
{
    
    gpiote_pins_init();
    ppi_init();

    while (true)
    {

    }
}


/** @} */
