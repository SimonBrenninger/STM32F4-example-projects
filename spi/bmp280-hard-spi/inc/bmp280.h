#ifndef BMB280_H_INCLUDED
#define BMP280_H_INCLUDED

// BMP280 specific registers
#define BMP280_BASE                     (0x88)
#define BMP280_CALIB_BASE               BMP280_BASE                 /* 0x88 */
#define BMP280_PRESS_BASE               (0xF7)                      /* 0xF7 */
#define BMP280_TEMP_BASE                (0xFA)                      /* 0xFA */

#define BMP280_CALIB(a)                 (BMP280_CALIB_BASE + a)     /* 0x88 + a */
#define BMP280_ID                       (0xD0)                      /* 0xD0 */
#define BMP280_RESET                    (0xE0)                      /* 0xE0 */
#define BMP280_STATUS                   (0xF3)                      /* 0xF3 */
#define BMP280_CTRL_MEAS                (0xF4)                      /* 0xF4 */
#define BMP280_CONFIG                   (0xF5)                      /* 0xF5 */
#define BMP280_PRESS_MSB                (0xF7)                      /* 0xF7 */
#define BMP280_PRESS_LSB                (0xF8)                      /* 0xF8 */
#define BMP280_PRESS_XLSB               (0xF9)                      /* 0xF9 */
#define BMP280_TEMP_MSB                 (0xFA)                      /* 0xFA */
#define BMP280_TEMP_LSB                 (0xFB)                      /* 0xFB */
#define BMP280_TEMP_XLSB                (0xFC)                      /* 0xFC */

// BMP280 bit definitions

// BMP280_CALIB bit definitions
#define BMP280_DIG_T1_LSB               BMP280_CALIB(0)
#define BMP280_DIG_T1_MSB               BMP280_CALIB(1)
#define BMP280_DIG_T2_LSB               BMP280_CALIB(2)
#define BMP280_DIG_T2_MSB               BMP280_CALIB(3)
#define BMP280_DIG_T3_LSB               BMP280_CALIB(4)
#define BMP280_DIG_T3_MSB               BMP280_CALIB(5)
#define BMP280_DIG_P1_LSB               BMP280_CALIB(6)
#define BMP280_DIG_P1_MSB               BMP280_CALIB(7)
#define BMP280_DIG_P2_LSB               BMP280_CALIB(8)
#define BMP280_DIG_P2_MSB               BMP280_CALIB(9)
#define BMP280_DIG_P3_LSB               BMP280_CALIB(10)
#define BMP280_DIG_P3_MSB               BMP280_CALIB(11)
#define BMP280_DIG_P4_LSB               BMP280_CALIB(12)
#define BMP280_DIG_P4_MSB               BMP280_CALIB(13)
#define BMP280_DIG_P5_LSB               BMP280_CALIB(14)
#define BMP280_DIG_P5_MSB               BMP280_CALIB(15)
#define BMP280_DIG_P6_LSB               BMP280_CALIB(16)
#define BMP280_DIG_P6_MSB               BMP280_CALIB(17)
#define BMP280_DIG_P7_LSB               BMP280_CALIB(18)
#define BMP280_DIG_P7_MSB               BMP280_CALIB(19)
#define BMP280_DIG_P8_LSB               BMP280_CALIB(20)
#define BMP280_DIG_P8_MSB               BMP280_CALIB(21)
#define BMP280_DIG_P9_LSB               BMP280_CALIB(22)
#define BMP280_DIG_P9_MSB               BMP280_CALIB(23)


