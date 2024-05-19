
#ifndef _DRV_I2C_H_
#define _DRV_I2C_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	volatile uint32_t Prescale_reg0;	// クロックプリスケールレジスタの下位 8 ビット
	volatile uint32_t Prescale_reg1;	// クロックプリスケールレジスタの上位 8 ビット
	volatile uint32_t Control_reg;		// 制御レジスタ
	union {
		volatile uint32_t Transmit_reg;		// 送信レジスタ
		volatile uint32_t Receive_reg;		// 受信レジスタ
	};
	union {
		volatile uint32_t Command_reg;		// コマンドレジスタ
		volatile uint32_t Status_reg;		// ステータスレジスタ
	};
} ST_I2C_IP;

typedef enum {
	I2C_CLK_FREQ_100K = 0,
	I2C_CLK_FREQ_400K,
}I2C_CLK_FREQ;

// i2c=100kHz @ 27MHz input
#define I2C_PRESCALE_REG0_100K        0x35
#define I2C_PRESCALE_REG1_100K        0x00
// i2c=400kHz @ 27MHz input
// 元発27Mhzでは端数が出るため400kHzよりは少し遅い
#define I2C_PRESCALE_REG0_400K        0x0D
#define I2C_PRESCALE_REG1_400K        0x00

#define I2C_IP ((ST_I2C_IP*)0x85000000)

void i2c_init(I2C_CLK_FREQ clk_freq);
void i2c_read_reg(uint8_t slv_adr, uint8_t reg_adr, uint8_t* reg_data, uint8_t data_count);
void i2c_write_reg(uint8_t slv_adr, uint8_t reg_adr, uint8_t* reg_data, uint8_t data_count);


#endif
