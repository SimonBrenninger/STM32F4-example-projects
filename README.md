# STM32F4 example projects

## Description

This repository includes various example projects for the STM32F411xC/E peripherals.

## Usage

Navigate to the desired project:
```console
cd foo/bar/
```

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