#define BMP280_DIG_T1_LSB_Pos           (0)
#define BMP280_DIG_T1_MSB_Pos           (1)
#define BMP280_DIG_T2_LSB_Pos           (2)
#define BMP280_DIG_T2_MSB_Pos           (3)
#define BMP280_DIG_T3_LSB_Pos           (4)
#define BMP280_DIG_T3_MSB_Pos           (5)
#define BMP280_DIG_P1_LSB_Pos           (6)
#define BMP280_DIG_P1_MSB_Pos           (7)
#define BMP280_DIG_P2_LSB_Pos           (8)
#define BMP280_DIG_P2_MSB_Pos           (9)
#define BMP280_DIG_P3_LSB_Pos           (10)
#define BMP280_DIG_P3_MSB_Pos           (11)
#define BMP280_DIG_P4_LSB_Pos           (12)
#define BMP280_DIG_P4_MSB_Pos           (13)
#define BMP280_DIG_P5_LSB_Pos           (14)
#define BMP280_DIG_P5_MSB_Pos           (15)
#define BMP280_DIG_P6_LSB_Pos           (16)
#define BMP280_DIG_P6_MSB_Pos           (17)
#define BMP280_DIG_P7_LSB_Pos           (18)
#define BMP280_DIG_P7_MSB_Pos           (19)
#define BMP280_DIG_P8_LSB_Pos           (20)
#define BMP280_DIG_P8_MSB_Pos           (21)
#define BMP280_DIG_P9_LSB_Pos           (22)
#define BMP280_DIG_P9_MSB_Pos           (23)
#define BMP280_CALIB_SIZE               (24)

// BMP280_ID bit definitions
#define BMP280_ID_VAL                   (0x58)

// BMP280_RESET bit definitions
#define BMP280_RESET_VAL                (0xB6)

// BMP280_STATUS bit definitions
#define BMP280_IM_UPDATE_Pos            (0)
#define BMP280_IM_UPDATE                (0x1 << BMP280_IM_UPDATE_Pos)
#define BMP280_MEASURING_Pos            (3)
#define BMP280_MEASURING                (0x1 << BMP280_MEASURING_Pos)

// BMP280_CTRL_MEAS bit definitions
#define BMP280_MODE_Pos                 (0)
#define BMP280_MODE_Msk                 (0x3 << BMP280_MODE_Pos)
#define BMP280_MODE                     BMP280_MODE_Msk
#define BMP280_OSRS_P_Pos               (2)
#define BMP280_OSRS_P_Msk               (0x7 << BMP280_OSRS_P_Pos)
#define BMP280_OSRS_P                   BMP280_OSRS_P_Msk
#define BMP280_OSRS_T_Pos               (5)
#define BMP280_OSRS_T_Msk               (0x7 << BMP280_OSRS_T_Pos)
#define BMP280_OSRS_T                   BMP280_OSRS_T_Msk

#define BMP280_MODE_SLEEP               (0b00)
#define BMP280_MODE_FORCED              (0b01)
#define BMP280_MODE_NORMAL              (0b11)

#define BMP280_OSRS_P_SKIP              (0b000)
#define BMP280_OSRS_P_OSRS_1            (0b001)
#define BMP280_OSRS_P_OSRS_2            (0b010)
#define BMP280_OSRS_P_OSRS_4            (0b011)
#define BMP280_OSRS_P_OSRS_8            (0b100)
#define BMP280_OSRS_P_OSRS_16           (0b101)

#define BMP280_OSRS_T_SKIP              (0b000)
#define BMP280_OSRS_T_OSRS_1            (0b001)
#define BMP280_OSRS_T_OSRS_2            (0b010)
#define BMP280_OSRS_T_OSRS_4            (0b011)
#define BMP280_OSRS_T_OSRS_8            (0b100)
#define BMP280_OSRS_T_OSRS_16           (0b101)

// BMP280 CONFIG bit definitions
#define BMP280_SPI3W_EN_Pos             (0)
#define BMP280_SPI3W_EN                 (0x1 << BMP280_SPI3W_EN_Pos)
#define BMP280_FILTER_Pos               (2)
#define BMP280_FILTER_Msk               (0x7 << BMP280_FILTER_Pos)
#define BMP280_FILTER                   BMP280_FILTER_Msk
#define BMP280_T_SB_Pos                 (5)
#define BMP280_T_SB_Msk                 (0x7 << BMP280_T_SB_Pos)
#define BMP280_T_SB                     BMP280_T_SB_Msk

#define BMP280_SPI3W_EN_ENABLE          (0b1)
#define BMP280_SPI3W_EN_DISABLE         (0b0)

