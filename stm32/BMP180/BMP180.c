////////////////////////////////////////////////////////////////////////////////
/**
 * @file           BMP180.c
 * @brief          BMP180センサ用ライブラリ
 * @date           2019/09/01
 * $Version:       ver1.0
 * @note           STM32 HALライブラリ用
 * @par            History
 */

////////////////////////////////////////////////////////////////////////////////
// include
#include "BMP180.h"
#include <math.h>
#include "cmsis_os.h"

//! デバッグ用の調整値設定、通常時はコメントアウト
//#define DEBUG_BMP180
#ifdef DEBUG_BMP180
#include <stdio.h>
#endif // DEBUG_BMP180

////////////////////////////////////////////////////////////////////////////////
// macro

////////////////////////////////////////////////////////////////////////////////
// struct
//! 調整値保存用構造体
typedef struct{
	int16_t EEP_AC1;
	int16_t EEP_AC2;
	int16_t EEP_AC3;
	uint16_t EEP_AC4;
	uint16_t EEP_AC5;
	uint16_t EEP_AC6;
	int16_t EEP_B1;
	int16_t EEP_B2;
	int16_t EEP_MB;
	int16_t EEP_MC;
	int16_t EEP_MD;
}EEP_TYPE;

////////////////////////////////////////////////////////////////////////////////
// enum

////////////////////////////////////////////////////////////////////////////////
// global variable
//! サンプルモード設定値
static BMP180_MODE OverSample;
//! 調整値構造体
static EEP_TYPE EepData;

////////////////////////////////////////////////////////////////////////////////
// function prototype

////////////////////////////////////////////////////////////////////////////////
// function
/**
 * @brief       温度rawデータリード
 * @fn          I2C_readTemp
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @return      温度データ
 */
static uint32_t I2C_readTemp(I2C_HandleTypeDef* hi2c)
{
	uint8_t txData[2] = {BMP180_REG_CTRL_MEAS, BMP180_MEAS_TEMP};
	uint8_t rxData[2];
	uint8_t readMsbAddr = BMP180_REG_OUT_MSB;

	HAL_I2C_Master_Transmit(hi2c, BMP180_I2CADDR, txData, 2, 3000);
	osDelay(5); // ほんとはwait4.5msec

	HAL_I2C_Master_Transmit(hi2c, BMP180_I2CADDR, &readMsbAddr, 1, 3000);
	HAL_I2C_Master_Receive(hi2c, BMP180_I2CADDR|0x01 , rxData, 2, 3000);

	return ((rxData[0]<<8) | rxData[1]);
}
/**
 * @brief       気圧rawデータリード
 * @fn          I2C_readPress
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @return      気圧データ
 */
static uint32_t I2C_readPress(I2C_HandleTypeDef *hi2c)
{
	uint8_t txData[2] = {BMP180_REG_CTRL_MEAS, BMP180_MEAS_PRES | (OverSample<<6)};
	uint8_t rxData[3];
	uint8_t readMsbAddr = BMP180_REG_OUT_MSB;

	HAL_I2C_Master_Transmit(hi2c, BMP180_I2CADDR, txData, 2, 3000);
	osDelay(26); // ほんとはwait25.5msec

	HAL_I2C_Master_Transmit(hi2c, BMP180_I2CADDR, &readMsbAddr, 1, 3000);
	HAL_I2C_Master_Receive(hi2c, BMP180_I2CADDR|0x01 , rxData, 3, 3000);

	return (((uint32_t)rxData[0]<<16) | ((uint32_t)rxData[1]<<8) | ((uint32_t)rxData[2]))>>(8-OverSample);
}

/**
 * @brief       EERPOM内の調整値データリード
 * @fn          I2C_readEEPRAM
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @param[out]  readData 調整値出力
 * @return      none
 */
static void I2C_readEEPRAM(I2C_HandleTypeDef *hi2c, EEP_TYPE* readData)
{
	uint8_t rxData[22];
	uint8_t readAddr = BMP180_EEP_AC1;
	HAL_I2C_Master_Transmit(hi2c, BMP180_I2CADDR, &readAddr, 1, 3000);
	HAL_I2C_Master_Receive(hi2c, BMP180_I2CADDR|0x01 , rxData, 22, 3000);

	readData->EEP_AC1 = ( int16_t)((rxData[ 0]<<8) | rxData[ 1]);
	readData->EEP_AC2 = ( int16_t)((rxData[ 2]<<8) | rxData[ 3]);
	readData->EEP_AC3 = ( int16_t)((rxData[ 4]<<8) | rxData[ 5]);
	readData->EEP_AC4 = (uint16_t)((rxData[ 6]<<8) | rxData[ 7]);
	readData->EEP_AC5 = (uint16_t)((rxData[ 8]<<8) | rxData[ 9]);
	readData->EEP_AC6 = (uint16_t)((rxData[10]<<8) | rxData[11]);
	readData->EEP_B1  = ( int16_t)((rxData[12]<<8) | rxData[13]);
	readData->EEP_B2  = ( int16_t)((rxData[14]<<8) | rxData[15]);
	readData->EEP_MB  = ( int16_t)((rxData[16]<<8) | rxData[17]);
	readData->EEP_MC  = ( int16_t)((rxData[18]<<8) | rxData[19]);
	readData->EEP_MD  = ( int16_t)((rxData[20]<<8) | rxData[21]);

}

