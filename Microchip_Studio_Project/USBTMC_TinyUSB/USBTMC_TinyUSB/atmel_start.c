#include <atmel_start.h>
#include "atmel_start_pins.h"

#include "clock_defs.h"
#include "clock_init.h"
#include "hal/include/hal_gpio.h"
#include "hal/include/hal_init.h"
#include "hri/hri_nvmctrl_d21.h"

#include "hpl/gclk/hpl_gclk_base.h"
#include "hpl_pm_config.h"
#include "hpl/pm/hpl_pm_base.h"

/**
 * Initializes MCU, drivers and middleware in the project
 **/
void atmel_start_init(void)
{
	//system_init();
	clock_init();
	  // USB Pin Init
	  gpio_set_pin_direction(PIN_PA24, GPIO_DIRECTION_OUT);
	  gpio_set_pin_level(PIN_PA24, false);
	  gpio_set_pin_pull_mode(PIN_PA24, GPIO_PULL_OFF);
	  gpio_set_pin_direction(PIN_PA25, GPIO_DIRECTION_OUT);
	  gpio_set_pin_level(PIN_PA25, false);
	  gpio_set_pin_pull_mode(PIN_PA25, GPIO_PULL_OFF);

	  gpio_set_pin_function(PIN_PA24, PINMUX_PA24G_USB_DM);
	  gpio_set_pin_function(PIN_PA25, PINMUX_PA25G_USB_DP);
	  
	  // clock output to pa10
	  //gpio_set_pin_direction(GCLK_OUT,GPIO_DIRECTION_OUT);
	  //gpio_set_pin_level(GCLK_OUT,false);
	  //gpio_set_pin_pull_mode(GCLK_OUT, GPIO_PULL_OFF);
	  //gpio_set_pin_function(GCLK_OUT,PINMUX_PA10H_GCLK_IO4);
	  
	  //led
	  //gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);
	  //gpio_set_pin_level(LED,false);
	  
	    // Output 500hz PWM on D12 (PA19 - TCC0 WO[3]) so we can validate the GCLK0 clock speed with a Saleae.
	    _pm_enable_bus_clock(PM_BUS_APBC, TCC0);
	    TCC0->PER.bit.PER = 48000000 / 1000;
	    TCC0->CC[3].bit.CC = 48000000 / 2000;
	    TCC0->CTRLA.bit.ENABLE = true;

	    gpio_set_pin_function(PIN_PA19, PINMUX_PA19F_TCC0_WO3);
	    _gclk_enable_channel(TCC0_GCLK_ID, GCLK_CLKCTRL_GEN_GCLK0_Val);
}