#define BMP280_FILTER_DISABLE           (0b000)
#define BMP280_FILTER_COEFF_2           (0b001)
#define BMP280_FILTER_COEFF_4           (0b010)
#define BMP280_FILTER_COEFF_8           (0b011)
#define BMP280_FILTER_COEFF_16          (0b100)

#define BMP280_T_SB_0_5_MS              (0b000)
#define BMP280_T_SB_62_5_MS             (0b001)
#define BMP280_T_SB_125_MS              (0b010)
#define BMP280_T_SB_250_MS              (0b011)
#define BMP280_T_SB_500_MS              (0b100)
#define BMP280_T_SB_1000_MS             (0b101)
#define BMP280_T_SB_2000_MS             (0b110)
#define BMP280_T_SB_4000_MS             (0b111)

// BMP280 PRESS_MSB bit definitions
#define BMP280_PRESS_MSB_Pos            (0)
#define BMP280_PRESS_MSB_Msk            (0xFF << BMP280_PRESS_MSB_Pos)

// BMP280 PRESS_LSB bit definitions
#define BMP280_PRESS_LSB_Pos            (0)
#define BMP280_PRESS_LSB_Msk            (0xFF << BMP280_PRESS_LSB_Pos)

// BMP280 PRESS_XLSB bit definitions
#define BMP280_PRESS_XLSB_Pos           (4)
#define BMP280_PRESS_XLSB_Msk           (0xF << BMP280_PRESS_XLSB_Pos)

// BMP280 TEMP_MSB bit definitions
#define BMP280_TEMP_MSB_Pos             (0)
#define BMP280_TEMP_MSB_Msk             (0xFF << BMP280_TEMP_MSB_Pos)

// BMP280 TEMP_LSB bit definitions
#define BMP280_TEMP_LSB_Pos             (0)
#define BMP280_TEMP_LSB_Msk             (0xFF << BMP280_TEMP_LSB_Pos)

// BMP280 TEMP_XLSB bit definitions
#define BMP280_TEMP_XLSB_Pos            (4)
#define BMP280_TEMP_XLSB_Msk            (0xF << BMP280_TEMP_XLSB_Pos)

// BMP280 structures

typedef struct bmp280_conf_t {
    uint8_t mode;
    uint8_t osrs_press;
    uint8_t osrs_temp;
    uint8_t t_sb;
    uint8_t filter;
    uint8_t spi3w_en;
}bmp280_conf_t;

typedef struct bmp280_calib_t {
    uint16_t dig_t1;
    int16_t dig_t2;
    int16_t dig_t3;
    uint16_t dig_p1;
    int16_t dig_p2;
    int16_t dig_p3;
    int16_t dig_p4;
    int16_t dig_p5;
    int16_t dig_p6;
    int16_t dig_p7;
    int16_t dig_p8;
    int16_t dig_p9;
}bmp280_calib_t;

typedef struct bmp280_raw_t {
    uint32_t temp;
    uint32_t press;
}bmp280_raw_t;

// BMP280 specific functions
void SPI1_BMP280_start(void);
void SPI1_BMP280_end(void);
uint8_t SPI1_BMP280_read_byte(uint8_t addr);
uint8_t *SPI1_BMP280_read_bytes(uint8_t start_addr, uint8_t num_bytes);
void SPI1_BMP280_write_byte(uint8_t addr, uint8_t data);
void SPI1_BMP280_write_bytes(uint8_t start_addr, uint8_t *data, uint8_t num_bytes);
uint8_t SPI1_BMP280_get_id(void);
void SPI1_BMP280_config(bmp280_conf_t *bmp280_conf_ptr);
void SPI1_BMP280_reset(void);
uint8_t SPI1_BMP280_is_busy(void);
void SPI1_BMP280_get_data(void);
uint32_t SPI1_BMP280_get_temp(uint8_t digits);
uint32_t SPI1_BMP280_get_press(uint8_t digits);
uint32_t SPI1_BMP280_get_calib(bmp280_conf_t *bmp280_conf_ptr, bmp280_calib_t *bmp280_calib_ptr);


#endif // BMP280_H_INCLUDED