# STM32F4 manual blink

## Description

This example uses STMicroelectronics STM32F411CE Microcontroller on a custom devboard.
The onboard LED on Pin PC13 gets toggled when pressing the button attached on pin PA0.

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