#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>

extern "C" {
#include "gpio_lib.h"
}

int long_signal  = 1025;
int short_signal = 375;
int pin;
char* systemCode;
int unitCode;
int command;


int get_pin(char* pin_arg)
{
    std::string pin_str(pin_arg);
    // TODO convert to uppercase
    char pin_char = pin_arg[0];
    int pin_number = atoi(pin_str.substr(1).c_str());

    if (pin_char == 'P')
    {
        pin_char = pin_arg[1];
        pin_number = atoi(pin_str.substr(2).c_str());
    }

    switch (pin_char) {
        case 'A':
            return SUNXI_GPA(pin_number);

        case 'B':
            return SUNXI_GPB(pin_number);

        case 'C':
            return SUNXI_GPC(pin_number);

        case 'D':
            return SUNXI_GPD(pin_number);

        case 'E':
            return SUNXI_GPE(pin_number);

        case 'F':
            return SUNXI_GPF(pin_number);

        case 'G':
            return SUNXI_GPG(pin_number);

        case 'H':
            return SUNXI_GPH(pin_number);

        case 'I':
            return SUNXI_GPI(pin_number);
    }
}


void set_output()
{
    sunxi_gpio_set_cfgpin(pin, OUTPUT);
}

void sequence_up()
{
    sunxi_gpio_output(pin, HIGH);
    usleep(short_signal);
    sunxi_gpio_output(pin, LOW);
    usleep(long_signal);
    sunxi_gpio_output(pin, HIGH);
    usleep(short_signal);
    sunxi_gpio_output(pin, LOW);
    usleep(long_signal);
    return;
}

void sequence_down()
{
    sunxi_gpio_output(pin, HIGH);
    usleep(short_signal);
    sunxi_gpio_output(pin, LOW);
    usleep(long_signal);
    sunxi_gpio_output(pin, HIGH);
    usleep(long_signal);
    sunxi_gpio_output(pin, LOW);
    usleep(short_signal);
    return;
}

void sync_sequence()
{
    sunxi_gpio_output(pin, HIGH);
    usleep(short_signal);
    sunxi_gpio_output(pin, LOW);
    usleep(11625);
}



int main(int argc, char *argv[])
{
    if (SETUP_OK != sunxi_gpio_init())
    {
        printf("Error while initializing the gpio!\n");
        return -1;
    }

    pin = get_pin(argv[1]);
    systemCode = argv[2];
    unitCode = atoi(argv[3]);
    command  = atoi(argv[4]);

    set_output();

    int i, j;

    for(i = 0; i < 10; i++) {
        sync_sequence();

        for(char* c = systemCode; *c; ++c)
        {
            if (*c == '1')
            {
                sequence_up();
            }
            else
            {
                sequence_down();
            }
        }

        switch (unitCode)
        {
            case 1:
                sequence_up();
                sequence_down();
                sequence_down();
                sequence_down();
                sequence_down();
                break;
            case 2:
                sequence_down();
                sequence_up();
                sequence_down();
                sequence_down();
                sequence_down();
                break;

            case 3:
                sequence_down();
                sequence_down();
                sequence_up();
                sequence_down();
                sequence_down();
                break;

            case 4:
                sequence_down();
                sequence_down();
                sequence_down();
                sequence_up();
                sequence_down();
                break;

            case 5:
                sequence_down();
                sequence_down();
                sequence_down();
                sequence_down();
                sequence_up();
                break;
        }

        switch (command)
        {
            case 1:
                sequence_down();
                sequence_down();
                break;

            case 0:
                sequence_down();
                sequence_up();
                break;
        }

    }

    void sunxi_gpio_cleanup();

    return 0;
}
