////////////////////////////////////////////////////////////////////////////////
/**
 * @file           BMP180.h
 * @brief          BMP180センサ用ライブラリヘッダ
 * @date           2019/09/01
 * $Version:       ver1.0
 * @note           STM32 HALライブラリ用
 * @par            History
 */

#ifndef __BMP180_H__
#define __BMP180_H__

////////////////////////////////////////////////////////////////////////////////
// include
#include "stm32f1xx_hal.h"
////////////////////////////////////////////////////////////////////////////////
// macro
#define BMP180_I2CADDR (0x77<<1)	//!< I2Cデバイスアドレス

#define BMP180_EEP_AC1	0xAA	//!< 調整値レジスタアドレスAC1
#define BMP180_EEP_AC2	0xAC	//!< 調整値レジスタアドレスAC2
#define BMP180_EEP_AC3	0xAE	//!< 調整値レジスタアドレスAC3
#define BMP180_EEP_AC4	0xB0	//!< 調整値レジスタアドレスAC4
#define BMP180_EEP_AC5	0xB2	//!< 調整値レジスタアドレスAC5
#define BMP180_EEP_AC6	0xB4	//!< 調整値レジスタアドレスAC6
#define BMP180_EEP_B1 	0xB6	//!< 調整値レジスタアドレスB1
#define BMP180_EEP_B2 	0xB8	//!< 調整値レジスタアドレスB2
#define BMP180_EEP_MB 	0xBA	//!< 調整値レジスタアドレスMB
#define BMP180_EEP_MC 	0xBC	//!< 調整値レジスタアドレスMC
#define BMP180_EEP_MD 	0xBE	//!< 調整値レジスタアドレスMD

#define BMP180_REG_CTRL_MEAS	0xF4	//!< 測定開始レジスタアドレス
#define BMP180_REG_OUT_MSB		0xF6	//!< 測定値のMSBレジスタアドレス
#define BMP180_REG_OUT_LSB		0xF7	//!< 測定値のLSBレジスタアドレス
#define BMP180_REG_OUT_XLSB		0xF8	//!< 測定値のXLSBレジスタアドレス

#define BMP180_MEAS_TEMP       0x2E		//!< 温度データ測定時のレジスタ設定
#define BMP180_MEAS_PRES   		0x34	//!< 気圧データ測定時のレジスタ設定

////////////////////////////////////////////////////////////////////////////////
// struct

////////////////////////////////////////////////////////////////////////////////
// enum
/**
 * @enum BMP180_MODE
 * サンプリングモード設定
 */
typedef enum{
	BMP180_MODE_ULTRALOWPOWER = 0,
	BMP180_MODE_STANDARD      = 1,
	BMP180_MODE_HIGHRES       = 2,
	BMP180_MODE_ULTRAHIGHRES  = 3
}BMP180_MODE;

////////////////////////////////////////////////////////////////////////////////
// global variable
////////////////////////////////////////////////////////////////////////////////
// function prototype
void BMP180_getValue(I2C_HandleTypeDef *hi2c, int32_t* temperature, int32_t* pressure);
void BMP180_getAltitude(int32_t pressure, int32_t* altitude);
void BMP180_init(I2C_HandleTypeDef *hi2c, BMP180_MODE mode);

#endif// __BMP180_H__
