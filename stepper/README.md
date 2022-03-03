# STM32F4 stepper motor example

## Description

This example uses STMicroelectronics STM32F411CE Microcontroller on a custom devboard.
The stepper motor is attached at the pins PA0, PA1, PA2, PA3.

## Usage

Build the project using make:
```console
make build
```

and download the image to your target over USB:
```console
make flash-usb
```
or over USART using a USB to UART bridge:
```console
make flash-usart
```

## Troubleshooting

When encountering an error during flashing make sure your USB device port on your machine matches the port in the Makefile.