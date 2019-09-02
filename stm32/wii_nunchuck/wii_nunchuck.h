////////////////////////////////////////////////////////////////////////////////
/**
 * @file           wii_nunchuck.h
 * @brief          Wiiヌンチャク用ライブラリヘッダ
 * @date           2019/09/01
 * $Version:       ver1.0
 * @note           STM32 HALライブラリ用
 * @par            History
 */
#ifndef __WII_NUNCHUCK_H__
#define __WII_NUNCHUCK_H__

////////////////////////////////////////////////////////////////////////////////
// include
#include "stm32f1xx_hal.h"
////////////////////////////////////////////////////////////////////////////////
// macro

////////////////////////////////////////////////////////////////////////////////
// struct
//! ヌンチャク入力構造体
typedef struct {
	uint8_t joy_x;
	uint8_t joy_y;
	uint8_t button_c;
	uint8_t button_z;
	uint16_t accel_x;
	uint16_t accel_y;
	uint16_t accel_z;
}wiiNunchuck;

////////////////////////////////////////////////////////////////////////////////
// enum
////////////////////////////////////////////////////////////////////////////////
// global variable

////////////////////////////////////////////////////////////////////////////////
// function prototype
void WiiNunchuck_getKey(I2C_HandleTypeDef *hi2c, wiiNunchuck *keyStatus);
void WiiNunchuck_init(I2C_HandleTypeDef *hi2c);

#endif // __WII_NUNCHUCK_H__
