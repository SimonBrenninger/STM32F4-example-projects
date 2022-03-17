#ifndef BMB280_H_INCLUDED
#define BMP280_H_INCLUDED

// BMP280 specific registers
#define BMP280_BASE         (0x88)
#define BMP280_CALIB_BASE   BMP280_BASE                 /* 0x88 */
#define BMP280_PRESS_BASE   (0xF7)                      /* 0xF7 */
#define BMP280_TEMP_BASE    (0xFA)                      /* 0xFA */

#define BMP280_CALIB(a)     (BMP280_CALIB_BASE + a)     /* 0x88 + a */
#define BMP280_ID           (0xD0)                      /* 0xD0 */
#define BMP280_RESET        (0xE0)                      /* 0xE0 */
#define BMP280_STATUS       (0xF3)                      /* 0xF3 */
#define BMP280_CTRL_MEAS    (0xF4)                      /* 0xF4 */
#define BMP280_CONFIG       (0xF5)                      /* 0xF5 */
#define BMP280_PRESS_MSB    (0xF7)                      /* 0xF7 */
#define BMP280_PRESS_LSB    (0xF8)                      /* 0xF8 */
#define BMP280_PRESS_XLSB   (0xF9)                      /* 0xF9 */
#define BMP280_TEMP_MSB     (0xFA)                      /* 0xFA */
#define BMP280_TEMP_LSB     (0xFB)                      /* 0xFB */
#define BMP280_TEMP_XLSB    (0xFC)                      /* 0xFC */

// BMP280 bit definitions

// BMP280_ID bit definitions
#define BMP280_ID_VAL       (0x58)

// BMP280_RESET bit definitions
#define BMP280_RESET_VAL    (0xB6)

// BMP280_STATUS bit definitions
#define BMP280_STATUS_IM_UPDATE_Pos     (0)
#define BMP280_STATUS_IM_UPDATE         (0x1 << BMP280_STATUS_IM_UPDATE_Pos)
#define BMP280_STATUS_MEASURING_Pos     (3)
#define BMP280_STATUS_MEASURING         (0x1 << BMP280_STATUS_MEASURING_Pos)

// BMP280_CTRL_MEAS bit definitions
#define BMP280_CTRL_MEAS_MODE_Pos       (0)
#define BMP280_CTRL_MEAS_MODE_Msk       (0x3 << BMP280_CTRL_MEAS_MODE_Pos)
#define BMP280_CTRL_MEAS_MODE           BMP280_CTRL_MEAS_MODE_Msk
#define BMP280_CTRL_MEAS_OSRS_P_Pos     (2)
#define BMP280_CTRL_MEAS_OSRS_P_Msk     (0x7 << BMP280_CTRL_MEAS_OSRS_P_Pos)
#define BMP280_CTRL_MEAS_OSRS_P         BMP280_CTRL_MEAS_OSRS_P_Msk
#define BMP280_CTRL_MEAS_OSRS_T_Pos     (5)
#define BMP280_CTRL_MEAS_OSRS_T_Msk     (0x7 << BMP280_CTRL_MEAS_OSRS_T_Pos)
#define BMP280_CTRL_MEAS_OSRS_T         BMP280_CTRL_MEAS_OSRS_T_Msk

// BMP280 CONFIG bit definitions
#define BMP280_CONFIG_SPI3W_EN_Pos      (0)
#define BMP280_CONFIG_SPI3W_EN          (0x1 << BMP280_CONFIG_SPI3W_EN_Pos)
#define BMP280_CONFIG_FILTER_Pos        (2)
#define BMP280_CONFIG_FILTER_Msk        (0x7 << BMP280_CONFIG_FILTER_Pos)
#define BMP280_CONFIG_FILTER            BMP280_CONFIG_FILTER_Msk
#define BMP280_CONFIG_T_SB_Pos          (5)
#define BMP280_CONFIG_T_SB_Msk          (0x7 << BMP280_CONFIG_T_SB_Pos)
#define BMP280_CONFIG_T_SB              BMP280_CONFIG_T_SB_Msk

// BMP280 PRESS_MSB bit definitions
#define BMP280_PRESS_MSB_Pos           (0)
#define BMP280_PRESS_MSB_Msk           (0xFF << BMP280_PRESS_MSB_Pos)

// BMP280 PRESS_LSB bit definitions
#define BMP280_PRESS_LSB_Pos           (0)
#define BMP280_PRESS_LSB_Msk           (0xFF << BMP280_PRESS_LSB_Pos)

// BMP280 PRESS_XLSB bit definitions
#define BMP280_PRESS_XLSB_Pos           (4)
#define BMP280_PRESS_XLSB_Msk           (0xF << BMP280_PRESS_XLSB_Pos)

// BMP280 TEMP_MSB bit definitions
#define BMP280_TEMP_MSB_Pos           (0)
#define BMP280_TEMP_MSB_Msk           (0xFF << BMP280_TEMP_MSB_Pos)

// BMP280 TEMP_LSB bit definitions
#define BMP280_TEMP_LSB_Pos           (0)
#define BMP280_TEMP_LSB_Msk           (0xFF << BMP280_TEMP_LSB_Pos)

// BMP280 TEMP_XLSB bit definitions
#define BMP280_TEMP_XLSB_Pos           (4)
#define BMP280_TEMP_XLSB_Msk           (0xF << BMP280_TEMP_XLSB_Pos)

// bmp280 specific functions


#endif // BMP280_H_INCLUDED