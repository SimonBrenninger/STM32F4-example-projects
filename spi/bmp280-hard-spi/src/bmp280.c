#include "header.h"

void SPI1_BMP280_start(void)
{
    // begin SPI1 communication by setting CS low
    GPIOA->ODR &= ~SPI1_CS;
}

void SPI1_BMP280_end(void)
{
    // end SPI1 communication by setting CS high
    GPIOA->ODR |= SPI1_CS;
}

uint8_t SPI1_BMP280_read_byte(uint8_t addr)
{
    // begin SPI1 communication
    SPI1_BMP280_start();
    addr = SPI1_read_byte(addr);
    // end SPI1 BMP280 communication
    SPI1_BMP280_end();
    return addr;
}

uint8_t *SPI1_BMP280_read_bytes(uint8_t start_addr, uint8_t num_bytes)
{
    uint8_t *bytes_ptr = NULL;
    // begin SPI1 communication
    SPI1_BMP280_start();
    bytes_ptr = SPI1_read_bytes(start_addr, num_bytes);
    // end SPI1 BMP280 communication
    SPI1_BMP280_end();
    return bytes_ptr;
}
void SPI1_BMP280_write_byte(uint8_t addr, uint8_t data)
{
    // for writing to BMP280 register set MSB of addr low
    addr &= ~(1 << 7);
    // begin SPI1 communication
    SPI1_BMP280_start();
    SPI1_write_byte(addr, data);
    // end SPI1 BMP280 communication
    SPI1_BMP280_end();
}

void SPI1_BMP280_write_bytes(uint8_t start_addr, uint8_t *data, uint8_t num_bytes)
{
    start_addr &= ~(1 << 7);
    // begin SPI1 communication
    SPI1_BMP280_start();
    SPI1_write_bytes(start_addr, data, num_bytes);
    // end SPI1 communication
    SPI1_BMP280_end();
}

uint8_t SPI1_BMP280_get_id(void)
{
    uint8_t chip_id;

    // get result from BMP280 sensor
    chip_id = SPI1_BMP280_read_byte(BMP280_ID);

    // return value
    return chip_id;
}

void SPI1_BMP280_config(bmp280_conf_t *bmp280_conf_ptr)
{
    // check that BMP280 is ready
    while(SPI1_BMP280_is_busy());

    // write to ctrl_meas and config register
    // write to ctrl_meas register
    SPI1_BMP280_write_byte(BMP280_CTRL_MEAS, ((bmp280_conf_ptr->osrs_temp << BMP280_OSRS_T_Pos) |
                                              (bmp280_conf_ptr->osrs_press << BMP280_OSRS_P_Pos) |
                                              (bmp280_conf_ptr->mode << BMP280_MODE_Pos)));
    // write temp to BMP280
    SPI1_BMP280_write_byte(BMP280_CONFIG, ((bmp280_conf_ptr->t_sb << BMP280_T_SB_Pos) |
                                           (bmp280_conf_ptr->filter << BMP280_FILTER_Pos) |
                                           (bmp280_conf_ptr->spi3w_en << BMP280_SPI3W_EN_Pos)));
}

void SPI1_BMP280_reset(void)
{
    // reset BMP280
    SPI1_BMP280_write_byte(BMP280_RESET, BMP280_RESET_VAL);
    // wait until BMP280 is ready
    while(SPI1_BMP280_is_busy());
}

uint8_t SPI1_BMP280_is_busy(void)
{
    uint8_t temp = SPI1_BMP280_read_byte(BMP280_STATUS);
    // sensor is busy if measuring or im_update is set
    return ((temp & BMP280_MEASURING) || 
            (temp & BMP280_IM_UPDATE));
}
void SPI1_BMP280_get_raw(bmp280_raw_t *bmp280_raw_ptr)
{
    uint8_t *tmp_ptr = NULL;
    bmp280_raw_ptr->press = 0;
    bmp280_raw_ptr->temp = 0;

    // get raw temperature and pressure using burst readout (read from 0xF7 to 0xFC at once)
    // receive 6 bytes (temp and press each msb, lsb & xlsb) starting with 0xF7 (MSB)
    tmp_ptr = SPI1_BMP280_read_bytes(BMP280_PRESS_BASE, 6);

    // concatenate temp-pointer content (uint8_t) into one single temperature variable (uint32_t)
    // copy msb, lsb and xlsb to temp variable
    bmp280_raw_ptr->press  = ((tmp_ptr[0] << 12) | (tmp_ptr[1] << 4) | (tmp_ptr[2] >> 4));
    bmp280_raw_ptr->temp = ((tmp_ptr[3] << 12) | (tmp_ptr[4] << 4) | (tmp_ptr[5] >> 4));

    // free memory allocated to temp_ptr
    free(tmp_ptr);
    tmp_ptr = NULL;
}

