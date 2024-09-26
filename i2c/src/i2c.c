#include "header.h"

/* RDA5807 Interface Timing Characteristics
 * f_max = 400kHz
 * T_rise_scl_max = 300ns
 * 
 * adress: (0010000b)
 */

/*
 * periph input clock: CR2
 * clock control register
 * rise time register
 * enable periph: CR1
 * start condition with START bit in CR1
 */

void i2c1_config(void)
{
	// set periph input clock (APB1 = 25MHz) into CR2
	I2C1->CR2 |= (25 << I2C_CR2_FREQ_Pos);
	// set SCL clock frequency to 100kHz (T_scl=0.01ms = 10us)
	// T_scl/2 = CCR * T_pclk1
	// 10us / 2 = CCR * (1 / 25MHz)
	// CCR = 5us * 25MHz = 125
	// CCR = 125
	I2C1->CCR |= (122 << I2C_CCR_CCR_Pos); // T_high = T_low = 4.88 us -> 120ns rise time
					       // set rise time
					       // t_rise_scl_max / T_pclk1 + 1
					       // 300ns / (1 / 25MHz) + 1
					       // 300ns * 25MHz + 1 = 8.5 --> 8
	I2C1->TRISE = 26;

	// enable I2C1 peripheral
	I2C1->CR1 |= I2C_CR1_PE;
}

static void i2c1_generate_start_condition(void)
{
	// send start condition
	I2C1->CR1 |= I2C_CR1_START;
	// wait until SB bit from SR1 is set
	while (!(I2C1->SR1 & I2C_SR1_SB));
}

static void i2c1_generate_stop_condition(void)
{
	// send stop condition
	I2C1->CR1 |= I2C_CR1_STOP;
}

static int32_t i2c1_transmit_address(uint8_t addr)
{
	uint32_t status_register = 0x00;
	I2C1->DR = addr;
	status_register = I2C1->SR1;
	while (!(status_register & I2C_SR1_ADDR))
	{
		if (status_register & I2C_SR1_AF)
		{
			return RETURN_ERROR_I2C_NACK;
		}
		if (status_register & I2C_SR1_ARLO)
		{
			return RETURN_ERROR_I2C_ARLO;
		}
		if (status_register & I2C_SR1_BERR)
		{
			return RETURN_ERROR_I2C_BERR;
		}
		status_register = I2C1->SR1;
	}
	if (!(I2C1->SR2 & I2C_SR2_MSL))
	{
		return RETURN_ERROR_I2C_MSL;
	}
	return RETURN_SUCCESS;
}

int32_t i2c1_transmit_byte(uint8_t addr, uint8_t byte)
{
	int32_t ret;
	i2c1_generate_start_condition();
	ret = i2c1_transmit_address((addr << 1) | 0b0);
	if (ret != RETURN_SUCCESS)
	{
		i2c1_generate_stop_condition();
		return ret;
	}
	I2C1->DR = byte;
	while (!(I2C1->SR1 & I2C_SR1_BTF));
	i2c1_generate_stop_condition();
	return RETURN_SUCCESS;
}

int32_t i2c1_receive_byte(uint8_t addr, uint8_t *byte)
{
	uint32_t ret;
	i2c1_generate_start_condition();
	I2C1->CR1 &= ~I2C_CR1_ACK;
	ret = i2c1_transmit_address((addr << 1) | 0b1);
	i2c1_generate_stop_condition();
	if (ret != RETURN_SUCCESS)
	{
		return ret;
	}
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	*byte = I2C1->DR;
	return RETURN_SUCCESS;
}

int32_t i2c1_transmit_bytes(uint8_t addr, uint8_t *buf, uint32_t len)
{
	uint32_t ret;
	uint32_t bytes_written = 0;
	if (len == 0)
	{
		return RETURN_SUCCESS;
	}
	i2c1_generate_start_condition();
	ret = i2c1_transmit_address((addr << 1) | 0b0);
	if (ret != RETURN_SUCCESS)
	{
		i2c1_generate_stop_condition();
		return ret;
	}
	while (bytes_written < len)
	{
		// send address
		I2C1->DR = buf[bytes_written];
		bytes_written++;
		while (!(I2C1->SR1 & I2C_SR1_TXE));
	}
	while (!(I2C1->SR1 & I2C_SR1_BTF));
	i2c1_generate_stop_condition();
	return RETURN_SUCCESS;
}

int32_t i2c1_receive_bytes(uint8_t addr, uint8_t *buf, uint32_t len)
{
	uint32_t ret;
	uint32_t bytes_read = 0;
	if (len == 0)
	{
		return RETURN_SUCCESS;
	}
	i2c1_generate_start_condition();
	if (len == 1)
	{
		// disable ACK generation when only one byte is being received
		I2C1->CR1 &= ~I2C_CR1_ACK;
	}
	else
	{
		I2C1->CR1 |= I2C_CR1_ACK;
	}
	ret = i2c1_transmit_address((addr << 1) | 0b1);
	if (len == 1)
	{
		// generate stop bit when only one byte is being received
		i2c1_generate_stop_condition();
	}
	if (ret != RETURN_SUCCESS)
	{
		i2c1_generate_stop_condition();
		return ret;
	}
	while (bytes_read < len)
	{
		while (!(I2C1->SR1 & I2C_SR1_RXNE));
		buf[bytes_read] = I2C1->DR;
		bytes_read++;
		if (bytes_read == len-1)
		{
			I2C1->CR1 &= ~I2C_CR1_ACK;
			i2c1_generate_stop_condition();
		}
	}
	return bytes_read;
}

const char *i2c_err_to_name(uint32_t err)
{
	if (err == RETURN_ERROR_I2C_NACK)
	{
		return "I2C no acknowledge";
	}
	if (err == RETURN_ERROR_I2C_ARLO)
	{
		return "I2C arbitration lost";
	}
	if (err == RETURN_ERROR_I2C_BERR)
	{
		return "I2C bus error";
	}
	if (err == RETURN_ERROR_I2C_MSL)
	{
		return "I2C invalid mode";
	}
	return "unknown error";
}
