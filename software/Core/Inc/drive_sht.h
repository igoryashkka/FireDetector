#ifndef SHT41_H
#define SHT41_H

// -------------- INCLUDE AREA ----------------------------------- //

#include "stm32g0xx_hal.h"
//#include "stdint.h"
//#include "stdbool.h"

// -------------- MACRO AND DEFINES AREA ------------------------- //

extern I2C_HandleTypeDef hi2c1;


#define I2C_ADDRESS 				   0x45
#define SHT41_MEASURE_HIGHREP_STRETCH  0xFD
#define SHT41_MEASURE_MEDREP_STRETCH   0xF6
#define SHT41_MEASURE_LOWREP_STRETCH   0xE0
#define SHT41_READ_SERIAL              0x89
#define SHT41_SOFT_RESET               0x94
#define SHT41_HEATER_200MW_1S          0x39
#define SHT41_HEATER_200MW_0_1S        0x32
#define SHT41_HEATER_110MW_1S          0x2F
#define SHT41_HEATER_110MW_0_1S        0x24
#define SHT41_HEATER_20MW_1S           0x1E
#define SHT41_HEATER_20MW_0_1S         0x15

// -------------- FUNCTION DECLARATIONS AREA --------------------- //
HAL_StatusTypeDef SHT41_TransmitReceive(uint8_t cmd, uint8_t *data, uint16_t length);
HAL_StatusTypeDef SHT41_Read_Temperature_Humidity(uint8_t cmd, float *temperature, float *humidity);
HAL_StatusTypeDef SHT41_Read_Serial(uint32_t *serial_number);
HAL_StatusTypeDef SHT41_Soft_Reset(void);
HAL_StatusTypeDef SHT41_Activate_Heater(uint8_t cmd);

#endif // SHT41_H
