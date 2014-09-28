%module gpio_lib
%{
  #include "gpio_lib.h"
%}

extern unsigned int SUNXI_PIO_BASE;

extern struct sunxi_gpio;
extern struct sunxi_gpio_int;
extern struct sunxi_gpio_reg;

extern enum sunxi_gpio_number;

extern int sunxi_gpio_input(unsigned int pin);
extern int sunxi_gpio_init(void);
extern int sunxi_gpio_set_cfgpin(unsigned int pin, unsigned int val);
extern int sunxi_gpio_get_cfgpin(unsigned int pin);
extern int sunxi_gpio_output(unsigned int pin, unsigned int val);
extern void sunxi_gpio_cleanup(void);

