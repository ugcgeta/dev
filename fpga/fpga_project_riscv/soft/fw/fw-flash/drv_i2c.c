#include <stdint.h>
#include <stdbool.h>
#include "debug_uart.h"
#include "drv_i2c.h"

#define I2C_ACCESS_WRITE_BIT 0x00
#define I2C_ACCESS_READ_BIT  0x01
#define I2C_COMMAND_START	 0x80
#define I2C_COMMAND_STOP	 0x40
#define I2C_COMMAND_READ	 0x20
#define I2C_COMMAND_WRITE	 0x10
#define I2C_COMMAND_ACK		 0x08

void i2c_init(I2C_CLK_FREQ clk_freq)
{
	if(clk_freq == I2C_CLK_FREQ_100K){
    	I2C_IP->Prescale_reg0 = I2C_PRESCALE_REG0_100K;
		I2C_IP->Prescale_reg1 = I2C_PRESCALE_REG1_100K;
	}else{
		I2C_IP->Prescale_reg0 = I2C_PRESCALE_REG0_400K;
		I2C_IP->Prescale_reg1 = I2C_PRESCALE_REG1_400K;
	}
	// I2C enable
	I2C_IP->Control_reg = 0x80;
}
	
bool waitTIP()
{
	uint32_t timeout=0;
	debug_print("I2C_IP->Status_reg : \n");
	while(1){
		uint8_t reg = I2C_IP->Status_reg;
		debug_print(" 0x");
		debug_print_hex(reg, 2);
		if((reg & 0x02)!=0x02){
			return true;
		}
		
		timeout++;
		if(timeout > 0xFFFF){
			break;
		}
	}
	return false;
}

void i2c_read_reg(uint8_t slv_adr, uint8_t reg_adr, uint8_t* reg_data, uint8_t data_count)
{
	bool result;
	uint8_t count;
	print("I2C read : \n");
	// 1. 送信レジスタの値を以下に設定します
	//   ： Slave address + Write bit；
	debug_print("I2C_IP->Transmit_reg : \n");
	I2C_IP->Transmit_reg = (slv_adr<<1) | I2C_ACCESS_WRITE_BIT;
	
	// 2. コマンドレジスタの値を 8’ h90 に設定して、
	//    開始及び書き込みコマンドを有効にし、
	//    I2C バスでデータ送信を開始します；
	debug_print("I2C_IP->Command_reg : \n");
	I2C_IP->Command_reg = I2C_COMMAND_START | I2C_COMMAND_WRITE;
	
	// 3. ステータスレジスタの TIP ビットを検査し、
	//    コマンドの実行完了を確認します；
	result = waitTIP();
	if(!result){
		// Timeout Error
		debug_print("Timeout Error \n");
		//return;
	}
	debug_print(" \n");
		
	// 4. 送信レジスタの値をスレーブメモリのアドレスに設定し、
	//    マスターがこのメモリ内からデータを読み出します；
	debug_print("I2C_IP->Transmit_reg : \n");
	I2C_IP->Transmit_reg = (reg_adr);
	
	// 5. コマンドレジスタの値を 8’ h10 に設定し、
	//    書き込みコマンドを有効にして、
	//    スレーブメモリのアドレスを送信します；
	debug_print("I2C_IP->Command_reg : \n");
	I2C_IP->Command_reg = I2C_COMMAND_WRITE;
	
	// 6. ステータスレジスタの TIP ビットを検査し、
	//    コマンドの実行完了を確認します；
	debug_print("I2C_IP->Status_reg : \n");
	result = waitTIP();
	if(!result){
		// Timeout Error
		debug_print("Timeout Error \n");
		//return;
	}
	debug_print(" \n");
	
	// 7. 送信レジスタの値を設定します： 
	//      Slave address + Read bit。
	debug_print("I2C_IP->Transmit_reg : \n");
	I2C_IP->Transmit_reg = (slv_adr<<1) | I2C_ACCESS_READ_BIT;
	
	// 8. コマンドレジスタの値を 8’ h90 に設定し、
	//    開始（この場合、リピート開始）及び書き込みを有効にすると、
	//    送信レジスタ内のデータをスレーブに書き込みます；
	debug_print("I2C_IP->Command_reg : \n");
	I2C_IP->Command_reg = I2C_COMMAND_START | I2C_COMMAND_WRITE;
	// 9. ステータスレジスタの TIP ビットを検査し、
	//     コマンドの実行完了を確認します；
	debug_print("I2C_IP->Status_reg : \n");
	result = waitTIP();
	if(!result){
		// Timeout Error
		debug_print("Timeout Error \n");
		//return;
	}
	debug_print(" \n");
	
	for(count=0; count < data_count; count++){
		// 10. コマンドレジスタの値を 8’ h20 に設定して、
		//     読み出し及び応答コマンドを実行し、
		//     スレーブからのデータ読み出しを完了させます；
		debug_print("I2C_IP->Command_reg : \n");
		if(count == (data_count-1)){
			// 13. マスターがスレーブのデータ読み出しを停止して、
			//     コマンドレジスタの値を 8’ h68に設定すると、
			//     スレーブが最後の 1バイトを読み出し、NACK を実行します。
			// 最終データ時はstopとackを返す
			I2C_IP->Command_reg = I2C_COMMAND_STOP | I2C_COMMAND_READ | I2C_COMMAND_ACK;
		}else{
			I2C_IP->Command_reg = I2C_COMMAND_READ;
		}
		
		// 11. ステータスレジスタの TIP ビットを検査し、
		//     コマンドの実行完了を確認します；
		debug_print("I2C_IP->Status_reg : \n");
		result = waitTIP();
		if(!result){
			// Timeout Error
			debug_print("Timeout Error \n");
			//return;
		}
		debug_print(" \n");
		
		reg_data[count] = I2C_IP->Receive_reg;
		debug_print_hex(reg_data[count], 2);
		debug_print(" \n");
		
		// 12. 手順 10~11 を繰り返して、スレーブからのデータ読み出しを継続します；
	}
	

}

