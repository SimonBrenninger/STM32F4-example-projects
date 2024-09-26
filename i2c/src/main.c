#include "header.h"

int main(void)
{
	uint32_t ret;
	rcc_config();
	gpio_config();
	usart_config();
	i2c1_config();
	ret = rda_init();
	if (ret != RETURN_SUCCESS)
	{
		usart_transmit_string("failed to initialize rda5807\r\n");
		return 1;
	}

	usart_transmit_string("RDA5807 initialized\r\n");

	rda_set_volume(0x3);
	usart_transmit_string("RDA5807 volume updated\r\n");
	rda_set_frequency(104700);
	usart_transmit_string("RDA5807 frequency updated\r\n");
	//rda_seek();
	// rda_set_volume(0xF);
	/*
	while (1)
	{
		volatile uint32_t i;
		rda_read_status_register(&reg);
		usart_transmit_hex(reg);
		usart_transmit_string("\r\n");
		i = 0;
		while(++i != 0x20000);
	}
	*/

	/*
	ret = i2c1_transmit_byte(0x11, 0x00);
	ret = i2c1_receive_bytes(0x11, bytes, 2);
	if (ret != RETURN_SUCCESS)
	{
		usart_transmit_string("failed to receive byte: ");
		usart_transmit_string(i2c_err_to_name(ret));
		usart_transmit_string("\r\n");
	}
	usart_transmit_string("received_byte: ");
	chip_id = 0x0;
	chip_id |= (bytes[0] << 8) | bytes[1];
	usart_transmit_hex(chip_id);
	usart_transmit_string("\r\n");
	*/

	/*
	ret = i2c1_transmit_byte(0x10, 0xA5);
	if (ret != RETURN_SUCCESS)
	{
		usart_transmit_string("failed to transmit byte: ");
		usart_transmit_string(i2c_err_to_name(ret));
		usart_transmit_string("\r\n");
	}
	*/
	/*
	ret = i2c1_receive_bytes(0x10, bytes, sizeof(bytes));
	if (ret & RETURN_ERROR_BASE)
	{
		usart_transmit_string("failed to receive bytes: ");
		usart_transmit_string(i2c_err_to_name(ret));
		usart_transmit_string("\r\n");
	}

	usart_transmit_string("received: ");
	usart_transmit_hex(ret);
	usart_transmit_string(" bytes from i2c device\r\n");
	*/

	while(1)
	{
		// start I2C communication
	}
}
