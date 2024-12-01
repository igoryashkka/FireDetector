#include "drive_signal.h"

// ---------- LED Control ------------------------- //
void LED_SetBrightness(uint16_t brightness)
{
	__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, brightness);
}

void LED_Off(void)
{
    LED_SetBrightness(0);
}

void LED_On(void)
{
    LED_SetBrightness(65535);
}

void LED_Blink_Start(uint16_t period)
{

    HAL_TIM_Base_Stop_IT(&htim3); // Stop the timer first if it was running
    __HAL_TIM_SET_AUTORELOAD(&htim3, period - 1); // Set the period for blinking
    HAL_TIM_Base_Start_IT(&htim3); // Start the timer interrupt
}

void LED_Blink_Stop(void)
{
    HAL_TIM_Base_Stop_IT(&htim3); // Stop the timer interrupt
    LED_Off();
}

// ---------- Buzzer Control ---------------------- //
void Buzzer_SetVolume(uint16_t volume)
{
    __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, volume);
}

void Buzzer_Off(void)
{
    Buzzer_SetVolume(0);
}

void Buzzer_On(void)
{
    Buzzer_SetVolume(htim16.Init.Period / 2);
}

void Buzzer_Beep(uint16_t duration)
{
    Buzzer_On();
    HAL_Delay(duration);
    Buzzer_Off();
}

// ---------- Signaling Functions ---------------------- //

void Signal_idle_state(void)
{
	LED_Blink_Stop();
	LED_On();
    Buzzer_Off();
}

void Signal_detect_emergency(void)
{
    LED_Blink_Start(500);
    Buzzer_On();
}

void Signal_detect_fire(void)
{
    LED_Blink_Start(100);
    Buzzer_On();
}
