#include "drive_mq.h"

uint32_t currentTick60_90 = 0;
uint8_t flag_period = 0;

float value_voltage = 0;
extern uint32_t value_ppm;

HAL_StatusTypeDef MQ7_Validate(float voltage, uint32_t ppm) {
    if (voltage < 0.1 || voltage > REF_VOLTAGE) {
        Signal_error();
        return HAL_ERROR;
    }
    if (ppm == MAX_VALUE_PPM) {
        Signal_error();
        return HAL_ERROR;
    }
    return HAL_OK;
}


float read_voltage(){
	uint32_t value_adc = 0;

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	value_adc = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	float voltage = (value_adc * REF_VOLTAGE) / BIT_ADC_VALUE;

	 if (MQ7_Validate(voltage, convert_voltage_to_ppm(voltage)) != HAL_OK) {
	        return -1;
	    }

	return voltage;
}

uint32_t convert_voltage_to_ppm(float mq7_volts){
	uint32_t ppm;
	float Rs;
	float RsRo; // Check datasheet for getting importance of the value of this devision

	// Ro: sensor resistance at 100ppm
	// CO in the clean air.
	// Rs: sensor resistance at various
	// concentrations of gases.

	Rs=((REF_VOLTAGE*MQ7_LOAD_RESISTOR)/mq7_volts)-MQ7_LOAD_RESISTOR; // Resistance of sensor
	RsRo=Rs/MQ7_RO;

	if(RsRo>0.09){ 							// Check if Rs/Ro is aplicable
		ppm=(pow((0.3/RsRo),(1/1.3)))*1000; //
	}	else {ppm=3999;}

	return ppm;
}

void MQ_run_mesurments(){
	 currentTick60_90 = __HAL_TIM_GET_COUNTER(&htim1);
	 if (currentTick60_90 >= TIMER_PERIOD_30SEC_HEAT && flag_period==PERIOD_1_HEAT)
	 {
		 __HAL_TIM_SET_COUNTER(&htim1, 0);				//Reset Counter To start Count another period
		 flag_period=PERIOD_2_HEAT;
		 TIM1->ARR = TIMER_PERIOD_60SEC_HEAT;
	 }

	 if (currentTick60_90 >= TIMER_PERIOD_60SEC_HEAT && flag_period==PERIOD_2_HEAT)
	 {
		 __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 0); //set Transistor as 5 Volt to heat
		 __HAL_TIM_SET_COUNTER(&htim1, 0);					//Reset Counter To start Count another period
		 flag_period=PERIOD_MESURE;
		 TIM1->ARR = TIMER_PERIOD_60SEC_MESURE;
	 }

	 if (currentTick60_90 >= TIMER_PERIOD_60SEC_MESURE && flag_period==PERIOD_MESURE)
	 {
		 __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, ((htim14.Init.Period/2) + OFFSET_PERIOD_MESURE));// set Transistor as 1.4 Volt to mesure values
		 __HAL_TIM_SET_COUNTER(&htim1, 0);																//Reset Counter To start Count another period
		 flag_period=PERIOD_1_HEAT;
		 TIM1->ARR = TIMER_PERIOD_30SEC_HEAT;
	 }

	 if(flag_period==PERIOD_MESURE){
		 value_voltage = read_voltage();
		 value_ppm = convert_voltage_to_ppm(value_voltage);
	 }
}
