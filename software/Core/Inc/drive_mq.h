#ifndef MQ_SENSOR_H
#define MQ_SENSOR_H

// -------------- INCLUDE AREA ----------------------------------- //

#include "stm32g0xx_hal.h"
#include "drive_signal.h"
#include <math.h>

// -------------- MACRO AND DEFINES AREA ------------------------- //
#define MQ7_LOAD_RESISTOR 			10000
#define REF_VOLTAGE 	  			3.3
#define MQ7_RO 	      				10000 // Resistance of sensor within 100ppm (in Ohm)
#define NUM_READ 		  			1000
#define BIT_ADC_VALUE	  			4095
#define TIMER_PERIOD_30SEC_HEAT		29999
#define TIMER_PERIOD_60SEC_HEAT		59998
#define TIMER_PERIOD_60SEC_MESURE	59999
#define PERIOD_2_HEAT				2
#define PERIOD_1_HEAT				1
#define PERIOD_MESURE				0
#define OFFSET_PERIOD_MESURE		5500
#define MAX_VALUE_PPM    			3999
// -------------------------

// -------------------------
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim14;

// -------------- FUNCTION DECLARATIONS AREA --------------------- //
float read_voltage();
uint32_t convert_voltage_to_ppm(float mq7_volts);
void MQ_run_mesurments();

#endif // MQ_SENSOR_H