int32_t BMP280_compute_temp(bmp280_calib_t *calib_ptr, bmp280_raw_t *raw_ptr)
{
    int32_t var1, var2, calib_temp;

    var1 = ((((raw_ptr->temp >> 3) - (((int32_t)calib_ptr->dig_t1) << 1))) * ((int32_t)calib_ptr->dig_t2)) >> 11;
    var2 = (((((raw_ptr->temp >> 4) - ((int32_t)calib_ptr->dig_t1)) * ((raw_ptr->temp >> 4) - ((int32_t)calib_ptr->dig_t1))) >> 12) *
        ((int32_t)calib_ptr->dig_t3)) >> 14;
    calib_ptr->t_fine = var1 + var2;
    calib_temp = (calib_ptr->t_fine * 5 + 128) >> 8;
    return calib_temp;
}

uint32_t BMP280_compute_press(bmp280_calib_t *calib_ptr, bmp280_raw_t *raw_ptr)
{
    int64_t var1, var2, calib_press;
    
    var1 = ((int64_t)calib_ptr->t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)calib_ptr->dig_p6;
    var2 = var2 + ((var1 * (int64_t)calib_ptr->dig_p5) << 17);
    var2 = var2 + (((int64_t)calib_ptr->dig_p4) << 35);
    var1 = ((var1 * var1 * (int64_t)calib_ptr->dig_p3) >> 8) + ((var1 * (int64_t)calib_ptr->dig_p2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)calib_ptr->dig_p1) >> 33;
    if (var1 == 0)
    {
    return 0; // avoid exception caused by division by zero
    }
    calib_press = 1048576 - raw_ptr->press;
    calib_press = (((calib_press << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)calib_ptr->dig_p9) * (calib_press >> 13) * (calib_press >> 13)) >> 25;
    var2 = (((int64_t)calib_ptr->dig_p8) * calib_press) >> 19;
    calib_press = ((calib_press + var1 + var2) >> 8) + (((int64_t)calib_ptr->dig_p7) << 4);
    return (uint32_t)calib_press;
}

void SPI1_BMP280_get_calib(bmp280_conf_t *bmp280_conf_ptr, bmp280_calib_t *bmp280_calib_ptr)
{
    uint8_t *calib_ptr = NULL;
    // read register content @ address 0x88 -> 0x9F (24 byte)
    calib_ptr = SPI1_BMP280_read_bytes(BMP280_CALIB_BASE, BMP280_CALIB_SIZE);

    // copy MSB & LSB calibration data from calib_ptr into calibration structure
    bmp280_calib_ptr->dig_t1 = ((calib_ptr[BMP280_DIG_T1_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_T1_LSB_Pos]);
    bmp280_calib_ptr->dig_t2 = ((calib_ptr[BMP280_DIG_T2_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_T2_LSB_Pos]);
    bmp280_calib_ptr->dig_t3 = ((calib_ptr[BMP280_DIG_T3_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_T3_LSB_Pos]);
    bmp280_calib_ptr->dig_p1 = ((calib_ptr[BMP280_DIG_P1_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P1_LSB_Pos]);
    bmp280_calib_ptr->dig_p2 = ((calib_ptr[BMP280_DIG_P2_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P2_LSB_Pos]);
    bmp280_calib_ptr->dig_p3 = ((calib_ptr[BMP280_DIG_P3_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P3_LSB_Pos]);
    bmp280_calib_ptr->dig_p4 = ((calib_ptr[BMP280_DIG_P4_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P4_LSB_Pos]);
    bmp280_calib_ptr->dig_p5 = ((calib_ptr[BMP280_DIG_P5_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P5_LSB_Pos]);
    bmp280_calib_ptr->dig_p6 = ((calib_ptr[BMP280_DIG_P6_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P6_LSB_Pos]);
    bmp280_calib_ptr->dig_p7 = ((calib_ptr[BMP280_DIG_P7_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P7_LSB_Pos]);
    bmp280_calib_ptr->dig_p8 = ((calib_ptr[BMP280_DIG_P8_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P8_LSB_Pos]);
    bmp280_calib_ptr->dig_p9 = ((calib_ptr[BMP280_DIG_P9_MSB_Pos] << 8 ) | calib_ptr[BMP280_DIG_P9_LSB_Pos]);
    
    free(calib_ptr);
    calib_ptr = NULL;
}