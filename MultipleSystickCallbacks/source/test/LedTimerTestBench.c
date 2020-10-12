/***************************************************************************//**
  @file     Led&TimerTestBench.c
  @brief    Led & Timer Drivers Test Bench
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <test/LedTimerTestBench.h>
#include "../Timer.h"
#include "../Led.h"
int onForDefinedTimeTestID;
int callBackProgressID;
int pauseCallbackId;
bool paused;
static void OnForDefinedTimeTest(void);
static void OnlyOnceCallbackTest(void);
static void OnlyOnceCallbackTest2(void);
static void FinishInfiniteBlinkTestGreen(void);
static void FinishInfiniteBlinkTestRed(void);
static void FinishAllTestBlue(void);
static void FinishAll(void);
static void GetCallbackProgress(void);
static void PauseAndResumeCallbackTest(void);
static void PauseAndResumeCallbackTestAction(void);
static void ResetTimerTest(void);
void TestLedAndTimer()
{
	/*On For Define Time Test + Timer Add Callback Test + Timer Delete Callback Test*/
	onForDefinedTimeTestID = Timer_AddCallback(&OnForDefinedTimeTest, 4000, false);	//Wait 4 seconds before it starts.


	/*Call callback only once test*/
	//Timer_AddCallback(&OnlyOnceCallbackTest, 1000, true);


	/*Custom Blink*/
	//Led_CustomBlink(LED_RED, 4, 4000, 1000); //Blink 4 times.Each time: 4s TOTAL, 1s ON, 3s OFF

	 /*Custom Blink Error Test:*/
	 /*int i = Led_CustomBlink(LED_GREEN, 4, 1000, 4000); //ERROR. PERIOD < ON TIME
	 if (i == LedPeriodError )
		 Led_On(LED_RED);	//Should turn on.
	 */


	/*Repetition Blink*/
	//Led_CustomRepetitionBlink(LED_RED, 4, 30000, 3, 5000, 4000);	//4 repetitions every 30 seconds of: 3 blinks of 5s TOTAL, 4s ON, 1s OFF
	/*Repetition Blink Error Test 1:*/
	/*
	 int i = Led_CustomRepetitionBlink(LED_GREEN, 4, 3000, 3, 5000, 4000); //ERROR. REPETITION PERIOD < BLINK PERIOD
	 if (i == LedPeriodError )
		 Led_On(LED_RED);	//Should turn on.
	 */



	/*Repetition Blink Error Test 2:*/
	/*
	int i = Led_CustomRepetitionBlink(LED_GREEN, 4, 30000, 3, 4000, 5000); //ERROR. BLINK PERIOD < ON TIME
	if (i == LedPeriodError )
		Led_On(LED_RED);	//Should turn on.
	*/

	/*Infinite Blink & Cancel Infinite Blink*/
	/*Fast. Red.*/
	/*
	Led_InfiniteBlink(LED_RED, FAST);
	Timer_AddCallback(&FinishInfiniteBlinkTestRed, 3000, true);
	*/

	/*SLOW. Green.*/
	/*
	Led_InfiniteBlink(LED_GREEN, SLOW);
	Timer_AddCallback(&FinishInfiniteBlinkTestGreen, 6000, true);
	*/

	/*Led End All Processes Test*/
	/*
	Led_InfiniteBlink(LED_BLUE, FAST);
	Led_CustomBlink(LED_BLUE, 4, 4000, 1000);
	Led_InfiniteBlink(LED_RED, SLOW);
	Timer_AddCallback(&FinishAllTestBlue, 8000, true);	//Should remain LED RED blinking after 8s
	*/

	/*Led End All Processes From All Leds Test*/
	/*
	Led_InfiniteBlink(LED_BLUE, FAST);
	Led_CustomBlink(LED_BLUE, 4, 4000, 1000);
	Led_InfiniteBlink(LED_RED, SLOW);
	Led_CustomRepetitionBlink(LED_GREEN, 4, 30000, 3, 5000, 4000);
	Timer_AddCallback(&FinishAll, 8000, true);	//Should cancel all blinks after 8 seconds.
	*/

	/*Get Timer Callback Progress*/
	/*
	callBackProgressID = Timer_AddCallback(&FinishAll, 8000, false); //8 seconds.
	Timer_AddCallback(&GetCallbackProgress, 1000, false); //Prints fraction every 1 second.
	*/

	/*Timer Pause and Resume Callback*/
	/*
	paused = false;
	pauseCallbackId = Timer_AddCallback(&PauseAndResumeCallbackTest, 1000, false); //1 seconds.
	Timer_AddCallback(&PauseAndResumeCallbackTestAction, 4000, false); //4 seconds.	Should pause and resume every 4 seconds.
	*/

	/*Timer Reset*/
	/*
	onForDefinedTimeTestID = Timer_AddCallback(&OnlyOnceCallbackTest2, 5000, true);	//Wait 5 seconds before it starts.
	Timer_AddCallback(&ResetTimerTest, 2500, true);	//After 2.5 seconds of waiting, it resets the timer -> The led should turn on after 7.5 seconds in total.
	*/
}

static void OnForDefinedTimeTest(void)
{
	static int i = 0;
	switch(i){
	case 0:
		Led_OnForDefinedTime(LED_RED, 4000); //4s
		break;
	case 1:
		Led_OnForDefinedTime(LED_GREEN, 4000); //4s
		break;
	case 2:
		Led_OnForDefinedTime(LED_BLUE, 4000); //4s
		break;
	case 3:
		Timer_Delete(onForDefinedTimeTestID);
		break;
	case 4:
		Led_OnForDefinedTime(LED_BLUE, 4000); //WILL TURN ON ONLY IF DELETE CALLBACK FAILS.
	}
	i++;
}

static void OnlyOnceCallbackTest(void)
{
	Led_OnForDefinedTime(LED_RED, 1000); //1s
}

static void FinishInfiniteBlinkTestRed(void)
{
	Led_StopInfiniteBlink(LED_RED);
}
static void FinishInfiniteBlinkTestGreen(void)
{
	Led_StopInfiniteBlink(LED_GREEN);
}
static void FinishAllTestBlue(void)
{
	Led_StopAllProcesses(LED_BLUE);
}
static void FinishAll(void)
{
	Led_StopAllProcessedFromAllLeds();
}
static void GetCallbackProgress(void)
{

	float fraction = Timer_GetCallbackProgress(callBackProgressID);
	Led_OnForDefinedTime(LED_RED, (int) (fraction*1000));

	printf("Progress: %d%%\n", (int) (fraction*100));
}

static void PauseAndResumeCallbackTest(void)
{
	Led_OnForDefinedTime(LED_GREEN, 500); //0.5s
}

static void PauseAndResumeCallbackTestAction(void)
{
	if (paused)
		Timer_Resume(pauseCallbackId);
	else
		Timer_Pause(pauseCallbackId);
	paused = !paused;
}

static void ResetTimerTest(void)
{
	Timer_Reset(onForDefinedTimeTestID);
}
static void OnlyOnceCallbackTest2(void)
{
	Led_OnForDefinedTime(LED_RED, 5000); //5s
}









