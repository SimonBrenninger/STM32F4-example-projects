# STM32F4 Soft-I2C example

## Description

This example uses STMicroelectronics STM32F411CE Microcontroller on a custom devboard.
A Software-I2C implementation is used to communicate with the RDA5807.
USART1 (baudrate 115200) is used to print out CHIP_ID register.

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

## Output


## Troubleshooting

When encountering an error during flashing make sure your USB device port on your machine matches the port in the Makefile.
