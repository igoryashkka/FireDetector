#ifndef SIGNAL_H
#define SIGNAL_H

// -------------- INCLUDE AREA ----------------------------------- //

#include "stm32g0xx_hal.h"


// -------------- MACRO AND DEFINES AREA ------------------------- //
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;
extern TIM_HandleTypeDef htim3;
// -------------- FUNCTION DECLARATIONS AREA --------------------- //
// LED Control
void LED_SetBrightness(uint16_t brightness);
void LED_Off(void);
void LED_On(void);
void LED_Blink(uint16_t duration);

// Buzzer Control
void Buzzer_SetVolume(uint16_t volume);
void Buzzer_Off(void);
void Buzzer_On(void);
void Buzzer_Beep(uint16_t duration);

// Signaling Functions
void Signal_idle_state(void);
void Signal_detect_emergency(void);
void Signal_detect_fire(void);

#endif // SIGNAL_H

