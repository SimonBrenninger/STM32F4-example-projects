# STM32F4 SPI BMP280 example

## Description

This example uses STMicroelectronics STM32F411CE Microcontroller on a custom devboard.
SPI1 (at baudrate 115200, 8 data bits, no parity bit, 1 stop bits) configured in polling mode echoes the received data back.

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