/**
 * @brief       温度、気圧データ取得(校正後データ)
 * @fn          BMP180_getValue
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @param[out]  temperature	温度出力@n
 * 							小数を無くすため10倍の値を出力@n
 * 							使用時に÷10して単位を[℃]にもどす
 * @param[out]  pressure	気圧出力@n
 * 							小数を無くすため100倍の値を出力@n
 * 							使用時に÷100して単位を[hPa]にもどす
 * @return      none
 */
void BMP180_getValue(I2C_HandleTypeDef *hi2c, int32_t* temperature, int32_t* pressure)
{
	int32_t UT,UP;

	// read uncompensated temperature & pressure
	UT = I2C_readTemp(hi2c);
	UP = I2C_readPress(hi2c);

#ifdef DEBUG_BMP180
	EepData.EEP_AC1 = 408;
	EepData.EEP_AC2 = -72;
	EepData.EEP_AC3 = -14383;
	EepData.EEP_AC4 = 32741;
	EepData.EEP_AC5 = 32757;
	EepData.EEP_AC6 = 23153;
	EepData.EEP_B1  = 6190;
	EepData.EEP_B2  = 4;
	EepData.EEP_MB  = -32768;
	EepData.EEP_MC  = -8711;
	EepData.EEP_MD  = 2868;
	UT = 27898;
	UP = 23843;
#endif // DEBUG_BMP180

	// Calculate true temperature
	int32_t trueTemp;
	int32_t B5;
	{
		int32_t X1,X2,T;
		X1 = ((UT - EepData.EEP_AC6) * EepData.EEP_AC5)>>15;
		X2 = (((int32_t)EepData.EEP_MC)<<11)/(X1+(int32_t)EepData.EEP_MD);
		B5 = X1+X2;
		T = (B5+8)>>4;
		trueTemp = T;
	}
	// Calculate true pressure
	int32_t truePres;
	{
		int32_t B6,X1,X2,X3,B3,P;
		uint32_t B4,B7;

		B6 = B5 - 4000;
		X1 = (EepData.EEP_B2 * ((B6*B6)>>12))>>11;
		X2 = (EepData.EEP_AC2 * B6)>>11;
		X3 = X1+X2;
		B3 = (((((int32_t)EepData.EEP_AC1)*4 + X3)<<OverSample)+2)/4;
		X1 = (EepData.EEP_AC3 * B6)>>13;
		X2 = (EepData.EEP_B1  * ((B6*B6)>>12))>>16;
		X3 = (X1+X2+2)>>2;
		B4 = (EepData.EEP_AC4 * (uint32_t)(X3+32768))>>15;
		B7 = (((uint32_t)UP) - B3)*(50000>>OverSample);
		if(B7 < 0x80000000){
			P = (B7*2)/B4;
		}else{
			P = (B7/B4)*2;
		}
		X1 = (P>>8) * (P>>8);
		X1 = (X1*3038)>>16;
		X2 = (-7357*P)>>16;
		P = P+((X1+X2+3791)>>4);
		truePres = P;

	}

	*temperature = trueTemp;
	*pressure = truePres;
}

/**
 * @brief       気圧から海抜値を算出
 * @fn          BMP180_getAltitude
 * @param[in]   pressure 取得した気圧値(BMP180_getValue()の出力値)
 * @param[out]  altitude　海抜@n
 * 						　1気圧を基準としたときの海抜を出力@n
 * 							小数を無くすため100倍の値を出力@n
 * 							使用時に÷100して単位を[m]にもどす
 * @return      none
 */
void BMP180_getAltitude(int32_t pressure, int32_t* altitude)
{
	*altitude = (int32_t)(44330 * (1 - pow((float)pressure/101325, 1.0f/5.255))*1000);
}

/**
 * @brief       センサ初期化
 * @fn          BMP180_init
 * @param[in]   hi2c I2Cデバイスハンドルポインタ
 * @param[in]   mode BMP180のサンプリングモード
 * @return      none
 */
void BMP180_init(I2C_HandleTypeDef *hi2c, BMP180_MODE mode)
{
	OverSample = mode;
	osDelay(5);

	// 調整値の取得
	I2C_readEEPRAM(hi2c, &EepData);

#ifdef DEBUG_BMP180
	printf("AC1 = %6d\r\n",EepData.EEP_AC1);
	printf("AC2 = %6d\r\n",EepData.EEP_AC2);
	printf("AC3 = %6d\r\n",EepData.EEP_AC3);
	printf("AC4 = %6d\r\n",EepData.EEP_AC4);
	printf("AC5 = %6d\r\n",EepData.EEP_AC5);
	printf("AC6 = %6d\r\n",EepData.EEP_AC6);
	printf("B1  = %6d\r\n",EepData.EEP_B1 );
	printf("B2  = %6d\r\n",EepData.EEP_B2 );
	printf("MB  = %6d\r\n",EepData.EEP_MB );
	printf("MC  = %6d\r\n",EepData.EEP_MC );
	printf("MD  = %6d\r\n",EepData.EEP_MD );
#endif// DEBUG_BMP180
}
