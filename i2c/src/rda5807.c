#include <string.h>
#include "header.h"
#include "rda5807.h"


struct rda_state_t
{
	uint16_t ctrl_02;
	uint16_t ctrl_03;
	uint16_t ctrl_04;
	uint16_t ctrl_05;
	uint16_t ctrl_06;
	uint16_t ctrl_07;
	uint16_t ctrl_08;
	uint16_t ctrl_0A;
	uint16_t ctrl_0B;
	uint16_t ctrl_0C;
	uint16_t ctrl_0D;
	uint16_t ctrl_0E;
	uint16_t ctrl_0F;
};

static const struct rda_state_t rda_reset_state = {
	.ctrl_03 = (0x13f << RDA_REG_CTRL_03_CHANNEL_Pos),
	.ctrl_04 = RDA_REG_CTRL_04_RDS_FIFO_CLEAR,
	.ctrl_05 = (0x8 << RDA_REG_CTRL_05_SEEK_SNR_Pos) | (0x2 << RDA_REG_CTRL_05_LNA_SELECT_Pos) |
		(0xB << RDA_REG_CTRL_05_VOLUME_Pos),
	/*
	.ctrl_05 = RDA_REG_CTRL_05_INT_MODE | (0x8 << RDA_REG_CTRL_05_SEEK_SNR_Pos) |
		(0xB << RDA_REG_CTRL_05_VOLUME_Pos),
	*/
	.ctrl_07 = (0x10 << RDA_REG_CTRL_07_THESHHOLD_SOFT_BLEND_Pos) | 
		RDA_REG_CTRL_07_65M_50M_MODE | RDA_REG_CTRL_07_SOFT_BLEND_ENABLE,
	.ctrl_0A = RDA_REG_CTRL_0A_STEREO_ENABLED,
	.ctrl_0C = 0x5803,
	.ctrl_0D = 0x5804,
	.ctrl_0E = 0x5808,
	.ctrl_0F = 0x5804,
};

static struct rda_state_t rda_state;

static uint32_t verify_chip_id(void)
{
	uint32_t ret;
	uint8_t buf[2];
	uint16_t chip_id;
	ret = i2c1_transmit_byte(RDA5807_ADDRESS, RDA_REG_CHIP_ID);
	if (ret != RETURN_SUCCESS)
	{
		return RETURN_ERROR_RDA_INVAL_CHIP_ID;
	}
	ret = i2c1_receive_bytes(RDA5807_ADDRESS, buf, sizeof(buf));
	if (ret & RETURN_ERROR_BASE)
	{
		return RETURN_ERROR_RDA_INVAL_CHIP_ID;
	}
	chip_id = (buf[0] << 8) | buf[1];
	if (chip_id != RDA5807_CHIP_ID)
	{
		return RETURN_ERROR_RDA_INVAL_CHIP_ID;
	}
	return RETURN_SUCCESS;
}

static uint32_t set_register(uint8_t reg, uint16_t value)
{
	uint32_t ret;
	uint8_t buf[3];
	buf[0] = reg;
	buf[1] = value >> 8;
	buf[2] = value;
	ret = i2c1_transmit_bytes(RDA5807_ADDRESS, buf, sizeof(buf));
	return ret;
}

static uint32_t get_register(uint8_t reg, uint16_t *value)
{
	uint32_t ret;
	uint8_t buf[2];
	ret = i2c1_transmit_byte(RDA5807_ADDRESS, reg);
	if (ret != RETURN_SUCCESS)
	{
		return RETURN_ERROR_RDA_REGISTER_GET;
	}
	ret = i2c1_receive_bytes(RDA5807_ADDRESS, buf, sizeof(buf));
	if (ret & RETURN_ERROR_BASE)
	{
		return ret;
	}
	*value = (buf[0] << 8) | buf[1];
	return RETURN_SUCCESS;
}

static uint32_t enable_device(void)
{
	uint32_t ret;
	rda_state.ctrl_02 |= RDA_REG_CTRL_02_AUDIO_ENABLE | RDA_REG_CTRL_02_MUTE_DISABLE | 
		RDA_REG_CTRL_02_POWER_ENABLE;
	rda_state.ctrl_02 |= RDA_REG_CTRL_02_MONO_ENABLE | RDA_REG_CTRL_02_BASS_BOOST;
	ret = set_register(RDA_REG_CTRL_02, rda_state.ctrl_02);
	if (ret != RETURN_SUCCESS)
	{
		return ret;
	}
	return RETURN_SUCCESS;
}

static uint32_t reset_device(void)
{
	uint32_t ret;
	rda_state.ctrl_02 |= RDA_REG_CTRL_02_SOFT_RESET | RDA_REG_CTRL_02_POWER_ENABLE;
	ret = set_register(RDA_REG_CTRL_02, rda_state.ctrl_02);
	if (ret != RETURN_SUCCESS)
	{
		return ret;
	}
	memcpy(&rda_state, &rda_reset_state, sizeof(struct rda_state_t));
	return RETURN_SUCCESS;
}

