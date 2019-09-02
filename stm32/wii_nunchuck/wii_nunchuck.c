////////////////////////////////////////////////////////////////////////////////
/**
 * @file           wii_nunchuck.c
 * @brief          Wiiヌンチャク使用ライブラリ
 * @date           2019/09/02
 * $Version:       ver1.0
 * @note           STM32 HALライブラリ用
 * @par            History
 */
////////////////////////////////////////////////////////////////////////////////
// include
#include "wii_nunchuck.h"
#include "cmsis_os.h"
////////////////////////////////////////////////////////////////////////////////
// macro
//! デバイスID HALライブラリでは7bitアドレスを左シフトして設定する
#define WII_NUNCHUCK_DEV_ID ((0x52)<<1)

////////////////////////////////////////////////////////////////////////////////
// struct
////////////////////////////////////////////////////////////////////////////////
// enum
////////////////////////////////////////////////////////////////////////////////
// global variable
////////////////////////////////////////////////////////////////////////////////
// function prototype
////////////////////////////////////////////////////////////////////////////////
// function
/**
 * @brief       ミリ秒単位のウェイト実行
 * @fn          userDelay
 * @param[in]   millisec ウェイト時間(msec単位)
 * @return      none
 */
static void userDelay(uint32_t millisec)
{
	osDelay(millisec);
}

/**
 * @brief       データリード前に0x00をライト(サンプリング指示？レジスタアドレス設定？)
 * @fn          send_request
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @return      none
 */
static void send_request(I2C_HandleTypeDef *hi2c)
{
	uint8_t pData[2] = {0x00, 0x00};
	HAL_I2C_Master_Transmit(hi2c, WII_NUNCHUCK_DEV_ID, pData, 1, 3000);
}

/**
 * @brief       デバイス出力の復号
 * @fn          decode_byte
 * @param[in]   x 復号元データ
 * @return      復号結果
 */
static uint8_t decode_byte(uint8_t x)
{
	return ((x ^ 0x17) + 0x17);
}

/**
 * @brief       ボタン＆スティック＆加速度センサ　データ取得
 * @fn          WiiNunchuck_getKey
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @param[out]  keyStatus ヌンチャクデータ
 * @return      none
 */
void WiiNunchuck_getKey(I2C_HandleTypeDef *hi2c, wiiNunchuck *keyStatus)
{
    int cnt=0;
    uint8_t rxData[6],decData[6];

    send_request(hi2c);
    userDelay(2);

    // 6Byteリード
    HAL_I2C_Master_Receive(hi2c, WII_NUNCHUCK_DEV_ID|0x01 , rxData, 6, 3000);

    // データ複合
    for(cnt=0; cnt<6; cnt++){
    	decData[cnt] = decode_byte(rxData[cnt]);
    }

    // 構造体へ代入
    keyStatus->joy_x = decData[0];
    keyStatus->joy_y = decData[1];
    keyStatus->button_c = (decData[5]>>1) & 0x01;
    keyStatus->button_z = (decData[5]>>0) & 0x01;
    keyStatus->accel_x = (((uint16_t)decData[2])<<2) | ((decData[5]>>2) & 0x03);
    keyStatus->accel_y = (((uint16_t)decData[3])<<2) | ((decData[5]>>4) & 0x03);
    keyStatus->accel_z = (((uint16_t)decData[4])<<2) | ((decData[5]>>6) & 0x03);

}

/**
 * @brief       ヌンチャク初期化
 * @fn          WiiNunchuck_init
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @return      none
 */
void WiiNunchuck_init(I2C_HandleTypeDef *hi2c)
{
	uint8_t pData[2] = {0x40, 0x00};
	HAL_I2C_Master_Transmit(hi2c, WII_NUNCHUCK_DEV_ID, pData, 2, 3000);

}
