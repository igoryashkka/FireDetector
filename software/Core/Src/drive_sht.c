#include "drive_sht.h"


HAL_StatusTypeDef SHT41_TransmitReceive(uint8_t cmd, uint8_t *data, uint16_t length) {
    HAL_StatusTypeDef ret;
    ret = HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDRESS << 1, &cmd, 1, HAL_MAX_DELAY);
    if (ret != HAL_OK) return ret;
    HAL_Delay(15);
    ret = HAL_I2C_Master_Receive(&hi2c1, I2C_ADDRESS << 1, data, length, HAL_MAX_DELAY);

    return ret;
}


HAL_StatusTypeDef SHT41_Read_Temperature_Humidity(uint8_t cmd, float *temperature, float *humidity) {
    uint8_t data[6];
    HAL_StatusTypeDef ret;

    ret = SHT41_TransmitReceive(cmd, data, 6);
    if (ret != HAL_OK) return ret;

    uint16_t temp_raw = (data[0] << 8) | data[1];
    uint16_t hum_raw = (data[3] << 8) | data[4];

    *temperature = -45.0 + 175.0 * ((float)temp_raw / 65535.0);
    *humidity = 100.0 * ((float)hum_raw / 65535.0);

    return HAL_OK;
}

HAL_StatusTypeDef SHT41_Soft_Reset(void) {
    uint8_t cmd = SHT41_SOFT_RESET;
    return HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDRESS << 1, &cmd, 1, HAL_MAX_DELAY);
}


HAL_StatusTypeDef SHT41_Activate_Heater(uint8_t cmd) {
    uint8_t data[6];
    HAL_StatusTypeDef ret;

    ret = SHT41_TransmitReceive(cmd, data, 6);
    if (ret != HAL_OK) return ret;

    return HAL_OK;
}