void i2c_write_reg(uint8_t slv_adr, uint8_t reg_adr, uint8_t* reg_data, uint8_t data_count)
{
	bool result;
	uint8_t count;
	print("I2C write : \n");
	// 1. 送信レジスタの値を設定します： 
	//    Slave address + Write bit
	debug_print("I2C_IP->Transmit_reg : \n");
	I2C_IP->Transmit_reg = (slv_adr<<1) | I2C_ACCESS_WRITE_BIT;
	
	// 2. コマンドレジスタの値を 8’ h90 に設定して、
	//    開始及び書き込みコマンドを有効にし、
	//    I2C バスでデータ送信を開始します；
	debug_print("I2C_IP->Command_reg : \n");
	I2C_IP->Command_reg = I2C_COMMAND_START | I2C_COMMAND_WRITE;
	
	// 3. ステータスレジスタの TIP ビットを検査し、
	//    コマンドの実行完了を確認します；
	result = waitTIP();
	if(!result){
		// Timeout Error
		debug_print("Timeout Error \n");
		//return;
	}
	debug_print(" \n");
		
	// 4. 送信レジスタの値をスレーブメモリのアドレスに設定し、
	//    マスターがこのメモリ内からデータを読み出します；
	debug_print("I2C_IP->Transmit_reg : \n");
	I2C_IP->Transmit_reg = (reg_adr);
	
	// 5. コマンドレジスタの値を 8’ h10 に設定し、
	//    書き込みコマンドを有効にして、
	//    スレーブメモリのアドレスを送信します；
	debug_print("I2C_IP->Command_reg : \n");
	I2C_IP->Command_reg = I2C_COMMAND_WRITE;
	
	// 6. ステータスレジスタの TIP ビットを検査し、
	//    コマンドの実行完了を確認します；
	debug_print("I2C_IP->Status_reg : \n");
	result = waitTIP();
	if(!result){
		// Timeout Error
		debug_print("Timeout Error \n");
		//return;
	}
	debug_print(" \n");
	
	for(count=0; count < data_count; count++){
		// 7. 送信レジストを 8 ビットのデータに設定し、このデータをスレーブに書き込みます；
		debug_print("I2C_IP->Transmit_reg : \n");
		I2C_IP->Transmit_reg = reg_data[count];
		
		// 8. コマンドレジスタの値を 8’ h10 に設定し、
		// 書き込みコマンドを有効にして、データを送信します；
		debug_print("I2C_IP->Command_reg : \n");
		if(count == (data_count-1)){
			// 11. データの最後のバイトで送信レジスタを設定します。
			// 12. コマンドレジスタの値を 8’ h50 に設定し、
			//     書き込みコマンドを有効にして最後の 1 バイトを送信してから、
			//     停止命令を送信します。
			// 最終データ時はstopとnackを返す
			I2C_IP->Command_reg = I2C_COMMAND_STOP | I2C_COMMAND_WRITE;
		}else{
			I2C_IP->Command_reg = I2C_COMMAND_WRITE;
		}
		
		
		// 9. ステータスレジスタの TIP ビットを検査し、
		//     コマンドの実行完了を確認します；
		debug_print("I2C_IP->Status_reg : \n");
		result = waitTIP();
		if(!result){
			// Timeout Error
			debug_print("Timeout Error \n");
			//return;
		}
		debug_print(" \n");
		
		// 10. 手順 7～9 を繰り返して継続的にスレーブにデータを書き込みます；
		
	}	
	

}
