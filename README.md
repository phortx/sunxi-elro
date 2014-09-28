sunxi-elro
===========

This is a fork of [Elrosend-CT from klagges](https://github.com/klagges/Elrosend-CT) to provide additional features, english documentation and improved code formatting.

sunxi-elro provides a way to switch Elro Remote Sockets on the Cubietruck or other Sunxi based boards.

It requires the (gpio_lib.h)[https://github.com/youyudehexie/node-cubieboard-gpio/blob/master/lib/gpio_lib.h]


## Compile

gcc gpio_lib.h -c
gcc send.c -c
gcc gpio_lib.o send.o -o send


## Usage

```bash
./send gpio_port code socket state
```

Where ...

- `gpio_port` is the GPIO Port in Uppercase like `PB2` or `PC21`
- `code` is the home code of the socket like `10100`
- `socket` is the number of the socket: `1` is `A`, `2` is `B` and so on
- `state` is the state to switch in: `1` for on, `0` for off

Example: 

```bash
./send PC21 10100 2 1
```