uint32_t rda_init(void)
{
	uint32_t ret;
	ret = verify_chip_id();
	memcpy(&rda_state, &rda_reset_state, sizeof(struct rda_state_t));
	if (ret != RETURN_SUCCESS)
	{
		return ret;
	}
	//ret = reset_device();
	ret = enable_device();
	return ret;
}

static uint32_t determine_band_start_frequency(void)
{
	uint16_t band_select = rda_state.ctrl_03 & RDA_REG_CTRL_03_BAND_SELECT_Msk;
	if (band_select == RDA_REG_CTRL_03_BAND_SELECT_EU_US)
	{
		return 87000; // 87MHz
	}
	if ((band_select == RDA_REG_CTRL_03_BAND_SELECT_JAPAN) ||
		(band_select == RDA_REG_CTRL_03_BAND_SELECT_WW))
	{
		return 76000; // 76MHz
	}
	if (band_select == RDA_REG_CTRL_03_BAND_SELECT_EAST_EU)
	{
		return 65000; // 65MHz
	}
	return 0;
}

static uint8_t determine_channel_spacing(void)
{
	uint16_t channel_spacing = rda_state.ctrl_03 & RDA_REG_CTRL_03_CHANNEL_SPACING_Msk;
	if (channel_spacing == (0x0 << RDA_REG_CTRL_03_CHANNEL_SPACING_Pos))
	{
		return 100; // 100kHz
	}
	if (channel_spacing == (0x1 << RDA_REG_CTRL_03_CHANNEL_SPACING_Pos))
	{
		return 200; // 200kHz
	}
	if (channel_spacing == (0x2 << RDA_REG_CTRL_03_CHANNEL_SPACING_Pos))
	{
		return 50; // 50kHz
	}
	if (channel_spacing == (0x3 << RDA_REG_CTRL_03_CHANNEL_SPACING_Pos))
	{
		return 25; // 25kHz
	}
	return 0;
}

static uint32_t wait_until_tune_seek_complete(void)
{
	uint32_t ret;
	uint16_t status_reg = 0x0;
	while (!(status_reg & RDA_REG_CTRL_0A_SEEK_TUNE_COMPLETE))
	{
		ret = rda_read_status_register(&status_reg);
		if (ret != RETURN_SUCCESS)
		{
			return ret;
		}
		if (status_reg & RDA_REG_CTRL_0A_SEEK_TUNE_FAILURE)
		{
			return RETURN_ERROR_RDA_SEEK_TUNE_FAILED;
		}
	}
	return RETURN_SUCCESS;
}

uint32_t rda_set_frequency(uint32_t freq_khz)
{
	uint32_t ret;
	uint16_t channel;
	uint32_t band_start_freq_khz = determine_band_start_frequency();
	uint8_t channel_spacing_khz = determine_channel_spacing();
	channel = (freq_khz - band_start_freq_khz) / channel_spacing_khz;
	channel &= (RDA_REG_CTRL_03_CHANNEL_Msk >> RDA_REG_CTRL_03_CHANNEL_Pos);
	rda_state.ctrl_03 &= ~RDA_REG_CTRL_03_CHANNEL_Msk;
	rda_state.ctrl_03 |= (channel << RDA_REG_CTRL_03_CHANNEL_Pos) | RDA_REG_CTRL_03_TUNE_ENABLE;
	ret = set_register(RDA_REG_CTRL_03, rda_state.ctrl_03);
	if (ret != RETURN_SUCCESS)
	{
		return ret;
	}
	ret = wait_until_tune_seek_complete();
	return RETURN_SUCCESS;
}

uint32_t rda_seek(void)
{
	uint32_t ret;
	uint16_t reg;
	ret = set_register(RDA_REG_CTRL_02, rda_state.ctrl_02 | RDA_REG_CTRL_02_SEEK_ENABLE);
	get_register(RDA_REG_CTRL_0A, &reg);
	return ret;
}

uint32_t rda_set_volume(uint8_t volume)
{
	uint32_t ret;
	volume &= 0x0F;
	rda_state.ctrl_05 &= ~RDA_REG_CTRL_05_VOLUME_Msk;
	rda_state.ctrl_05 |= (volume << RDA_REG_CTRL_05_VOLUME_Pos);
	ret = set_register(RDA_REG_CTRL_05, rda_state.ctrl_05);
	return ret;
}

uint32_t rda_read_status_register(uint16_t *reg)
{
	uint32_t ret;
	ret = get_register(RDA_REG_CTRL_0A, reg);
	return ret;
}
