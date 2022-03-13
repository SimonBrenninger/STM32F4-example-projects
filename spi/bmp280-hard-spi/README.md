# STM32F4 SPI BMP280 example

## Description

This example uses STMicroelectronics STM32F411CE Microcontroller on a custom devboard.
A Hardware-SPI implementation is used to communicate with the BMP280 to read the temperature and pressure.
USART1 (baudrate 115200) is used to print out the received chip-id register.

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