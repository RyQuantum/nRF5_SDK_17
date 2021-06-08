#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"

//#define LED 17
//#define Btn 13

#define LED_1          NRF_GPIO_PIN_MAP(0,13)
#define LED_2          NRF_GPIO_PIN_MAP(0,14)
#define LED_3          NRF_GPIO_PIN_MAP(0,15)
#define LED_4          NRF_GPIO_PIN_MAP(0,16)            
#define BUTTON_1       11
#define BUTTON_2       12
#define BUTTON_3       24
#define BUTTON_4       25

void input_pin_handle(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_gpio_pin_toggle(LED_1);
}

void gpio_init()
{
    ret_code_t err_code;
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_pin_set(LED_1);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(BUTTON_1, &in_config, input_pin_handle);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_event_enable(BUTTON_1, true);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    gpio_init();
    //nrf_gpio_cfg_output(LED_1);
    //nrf_gpio_cfg_output(LED_2); 
    //nrf_gpio_cfg_output(LED_3);
    //nrf_gpio_cfg_output(LED_4);   

    while (true)
    {
      //nrf_gpio_pin_clear(LED_1);
      //nrf_gpio_pin_clear(LED_2);
      //nrf_gpio_pin_clear(LED_3);
      //nrf_gpio_pin_clear(LED_4);
    }
}


/** @} */
