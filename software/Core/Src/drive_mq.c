#include "drive_mq.h"

uint32_t currentTick60_90 = 0;
uint8_t flag_period = 0;

extern float value_voltage;
extern uint32_t value_ppm;

float read_voltage(){
	uint32_t value_adc = 0;

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	value_adc = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	float voltage = (value_adc * REF_VOLTAGE) / BIT_ADC_VALUE;

	HAL_Delay (10);
	return voltage;
}

uint32_t convert_voltage_to_ppm(float mq7_volts){
	uint32_t ppm;
	float Rs;
	float RsRo;

	Rs=((REF_VOLTAGE*MQ7_LOAD_RESISTOR)/mq7_volts)-MQ7_LOAD_RESISTOR;
	RsRo=Rs/MQ7_RO2;

	//if(RsRo>0.09){
		ppm=(pow((0.196/RsRo),(1/0.72)))*1000;
	// }
	//else {ppm=1999;}

	 return ppm;
}

void run_mq_mesurments(){
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
